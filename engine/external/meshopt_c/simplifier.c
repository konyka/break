// This file is part of meshoptimizer library; see meshopt.h / LICENSE.md for version/license details
// Pure C11 port of meshoptimizer v1.3 src/simplifier.cpp (edge-collapse simplifier only); see README.md
#include "meshopt.h"

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// This work is based on:
// Michael Garland and Paul S. Heckbert. Surface simplification using quadric error metrics. 1997
// Michael Garland. Quadric-based polygonal surface simplification. 1999
// Peter Lindstrom. Out-of-Core Simplification of Large Polygonal Models. 2000
// Matthias Teschner, Bruno Heidelberger, Matthias Mueller, Danat Pomeranets, Markus Gross. Optimized Spatial Hashing for Collision Detection of Deformable Objects. 2003
// Peter Van Sandt, Yannis Chronis, Jignesh M. Patel. Efficiently Searching In-Memory Sorted Arrays: Revenge of the Interpolation Search? 2019
// Hugues Hoppe. New Quadric Metric for Simplifying Meshes with Appearance Attributes. 1999
// Hugues Hoppe, Steve Marschner. Efficient Minimization of New Quadric Metric for Simplifying Meshes with Appearance Attributes. 2000

// replacement for meshopt_Allocator: fixed-capacity block list, freed in reverse order
#define MESHOPT_ARENA_MAX_BLOCKS 24

typedef struct
{
	void* blocks[MESHOPT_ARENA_MAX_BLOCKS];
	size_t count;
} MeshoptArena;

static void* meshopt_arena_alloc(MeshoptArena* a, size_t bytes)
{
	assert(a->count < MESHOPT_ARENA_MAX_BLOCKS);
	if (a->count >= MESHOPT_ARENA_MAX_BLOCKS)
		return NULL;

	void* result = malloc(bytes ? bytes : 1);
	if (!result)
		return NULL;

	a->blocks[a->count++] = result;
	return result;
}

static void* meshopt_arena_alloc_array(MeshoptArena* a, size_t count, size_t size)
{
	if (size != 0 && count > SIZE_MAX / size)
		return NULL;

	return meshopt_arena_alloc(a, count * size);
}

static void meshopt_arena_pop(MeshoptArena* a, void* ptr)
{
	assert(a->count > 0 && a->blocks[a->count - 1] == ptr);
	(void)ptr;
	free(a->blocks[a->count - 1]);
	a->count--;
}

static void meshopt_arena_free_all(MeshoptArena* a)
{
	for (size_t i = a->count; i > 0; --i)
		free(a->blocks[i - 1]);

	a->count = 0;
}

#define MESHOPT_ALLOC(arena, T, n) ((T*)meshopt_arena_alloc_array((arena), (n), sizeof(T)))

typedef struct
{
	unsigned int next;
	unsigned int prev;
} EdgeAdjacencyEdge;

typedef struct
{
	unsigned int* offsets;
	EdgeAdjacencyEdge* data;
} EdgeAdjacency;

static bool prepareEdgeAdjacency(EdgeAdjacency* adjacency, size_t index_count, size_t vertex_count, MeshoptArena* allocator)
{
	adjacency->offsets = MESHOPT_ALLOC(allocator, unsigned int, vertex_count + 1);
	adjacency->data = MESHOPT_ALLOC(allocator, EdgeAdjacencyEdge, index_count);

	return adjacency->offsets && adjacency->data;
}

static void updateEdgeAdjacency(EdgeAdjacency* adjacency, const unsigned int* indices, size_t index_count, size_t vertex_count, const unsigned int* remap)
{
	size_t face_count = index_count / 3;
	unsigned int* offsets = adjacency->offsets + 1;
	EdgeAdjacencyEdge* data = adjacency->data;

	// fill edge counts
	memset(offsets, 0, vertex_count * sizeof(unsigned int));

	for (size_t i = 0; i < index_count; ++i)
	{
		unsigned int v = remap ? remap[indices[i]] : indices[i];
		assert(v < vertex_count);

		offsets[v]++;
	}

	// fill offset table
	unsigned int offset = 0;

	for (size_t i = 0; i < vertex_count; ++i)
	{
		unsigned int count = offsets[i];
		offsets[i] = offset;
		offset += count;
	}

	assert(offset == index_count);

	// fill edge data
	for (size_t i = 0; i < face_count; ++i)
	{
		unsigned int a = indices[i * 3 + 0], b = indices[i * 3 + 1], c = indices[i * 3 + 2];

		if (remap)
		{
			a = remap[a];
			b = remap[b];
			c = remap[c];
		}

		data[offsets[a]].next = b;
		data[offsets[a]].prev = c;
		offsets[a]++;

		data[offsets[b]].next = c;
		data[offsets[b]].prev = a;
		offsets[b]++;

		data[offsets[c]].next = a;
		data[offsets[c]].prev = b;
		offsets[c]++;
	}

	// finalize offsets
	adjacency->offsets[0] = 0;
	assert(adjacency->offsets[vertex_count] == index_count);
}

typedef struct
{
	const float* vertex_positions;
	size_t vertex_stride_float;
	const unsigned int* sparse_remap;
} PositionHasher;

static size_t positionHasherHash(const PositionHasher* hasher, unsigned int index)
{
	unsigned int ri = hasher->sparse_remap ? hasher->sparse_remap[index] : index;
	const unsigned int* key = (const unsigned int*)(hasher->vertex_positions + ri * hasher->vertex_stride_float);

	unsigned int x = key[0], y = key[1], z = key[2];

	// replace negative zero with zero
	x = (x == 0x80000000) ? 0 : x;
	y = (y == 0x80000000) ? 0 : y;
	z = (z == 0x80000000) ? 0 : z;

	// scramble bits to make sure that integer coordinates have entropy in lower bits
	x ^= x >> 17;
	y ^= y >> 17;
	z ^= z >> 17;

	// Optimized Spatial Hashing for Collision Detection of Deformable Objects
	return (x * 73856093) ^ (y * 19349663) ^ (z * 83492791);
}

static bool positionHasherEqual(const PositionHasher* hasher, unsigned int lhs, unsigned int rhs)
{
	unsigned int li = hasher->sparse_remap ? hasher->sparse_remap[lhs] : lhs;
	unsigned int ri = hasher->sparse_remap ? hasher->sparse_remap[rhs] : rhs;

	const float* lv = hasher->vertex_positions + li * hasher->vertex_stride_float;
	const float* rv = hasher->vertex_positions + ri * hasher->vertex_stride_float;

	return lv[0] == rv[0] && lv[1] == rv[1] && lv[2] == rv[2];
}

typedef struct
{
	unsigned int* remap;
} RemapHasher;

static size_t remapHasherHash(const RemapHasher* hasher, unsigned int id)
{
	(void)hasher;
	return id * 0x5bd1e995;
}

static bool remapHasherEqual(const RemapHasher* hasher, unsigned int lhs, unsigned int rhs)
{
	return hasher->remap[lhs] == rhs;
}

static size_t hashBuckets2(size_t count)
{
	size_t buckets = 1;
	while (buckets < count + count / 4)
		buckets *= 2;

	return buckets;
}

// hashLookup2<unsigned int, PositionHasher>
static unsigned int* hashLookup2Position(unsigned int* table, size_t buckets, const PositionHasher* hash, unsigned int key, unsigned int empty)
{
	assert(buckets > 0);
	assert((buckets & (buckets - 1)) == 0);

	size_t hashmod = buckets - 1;
	size_t bucket = positionHasherHash(hash, key) & hashmod;

	for (size_t probe = 0; probe <= hashmod; ++probe)
	{
		unsigned int* item = &table[bucket];

		if (*item == empty)
			return item;

		if (positionHasherEqual(hash, *item, key))
			return item;

		// hash collision, quadratic probing
		bucket = (bucket + probe + 1) & hashmod;
	}

	assert(0 && "Hash table is full"); // unreachable
	return NULL;
}

// hashLookup2<unsigned int, RemapHasher>
static unsigned int* hashLookup2Remap(unsigned int* table, size_t buckets, const RemapHasher* hash, unsigned int key, unsigned int empty)
{
	assert(buckets > 0);
	assert((buckets & (buckets - 1)) == 0);

	size_t hashmod = buckets - 1;
	size_t bucket = remapHasherHash(hash, key) & hashmod;

	for (size_t probe = 0; probe <= hashmod; ++probe)
	{
		unsigned int* item = &table[bucket];

		if (*item == empty)
			return item;

		if (remapHasherEqual(hash, *item, key))
			return item;

		// hash collision, quadratic probing
		bucket = (bucket + probe + 1) & hashmod;
	}

	assert(0 && "Hash table is full"); // unreachable
	return NULL;
}

static bool buildPositionRemap(unsigned int* remap, unsigned int* wedge, const float* vertex_positions_data, size_t vertex_count, size_t vertex_positions_stride, const unsigned int* sparse_remap, MeshoptArena* allocator)
{
	PositionHasher hasher = {vertex_positions_data, vertex_positions_stride / sizeof(float), sparse_remap};

	size_t table_size = hashBuckets2(vertex_count);
	unsigned int* table = MESHOPT_ALLOC(allocator, unsigned int, table_size);
	if (!table)
		return false;
	memset(table, -1, table_size * sizeof(unsigned int));

	// build forward remap: for each vertex, which other (canonical) vertex does it map to?
	// we use position equivalence for this, and remap vertices to other existing vertices
	for (size_t i = 0; i < vertex_count; ++i)
	{
		unsigned int index = (unsigned int)i;
		unsigned int* entry = hashLookup2Position(table, table_size, &hasher, index, ~0u);

		if (*entry == ~0u)
			*entry = index;

		remap[index] = *entry;
	}

	meshopt_arena_pop(allocator, table);

	if (!wedge)
		return true;

	// build wedge table: for each vertex, which other vertex is the next wedge that also maps to the same vertex?
	// entries in table form a (cyclic) wedge loop per vertex; for manifold vertices, wedge[i] == remap[i] == i
	for (size_t i = 0; i < vertex_count; ++i)
		wedge[i] = (unsigned int)i;

	for (size_t i = 0; i < vertex_count; ++i)
		if (remap[i] != i)
		{
			unsigned int r = remap[i];

			wedge[i] = wedge[r];
			wedge[r] = (unsigned int)i;
		}

	return true;
}

