// This file is part of meshoptimizer library; see meshopt.h / LICENSE.md for version/license details
// Pure C11 port of meshoptimizer v1.3 src/vcacheoptimizer.cpp (meshopt_optimizeVertexCache only); see README.md
#include "meshopt.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// This work is based on:
// Tom Forsyth. Linear-Speed Vertex Cache Optimisation. 2006
// Pedro Sander, Diego Nehab and Joshua Barczak. Fast Triangle Reordering for Vertex Locality and Reduced Overdraw. 2007

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

static void meshopt_arena_free_all(MeshoptArena* a)
{
	for (size_t i = a->count; i > 0; --i)
		free(a->blocks[i - 1]);

	a->count = 0;
}

#define MESHOPT_ALLOC(arena, T, n) ((T*)meshopt_arena_alloc_array((arena), (n), sizeof(T)))

#define kCacheSizeMax 16
#define kValenceMax 8

typedef struct
{
	float cache[1 + kCacheSizeMax];
	float live[1 + kValenceMax];
} VertexScoreTable;

// Tuned to minimize the ACMR of a GPU that has a cache profile similar to NVidia and AMD
static const VertexScoreTable kVertexScoreTable = {
    {0.f, 0.779f, 0.791f, 0.789f, 0.981f, 0.843f, 0.726f, 0.847f, 0.882f, 0.867f, 0.799f, 0.642f, 0.613f, 0.600f, 0.568f, 0.372f, 0.234f},
    {0.f, 0.995f, 0.713f, 0.450f, 0.404f, 0.059f, 0.005f, 0.147f, 0.006f},
};

typedef struct
{
	unsigned int* counts;
	unsigned int* offsets;
	unsigned int* data;
} TriangleAdjacency;

static bool buildTriangleAdjacency(TriangleAdjacency* adjacency, const unsigned int* indices, size_t index_count, size_t vertex_count, MeshoptArena* allocator)
{
	size_t face_count = index_count / 3;

	// allocate arrays
	adjacency->counts = MESHOPT_ALLOC(allocator, unsigned int, vertex_count);
	adjacency->offsets = MESHOPT_ALLOC(allocator, unsigned int, vertex_count);
	adjacency->data = MESHOPT_ALLOC(allocator, unsigned int, index_count);
	if (!adjacency->counts || !adjacency->offsets || !adjacency->data)
		return false;

	// fill triangle counts
	memset(adjacency->counts, 0, vertex_count * sizeof(unsigned int));

	for (size_t i = 0; i < index_count; ++i)
	{
		assert(indices[i] < vertex_count);

		adjacency->counts[indices[i]]++;
	}

	// fill offset table
	unsigned int offset = 0;

	for (size_t i = 0; i < vertex_count; ++i)
	{
		adjacency->offsets[i] = offset;
		offset += adjacency->counts[i];
	}

	assert(offset == index_count);

	// fill triangle data
	for (size_t i = 0; i < face_count; ++i)
	{
		unsigned int a = indices[i * 3 + 0], b = indices[i * 3 + 1], c = indices[i * 3 + 2];

		adjacency->data[adjacency->offsets[a]++] = (unsigned int)i;
		adjacency->data[adjacency->offsets[b]++] = (unsigned int)i;
		adjacency->data[adjacency->offsets[c]++] = (unsigned int)i;
	}

	// fix offsets that have been disturbed by the previous pass
	for (size_t i = 0; i < vertex_count; ++i)
	{
		assert(adjacency->offsets[i] >= adjacency->counts[i]);

		adjacency->offsets[i] -= adjacency->counts[i];
	}

	return true;
}

static float vertexScore(const VertexScoreTable* table, int cache_position, unsigned int live_triangles)
{
	assert(cache_position >= -1 && cache_position < (int)kCacheSizeMax);

	unsigned int live_triangles_clamped = live_triangles < kValenceMax ? live_triangles : kValenceMax;

	return table->cache[1 + cache_position] + table->live[live_triangles_clamped];
}

static unsigned int getNextTriangleDeadEnd(unsigned int* input_cursor, const unsigned char* emitted_flags, size_t face_count)
{
	// input order
	while (*input_cursor < face_count)
	{
		if (!emitted_flags[*input_cursor])
			return *input_cursor;

		++*input_cursor;
	}

	return ~0u;
}