static unsigned int* buildSparseRemap(unsigned int* indices, size_t index_count, size_t vertex_count, size_t* out_vertex_count, MeshoptArena* allocator)
{
	// use a bit set to compute the precise number of unique vertices
	unsigned char* filter = MESHOPT_ALLOC(allocator, unsigned char, (vertex_count + 7) / 8);
	if (!filter)
		return NULL;

	for (size_t i = 0; i < index_count; ++i)
	{
		unsigned int index = indices[i];
		assert(index < vertex_count);
		filter[index / 8] = 0;
	}

	size_t unique = 0;
	for (size_t i = 0; i < index_count; ++i)
	{
		unsigned int index = indices[i];
		unique += (filter[index / 8] & (1 << (index % 8))) == 0;
		filter[index / 8] |= 1 << (index % 8);
	}

	unsigned int* remap = MESHOPT_ALLOC(allocator, unsigned int, unique);
	if (!remap)
		return NULL;
	size_t offset = 0;

	// temporary map dense => sparse; we allocate it last so that we can deallocate it
	size_t revremap_size = hashBuckets2(unique);
	unsigned int* revremap = MESHOPT_ALLOC(allocator, unsigned int, revremap_size);
	if (!revremap)
		return NULL;
	memset(revremap, -1, revremap_size * sizeof(unsigned int));

	// fill remap, using revremap as a helper, and rewrite indices in the same pass
	RemapHasher hasher = {remap};

	for (size_t i = 0; i < index_count; ++i)
	{
		unsigned int index = indices[i];
		unsigned int* entry = hashLookup2Remap(revremap, revremap_size, &hasher, index, ~0u);

		if (*entry == ~0u)
		{
			remap[offset] = index;
			*entry = (unsigned int)offset;
			offset++;
		}

		indices[i] = *entry;
	}

	meshopt_arena_pop(allocator, revremap);

	assert(offset == unique);
	*out_vertex_count = unique;

	return remap;
}

typedef enum
{
	Kind_Manifold, // not on an attribute seam, not on any boundary
	Kind_Border,   // not on an attribute seam, has exactly two open edges
	Kind_Seam,     // on an attribute seam with exactly two attribute seam edges
	Kind_Complex,  // none of the above; these vertices can move as long as all wedges move to the target vertex
	Kind_Fringe,   // complex vertex on a geometric border; can only move to another fringe vertex
	Kind_Locked,   // none of the above; these vertices can't move

	Kind_Count
} VertexKind;

// manifold vertices can collapse onto anything
// border/seam vertices can collapse onto border/seam respectively, or locked
// complex vertices can collapse onto complex/locked
// fringe vertices can only collapse onto fringe vertices; border, manifold and complex vertices can collapse onto them
// a rule of thumb is that collapsing kind A into kind B preserves the kind B in the target vertex
// for example, while we could collapse Complex into Manifold, this would mean the target vertex isn't Manifold anymore
static const unsigned char kCanCollapse[Kind_Count][Kind_Count] = {
    {1, 1, 1, 1, 1, 1},
    {0, 1, 0, 0, 1, 1},
    {0, 0, 1, 0, 0, 1},
    {0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0},
};

// if a vertex is manifold or seam, adjoining edges are guaranteed to have an opposite edge
// note that for seam edges, the opposite edge isn't present in the attribute-based topology
// but is present if you consider a position-only mesh variant
// while many complex collapses have the opposite edge, since complex vertices collapse to the
// same wedge, keeping opposite edges separate improves the quality by considering both targets
static const unsigned char kHasOpposite[Kind_Count][Kind_Count] = {
    {1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0},
    {1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 0, 0},
};

static bool hasEdge(const EdgeAdjacency* adjacency, unsigned int a, unsigned int b)
{
	unsigned int count = adjacency->offsets[a + 1] - adjacency->offsets[a];
	const EdgeAdjacencyEdge* edges = adjacency->data + adjacency->offsets[a];

	for (size_t i = 0; i < count; ++i)
		if (edges[i].next == b)
			return true;

	return false;
}

static bool hasEdgeWedge(const EdgeAdjacency* adjacency, unsigned int a, unsigned int b, const unsigned int* remap, const unsigned int* wedge)
{
	unsigned int v = a;

	do
	{
		unsigned int count = adjacency->offsets[v + 1] - adjacency->offsets[v];
		const EdgeAdjacencyEdge* edges = adjacency->data + adjacency->offsets[v];

		for (size_t i = 0; i < count; ++i)
			if (remap[edges[i].next] == remap[b])
				return true;

		v = wedge[v];
	} while (v != a);

	return false;
}

static void classifyVertices(unsigned char* result, unsigned int* loop, unsigned int* loopback, size_t vertex_count, const EdgeAdjacency* adjacency, const unsigned int* remap, const unsigned int* wedge, const unsigned char* vertex_lock, const unsigned int* sparse_remap, unsigned int options)
{
	memset(loop, -1, vertex_count * sizeof(unsigned int));
	memset(loopback, -1, vertex_count * sizeof(unsigned int));

	// incoming & outgoing open edges: ~0u if no open edges, i if there are more than 1
	// note that this is the same data as required in loop[] arrays; loop[] data is only used for border/seam by default
	// in permissive mode we also use it to guide complex-complex collapses, so we fill it for all vertices
	unsigned int* openinc = loopback;
	unsigned int* openout = loop;

	for (size_t i = 0; i < vertex_count; ++i)
	{
		unsigned int vertex = (unsigned int)i;

		unsigned int count = adjacency->offsets[vertex + 1] - adjacency->offsets[vertex];
		const EdgeAdjacencyEdge* edges = adjacency->data + adjacency->offsets[vertex];

		for (size_t j = 0; j < count; ++j)
		{
			unsigned int target = edges[j].next;

			if (target == vertex)
			{
				// degenerate triangles have two distinct edges instead of three, and the self edge
				// is bi-directional by definition; this can break border/seam classification by "closing"
				// the open edge from another triangle and falsely marking the vertex as manifold
				// instead we mark the vertex as having >1 open edges which turns it into locked/complex
				openinc[vertex] = openout[vertex] = vertex;
			}
			else if (!hasEdge(adjacency, target, vertex))
			{
				openinc[target] = (openinc[target] == ~0u) ? vertex : target;
				openout[vertex] = (openout[vertex] == ~0u) ? target : vertex;
			}
		}
	}

	for (size_t i = 0; i < vertex_count; ++i)
	{
		if (remap[i] == i)
		{
			if (wedge[i] == i)
			{
				// no attribute seam, need to check if it's manifold
				unsigned int openi = openinc[i], openo = openout[i];

				// note: we classify any vertices with no open edges as manifold
				// this is technically incorrect - if 4 triangles share an edge, we'll classify vertices as manifold
				// it's unclear if this is a problem in practice
				if (openi == ~0u && openo == ~0u)
				{
					result[i] = Kind_Manifold;
				}
				else if (openi != ~0u && openo != ~0u && remap[openi] == remap[openo] && openi != i)
				{
					// classify half-seams as seams (the branch below would mis-classify them as borders)
					// half-seam is a single vertex that connects to both vertices of a potential seam
					// treating these as seams allows collapsing the "full" seam vertex onto them
					result[i] = Kind_Seam;
				}
				else if (openi != i && openo != i)
				{
					result[i] = Kind_Border;
				}
				else
				{
					result[i] = Kind_Locked;
				}
			}
			else if (wedge[wedge[i]] == i)
			{
				// attribute seam; need to distinguish between Seam and Locked
				unsigned int w = wedge[i];
				unsigned int openiv = openinc[i], openov = openout[i];
				unsigned int openiw = openinc[w], openow = openout[w];

				// seam should have one open half-edge for each vertex, and the edges need to "connect" - point to the same vertex post-remap
				if (openiv != ~0u && openiv != i && openov != ~0u && openov != i &&
				    openiw != ~0u && openiw != w && openow != ~0u && openow != w &&
				    remap[openiv] == remap[openow] && remap[openov] == remap[openiw] && remap[openiv] != remap[openov])
				{
					result[i] = Kind_Seam;
				}
				else
				{
					// mismatched seam endpoints or disconnected seam; we don't have classification available
					result[i] = Kind_Locked;
				}
			}
			else
			{
				// more than one vertex maps to this one; we don't have classification available
				result[i] = Kind_Locked;
			}
		}
		else
		{
			assert(remap[i] < i);

			result[i] = result[remap[i]];
		}
	}

	if (options & meshopt_SimplifyPermissive)
		for (size_t i = 0; i < vertex_count; ++i)
			if (result[i] == Kind_Seam || result[i] == Kind_Locked)
			{
				if (remap[i] != i)
				{
					// only process primary vertices; wedges will be updated to match the primary vertex
					result[i] = result[remap[i]];
					continue;
				}

				unsigned int v = (unsigned int)i;

				// vertex_lock may protect any wedge, not just the primary vertex, so we switch to complex only if no wedges are protected
				bool protect = false;
				do
				{
					unsigned int rv = sparse_remap ? sparse_remap[v] : v;
					protect |= vertex_lock && (vertex_lock[rv] & meshopt_SimplifyVertex_Protect) != 0;
					v = wedge[v];
				} while (v != i);

				// check if any adjoining edge doesn't have an opposite edge (indicating vertex is on the border)
				bool border = false;
				do
				{
					const EdgeAdjacencyEdge* edges = &adjacency->data[adjacency->offsets[v]];
					size_t count = adjacency->offsets[v + 1] - adjacency->offsets[v];

					for (size_t j = 0; j < count; ++j)
						border |= !hasEdgeWedge(adjacency, edges[j].next, v, remap, wedge);
					v = wedge[v];
				} while (v != i);

				// border vertices with attribute discontinuities can only collapse along the border, so they need a separate tagging
				result[i] = protect ? result[i] : (unsigned char)(border ? Kind_Fringe : Kind_Complex);
			}

	if (vertex_lock)
	{
		// vertex_lock may lock any wedge, not just the primary vertex, so we need to lock the primary vertex and relock any wedges
		for (size_t i = 0; i < vertex_count; ++i)
		{
			unsigned int ri = sparse_remap ? sparse_remap[i] : (unsigned int)i;

			if (vertex_lock[ri] & meshopt_SimplifyVertex_Lock)
				result[remap[i]] = Kind_Locked;
		}

		for (size_t i = 0; i < vertex_count; ++i)
			if (result[remap[i]] == Kind_Locked)
				result[i] = Kind_Locked;
	}

	if (options & meshopt_SimplifyLockBorder)
		for (size_t i = 0; i < vertex_count; ++i)
			if (result[i] == Kind_Border || result[i] == Kind_Fringe)
				result[i] = Kind_Locked;
}

typedef struct
{
	float x, y, z;
} Vector3;

static float rescalePositions(Vector3* result, const float* vertex_positions_data, size_t vertex_count, size_t vertex_positions_stride, const unsigned int* sparse_remap, float* out_offset)
{
	size_t vertex_stride_float = vertex_positions_stride / sizeof(float);

	float minv[3] = {FLT_MAX, FLT_MAX, FLT_MAX};
	float maxv[3] = {-FLT_MAX, -FLT_MAX, -FLT_MAX};

	for (size_t i = 0; i < vertex_count; ++i)
	{
		unsigned int ri = sparse_remap ? sparse_remap[i] : (unsigned int)i;
		const float* v = vertex_positions_data + ri * vertex_stride_float;

		if (result)
		{
			result[i].x = v[0];
			result[i].y = v[1];
			result[i].z = v[2];
		}

		for (int j = 0; j < 3; ++j)
		{
			float vj = v[j];

			minv[j] = minv[j] > vj ? vj : minv[j];
			maxv[j] = maxv[j] < vj ? vj : maxv[j];
		}
	}

	float extent = 0.f;

	extent = (maxv[0] - minv[0]) < extent ? extent : (maxv[0] - minv[0]);
	extent = (maxv[1] - minv[1]) < extent ? extent : (maxv[1] - minv[1]);
	extent = (maxv[2] - minv[2]) < extent ? extent : (maxv[2] - minv[2]);

	if (result)
	{
		float scale = extent == 0 ? 0.f : 1.f / extent;

		for (size_t i = 0; i < vertex_count; ++i)
		{
			result[i].x = (result[i].x - minv[0]) * scale;
			result[i].y = (result[i].y - minv[1]) * scale;
			result[i].z = (result[i].z - minv[2]) * scale;
		}
	}

	if (out_offset)
	{
		out_offset[0] = minv[0];
		out_offset[1] = minv[1];
		out_offset[2] = minv[2];
	}

	return extent;
}

static void rescaleAttributes(float* result, const float* vertex_attributes_data, size_t vertex_count, size_t vertex_attributes_stride, const float* attribute_weights, size_t attribute_count, const unsigned int* attribute_remap, const unsigned int* sparse_remap)
{
	size_t vertex_attributes_stride_float = vertex_attributes_stride / sizeof(float);

	for (size_t i = 0; i < vertex_count; ++i)
	{
		unsigned int ri = sparse_remap ? sparse_remap[i] : (unsigned int)i;

		for (size_t k = 0; k < attribute_count; ++k)
		{
			unsigned int rk = attribute_remap[k];
			float a = vertex_attributes_data[ri * vertex_attributes_stride_float + rk];

			result[i * attribute_count + k] = a * attribute_weights[rk];
		}
	}
}

#define kMaxAttributes 32

typedef struct
{
	// a00*x^2 + a11*y^2 + a22*z^2 + 2*a10*xy + 2*a20*xz + 2*a21*yz + 2*b0*x + 2*b1*y + 2*b2*z + c
	float a00, a11, a22;
	float a10, a20, a21;
	float b0, b1, b2, c;
	float w;
} Quadric;

typedef struct
{
	// gx*x + gy*y + gz*z + gw
	float gx, gy, gz, gw;
} QuadricGrad;

typedef struct
{
	unsigned int v0;
	unsigned int v1;

	union
	{
		unsigned int bidi;
		float error;
		unsigned int errorui;
	} u;
} Collapse;

static float normalize(Vector3* v)
{
	float length = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);

	if (length > 0)
	{
		v->x /= length;
		v->y /= length;
		v->z /= length;
	}

	return length;
}

static void quadricAdd(Quadric* Q, const Quadric* R)
{
	Q->a00 += R->a00;
	Q->a11 += R->a11;
	Q->a22 += R->a22;
	Q->a10 += R->a10;
	Q->a20 += R->a20;
	Q->a21 += R->a21;
	Q->b0 += R->b0;
	Q->b1 += R->b1;
	Q->b2 += R->b2;
	Q->c += R->c;
	Q->w += R->w;
}

static void quadricGradAddN(QuadricGrad* G, const QuadricGrad* R, size_t attribute_count)
{
	for (size_t k = 0; k < attribute_count; ++k)
	{
		G[k].gx += R[k].gx;
		G[k].gy += R[k].gy;
		G[k].gz += R[k].gz;
		G[k].gw += R[k].gw;
	}
}

static float quadricEval(const Quadric* Q, const Vector3* v)
{
	float rx = (Q->b0 + Q->a10 * v->y) * 2.f;
	float ry = (Q->b1 + Q->a21 * v->z) * 2.f;
	float rz = (Q->b2 + Q->a20 * v->x) * 2.f;

	rx += Q->a00 * v->x;
	ry += Q->a11 * v->y;
	rz += Q->a22 * v->z;

	return Q->c + rx * v->x + ry * v->y + rz * v->z;
}

static float quadricError(const Quadric* Q, const Vector3* v)
{
	float r = quadricEval(Q, v);
	float s = Q->w == 0.f ? 0.f : 1.f / Q->w;

	return fabsf(r) * s;
}

static float quadricErrorAttr(const Quadric* Q, const QuadricGrad* G, size_t attribute_count, const Vector3* v, const float* va, bool clamped)
{
	float r = quadricEval(Q, v);

	// see quadricFromAttributes for general derivation; here we need to add the parts of (eval(pos) - attr)^2 that depend on attr
	for (size_t k = 0; k < attribute_count; ++k)
	{
		float a = va[k];
		float g = v->x * G[k].gx + v->y * G[k].gy + v->z * G[k].gz + G[k].gw;

		r += a * (a * Q->w - 2 * g);
	}

	// note: unlike position error, we do not normalize by Q.w to retain edge scaling as described in quadricFromAttributes
	// we do support clamping, with the error limited to the cumulative weight (= area), which makes perceptual error map to position error more closely
	float e = fabsf(r);
	return clamped ? (e < Q->w ? e : Q->w) : e;
}

static void quadricFromPlane(Quadric* Q, float a, float b, float c, float d, float w)
{
	float aw = a * w;
	float bw = b * w;
	float cw = c * w;
	float dw = d * w;

	Q->a00 = a * aw;
	Q->a11 = b * bw;
	Q->a22 = c * cw;
	Q->a10 = a * bw;
	Q->a20 = a * cw;
	Q->a21 = b * cw;
	Q->b0 = a * dw;
	Q->b1 = b * dw;
	Q->b2 = c * dw;
	Q->c = d * dw;
	Q->w = w;
}

static void quadricFromPoint(Quadric* Q, float x, float y, float z, float w)
{
	Q->a00 = Q->a11 = Q->a22 = w;
	Q->a10 = Q->a20 = Q->a21 = 0;
	Q->b0 = -x * w;
	Q->b1 = -y * w;
	Q->b2 = -z * w;
	Q->c = (x * x + y * y + z * z) * w;
	Q->w = w;
}

static void quadricFromTriangle(Quadric* Q, const Vector3* p0, const Vector3* p1, const Vector3* p2, float weight)
{
	Vector3 p10 = {p1->x - p0->x, p1->y - p0->y, p1->z - p0->z};
	Vector3 p20 = {p2->x - p0->x, p2->y - p0->y, p2->z - p0->z};

	// normal = cross(p1 - p0, p2 - p0)
	Vector3 normal = {p10.y * p20.z - p10.z * p20.y, p10.z * p20.x - p10.x * p20.z, p10.x * p20.y - p10.y * p20.x};
	float area = normalize(&normal);

	float distance = normal.x * p0->x + normal.y * p0->y + normal.z * p0->z;

	// we use sqrtf(area) so that the error is scaled linearly; this tends to improve silhouettes
	quadricFromPlane(Q, normal.x, normal.y, normal.z, -distance, sqrtf(area) * weight);
}

static void quadricFromTriangleEdge(Quadric* Q, const Vector3* p0, const Vector3* p1, const Vector3* p2, float weight)
{
	Vector3 p10 = {p1->x - p0->x, p1->y - p0->y, p1->z - p0->z};

	// edge length; keep squared length around for projection correction
	float lengthsq = p10.x * p10.x + p10.y * p10.y + p10.z * p10.z;
	float length = sqrtf(lengthsq);

	// p20p = length of projection of p2-p0 onto p1-p0; note that p10 is unnormalized so we need to correct it later
	Vector3 p20 = {p2->x - p0->x, p2->y - p0->y, p2->z - p0->z};
	float p20p = p20.x * p10.x + p20.y * p10.y + p20.z * p10.z;

	// perp = perpendicular vector from p2 to line segment p1-p0
	// note: since p10 is unnormalized we need to correct the projection; we scale p20 instead to take advantage of normalize below
	Vector3 perp = {p20.x * lengthsq - p10.x * p20p, p20.y * lengthsq - p10.y * p20p, p20.z * lengthsq - p10.z * p20p};
	normalize(&perp);

	float distance = perp.x * p0->x + perp.y * p0->y + perp.z * p0->z;

	// note: the weight is scaled linearly with edge length; this has to match the triangle weight
	quadricFromPlane(Q, perp.x, perp.y, perp.z, -distance, length * weight);
}