static void meshopt_optimizeVertexCacheTable(unsigned int* destination, const unsigned int* indices, size_t index_count, size_t vertex_count, const VertexScoreTable* table)
{
	assert(index_count % 3 == 0);

	MeshoptArena allocator;
	allocator.count = 0;

	// guard for empty meshes
	if (index_count == 0 || vertex_count == 0)
		return;

	// support in-place optimization
	if (destination == indices)
	{
		unsigned int* indices_copy = MESHOPT_ALLOC(&allocator, unsigned int, index_count);
		if (!indices_copy)
			goto done;
		memcpy(indices_copy, indices, index_count * sizeof(unsigned int));
		indices = indices_copy;
	}

	unsigned int cache_size = 16;
	assert(cache_size <= kCacheSizeMax);

	size_t face_count = index_count / 3;

	// build adjacency information
	TriangleAdjacency adjacency = {NULL, NULL, NULL};
	if (!buildTriangleAdjacency(&adjacency, indices, index_count, vertex_count, &allocator))
		goto fail;

	// live triangle counts; note, we alias adjacency.counts as we remove triangles after emitting them so the counts always match
	unsigned int* live_triangles = adjacency.counts;

	// emitted flags
	unsigned char* emitted_flags = MESHOPT_ALLOC(&allocator, unsigned char, face_count);
	if (!emitted_flags)
		goto fail;
	memset(emitted_flags, 0, face_count);

	// compute initial vertex scores
	float* vertex_scores = MESHOPT_ALLOC(&allocator, float, vertex_count);
	if (!vertex_scores)
		goto fail;

	for (size_t i = 0; i < vertex_count; ++i)
		vertex_scores[i] = vertexScore(table, -1, live_triangles[i]);

	// compute triangle scores
	float* triangle_scores = MESHOPT_ALLOC(&allocator, float, face_count);
	if (!triangle_scores)
		goto fail;

	for (size_t i = 0; i < face_count; ++i)
	{
		unsigned int a = indices[i * 3 + 0];
		unsigned int b = indices[i * 3 + 1];
		unsigned int c = indices[i * 3 + 2];

		triangle_scores[i] = vertex_scores[a] + vertex_scores[b] + vertex_scores[c];
	}

	unsigned int cache_holder[2 * (kCacheSizeMax + 4)];
	unsigned int* cache = cache_holder;
	unsigned int* cache_new = cache_holder + kCacheSizeMax + 4;
	size_t cache_count = 0;

	unsigned int current_triangle = 0;
	unsigned int input_cursor = 1;

	unsigned int output_triangle = 0;

	while (current_triangle != ~0u)
	{
		assert(output_triangle < face_count);

		unsigned int a = indices[current_triangle * 3 + 0];
		unsigned int b = indices[current_triangle * 3 + 1];
		unsigned int c = indices[current_triangle * 3 + 2];

		// output indices
		destination[output_triangle * 3 + 0] = a;
		destination[output_triangle * 3 + 1] = b;
		destination[output_triangle * 3 + 2] = c;
		output_triangle++;

		// update emitted flags
		emitted_flags[current_triangle] = true;
		triangle_scores[current_triangle] = 0;

		// new triangle
		size_t cache_write = 0;
		cache_new[cache_write++] = a;
		cache_new[cache_write++] = b;
		cache_new[cache_write++] = c;

		// old triangles
		for (size_t i = 0; i < cache_count; ++i)
		{
			unsigned int index = cache[i];

			cache_new[cache_write] = index;
			cache_write += (index != a) & (index != b) & (index != c);
		}

		unsigned int* cache_temp = cache;
		cache = cache_new, cache_new = cache_temp;
		cache_count = cache_write > cache_size ? cache_size : cache_write;

		// remove emitted triangle from adjacency data
		// this makes sure that we spend less time traversing these lists on subsequent iterations
		// live triangle counts are updated as a byproduct of these adjustments
		for (size_t k = 0; k < 3; ++k)
		{
			unsigned int index = indices[current_triangle * 3 + k];

			unsigned int* neighbors = &adjacency.data[0] + adjacency.offsets[index];
			size_t neighbors_size = adjacency.counts[index];

			for (size_t i = 0; i < neighbors_size; ++i)
			{
				unsigned int tri = neighbors[i];

				if (tri == current_triangle)
				{
					neighbors[i] = neighbors[neighbors_size - 1];
					adjacency.counts[index]--;
					break;
				}
			}
		}

		unsigned int best_triangle = ~0u;
		float best_score = 0;

		// update cache positions, vertex scores and triangle scores, and find next best triangle
		for (size_t i = 0; i < cache_write; ++i)
		{
			unsigned int index = cache[i];

			// no need to update scores if we are never going to use this vertex
			if (adjacency.counts[index] == 0)
				continue;

			int cache_position = i >= cache_size ? -1 : (int)i;

			// update vertex score
			float score = vertexScore(table, cache_position, live_triangles[index]);
			float score_diff = score - vertex_scores[index];

			vertex_scores[index] = score;

			// update scores of vertex triangles
			const unsigned int* neighbors_begin = &adjacency.data[0] + adjacency.offsets[index];
			const unsigned int* neighbors_end = neighbors_begin + adjacency.counts[index];

			for (const unsigned int* it = neighbors_begin; it != neighbors_end; ++it)
			{
				unsigned int tri = *it;
				assert(!emitted_flags[tri]);

				float tri_score = triangle_scores[tri] + score_diff;
				assert(tri_score > 0);

				best_triangle = best_score < tri_score ? tri : best_triangle;
				best_score = best_score < tri_score ? tri_score : best_score;

				triangle_scores[tri] = tri_score;
			}
		}

		// step through input triangles in order if we hit a dead-end
		current_triangle = best_triangle;

		if (current_triangle == ~0u)
		{
			current_triangle = getNextTriangleDeadEnd(&input_cursor, &emitted_flags[0], face_count);
		}
	}

	assert(input_cursor == face_count);
	assert(output_triangle == face_count);
	goto done;

fail:
	// allocation failure: leave the input order unchanged (indices may alias the in-place copy)
	if (destination != indices)
		memcpy(destination, indices, index_count * sizeof(unsigned int));

done:
	meshopt_arena_free_all(&allocator);
}

void meshopt_optimizeVertexCache(unsigned int* destination, const unsigned int* indices, size_t index_count, size_t vertex_count)
{
	meshopt_optimizeVertexCacheTable(destination, indices, index_count, vertex_count, &kVertexScoreTable);
}