static void quadricFromAttributes(Quadric* Q, QuadricGrad* G, const Vector3* p0, const Vector3* p1, const Vector3* p2, const float* va0, const float* va1, const float* va2, size_t attribute_count)
{
	// for each attribute we want to encode the following function into the quadric:
	// (eval(pos) - attr)^2
	// where eval(pos) interpolates attribute across the triangle like so:
	// eval(pos) = pos.x * gx + pos.y * gy + pos.z * gz + gw
	// where gx/gy/gz/gw are gradients
	Vector3 p10 = {p1->x - p0->x, p1->y - p0->y, p1->z - p0->z};
	Vector3 p20 = {p2->x - p0->x, p2->y - p0->y, p2->z - p0->z};

	// normal = cross(p1 - p0, p2 - p0)
	Vector3 normal = {p10.y * p20.z - p10.z * p20.y, p10.z * p20.x - p10.x * p20.z, p10.x * p20.y - p10.y * p20.x};
	float area = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z) * 0.5f;

	// quadric is weighted with the square of edge length (= area)
	// this equalizes the units with the positional error (which, after normalization, is a square of distance)
	// as a result, a change in weighted attribute of 1 along distance d is approximately equivalent to a change in position of d
	float w = area;

	// we compute gradients using barycentric coordinates; barycentric coordinates can be computed as follows:
	// v = (d11 * d20 - d01 * d21) / denom
	// w = (d00 * d21 - d01 * d20) / denom
	// u = 1 - v - w
	// here v0, v1 are triangle edge vectors, v2 is a vector from point to triangle corner, and dij = dot(vi, vj)
	// note: v2 and d20/d21 can not be evaluated here as v2 is effectively an unknown variable; we need these only as variables for derivation of gradients
	const Vector3* v0 = &p10;
	const Vector3* v1 = &p20;
	float d00 = v0->x * v0->x + v0->y * v0->y + v0->z * v0->z;
	float d01 = v0->x * v1->x + v0->y * v1->y + v0->z * v1->z;
	float d11 = v1->x * v1->x + v1->y * v1->y + v1->z * v1->z;
	float denom = d00 * d11 - d01 * d01;
	float denomr = denom == 0 ? 0.f : 1.f / denom;

	// precompute gradient factors
	// these are derived by directly computing derivative of eval(pos) = a0 * u + a1 * v + a2 * w and factoring out expressions that are shared between attributes
	float gx1 = (d11 * v0->x - d01 * v1->x) * denomr;
	float gx2 = (d00 * v1->x - d01 * v0->x) * denomr;
	float gy1 = (d11 * v0->y - d01 * v1->y) * denomr;
	float gy2 = (d00 * v1->y - d01 * v0->y) * denomr;
	float gz1 = (d11 * v0->z - d01 * v1->z) * denomr;
	float gz2 = (d00 * v1->z - d01 * v0->z) * denomr;

	memset(Q, 0, sizeof(Quadric));

	Q->w = w;

	for (size_t k = 0; k < attribute_count; ++k)
	{
		float a0 = va0[k], a1 = va1[k], a2 = va2[k];

		// compute gradient of eval(pos) for x/y/z/w
		// the formulas below are obtained by directly computing derivative of eval(pos) = a0 * u + a1 * v + a2 * w
		float gx = gx1 * (a1 - a0) + gx2 * (a2 - a0);
		float gy = gy1 * (a1 - a0) + gy2 * (a2 - a0);
		float gz = gz1 * (a1 - a0) + gz2 * (a2 - a0);
		float gw = a0 - p0->x * gx - p0->y * gy - p0->z * gz;

		// quadric encodes (eval(pos)-attr)^2; this means that the resulting expansion needs to compute, for example, pos.x * pos.y * K
		// since quadrics already encode factors for pos.x * pos.y, we can accumulate almost everything in basic quadric fields
		// note: for simplicity we scale all factors by weight here instead of outside the loop
		Q->a00 += w * (gx * gx);
		Q->a11 += w * (gy * gy);
		Q->a22 += w * (gz * gz);

		Q->a10 += w * (gy * gx);
		Q->a20 += w * (gz * gx);
		Q->a21 += w * (gz * gy);

		Q->b0 += w * (gx * gw);
		Q->b1 += w * (gy * gw);
		Q->b2 += w * (gz * gw);

		Q->c += w * (gw * gw);

		// the only remaining sum components are ones that depend on attr; these will be added during error evaluation, see quadricError
		G[k].gx = w * gx;
		G[k].gy = w * gy;
		G[k].gz = w * gz;
		G[k].gw = w * gw;
	}
}

static void fillFaceQuadrics(Quadric* vertex_quadrics, const unsigned int* indices, size_t index_count, const Vector3* vertex_positions, const unsigned int* remap)
{
	for (size_t i = 0; i < index_count; i += 3)
	{
		unsigned int i0 = indices[i + 0];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];

		Quadric Q;
		quadricFromTriangle(&Q, &vertex_positions[i0], &vertex_positions[i1], &vertex_positions[i2], 1.f);

		quadricAdd(&vertex_quadrics[remap[i0]], &Q);
		quadricAdd(&vertex_quadrics[remap[i1]], &Q);
		quadricAdd(&vertex_quadrics[remap[i2]], &Q);
	}
}

static void fillVertexQuadrics(Quadric* vertex_quadrics, const Vector3* vertex_positions, size_t vertex_count, const unsigned int* remap, const unsigned char* vertex_lock, const unsigned int* sparse_remap, unsigned int options)
{
	// by default, we use a very small weight to improve triangulation and numerical stability without affecting the shape or error
	float factor = (options & meshopt_SimplifyRegularizeLight) ? 1e-2f : ((options & meshopt_SimplifyRegularize) ? 1e-1f : 1e-7f);

	for (size_t i = 0; i < vertex_count; ++i)
	{
		if (remap[i] != i)
			continue;

		// increase regularization weight for vertices marked as priority; for now we only examine the primary vertex
		unsigned int ri = sparse_remap ? sparse_remap[i] : (unsigned int)i;
		bool priority = vertex_lock && (vertex_lock[ri] & meshopt_SimplifyVertex_Priority) != 0;

		const Vector3* p = &vertex_positions[i];
		float w = vertex_quadrics[i].w * (priority ? 1.0f : factor);

		Quadric Q;
		quadricFromPoint(&Q, p->x, p->y, p->z, w);

		quadricAdd(&vertex_quadrics[i], &Q);
	}
}

static void fillEdgeQuadrics(Quadric* vertex_quadrics, const unsigned int* indices, size_t index_count, const Vector3* vertex_positions, const unsigned int* remap, const unsigned char* vertex_kind, const unsigned int* loop, const unsigned int* loopback)
{
	for (size_t i = 0; i < index_count; i += 3)
	{
		static const int next[4] = {1, 2, 0, 1};

		for (int e = 0; e < 3; ++e)
		{
			unsigned int i0 = indices[i + e];
			unsigned int i1 = indices[i + next[e]];

			unsigned char k0 = vertex_kind[i0];
			unsigned char k1 = vertex_kind[i1];

			// early out: manifold vertices never lie on a border
			if (k0 == Kind_Manifold || k1 == Kind_Manifold)
				continue;

			// one of the vertices must be border/seam/fringe; additional checks help validate the border
			if (k0 != Kind_Border && k0 != Kind_Seam && k0 != Kind_Fringe && k1 != Kind_Border && k1 != Kind_Seam && k1 != Kind_Fringe)
				continue;

			// if i0/i1 are border/seam we check if they are on the same edge loop
			// note that we need to add the error even for edges that connect e.g. border & locked
			// if we don't do that, the adjacent border->border edge won't have correct errors for corners
			if ((k0 == Kind_Border || k0 == Kind_Seam) && loop[i0] != i1)
				continue;

			if ((k1 == Kind_Border || k1 == Kind_Seam) && loopback[i1] != i0)
				continue;

			// fringe vertices don't have proper edge loops, so we need to add edge quadrics to fringe-fringe or fringe-locked edges
			// note that border-fringe edges are still processed, guarded by the loop check above
			if ((k0 == Kind_Fringe || k1 == Kind_Fringe) && (k0 == Kind_Complex || k1 == Kind_Complex))
				continue;

			unsigned int i2 = indices[i + next[e + 1]];

			// we try hard to maintain border edge geometry; seam edges can move more freely
			// due to topological restrictions on collapses, seam quadrics slightly improve collapse structure but aren't critical
			const float kEdgeWeightSeam = 0.5f; // applied twice due to opposite edges
			const float kEdgeWeightBorder = 10.f;

			float edgeWeight = (k0 == Kind_Seam || k1 == Kind_Seam) ? kEdgeWeightSeam : kEdgeWeightBorder;

			Quadric Q;
			quadricFromTriangleEdge(&Q, &vertex_positions[i0], &vertex_positions[i1], &vertex_positions[i2], edgeWeight);

			Quadric QT;
			quadricFromTriangle(&QT, &vertex_positions[i0], &vertex_positions[i1], &vertex_positions[i2], edgeWeight);

			// mix edge quadric with triangle quadric to stabilize collapses in both directions; both quadrics inherit edge weight so that their error is added
			QT.w = 0;
			quadricAdd(&Q, &QT);

			quadricAdd(&vertex_quadrics[remap[i0]], &Q);
			quadricAdd(&vertex_quadrics[remap[i1]], &Q);
		}
	}
}

static unsigned int oppositeVertex(const EdgeAdjacency* adjacency, unsigned int a, unsigned int b, const unsigned int* remap, const unsigned int* wedge)
{
	unsigned int v = a;
	unsigned int r = ~0u;

	do
	{
		unsigned int count = adjacency->offsets[v + 1] - adjacency->offsets[v];
		const EdgeAdjacencyEdge* edges = adjacency->data + adjacency->offsets[v];

		for (size_t i = 0; i < count; ++i)
			if (remap[edges[i].next] == remap[b])
				r = (r == ~0u) ? edges[i].prev : a;

		v = wedge[v];
	} while (v != a);

	// we only return the opposite vertex if it's unique
	return r == a ? ~0u : r;
}

static void fillFoldQuadrics(Quadric* vertex_quadrics, const EdgeAdjacency* adjacency, const Vector3* vertex_positions, size_t vertex_count, const unsigned int* remap, const unsigned int* wedge)
{
	for (size_t i0 = 0; i0 < vertex_count; ++i0)
		for (unsigned int i = adjacency->offsets[i0]; i < adjacency->offsets[i0 + 1]; ++i)
		{
			unsigned int i1 = adjacency->data[i].next;
			unsigned int i2 = adjacency->data[i].prev;

			// since we only process paired edges each edge should occur twice; skip redundant edges
			if (remap[i1] > remap[i0])
				continue;

			unsigned int i3 = oppositeVertex(adjacency, i1, (unsigned int)i0, remap, wedge);

			if (i3 == ~0u)
				continue;

			Vector3 p10 = {vertex_positions[i1].x - vertex_positions[i0].x, vertex_positions[i1].y - vertex_positions[i0].y, vertex_positions[i1].z - vertex_positions[i0].z};
			Vector3 p20 = {vertex_positions[i2].x - vertex_positions[i0].x, vertex_positions[i2].y - vertex_positions[i0].y, vertex_positions[i2].z - vertex_positions[i0].z};
			Vector3 p30 = {vertex_positions[i3].x - vertex_positions[i0].x, vertex_positions[i3].y - vertex_positions[i0].y, vertex_positions[i3].z - vertex_positions[i0].z};

			Vector3 normal = {p10.y * p20.z - p10.z * p20.y, p10.z * p20.x - p10.x * p20.z, p10.x * p20.y - p10.y * p20.x};
			Vector3 opposite = {p30.y * p10.z - p30.z * p10.y, p30.z * p10.x - p30.x * p10.z, p30.x * p10.y - p30.y * p10.x};
			float nl = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
			float ol = sqrtf(opposite.x * opposite.x + opposite.y * opposite.y + opposite.z * opposite.z);

			// identify folds by checking dihedral angle against a somewhat arbitrary ~30 degree cutoff
			if (normal.x * opposite.x + normal.y * opposite.y + normal.z * opposite.z >= -0.85f * nl * ol)
				continue;

			// use both triangles for symmetry since we won't visit this edge again
			Quadric Q, QO;
			quadricFromTriangleEdge(&Q, &vertex_positions[i0], &vertex_positions[i1], &vertex_positions[i2], 1.f);
			quadricFromTriangleEdge(&QO, &vertex_positions[i0], &vertex_positions[i1], &vertex_positions[i3], 1.f);
			quadricAdd(&Q, &QO);

			quadricAdd(&vertex_quadrics[remap[i0]], &Q);
			quadricAdd(&vertex_quadrics[remap[i1]], &Q);
		}
}

static void fillAttributeQuadrics(Quadric* attribute_quadrics, QuadricGrad* attribute_gradients, const unsigned int* indices, size_t index_count, const Vector3* vertex_positions, const float* vertex_attributes, size_t attribute_count)
{
	for (size_t i = 0; i < index_count; i += 3)
	{
		unsigned int i0 = indices[i + 0];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];

		Quadric QA;
		QuadricGrad G[kMaxAttributes];
		quadricFromAttributes(&QA, G, &vertex_positions[i0], &vertex_positions[i1], &vertex_positions[i2], &vertex_attributes[i0 * attribute_count], &vertex_attributes[i1 * attribute_count], &vertex_attributes[i2 * attribute_count], attribute_count);

		quadricAdd(&attribute_quadrics[i0], &QA);
		quadricAdd(&attribute_quadrics[i1], &QA);
		quadricAdd(&attribute_quadrics[i2], &QA);

		quadricGradAddN(&attribute_gradients[i0 * attribute_count], G, attribute_count);
		quadricGradAddN(&attribute_gradients[i1 * attribute_count], G, attribute_count);
		quadricGradAddN(&attribute_gradients[i2 * attribute_count], G, attribute_count);
	}
}

// does triangle ABC flip when C is replaced with D?
static bool hasTriangleFlip(const Vector3* a, const Vector3* b, const Vector3* c, const Vector3* d)
{
	Vector3 eb = {b->x - a->x, b->y - a->y, b->z - a->z};
	Vector3 ec = {c->x - a->x, c->y - a->y, c->z - a->z};
	Vector3 ed = {d->x - a->x, d->y - a->y, d->z - a->z};

	Vector3 nbc = {eb.y * ec.z - eb.z * ec.y, eb.z * ec.x - eb.x * ec.z, eb.x * ec.y - eb.y * ec.x};
	Vector3 nbd = {eb.y * ed.z - eb.z * ed.y, eb.z * ed.x - eb.x * ed.z, eb.x * ed.y - eb.y * ed.x};

	float ndp = nbc.x * nbd.x + nbc.y * nbd.y + nbc.z * nbd.z;
	float abc = nbc.x * nbc.x + nbc.y * nbc.y + nbc.z * nbc.z;
	float abd = nbd.x * nbd.x + nbd.y * nbd.y + nbd.z * nbd.z;

	// scale is cos(angle); somewhat arbitrarily set to ~75 degrees
	// note that the "pure" check is ndp <= 0 (90 degree cutoff) but that allows flipping through a series of close-to-90 collapses
	return ndp <= 0.25f * sqrtf(abc * abd);
}

static bool hasTriangleFlips(const EdgeAdjacency* adjacency, const Vector3* vertex_positions, const unsigned int* collapse_remap, unsigned int i0, unsigned int i1)
{
	assert(collapse_remap[i0] == i0);
	assert(collapse_remap[i1] == i1);

	const Vector3* v0 = &vertex_positions[i0];
	const Vector3* v1 = &vertex_positions[i1];

	const EdgeAdjacencyEdge* edges = &adjacency->data[adjacency->offsets[i0]];
	size_t count = adjacency->offsets[i0 + 1] - adjacency->offsets[i0];

	for (size_t i = 0; i < count; ++i)
	{
		unsigned int a = collapse_remap[edges[i].next];
		unsigned int b = collapse_remap[edges[i].prev];

		// skip triangles that will get collapsed by i0->i1 collapse or already got collapsed previously
		if (a == i1 || b == i1 || a == b)
			continue;

		// early-out when at least one triangle flips due to a collapse
		if (hasTriangleFlip(&vertex_positions[a], &vertex_positions[b], v0, v1))
			return true;
	}

	return false;
}

static unsigned int getComplexTarget(unsigned int v, unsigned int target, const unsigned int* remap, const unsigned int* loop, const unsigned int* loopback)
{
	unsigned int r = remap[target];

	// use loop metadata to guide complex collapses towards the correct wedge
	// this works for edges on attribute discontinuities because loop/loopback track the single half-edge without a pair, similar to seams
	if (loop[v] != ~0u && remap[loop[v]] == r)
		return loop[v];
	else if (loopback[v] != ~0u && remap[loopback[v]] == r)
		return loopback[v];
	else
		return target;
}

static size_t boundEdgeCollapses(const EdgeAdjacency* adjacency, size_t vertex_count, size_t index_count, unsigned char* vertex_kind)
{
	size_t dual_count = 0;

	for (size_t i = 0; i < vertex_count; ++i)
	{
		unsigned char k = vertex_kind[i];
		unsigned int e = adjacency->offsets[i + 1] - adjacency->offsets[i];

		dual_count += (k == Kind_Manifold || k == Kind_Seam) ? e : 0;
	}

	assert(dual_count <= index_count);

	// pad capacity by 3 so that we can check for overflow once per triangle instead of once per edge
	return (index_count - dual_count / 2) + 3;
}

static size_t pickEdgeCollapses(Collapse* collapses, size_t collapse_capacity, const unsigned int* indices, size_t index_count, const unsigned int* remap, const unsigned char* vertex_kind, const unsigned int* loop, const unsigned int* loopback)
{
	size_t collapse_count = 0;

	for (size_t i = 0; i < index_count; i += 3)
	{
		static const int next[3] = {1, 2, 0};

		// this should never happen as boundEdgeCollapses should give an upper bound for the collapse count, but in an unlikely event it does we can just drop extra collapses
		if (collapse_count + 3 > collapse_capacity)
			break;

		for (int e = 0; e < 3; ++e)
		{
			unsigned int i0 = indices[i + e];
			unsigned int i1 = indices[i + next[e]];

			// this can happen either when input has a zero-length edge, or when we perform collapses for complex
			// topology w/seams and collapse a manifold vertex that connects to both wedges onto one of them
			// we leave edges like this alone since they may be important for preserving mesh integrity
			if (remap[i0] == remap[i1])
				continue;

			unsigned char k0 = vertex_kind[i0];
			unsigned char k1 = vertex_kind[i1];

			// the edge has to be collapsible in at least one direction
			if (!(kCanCollapse[k0][k1] | kCanCollapse[k1][k0]))
				continue;

			// manifold and seam edges should occur twice (i0->i1 and i1->i0) - skip redundant edges
			if (kHasOpposite[k0][k1] && remap[i1] > remap[i0])
				continue;

			// two vertices are on a border or a seam, but there's no direct edge between them
			// this indicates that they belong to two different edge loops and we should not collapse this edge
			// loop[] and loopback[] track half edges so we only need to check one of them
			if ((k0 == Kind_Border || k0 == Kind_Seam) && k1 != Kind_Manifold && loop[i0] != i1)
				continue;
			if ((k1 == Kind_Border || k1 == Kind_Seam) && k0 != Kind_Manifold && loopback[i1] != i0)
				continue;

			// edge can be collapsed in either direction - we will pick the one with minimum error
			// note: we evaluate error later during collapse ranking, here we just tag the edge as bidirectional
			if (kCanCollapse[k0][k1] & kCanCollapse[k1][k0])
			{
				Collapse c = {i0, i1, {/* bidi= */ 1}};
				collapses[collapse_count++] = c;
			}
			else
			{
				// edge can only be collapsed in one direction
				unsigned int e0 = kCanCollapse[k0][k1] ? i0 : i1;
				unsigned int e1 = kCanCollapse[k0][k1] ? i1 : i0;

				Collapse c = {e0, e1, {/* bidi= */ 0}};
				collapses[collapse_count++] = c;
			}
		}
	}

	return collapse_count;
}

static void rankEdgeCollapses(Collapse* collapses, size_t collapse_count, const Vector3* vertex_positions, const float* vertex_attributes, const Quadric* vertex_quadrics, const Quadric* attribute_quadrics, const QuadricGrad* attribute_gradients, size_t attribute_count, const unsigned int* remap, const unsigned int* wedge, const unsigned char* vertex_kind, const unsigned int* loop, const unsigned int* loopback, bool clamped)
{
	for (size_t i = 0; i < collapse_count; ++i)
	{
		Collapse* c = &collapses[i];

		unsigned int i0 = c->v0;
		unsigned int i1 = c->v1;
		bool bidi = c->u.bidi;

		float ei = quadricError(&vertex_quadrics[remap[i0]], &vertex_positions[i1]);
		float ej = bidi ? quadricError(&vertex_quadrics[remap[i1]], &vertex_positions[i0]) : FLT_MAX;

		if (attribute_count)
		{
			ei += quadricErrorAttr(&attribute_quadrics[i0], &attribute_gradients[i0 * attribute_count], attribute_count, &vertex_positions[i1], &vertex_attributes[i1 * attribute_count], clamped);
			ej += bidi ? quadricErrorAttr(&attribute_quadrics[i1], &attribute_gradients[i1 * attribute_count], attribute_count, &vertex_positions[i0], &vertex_attributes[i0 * attribute_count], clamped) : 0;

			// seam edges need to aggregate attribute errors between primary and secondary edges, as attribute quadrics are separate
			if (vertex_kind[i0] == Kind_Seam)
			{
				// for seam collapses we need to find the seam pair; this is a bit tricky since we need to rely on edge loops as target vertex may be locked (and thus have more than two wedges)
				unsigned int s0 = wedge[i0];
				unsigned int s1 = loop[i0] == i1 ? loopback[s0] : loop[s0];

				assert(wedge[s0] == i0); // s0 may be equal to i0 for half-seams
				assert(s1 != ~0u && remap[s1] == remap[i1]);

				// note: this should never happen due to the assertion above, but when disabled if we ever hit this case we'll get a memory safety issue; for now play it safe
				s1 = (s1 != ~0u) ? s1 : wedge[i1];

				ei += quadricErrorAttr(&attribute_quadrics[s0], &attribute_gradients[s0 * attribute_count], attribute_count, &vertex_positions[s1], &vertex_attributes[s1 * attribute_count], clamped);
				ej += bidi ? quadricErrorAttr(&attribute_quadrics[s1], &attribute_gradients[s1 * attribute_count], attribute_count, &vertex_positions[s0], &vertex_attributes[s0 * attribute_count], clamped) : 0;
			}
			else
			{
				// complex edges can have multiple wedges, so we need to aggregate errors for all wedges based on the selected target
				if (vertex_kind[i0] == Kind_Complex || vertex_kind[i0] == Kind_Fringe)
					for (unsigned int v = wedge[i0]; v != i0; v = wedge[v])
					{
						unsigned int t = getComplexTarget(v, i1, remap, loop, loopback);

						ei += quadricErrorAttr(&attribute_quadrics[v], &attribute_gradients[v * attribute_count], attribute_count, &vertex_positions[t], &vertex_attributes[t * attribute_count], clamped);
					}

				if ((vertex_kind[i1] == Kind_Complex || vertex_kind[i1] == Kind_Fringe) && bidi)
					for (unsigned int v = wedge[i1]; v != i1; v = wedge[v])
					{
						unsigned int t = getComplexTarget(v, i0, remap, loop, loopback);

						ej += quadricErrorAttr(&attribute_quadrics[v], &attribute_gradients[v * attribute_count], attribute_count, &vertex_positions[t], &vertex_attributes[t * attribute_count], clamped);
					}
			}
		}

		// pick edge direction with minimal error (branchless)
		bool rev = bidi & (ej < ei);

		c->v0 = rev ? i1 : i0;
		c->v1 = rev ? i0 : i1;
		c->u.error = ej < ei ? ej : ei;
	}
}

static void sortEdgeCollapses(unsigned int* sort_order, const Collapse* collapses, size_t collapse_count)
{
	// we use counting sort to order collapses by error; since the exact sort order is not as critical,
	// only top 12 bits of exponent+mantissa (8 bits of exponent and 4 bits of mantissa) are used.
	// to avoid excessive stack usage, we clamp the exponent range as collapses with errors much higher than 1 are not useful.
	enum
	{
		sort_bits = 12,
		sort_bins = 2048 + 512 // exponent range [-127, 32)
	};

	// fill histogram for counting sort
	unsigned int histogram[sort_bins];
	memset(histogram, 0, sizeof(histogram));

	for (size_t i = 0; i < collapse_count; ++i)
	{
		// skip sign bit since error is non-negative
		unsigned int error = collapses[i].u.errorui;
		unsigned int key = (error << 1) >> (32 - sort_bits);
		key = key < sort_bins ? key : sort_bins - 1;

		histogram[key]++;
	}

	// compute offsets based on histogram data
	size_t histogram_sum = 0;

	for (size_t i = 0; i < sort_bins; ++i)
	{
		size_t count = histogram[i];
		histogram[i] = (unsigned int)histogram_sum;
		histogram_sum += count;
	}

	assert(histogram_sum == collapse_count);

	// compute sort order based on offsets
	for (size_t i = 0; i < collapse_count; ++i)
	{
		// skip sign bit since error is non-negative
		unsigned int error = collapses[i].u.errorui;
		unsigned int key = (error << 1) >> (32 - sort_bits);
		key = key < sort_bins ? key : sort_bins - 1;

		sort_order[histogram[key]++] = (unsigned int)i;
	}
}

static size_t performEdgeCollapses(unsigned int* collapse_remap, unsigned char* collapse_locked, const Collapse* collapses, size_t collapse_count, const unsigned int* collapse_order, const unsigned int* remap, const unsigned int* wedge, const unsigned char* vertex_kind, const unsigned int* loop, const unsigned int* loopback, const Vector3* vertex_positions, const EdgeAdjacency* adjacency, size_t triangle_collapse_goal, float error_limit, float* result_error)
{
	size_t edge_collapses = 0;
	size_t triangle_collapses = 0;

	// most collapses remove 2 triangles; use this to establish a bound on the pass in terms of error limit
	// note that edge_collapse_goal is an estimate; triangle_collapse_goal will be used to actually limit collapses
	size_t edge_collapse_goal = triangle_collapse_goal / 2;

	for (size_t i = 0; i < collapse_count; ++i)
	{
		const Collapse* c = &collapses[collapse_order[i]];

		if (c->u.error > error_limit)
			break;

		if (triangle_collapses >= triangle_collapse_goal)
			break;

		// we limit the error in each pass based on the error of optimal last collapse; since many collapses will be locked
		// as they will share vertices with other successful collapses, we need to increase the acceptable error by some factor
		float error_goal = edge_collapse_goal < collapse_count ? 1.5f * collapses[collapse_order[edge_collapse_goal]].u.error : FLT_MAX;

		// on average, each collapse is expected to lock 6 other collapses; to avoid degenerate passes on meshes with odd
		// topology, we only abort if we got over 1/6 collapses accordingly.
		if (c->u.error > error_goal && c->u.error > *result_error && triangle_collapses > triangle_collapse_goal / 6)
			break;

		unsigned int i0 = c->v0;
		unsigned int i1 = c->v1;

		unsigned int r0 = remap[i0];
		unsigned int r1 = remap[i1];

		unsigned char kind = vertex_kind[i0];

		// we don't collapse vertices that had source or target vertex involved in a collapse
		// it's important to not move the vertices twice since it complicates the tracking/remapping logic
		// it's important to not move other vertices towards a moved vertex to preserve error since we don't re-rank collapses mid-pass
		if (collapse_locked[r0] | collapse_locked[r1])
			continue;

		if (hasTriangleFlips(adjacency, vertex_positions, collapse_remap, r0, r1))
		{
			// adjust collapse goal since this collapse is invalid and shouldn't factor into error goal
			edge_collapse_goal++;

			continue;
		}

		assert(collapse_remap[r0] == r0);
		assert(collapse_remap[r1] == r1);

		if (kind == Kind_Complex || kind == Kind_Fringe)
		{
			collapse_remap[i0] = i1;

			// remap all vertices in the complex to the target vertex, using the same ranking that we used to evaluate the collapses
			for (unsigned int v = wedge[i0]; v != i0; v = wedge[v])
				collapse_remap[v] = getComplexTarget(v, i1, remap, loop, loopback);
		}
		else if (kind == Kind_Seam)
		{
			// for seam collapses we need to move the seam pair together; this is a bit tricky since we need to rely on edge loops as target vertex may be locked (and thus have more than two wedges)
			unsigned int s0 = wedge[i0];
			unsigned int s1 = loop[i0] == i1 ? loopback[s0] : loop[s0];
			assert(wedge[s0] == i0); // s0 may be equal to i0 for half-seams
			assert(s1 != ~0u && remap[s1] == r1);

			// additional asserts to verify that the seam pair is consistent
			assert(kind != vertex_kind[i1] || s1 == wedge[i1]);
			assert(loop[i0] == i1 || loopback[i0] == i1);
			assert(loop[s0] == s1 || loopback[s0] == s1);

			// note: this should never happen due to the assertion above, but when disabled if we ever hit this case we'll get a memory safety issue; for now play it safe
			s1 = (s1 != ~0u) ? s1 : wedge[i1];

			collapse_remap[i0] = i1;
			collapse_remap[s0] = s1;
		}
		else
		{
			assert(wedge[i0] == i0);

			collapse_remap[i0] = i1;
		}

		// note: we technically don't need to lock r1 if it's a locked vertex, as it can't move and its quadric won't be used
		// however, this results in slightly worse error on some meshes because the locked collapses get an unfair advantage wrt scheduling
		collapse_locked[r0] = 1;
		collapse_locked[r1] = 1;

		// border edges collapse 1 triangle, other edges collapse 2 or more
		// fringe edges often collapse 1 but may also collapse 2 because they don't respect loops, so we conservatively assume 2
		triangle_collapses += (kind == Kind_Border) ? 1 : 2;
		edge_collapses++;

		*result_error = *result_error < c->u.error ? c->u.error : *result_error;
	}

	return edge_collapses;
}

static void updateQuadrics(const unsigned int* collapse_remap, size_t vertex_count, Quadric* vertex_quadrics, Quadric* attribute_quadrics, QuadricGrad* attribute_gradients, size_t attribute_count, const Vector3* vertex_positions, const unsigned int* remap, float* vertex_error)
{
	for (size_t i = 0; i < vertex_count; ++i)
	{
		if (collapse_remap[i] == i)
			continue;

		unsigned int i0 = (unsigned int)i;
		unsigned int i1 = collapse_remap[i];

		unsigned int r0 = remap[i0];
		unsigned int r1 = remap[i1];

		// ensure we only update vertex_quadrics once: primary vertex must be moved if any wedge is moved
		if (i0 == r0)
			quadricAdd(&vertex_quadrics[r1], &vertex_quadrics[r0]);

		if (attribute_count)
		{
			quadricAdd(&attribute_quadrics[i1], &attribute_quadrics[i0]);
			quadricGradAddN(&attribute_gradients[i1 * attribute_count], &attribute_gradients[i0 * attribute_count], attribute_count);

			if (i0 == r0)
			{
				// when attributes are used, distance error needs to be recomputed as collapses don't track it; it is safe to do this after the quadric adjustment
				float derr = quadricError(&vertex_quadrics[r0], &vertex_positions[r1]);
				*vertex_error = *vertex_error < derr ? derr : *vertex_error;
			}
		}
	}
}

static size_t remapIndexBuffer(unsigned int* indices, size_t index_count, const unsigned int* collapse_remap, const unsigned int* remap)
{
	size_t write = 0;

	for (size_t i = 0; i < index_count; i += 3)
	{
		unsigned int v0 = collapse_remap[indices[i + 0]];
		unsigned int v1 = collapse_remap[indices[i + 1]];
		unsigned int v2 = collapse_remap[indices[i + 2]];

		// we never move the vertex twice during a single pass
		assert(collapse_remap[v0] == v0);
		assert(collapse_remap[v1] == v1);
		assert(collapse_remap[v2] == v2);

		// collapse zero area triangles even if they are not topologically degenerate
		// this is required to cleanup manifold->seam collapses when a vertex is collapsed onto a seam pair
		// as well as complex collapses and some other cases where cross wedge collapses are performed
		unsigned int r0 = remap[v0];
		unsigned int r1 = remap[v1];
		unsigned int r2 = remap[v2];

		if (r0 != r1 && r0 != r2 && r1 != r2)
		{
			indices[write + 0] = v0;
			indices[write + 1] = v1;
			indices[write + 2] = v2;
			write += 3;
		}
	}

	return write;
}

static void remapEdgeLoops(unsigned int* loop, size_t vertex_count, const unsigned int* collapse_remap)
{
	for (size_t i = 0; i < vertex_count; ++i)
	{
		// note: this is a no-op for vertices that were remapped
		// ideally we would clear the loop entries for those for consistency, even though they aren't going to be used
		// however, the remapping process needs loop information for remapped vertices, so this would require a separate pass
		if (loop[i] != ~0u)
		{
			unsigned int l = loop[i];
			unsigned int r = collapse_remap[l];

			// i == r is a special case when the seam edge is collapsed in a direction opposite to where loop goes
			if (i == r)
				loop[i] = (loop[l] != ~0u) ? collapse_remap[loop[l]] : ~0u;
			else
				loop[i] = r;
		}
	}
}

static unsigned int follow(unsigned int* parents, unsigned int index)
{
	while (index != parents[index])
	{
		unsigned int parent = parents[index];
		parents[index] = parents[parent];
		index = parent;
	}

	return index;
}

static size_t buildComponents(unsigned int* components, size_t vertex_count, const unsigned int* indices, size_t index_count, const unsigned int* remap)
{
	for (size_t i = 0; i < vertex_count; ++i)
		components[i] = (unsigned int)i;

	// compute a unique (but not sequential!) index for each component via union-find
	for (size_t i = 0; i < index_count; i += 3)
	{
		static const int next[4] = {1, 2, 0, 1};

		for (int e = 0; e < 3; ++e)
		{
			unsigned int i0 = indices[i + e];
			unsigned int i1 = indices[i + next[e]];

			unsigned int r0 = remap[i0];
			unsigned int r1 = remap[i1];

			r0 = follow(components, r0);
			r1 = follow(components, r1);

			// merge components with larger indices into components with smaller indices
			// this guarantees that the root of the component is always the one with the smallest index
			if (r0 != r1)
				components[r0 < r1 ? r1 : r0] = r0 < r1 ? r0 : r1;
		}
	}

	// make sure each element points to the component root *before* we renumber the components
	for (size_t i = 0; i < vertex_count; ++i)
		if (remap[i] == i)
			components[i] = follow(components, (unsigned int)i);

	unsigned int next_component = 0;

	// renumber components using sequential indices
	// a sequential pass is sufficient because component root always has the smallest index
	// note: it is unsafe to use follow() in this pass because we're replacing component links with sequential indices inplace
	for (size_t i = 0; i < vertex_count; ++i)
	{
		if (remap[i] == i)
		{
			unsigned int root = components[i];
			assert(root <= i); // make sure we already computed the component for non-roots
			components[i] = (root == i) ? next_component++ : components[root];
		}
		else
		{
			assert(remap[i] < i); // make sure we already computed the component
			components[i] = components[remap[i]];
		}
	}

	return next_component;
}

static void measureComponents(float* component_errors, size_t component_count, const unsigned int* components, const Vector3* vertex_positions, size_t vertex_count)
{
	memset(component_errors, 0, component_count * 4 * sizeof(float));

	// compute approximate sphere center for each component as an average
	for (size_t i = 0; i < vertex_count; ++i)
	{
		unsigned int c = components[i];
		assert(components[i] < component_count);

		Vector3 v = vertex_positions[i]; // copy avoids aliasing issues

		component_errors[c * 4 + 0] += v.x;
		component_errors[c * 4 + 1] += v.y;
		component_errors[c * 4 + 2] += v.z;
		component_errors[c * 4 + 3] += 1; // weight
	}

	// complete the center computation, and reinitialize [3] as a radius
	for (size_t i = 0; i < component_count; ++i)
	{
		float w = component_errors[i * 4 + 3];
		float iw = w == 0.f ? 0.f : 1.f / w;

		component_errors[i * 4 + 0] *= iw;
		component_errors[i * 4 + 1] *= iw;
		component_errors[i * 4 + 2] *= iw;
		component_errors[i * 4 + 3] = 0; // radius
	}

	// compute squared radius for each component
	for (size_t i = 0; i < vertex_count; ++i)
	{
		unsigned int c = components[i];

		float dx = vertex_positions[i].x - component_errors[c * 4 + 0];
		float dy = vertex_positions[i].y - component_errors[c * 4 + 1];
		float dz = vertex_positions[i].z - component_errors[c * 4 + 2];
		float r = dx * dx + dy * dy + dz * dz;

		component_errors[c * 4 + 3] = component_errors[c * 4 + 3] < r ? r : component_errors[c * 4 + 3];
	}

	// we've used the output buffer as scratch space, so we need to move the results to proper indices
	// note: we keep the squared error to make it match quadric error metric
	for (size_t i = 0; i < component_count; ++i)
		component_errors[i] = component_errors[i * 4 + 3];
}

static size_t pruneComponents(unsigned int* indices, size_t index_count, const unsigned int* components, const float* component_errors, size_t component_count, float error_cutoff, float* nexterror)
{
	(void)component_count;

	size_t write = 0;
	float min_error = FLT_MAX;

	for (size_t i = 0; i < index_count; i += 3)
	{
		unsigned int v0 = indices[i + 0], v1 = indices[i + 1], v2 = indices[i + 2];
		unsigned int c = components[v0];
		assert(c == components[v1] && c == components[v2]);

		if (component_errors[c] > error_cutoff)
		{
			min_error = min_error > component_errors[c] ? component_errors[c] : min_error;

			indices[write + 0] = v0;
			indices[write + 1] = v1;
			indices[write + 2] = v2;
			write += 3;
		}
	}

	// update next error with the smallest error of the remaining components
	*nexterror = min_error;
	return write;
}

static size_t meshopt_simplifyEdge(unsigned int* destination, const unsigned int* indices, size_t index_count, const float* vertex_positions_data, size_t vertex_count, size_t vertex_positions_stride, const float* vertex_attributes_data, size_t vertex_attributes_stride, const float* attribute_weights, size_t attribute_count, const unsigned char* vertex_lock, size_t target_index_count, float target_error, unsigned int options, float* out_result_error)
{
	assert(index_count % 3 == 0);
	assert(vertex_positions_stride >= 12 && vertex_positions_stride <= 256);
	assert(vertex_positions_stride % sizeof(float) == 0);
	assert(target_index_count <= index_count);
	assert(target_error >= 0);
	assert(vertex_attributes_stride >= attribute_count * sizeof(float) && vertex_attributes_stride <= 256);
	assert(vertex_attributes_stride % sizeof(float) == 0);
	assert(attribute_count <= kMaxAttributes);
	for (size_t i = 0; i < attribute_count; ++i)
		assert(attribute_weights[i] >= 0);

	MeshoptArena allocator;
	allocator.count = 0;

	size_t result_count = 0;
	float result_error = 0;
	float error_scale = 1.f;
	bool ok = false;

	unsigned int* result = destination;
	if (result != indices)
		memcpy(result, indices, index_count * sizeof(unsigned int));

	// build an index remap and update indices/vertex_count to minimize the subsequent work
	// note: as a consequence, errors will be computed relative to the subset extent
	unsigned int* sparse_remap = NULL;
	if (options & meshopt_SimplifySparse)
	{
		sparse_remap = buildSparseRemap(result, index_count, vertex_count, &vertex_count, &allocator);
		if (!sparse_remap)
			goto done;
	}

	// build adjacency information
	EdgeAdjacency adjacency = {NULL, NULL};
	if (!prepareEdgeAdjacency(&adjacency, index_count, vertex_count, &allocator))
		goto done;
	updateEdgeAdjacency(&adjacency, result, index_count, vertex_count, NULL);

	// build position remap that maps each vertex to the one with identical position
	// wedge table stores next vertex with identical position for each vertex
	unsigned int* remap = MESHOPT_ALLOC(&allocator, unsigned int, vertex_count);
	unsigned int* wedge = MESHOPT_ALLOC(&allocator, unsigned int, vertex_count);
	if (!remap || !wedge)
		goto done;
	if (!buildPositionRemap(remap, wedge, vertex_positions_data, vertex_count, vertex_positions_stride, sparse_remap, &allocator))
		goto done;

	// classify vertices; vertex kind determines collapse rules, see kCanCollapse
	unsigned char* vertex_kind = MESHOPT_ALLOC(&allocator, unsigned char, vertex_count);
	unsigned int* loop = MESHOPT_ALLOC(&allocator, unsigned int, vertex_count);
	unsigned int* loopback = MESHOPT_ALLOC(&allocator, unsigned int, vertex_count);
	if (!vertex_kind || !loop || !loopback)
		goto done;
	classifyVertices(vertex_kind, loop, loopback, vertex_count, &adjacency, remap, wedge, vertex_lock, sparse_remap, options);

	Vector3* vertex_positions = MESHOPT_ALLOC(&allocator, Vector3, vertex_count);
	if (!vertex_positions)
		goto done;
	float vertex_offset[3] = {0, 0, 0};
	float vertex_scale = rescalePositions(vertex_positions, vertex_positions_data, vertex_count, vertex_positions_stride, sparse_remap, vertex_offset);

	float* vertex_attributes = NULL;
	unsigned int attribute_remap[kMaxAttributes];

	if (attribute_count)
	{
		// remap attributes to only include ones with weight > 0 to minimize memory/compute overhead for quadrics
		size_t attributes_used = 0;
		for (size_t i = 0; i < attribute_count; ++i)
			if (attribute_weights[i] > 0)
				attribute_remap[attributes_used++] = (unsigned int)i;

		attribute_count = attributes_used;
		vertex_attributes = MESHOPT_ALLOC(&allocator, float, vertex_count * attribute_count);
		if (!vertex_attributes)
			goto done;
		rescaleAttributes(vertex_attributes, vertex_attributes_data, vertex_count, vertex_attributes_stride, attribute_weights, attribute_count, attribute_remap, sparse_remap);
	}

	Quadric* vertex_quadrics = MESHOPT_ALLOC(&allocator, Quadric, vertex_count);
	if (!vertex_quadrics)
		goto done;
	memset(vertex_quadrics, 0, vertex_count * sizeof(Quadric));

	Quadric* attribute_quadrics = NULL;
	QuadricGrad* attribute_gradients = NULL;

	if (attribute_count)
	{
		attribute_quadrics = MESHOPT_ALLOC(&allocator, Quadric, vertex_count);
		if (!attribute_quadrics)
			goto done;
		memset(attribute_quadrics, 0, vertex_count * sizeof(Quadric));

		attribute_gradients = MESHOPT_ALLOC(&allocator, QuadricGrad, vertex_count * attribute_count);
		if (!attribute_gradients)
			goto done;
		memset(attribute_gradients, 0, vertex_count * attribute_count * sizeof(QuadricGrad));
	}

	fillFaceQuadrics(vertex_quadrics, result, index_count, vertex_positions, remap);
	fillVertexQuadrics(vertex_quadrics, vertex_positions, vertex_count, remap, vertex_lock, sparse_remap, options);
	fillEdgeQuadrics(vertex_quadrics, result, index_count, vertex_positions, remap, vertex_kind, loop, loopback);

	if (options & meshopt_SimplifyPreserveFolds)
		fillFoldQuadrics(vertex_quadrics, &adjacency, vertex_positions, vertex_count, remap, wedge);

	if (attribute_count)
		fillAttributeQuadrics(attribute_quadrics, attribute_gradients, result, index_count, vertex_positions, vertex_attributes, attribute_count);

	unsigned int* components = NULL;
	float* component_errors = NULL;
	size_t component_count = 0;
	float component_nexterror = 0;

	if (options & meshopt_SimplifyPrune)
	{
		components = MESHOPT_ALLOC(&allocator, unsigned int, vertex_count);
		if (!components)
			goto done;
		component_count = buildComponents(components, vertex_count, result, index_count, remap);

		component_errors = MESHOPT_ALLOC(&allocator, float, component_count * 4); // overallocate for temporary use inside measureComponents
		if (!component_errors)
			goto done;
		measureComponents(component_errors, component_count, components, vertex_positions, vertex_count);

		component_nexterror = FLT_MAX;
		for (size_t i = 0; i < component_count; ++i)
			component_nexterror = component_nexterror > component_errors[i] ? component_errors[i] : component_nexterror;
	}

	size_t collapse_capacity = boundEdgeCollapses(&adjacency, vertex_count, index_count, vertex_kind);

	Collapse* edge_collapses = MESHOPT_ALLOC(&allocator, Collapse, collapse_capacity);
	unsigned int* collapse_order = MESHOPT_ALLOC(&allocator, unsigned int, collapse_capacity);
	unsigned int* collapse_remap = MESHOPT_ALLOC(&allocator, unsigned int, vertex_count);
	unsigned char* collapse_locked = MESHOPT_ALLOC(&allocator, unsigned char, vertex_count);
	if (!edge_collapses || !collapse_order || !collapse_remap || !collapse_locked)
		goto done;

	result_count = index_count;
	float vertex_error = 0;

	// target_error input is linear; we need to adjust it to match quadricError units
	error_scale = (options & meshopt_SimplifyErrorAbsolute) ? vertex_scale : 1.f;
	float error_limit = (target_error * target_error) / (error_scale * error_scale);

	while (result_count > target_index_count)
	{
		// note: throughout the simplification process adjacency structure reflects welded topology for result-in-progress
		updateEdgeAdjacency(&adjacency, result, result_count, vertex_count, remap);

		size_t edge_collapse_count = pickEdgeCollapses(edge_collapses, collapse_capacity, result, result_count, remap, vertex_kind, loop, loopback);
		assert(edge_collapse_count <= collapse_capacity);

		// no edges can be collapsed any more due to topology restrictions
		if (edge_collapse_count == 0)
			break;

		rankEdgeCollapses(edge_collapses, edge_collapse_count, vertex_positions, vertex_attributes, vertex_quadrics, attribute_quadrics, attribute_gradients, attribute_count, remap, wedge, vertex_kind, loop, loopback, (options & meshopt_SimplifyErrorClamped) != 0);

		sortEdgeCollapses(collapse_order, edge_collapses, edge_collapse_count);

		size_t triangle_collapse_goal = (result_count - target_index_count) / 3;

		for (size_t i = 0; i < vertex_count; ++i)
			collapse_remap[i] = (unsigned int)i;

		memset(collapse_locked, 0, vertex_count);

		size_t collapses = performEdgeCollapses(collapse_remap, collapse_locked, edge_collapses, edge_collapse_count, collapse_order, remap, wedge, vertex_kind, loop, loopback, vertex_positions, &adjacency, triangle_collapse_goal, error_limit, &result_error);

		// no edges can be collapsed any more due to hitting the error limit or triangle collapse limit
		if (collapses == 0)
			break;

		updateQuadrics(collapse_remap, vertex_count, vertex_quadrics, attribute_quadrics, attribute_gradients, attribute_count, vertex_positions, remap, &vertex_error);

		// updateQuadrics will update vertex error if we use attributes, but if we don't then result_error and vertex_error are equivalent
		vertex_error = attribute_count == 0 ? result_error : vertex_error;

		// note: we update loops following edge collapses, but after this we might still have stale loop data
		// this can happen when a triangle with a loop edge gets collapsed along a non-loop edge
		// that works since a loop that points to a vertex that is no longer connected is not affecting collapse logic
		remapEdgeLoops(loop, vertex_count, collapse_remap);
		remapEdgeLoops(loopback, vertex_count, collapse_remap);

		result_count = remapIndexBuffer(result, result_count, collapse_remap, remap);

		if ((options & meshopt_SimplifyPrune) && result_count > target_index_count && component_nexterror <= vertex_error)
			result_count = pruneComponents(result, result_count, components, component_errors, component_count, vertex_error, &component_nexterror);
	}

	// at this point, component_nexterror might be stale: component it references may have been removed through a series of edge collapses
	bool component_nextstale = true;

	// we're done with the regular simplification but we're still short of the target; try pruning more aggressively towards error_limit
	while ((options & meshopt_SimplifyPrune) && result_count > target_index_count && component_nexterror <= error_limit)
	{
		float component_cutoff = component_nexterror * 1.5f < error_limit ? component_nexterror * 1.5f : error_limit;

		// track maximum error in eligible components as we are increasing resulting error
		float component_maxerror = 0;
		for (size_t i = 0; i < component_count; ++i)
			if (component_errors[i] > component_maxerror && component_errors[i] <= component_cutoff)
				component_maxerror = component_errors[i];

		size_t new_count = pruneComponents(result, result_count, components, component_errors, component_count, component_cutoff, &component_nexterror);
		if (new_count == result_count && !component_nextstale)
			break;

		component_nextstale = false; // pruneComponents guarantees next error is up to date
		result_count = new_count;
		result_error = result_error < component_maxerror ? component_maxerror : result_error;
		vertex_error = vertex_error < component_maxerror ? component_maxerror : vertex_error;
	}

	// convert resulting indices back into the dense space of the larger mesh
	if (sparse_remap)
		for (size_t i = 0; i < result_count; ++i)
			result[i] = sparse_remap[result[i]];

	ok = true;

done:
	meshopt_arena_free_all(&allocator);

	if (!ok)
	{
		if (out_result_error)
			*out_result_error = 0;

		return 0;
	}

	// result_error is quadratic; we need to remap it back to linear
	if (out_result_error)
		*out_result_error = sqrtf(result_error) * error_scale;

	return result_count;
}

size_t meshopt_simplify(unsigned int* destination, const unsigned int* indices, size_t index_count, const float* vertex_positions_data, size_t vertex_count, size_t vertex_positions_stride, size_t target_index_count, float target_error, unsigned int options, float* out_result_error)
{
	return meshopt_simplifyEdge(destination, indices, index_count, vertex_positions_data, vertex_count, vertex_positions_stride, NULL, 0, NULL, 0, NULL, target_index_count, target_error, options, out_result_error);
}

size_t meshopt_simplifyWithAttributes(unsigned int* destination, const unsigned int* indices, size_t index_count, const float* vertex_positions_data, size_t vertex_count, size_t vertex_positions_stride, const float* vertex_attributes_data, size_t vertex_attributes_stride, const float* attribute_weights, size_t attribute_count, const unsigned char* vertex_lock, size_t target_index_count, float target_error, unsigned int options, float* out_result_error)
{
	return meshopt_simplifyEdge(destination, indices, index_count, vertex_positions_data, vertex_count, vertex_positions_stride, vertex_attributes_data, vertex_attributes_stride, attribute_weights, attribute_count, vertex_lock, target_index_count, target_error, options, out_result_error);
}

float meshopt_simplifyScale(const float* vertex_positions, size_t vertex_count, size_t vertex_positions_stride)
{
	assert(vertex_positions_stride >= 12 && vertex_positions_stride <= 256);
	assert(vertex_positions_stride % sizeof(float) == 0);

	float extent = rescalePositions(NULL, vertex_positions, vertex_count, vertex_positions_stride, NULL, NULL);

	return extent;
}
