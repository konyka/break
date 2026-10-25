/* test_meshopt_c: invariants + bit-exact reference comparison for the pure C
 * port of meshoptimizer v1.3 (engine/external/meshopt_c).
 *
 * The expected table at the bottom was produced by building this same file with
 * -DMESHOPT_C_REFERENCE_DUMP and linking it against upstream meshoptimizer v1.3
 * C++ sources (see engine/external/meshopt_c/README.md for the exact commands).
 * Mesh generators use only IEEE basic operations (no libm transcendental calls)
 * so the inputs are identical on every compiler / CRT / optimization level. */
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meshopt_c/meshopt.h"

#ifndef MESHOPT_C_REFERENCE_DUMP
#include "test_framework.h"
#endif

/* ---- deterministic helpers ---- */

#define TM_PI 3.14159265358979323846

static double tm_sin(double x)
{
	double twopi = 2.0 * TM_PI;
	double k = (double)(long long)(x / twopi + (x >= 0 ? 0.5 : -0.5));
	x -= k * twopi;
	double x2 = x * x, term = x, sum = x;
	for (int n = 1; n <= 12; ++n)
	{
		term *= -x2 / (double)((2 * n) * (2 * n + 1));
		sum += term;
	}
	return sum;
}

static double tm_cos(double x)
{
	return tm_sin(x + TM_PI / 2);
}

static float tm_sqrtf_newton(float v)
{
	/* deterministic sqrt via Newton iterations in double (only used for normals) */
	if (v <= 0.f)
		return 0.f;
	double x = v > 1.0f ? (double)v : 1.0;
	for (int i = 0; i < 60; ++i)
		x = 0.5 * (x + (double)v / x);
	return (float)x;
}

static unsigned int g_lcg = 12345u;

static float tm_rand01(void)
{
	g_lcg = g_lcg * 1664525u + 1013904223u;
	return (float)(g_lcg >> 8) * (1.0f / 16777216.0f);
}

static uint64_t tm_fnv1a(const unsigned int* data, size_t count)
{
	uint64_t h = 1469598103934665603ull;
	for (size_t i = 0; i < count; ++i)
	{
		unsigned int v = data[i];
		for (int b = 0; b < 4; ++b)
		{
			h ^= (uint64_t)((v >> (8 * b)) & 0xffu);
			h *= 1099511628211ull;
		}
	}
	return h;
}

static unsigned int tm_float_bits(float f)
{
	unsigned int u;
	memcpy(&u, &f, sizeof(u));
	return u;
}

/* ---- meshes: 8 floats per vertex (position, normal, uv) ---- */

#define TM_STRIDE_FLOATS 8
#define TM_STRIDE (TM_STRIDE_FLOATS * sizeof(float))

typedef struct
{
	float* v;
	size_t vcount;
	unsigned int* idx;
	size_t icount;
	int open; /* has a geometric boundary */
} TestMesh;

static void tm_alloc(TestMesh* m, size_t vcount, size_t max_indices)
{
	m->v = (float*)calloc(vcount * TM_STRIDE_FLOATS, sizeof(float));
	m->vcount = vcount;
	m->idx = (unsigned int*)calloc(max_indices ? max_indices : 1, sizeof(unsigned int));
	m->icount = 0;
	m->open = 0;
}

static void tm_free(TestMesh* m)
{
	free(m->v);
	free(m->idx);
	memset(m, 0, sizeof(*m));
}

static void tm_set(TestMesh* m, size_t i, float px, float py, float pz, float nx, float ny, float nz, float u, float v)
{
	float* d = m->v + i * TM_STRIDE_FLOATS;
	d[0] = px, d[1] = py, d[2] = pz;
	d[3] = nx, d[4] = ny, d[5] = nz;
	d[6] = u, d[7] = v;
}

static void tm_tri(TestMesh* m, unsigned int a, unsigned int b, unsigned int c)
{
	m->idx[m->icount++] = a;
	m->idx[m->icount++] = b;
	m->idx[m->icount++] = c;
}

static void tm_make_sphere(TestMesh* m, int seg, int rings)
{
	tm_alloc(m, (size_t)(rings + 1) * (size_t)(seg + 1), (size_t)rings * (size_t)seg * 6);
	for (int r = 0; r <= rings; ++r)
		for (int s = 0; s <= seg; ++s)
		{
			double theta = TM_PI * r / rings, phi = 2.0 * TM_PI * s / seg;
			float x = (float)(tm_sin(theta) * tm_cos(phi));
			float y = (float)tm_cos(theta);
			float z = (float)(tm_sin(theta) * tm_sin(phi));
			tm_set(m, (size_t)r * (size_t)(seg + 1) + (size_t)s, x, y, z, x, y, z, (float)s / (float)seg, (float)r / (float)rings);
		}
	for (int r = 0; r < rings; ++r)
		for (int s = 0; s < seg; ++s)
		{
			unsigned int a = (unsigned int)(r * (seg + 1) + s);
			unsigned int b = a + (unsigned int)(seg + 1), c = b + 1, d = a + 1;
			if (r != rings - 1)
				tm_tri(m, a, b, c);
			if (r != 0)
				tm_tri(m, a, c, d);
		}
}

static void tm_make_torus(TestMesh* m, int nu, int nv)
{
	tm_alloc(m, (size_t)(nu + 1) * (size_t)(nv + 1), (size_t)nu * (size_t)nv * 6);
	for (int i = 0; i <= nu; ++i)
		for (int j = 0; j <= nv; ++j)
		{
			double u = 2.0 * TM_PI * i / nu, v = 2.0 * TM_PI * j / nv;
			double cu = tm_cos(u), su = tm_sin(u), cv = tm_cos(v), sv = tm_sin(v);
			double rr = 1.0 + 0.35 * cv;
			tm_set(m, (size_t)i * (size_t)(nv + 1) + (size_t)j, (float)(rr * cu), (float)(0.35 * sv), (float)(rr * su),
			    (float)(cv * cu), (float)sv, (float)(cv * su), (float)i / (float)nu, (float)j / (float)nv);
		}
	for (int i = 0; i < nu; ++i)
		for (int j = 0; j < nv; ++j)
		{
			unsigned int a = (unsigned int)(i * (nv + 1) + j);
			unsigned int b = a + (unsigned int)(nv + 1), c = b + 1, d = a + 1;
			tm_tri(m, a, b, c);
			tm_tri(m, a, c, d);
		}
}

/* height field grid over [0,1]^2; noise == 0 gives a flat grid */
static void tm_make_grid(TestMesh* m, int n, float noise, unsigned int seed)
{
	size_t w = (size_t)n + 1;
	tm_alloc(m, w * w, (size_t)n * (size_t)n * 6);
	m->open = 1;
	g_lcg = seed;
	float* h = (float*)calloc(w * w, sizeof(float));
	for (size_t j = 0; j < w; ++j)
		for (size_t i = 0; i < w; ++i)
		{
			float x = (float)i / (float)n, y = (float)j / (float)n;
			float bump = noise > 0 ? (float)(0.08 * tm_sin(3.0 * x) * tm_cos(2.0 * y)) : 0.f;
			h[j * w + i] = noise > 0 ? bump + (tm_rand01() - 0.5f) * noise : 0.f;
		}
	for (size_t j = 0; j < w; ++j)
		for (size_t i = 0; i < w; ++i)
		{
			float hl = h[j * w + (i > 0 ? i - 1 : i)], hr = h[j * w + (i + 1 < w ? i + 1 : i)];
			float hd = h[(j > 0 ? j - 1 : j) * w + i], hu = h[(j + 1 < w ? j + 1 : j) * w + i];
			float nx = (hl - hr) * (float)n * 0.5f, ny = (hd - hu) * (float)n * 0.5f, nz = 1.f;
			float len = tm_sqrtf_newton(nx * nx + ny * ny + nz * nz);
			float x = (float)i / (float)n, y = (float)j / (float)n;
			tm_set(m, j * w + i, x, y, h[j * w + i], nx / len, ny / len, nz / len, x, y);
		}
	free(h);
	for (size_t j = 0; j < (size_t)n; ++j)
		for (size_t i = 0; i < (size_t)n; ++i)
		{
			unsigned int a = (unsigned int)(j * w + i), b = a + 1, c = a + (unsigned int)w + 1, d = a + (unsigned int)w;
			tm_tri(m, a, b, c);
			tm_tri(m, a, c, d);
		}
}

static void tm_make_quad(TestMesh* m)
{
	tm_alloc(m, 4, 6);
	m->open = 1;
	tm_set(m, 0, 0, 0, 0, 0, 0, 1, 0, 0);
	tm_set(m, 1, 1, 0, 0, 0, 0, 1, 1, 0);
	tm_set(m, 2, 1, 1, 0, 0, 0, 1, 1, 1);
	tm_set(m, 3, 0, 1, 0, 0, 0, 1, 0, 1);
	tm_tri(m, 0, 1, 2);
	tm_tri(m, 0, 2, 3);
}

enum
{
	TM_MESH_SPHERE,
	TM_MESH_TORUS,
	TM_MESH_NOISY_GRID,
	TM_MESH_FLAT_GRID,
	TM_MESH_QUAD,
	TM_MESH_COUNT
};

static const char* const kMeshNames[TM_MESH_COUNT] = {"sphere32x16", "torus48x24", "noisygrid64", "flatgrid32", "quad2"};

static void tm_make_mesh(TestMesh* m, int which)
{
	switch (which)
	{
	case TM_MESH_SPHERE: tm_make_sphere(m, 32, 16); break;
	case TM_MESH_TORUS: tm_make_torus(m, 48, 24); break;
	case TM_MESH_NOISY_GRID: tm_make_grid(m, 64, 0.03f, 12345u); break;
	case TM_MESH_FLAT_GRID: tm_make_grid(m, 32, 0.f, 1u); break;
	default: tm_make_quad(m); break;
	}
}

/* ---- case table ---- */

enum
{
	TM_KIND_SIMPLIFY,
	TM_KIND_ATTR,
	TM_KIND_ATTR_LOCK,    /* vertex_lock: Lock on i%7==0, Priority on i%11==0 */
	TM_KIND_ATTR_PROTECT, /* vertex_lock: Protect on i%13==0 (with Permissive) */
	TM_KIND_SPARSE        /* first half of triangles, meshopt_SimplifySparse */
};

typedef struct
{
	int mesh;
	int kind;
	float ratio;
	float error;
	unsigned int options;
	int abs_error; /* target error multiplied by meshopt_simplifyScale */
} TestCase;

#define TM_CASES_PER_MESH 22
#define TM_CASE_COUNT (TM_CASES_PER_MESH * TM_MESH_COUNT)

static size_t tm_build_cases(TestCase* out)
{
	size_t n = 0;
	static const float ratios[2] = {0.5f, 0.25f};
	static const float errors[2] = {0.02f, 0.05f};
	static const unsigned int lock_opts[2] = {0, meshopt_SimplifyLockBorder};
	for (int m = 0; m < TM_MESH_COUNT; ++m)
	{
		for (int r = 0; r < 2; ++r)
			for (int e = 0; e < 2; ++e)
				for (int o = 0; o < 2; ++o)
					out[n++] = (TestCase){m, TM_KIND_SIMPLIFY, ratios[r], errors[e], lock_opts[o], 0};
		for (int r = 0; r < 2; ++r)
			for (int o = 0; o < 2; ++o)
				out[n++] = (TestCase){m, TM_KIND_ATTR, ratios[r], 0.05f, lock_opts[o], 0};
		out[n++] = (TestCase){m, TM_KIND_SIMPLIFY, 0.25f, 0.05f, meshopt_SimplifyErrorAbsolute, 1};
		out[n++] = (TestCase){m, TM_KIND_SIMPLIFY, 0.25f, 0.05f, meshopt_SimplifyPrune, 0};
		out[n++] = (TestCase){m, TM_KIND_SIMPLIFY, 0.25f, 0.05f, meshopt_SimplifyRegularize, 0};
		out[n++] = (TestCase){m, TM_KIND_SIMPLIFY, 0.25f, 0.05f, meshopt_SimplifyRegularizeLight, 0};
		out[n++] = (TestCase){m, TM_KIND_SIMPLIFY, 0.25f, 0.05f, meshopt_SimplifyPreserveFolds, 0};
		out[n++] = (TestCase){m, TM_KIND_ATTR_PROTECT, 0.25f, 0.05f, meshopt_SimplifyPermissive, 0};
		out[n++] = (TestCase){m, TM_KIND_ATTR, 0.25f, 0.05f, meshopt_SimplifyErrorClamped, 0};
		out[n++] = (TestCase){m, TM_KIND_ATTR_LOCK, 0.25f, 0.05f, 0, 0};
		out[n++] = (TestCase){m, TM_KIND_SPARSE, 0.5f, 0.05f, meshopt_SimplifySparse, 0};
		out[n++] = (TestCase){m, TM_KIND_SIMPLIFY, 0.f, 1.f, 0, 0};
	}
	return n;
}

typedef struct
{
	size_t count;
	unsigned int error_bits;
	uint64_t hash_simplify;
	uint64_t hash_vcache;
} TestResult;

static const float kAttrWeights[5] = {0.5f, 0.5f, 0.5f, 1.0f, 1.0f};

/* runs one case; dst/dst2 must hold mesh->icount indices */
static void tm_run_case(const TestMesh* mesh, const TestCase* c, unsigned int* dst, unsigned int* dst2, TestResult* res)
{
	const unsigned int* src = mesh->idx;
	size_t icount = mesh->icount;
	if (c->kind == TM_KIND_SPARSE)
		icount = (icount / 2) / 3 * 3;

	size_t target = (size_t)((float)icount * c->ratio) / 3 * 3;
	float target_error = c->error;
	if (c->abs_error)
		target_error = c->error * meshopt_simplifyScale(mesh->v, mesh->vcount, TM_STRIDE);

	unsigned char* lock = NULL;
	if (c->kind == TM_KIND_ATTR_LOCK || c->kind == TM_KIND_ATTR_PROTECT)
	{
		lock = (unsigned char*)calloc(mesh->vcount, 1);
		for (size_t i = 0; i < mesh->vcount; ++i)
		{
			if (c->kind == TM_KIND_ATTR_LOCK)
				lock[i] = (unsigned char)((i % 7 == 0 ? meshopt_SimplifyVertex_Lock : 0) | (i % 11 == 0 ? meshopt_SimplifyVertex_Priority : 0));
			else
				lock[i] = (unsigned char)(i % 13 == 0 ? meshopt_SimplifyVertex_Protect : 0);
		}
	}

	float err = -1.f;
	size_t count;
	if (c->kind == TM_KIND_SIMPLIFY || c->kind == TM_KIND_SPARSE)
		count = meshopt_simplify(dst, src, icount, mesh->v, mesh->vcount, TM_STRIDE, target, target_error, c->options, &err);
	else
		count = meshopt_simplifyWithAttributes(dst, src, icount, mesh->v, mesh->vcount, TM_STRIDE, mesh->v + 3, TM_STRIDE,
		    kAttrWeights, 5, lock, target, target_error, c->options, &err);
	free(lock);

	meshopt_optimizeVertexCache(dst2, dst, count, mesh->vcount);

	res->count = count;
	res->error_bits = tm_float_bits(err);
	res->hash_simplify = tm_fnv1a(dst, count);
	res->hash_vcache = tm_fnv1a(dst2, count);
}

#ifdef MESHOPT_C_REFERENCE_DUMP

int main(void)
{
	static TestCase cases[TM_CASE_COUNT];
	size_t n = tm_build_cases(cases);
	printf("static const unsigned int kExpectedScaleBits[TM_MESH_COUNT] = {");
	for (int m = 0; m < TM_MESH_COUNT; ++m)
	{
		TestMesh mesh;
		tm_make_mesh(&mesh, m);
		printf("%s0x%08xu", m ? ", " : "", tm_float_bits(meshopt_simplifyScale(mesh.v, mesh.vcount, TM_STRIDE)));
		tm_free(&mesh);
	}
	printf("};\n\nstatic const TestResult kExpected[TM_CASE_COUNT] = {\n");
	int cur = -1;
	TestMesh mesh = {0};
	for (size_t i = 0; i < n; ++i)
	{
		if (cases[i].mesh != cur)
		{
			if (cur >= 0)
				tm_free(&mesh);
			cur = cases[i].mesh;
			tm_make_mesh(&mesh, cur);
			printf("    /* %s: %zu vertices, %zu triangles */\n", kMeshNames[cur], mesh.vcount, mesh.icount / 3);
		}
		unsigned int* dst = (unsigned int*)malloc(mesh.icount * sizeof(unsigned int));
		unsigned int* dst2 = (unsigned int*)malloc(mesh.icount * sizeof(unsigned int));
		TestResult r;
		tm_run_case(&mesh, &cases[i], dst, dst2, &r);
		float e;
		memcpy(&e, &r.error_bits, sizeof(e));
		printf("    {%zuu, 0x%08xu, 0x%016llxull, 0x%016llxull}, /* %3zu kind=%d ratio=%.2f err=%.2f opt=0x%x -> %g */\n", r.count, r.error_bits,
		    (unsigned long long)r.hash_simplify, (unsigned long long)r.hash_vcache, i, cases[i].kind, (double)cases[i].ratio, (double)cases[i].error,
		    cases[i].options, (double)e);
		free(dst);
		free(dst2);
	}
	tm_free(&mesh);
	printf("};\n");
	return 0;
}

#else

/* Generated by the MESHOPT_C_REFERENCE_DUMP build of this file linked against upstream
 * meshoptimizer v1.3 C++ (commit 9e1f07b159d3cb777f1c67ed31fc11fd117986f4), clang++ -O2.
 * The C port reproduced it byte-for-byte at -O0, -O2 and -O3 -DNDEBUG. */
static const unsigned int kExpectedScaleBits[TM_MESH_COUNT] = {0x40000000u, 0x402ccccdu, 0x3f800000u, 0x3f800000u, 0x3f800000u};

static const TestResult kExpected[TM_CASE_COUNT] = {
    /* sphere32x16: 561 vertices, 960 triangles */
    {1440u, 0x3c5c836eu, 0x37b7bbd04cbb56b1ull, 0x492b0f4cde5f8f39ull}, /*   0 kind=0 ratio=0.50 err=0.02 opt=0x0 -> 0.0134591 */
    {1440u, 0x3c5c836eu, 0x37b7bbd04cbb56b1ull, 0x492b0f4cde5f8f39ull}, /*   1 kind=0 ratio=0.50 err=0.02 opt=0x1 -> 0.0134591 */
    {1440u, 0x3c5c836eu, 0x37b7bbd04cbb56b1ull, 0x492b0f4cde5f8f39ull}, /*   2 kind=0 ratio=0.50 err=0.05 opt=0x0 -> 0.0134591 */
    {1440u, 0x3c5c836eu, 0x37b7bbd04cbb56b1ull, 0x492b0f4cde5f8f39ull}, /*   3 kind=0 ratio=0.50 err=0.05 opt=0x1 -> 0.0134591 */
    {720u, 0x3c997b2eu, 0xa56886b7a06d0b78ull, 0xcbebbb5a5a5bd8a4ull}, /*   4 kind=0 ratio=0.25 err=0.02 opt=0x0 -> 0.0187355 */
    {720u, 0x3c997b2eu, 0x431f83d28598225bull, 0xebb61aff1307c753ull}, /*   5 kind=0 ratio=0.25 err=0.02 opt=0x1 -> 0.0187355 */
    {717u, 0x3d062a02u, 0xf7fab046e8407ac7ull, 0xa2482d703b480723ull}, /*   6 kind=0 ratio=0.25 err=0.05 opt=0x0 -> 0.0327549 */
    {720u, 0x3d062a02u, 0xebd863a7e8bc69f8ull, 0xeed69bbb84a79d08ull}, /*   7 kind=0 ratio=0.25 err=0.05 opt=0x1 -> 0.0327549 */
    {1437u, 0x3c5fa84fu, 0x4d99287d648cbbe0ull, 0x69d8d2181b1129f0ull}, /*   8 kind=1 ratio=0.50 err=0.05 opt=0x0 -> 0.013651 */
    {1440u, 0x3c5fa84fu, 0x4dc854e2cb9d0b30ull, 0x90498e578f0b9764ull}, /*   9 kind=1 ratio=0.50 err=0.05 opt=0x1 -> 0.013651 */
    {717u, 0x3d10f000u, 0xfc54031efff05d4cull, 0x59c1b1faa3fd68c0ull}, /*  10 kind=1 ratio=0.25 err=0.05 opt=0x0 -> 0.0353851 */
    {720u, 0x3d10f000u, 0xb1250fa61e6cdbe1ull, 0x7e38428b3222fa69ull}, /*  11 kind=1 ratio=0.25 err=0.05 opt=0x1 -> 0.0353851 */
    {717u, 0x3d862a02u, 0xf7fab046e8407ac7ull, 0xa2482d703b480723ull}, /*  12 kind=0 ratio=0.25 err=0.05 opt=0x4 -> 0.0655098 */
    {717u, 0x3d062a02u, 0xf7fab046e8407ac7ull, 0xa2482d703b480723ull}, /*  13 kind=0 ratio=0.25 err=0.05 opt=0x8 -> 0.0327549 */
    {717u, 0x3d47305fu, 0xa83f84b58c07b573ull, 0x9da80f3d416b4c07ull}, /*  14 kind=0 ratio=0.25 err=0.05 opt=0x10 -> 0.0486301 */
    {717u, 0x3cf05f1du, 0x5ce958e69bea7244ull, 0x0b2881591740609cull}, /*  15 kind=0 ratio=0.25 err=0.05 opt=0x40 -> 0.0293422 */
    {717u, 0x3d062a02u, 0xf7fab046e8407ac7ull, 0xa2482d703b480723ull}, /*  16 kind=0 ratio=0.25 err=0.05 opt=0x80 -> 0.0327549 */
    {720u, 0x3cd26bceu, 0x5ee6522c91572886ull, 0x2c06d889f79fc3baull}, /*  17 kind=3 ratio=0.25 err=0.05 opt=0x20 -> 0.0256862 */
    {717u, 0x3d10f000u, 0xfc54031efff05d4cull, 0x59c1b1faa3fd68c0ull}, /*  18 kind=1 ratio=0.25 err=0.05 opt=0x100 -> 0.0353851 */
    {720u, 0x3d4499e4u, 0x149e495a3eae9900ull, 0x7c8892204e5e796cull}, /*  19 kind=2 ratio=0.25 err=0.05 opt=0x0 -> 0.0479983 */
    {720u, 0x3c58b829u, 0x60a20d8c69bdd8e1ull, 0x3caf3839fa7ea91dull}, /*  20 kind=4 ratio=0.50 err=0.05 opt=0x2 -> 0.0132275 */
    {195u, 0x3f2c540du, 0x4bb854301ecd68e5ull, 0x34333f7b2073872dull}, /*  21 kind=0 ratio=0.00 err=1.00 opt=0x0 -> 0.673158 */
    /* torus48x24: 1225 vertices, 2304 triangles */
    {3456u, 0x3b9fef2du, 0xae95edbf996dfe50ull, 0xcb5218bc79e5bdd4ull}, /*  22 kind=0 ratio=0.50 err=0.02 opt=0x0 -> 0.00488081 */
    {3456u, 0x3b9fef2du, 0xae95edbf996dfe50ull, 0xcb5218bc79e5bdd4ull}, /*  23 kind=0 ratio=0.50 err=0.02 opt=0x1 -> 0.00488081 */
    {3456u, 0x3b9fef2du, 0xae95edbf996dfe50ull, 0xcb5218bc79e5bdd4ull}, /*  24 kind=0 ratio=0.50 err=0.05 opt=0x0 -> 0.00488081 */
    {3456u, 0x3b9fef2du, 0xae95edbf996dfe50ull, 0xcb5218bc79e5bdd4ull}, /*  25 kind=0 ratio=0.50 err=0.05 opt=0x1 -> 0.00488081 */
    {1728u, 0x3bf221bau, 0x04dd0d4e8fb0abdfull, 0x017219e858abf79full}, /*  26 kind=0 ratio=0.25 err=0.02 opt=0x0 -> 0.00738927 */
    {1728u, 0x3bf221bau, 0x04dd0d4e8fb0abdfull, 0x017219e858abf79full}, /*  27 kind=0 ratio=0.25 err=0.02 opt=0x1 -> 0.00738927 */
    {1728u, 0x3bf221bau, 0x04dd0d4e8fb0abdfull, 0x017219e858abf79full}, /*  28 kind=0 ratio=0.25 err=0.05 opt=0x0 -> 0.00738927 */
    {1728u, 0x3bf221bau, 0x04dd0d4e8fb0abdfull, 0x017219e858abf79full}, /*  29 kind=0 ratio=0.25 err=0.05 opt=0x1 -> 0.00738927 */
    {3456u, 0x3bbf68deu, 0xa3b1585e0659192full, 0xf1e144afdc215e1bull}, /*  30 kind=1 ratio=0.50 err=0.05 opt=0x0 -> 0.00584136 */
    {3456u, 0x3bbf68deu, 0xa3b1585e0659192full, 0xf1e144afdc215e1bull}, /*  31 kind=1 ratio=0.50 err=0.05 opt=0x1 -> 0.00584136 */
    {1728u, 0x3c09cc63u, 0x0cb6109f03fb8d2full, 0x46598541f2aba783ull}, /*  32 kind=1 ratio=0.25 err=0.05 opt=0x0 -> 0.00841055 */
    {1728u, 0x3c09cc63u, 0x0cb6109f03fb8d2full, 0x46598541f2aba783ull}, /*  33 kind=1 ratio=0.25 err=0.05 opt=0x1 -> 0.00841055 */
    {1728u, 0x3ca3705eu, 0x04dd0d4e8fb0abdfull, 0x017219e858abf79full}, /*  34 kind=0 ratio=0.25 err=0.05 opt=0x4 -> 0.019951 */
    {1728u, 0x3bf221bau, 0x04dd0d4e8fb0abdfull, 0x017219e858abf79full}, /*  35 kind=0 ratio=0.25 err=0.05 opt=0x8 -> 0.00738927 */
    {1728u, 0x3caf4526u, 0x93f1573925eab394ull, 0xcc2f861cf736841cull}, /*  36 kind=0 ratio=0.25 err=0.05 opt=0x10 -> 0.0213953 */
    {1728u, 0x3c1ebef4u, 0x6b65dc06e03d5417ull, 0xff1df9472ce69a5full}, /*  37 kind=0 ratio=0.25 err=0.05 opt=0x40 -> 0.00968908 */
    {1728u, 0x3bf221bau, 0x04dd0d4e8fb0abdfull, 0x017219e858abf79full}, /*  38 kind=0 ratio=0.25 err=0.05 opt=0x80 -> 0.00738927 */
    {1728u, 0x3c09cc63u, 0xcfa7e24bcfca0278ull, 0xfdeb27b3229f44fcull}, /*  39 kind=3 ratio=0.25 err=0.05 opt=0x20 -> 0.00841055 */
    {1728u, 0x3c09cc63u, 0x0cb6109f03fb8d2full, 0x46598541f2aba783ull}, /*  40 kind=1 ratio=0.25 err=0.05 opt=0x100 -> 0.00841055 */
    {1728u, 0x3c5d1522u, 0x418563176289f9a4ull, 0xed90b846c9088a48ull}, /*  41 kind=2 ratio=0.25 err=0.05 opt=0x0 -> 0.0134938 */
    {1728u, 0x3b9ffb38u, 0xa6730afcca9c2a29ull, 0x9e0e44bcb4fb402dull}, /*  42 kind=4 ratio=0.50 err=0.05 opt=0x2 -> 0.00488224 */
    {6u, 0x3efb361du, 0x04c43bac1d402fa3ull, 0x04c43bac1d402fa3ull}, /*  43 kind=0 ratio=0.00 err=1.00 opt=0x0 -> 0.490647 */
    /* noisygrid64: 4225 vertices, 8192 triangles */
    {12288u, 0x3beafdfcu, 0x035fb8002ad2d4cdull, 0x3e6487b4cd85bd61ull}, /*  44 kind=0 ratio=0.50 err=0.02 opt=0x0 -> 0.00717139 */
    {12288u, 0x3bef7612u, 0x7dd0ee6a0fa4c552ull, 0x1f7488e8d86cf9deull}, /*  45 kind=0 ratio=0.50 err=0.02 opt=0x1 -> 0.00730778 */
    {12288u, 0x3beafdfcu, 0x035fb8002ad2d4cdull, 0x3e6487b4cd85bd61ull}, /*  46 kind=0 ratio=0.50 err=0.05 opt=0x0 -> 0.00717139 */
    {12288u, 0x3bef7612u, 0x7dd0ee6a0fa4c552ull, 0x1f7488e8d86cf9deull}, /*  47 kind=0 ratio=0.50 err=0.05 opt=0x1 -> 0.00730778 */
    {6144u, 0x3c431ac0u, 0xce517d3f81b86adaull, 0x525350737bdabb6aull}, /*  48 kind=0 ratio=0.25 err=0.02 opt=0x0 -> 0.0119082 */
    {6144u, 0x3c4a5d80u, 0x31651fd5aa16e961ull, 0xe5d5934a20401101ull}, /*  49 kind=0 ratio=0.25 err=0.02 opt=0x1 -> 0.0123514 */
    {6144u, 0x3c431ac0u, 0xce517d3f81b86adaull, 0x525350737bdabb6aull}, /*  50 kind=0 ratio=0.25 err=0.05 opt=0x0 -> 0.0119082 */
    {6144u, 0x3c4a5d80u, 0x31651fd5aa16e961ull, 0xe5d5934a20401101ull}, /*  51 kind=0 ratio=0.25 err=0.05 opt=0x1 -> 0.0123514 */
    {12288u, 0x3c87aefcu, 0xb5b37bfa31659357ull, 0xde5500035da5cb8bull}, /*  52 kind=1 ratio=0.50 err=0.05 opt=0x0 -> 0.0165629 */
    {12288u, 0x3c8acba6u, 0x238f97de6c5471dfull, 0x59c0815de0b5645full}, /*  53 kind=1 ratio=0.50 err=0.05 opt=0x1 -> 0.0169428 */
    {6144u, 0x3ce23fadu, 0xd3f7eae5eeac63bcull, 0xc3e9d007ebbc8fa4ull}, /*  54 kind=1 ratio=0.25 err=0.05 opt=0x0 -> 0.0276183 */
    {6144u, 0x3ce5dd45u, 0x8869ca9667d54c13ull, 0xffbfb38a6eaeb2d3ull}, /*  55 kind=1 ratio=0.25 err=0.05 opt=0x1 -> 0.0280596 */
    {6144u, 0x3c431ac0u, 0xce517d3f81b86adaull, 0x525350737bdabb6aull}, /*  56 kind=0 ratio=0.25 err=0.05 opt=0x4 -> 0.0119082 */
    {6144u, 0x3c431ac0u, 0xce517d3f81b86adaull, 0x525350737bdabb6aull}, /*  57 kind=0 ratio=0.25 err=0.05 opt=0x8 -> 0.0119082 */
    {6144u, 0x3c7f7209u, 0x8a12f57322400a29ull, 0x0ac48478c6f346b1ull}, /*  58 kind=0 ratio=0.25 err=0.05 opt=0x10 -> 0.0155912 */
    {6144u, 0x3c4a5fdfu, 0xc3e6325b6c412673ull, 0x8e2e6d0a8877d85full}, /*  59 kind=0 ratio=0.25 err=0.05 opt=0x40 -> 0.012352 */
    {6144u, 0x3c431ac0u, 0xce517d3f81b86adaull, 0x525350737bdabb6aull}, /*  60 kind=0 ratio=0.25 err=0.05 opt=0x80 -> 0.0119082 */
    {6144u, 0x3ce23fadu, 0xd3f7eae5eeac63bcull, 0xc3e9d007ebbc8fa4ull}, /*  61 kind=3 ratio=0.25 err=0.05 opt=0x20 -> 0.0276183 */
    {6144u, 0x3ce23fadu, 0xd3f7eae5eeac63bcull, 0xc3e9d007ebbc8fa4ull}, /*  62 kind=1 ratio=0.25 err=0.05 opt=0x100 -> 0.0276183 */
    {6144u, 0x3cf2f99bu, 0x5eb3291633ec145aull, 0xcb2c2fa914651a36ull}, /*  63 kind=2 ratio=0.25 err=0.05 opt=0x0 -> 0.02966 */
    {6141u, 0x3bef5d19u, 0xd27ad4eb8acc3271ull, 0xa21fc9888513a561ull}, /*  64 kind=4 ratio=0.50 err=0.05 opt=0x2 -> 0.0073048 */
    {0u, 0x3ed6d0d1u, 0x14650fb0739d0383ull, 0x14650fb0739d0383ull}, /*  65 kind=0 ratio=0.00 err=1.00 opt=0x0 -> 0.419562 */
    /* flatgrid32: 1089 vertices, 2048 triangles */
    {3069u, 0x3725ce9fu, 0x3ceaf31f671b6e17ull, 0xb1f8ad25ccd8c563ull}, /*  66 kind=0 ratio=0.50 err=0.02 opt=0x0 -> 9.88287e-06 */
    {3072u, 0x374b0e7fu, 0xbb3ea7bc55b6b5baull, 0x495d250f106839feull}, /*  67 kind=0 ratio=0.50 err=0.02 opt=0x1 -> 1.21031e-05 */
    {3069u, 0x3725ce9fu, 0x3ceaf31f671b6e17ull, 0xb1f8ad25ccd8c563ull}, /*  68 kind=0 ratio=0.50 err=0.05 opt=0x0 -> 9.88287e-06 */
    {3072u, 0x374b0e7fu, 0xbb3ea7bc55b6b5baull, 0x495d250f106839feull}, /*  69 kind=0 ratio=0.50 err=0.05 opt=0x1 -> 1.21031e-05 */
    {1533u, 0x374b11ddu, 0x2c44e32909b3bf81ull, 0x0f742f2ea01115c9ull}, /*  70 kind=0 ratio=0.25 err=0.02 opt=0x0 -> 1.21039e-05 */
    {1536u, 0x378f9529u, 0x9c1480d819e9d809ull, 0x89c5912f0603cfc5ull}, /*  71 kind=0 ratio=0.25 err=0.02 opt=0x1 -> 1.71164e-05 */
    {1533u, 0x374b11ddu, 0x2c44e32909b3bf81ull, 0x0f742f2ea01115c9ull}, /*  72 kind=0 ratio=0.25 err=0.05 opt=0x0 -> 1.21039e-05 */
    {1536u, 0x378f9529u, 0x9c1480d819e9d809ull, 0x89c5912f0603cfc5ull}, /*  73 kind=0 ratio=0.25 err=0.05 opt=0x1 -> 1.71164e-05 */
    {3069u, 0x3725ce9fu, 0x3ceaf31f671b6e17ull, 0xb1f8ad25ccd8c563ull}, /*  74 kind=1 ratio=0.50 err=0.05 opt=0x0 -> 9.88287e-06 */
    {3072u, 0x374b0e7fu, 0xbb3ea7bc55b6b5baull, 0x495d250f106839feull}, /*  75 kind=1 ratio=0.50 err=0.05 opt=0x1 -> 1.21031e-05 */
    {1533u, 0x374b11ddu, 0x2c44e32909b3bf81ull, 0x0f742f2ea01115c9ull}, /*  76 kind=1 ratio=0.25 err=0.05 opt=0x0 -> 1.21039e-05 */
    {1536u, 0x378f9529u, 0x9c1480d819e9d809ull, 0x89c5912f0603cfc5ull}, /*  77 kind=1 ratio=0.25 err=0.05 opt=0x1 -> 1.71164e-05 */
    {1533u, 0x374b11ddu, 0x2c44e32909b3bf81ull, 0x0f742f2ea01115c9ull}, /*  78 kind=0 ratio=0.25 err=0.05 opt=0x4 -> 1.21039e-05 */
    {1533u, 0x374b11ddu, 0x2c44e32909b3bf81ull, 0x0f742f2ea01115c9ull}, /*  79 kind=0 ratio=0.25 err=0.05 opt=0x8 -> 1.21039e-05 */
    {1533u, 0x3c3d1720u, 0x70df3cb77756cd46ull, 0x79d12b900adb154aull}, /*  80 kind=0 ratio=0.25 err=0.05 opt=0x10 -> 0.0115412 */
    {1536u, 0x3b901806u, 0x7f6e2d3a9fa229f8ull, 0x7d41c185dd78b448ull}, /*  81 kind=0 ratio=0.25 err=0.05 opt=0x40 -> 0.0043974 */
    {1533u, 0x374b11ddu, 0x2c44e32909b3bf81ull, 0x0f742f2ea01115c9ull}, /*  82 kind=0 ratio=0.25 err=0.05 opt=0x80 -> 1.21039e-05 */
    {1533u, 0x374b11ddu, 0x2c44e32909b3bf81ull, 0x0f742f2ea01115c9ull}, /*  83 kind=3 ratio=0.25 err=0.05 opt=0x20 -> 1.21039e-05 */
    {1533u, 0x374b11ddu, 0x2c44e32909b3bf81ull, 0x0f742f2ea01115c9ull}, /*  84 kind=1 ratio=0.25 err=0.05 opt=0x100 -> 1.21039e-05 */
    {1536u, 0x378f95cfu, 0xae62d02b255f7575ull, 0x62abfaf92198ff05ull}, /*  85 kind=2 ratio=0.25 err=0.05 opt=0x0 -> 1.71167e-05 */
    {1536u, 0x3725ce3cu, 0x555775eafa59d204ull, 0x4be5d912ba01c178ull}, /*  86 kind=4 ratio=0.50 err=0.05 opt=0x2 -> 9.88278e-06 */
    {0u, 0x3eb29b28u, 0x14650fb0739d0383ull, 0x14650fb0739d0383ull}, /*  87 kind=0 ratio=0.00 err=1.00 opt=0x0 -> 0.34884 */
    /* quad2: 4 vertices, 2 triangles */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  88 kind=0 ratio=0.50 err=0.02 opt=0x0 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  89 kind=0 ratio=0.50 err=0.02 opt=0x1 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  90 kind=0 ratio=0.50 err=0.05 opt=0x0 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  91 kind=0 ratio=0.50 err=0.05 opt=0x1 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  92 kind=0 ratio=0.25 err=0.02 opt=0x0 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  93 kind=0 ratio=0.25 err=0.02 opt=0x1 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  94 kind=0 ratio=0.25 err=0.05 opt=0x0 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  95 kind=0 ratio=0.25 err=0.05 opt=0x1 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  96 kind=1 ratio=0.50 err=0.05 opt=0x0 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  97 kind=1 ratio=0.50 err=0.05 opt=0x1 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  98 kind=1 ratio=0.25 err=0.05 opt=0x0 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /*  99 kind=1 ratio=0.25 err=0.05 opt=0x1 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /* 100 kind=0 ratio=0.25 err=0.05 opt=0x4 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /* 101 kind=0 ratio=0.25 err=0.05 opt=0x8 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /* 102 kind=0 ratio=0.25 err=0.05 opt=0x10 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /* 103 kind=0 ratio=0.25 err=0.05 opt=0x40 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /* 104 kind=0 ratio=0.25 err=0.05 opt=0x80 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /* 105 kind=3 ratio=0.25 err=0.05 opt=0x20 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /* 106 kind=1 ratio=0.25 err=0.05 opt=0x100 -> 0 */
    {6u, 0x00000000u, 0xf624d74fecb64101ull, 0xf624d74fecb64101ull}, /* 107 kind=2 ratio=0.25 err=0.05 opt=0x0 -> 0 */
    {3u, 0x00000000u, 0x6437c9a572635250ull, 0x6437c9a572635250ull}, /* 108 kind=4 ratio=0.50 err=0.05 opt=0x2 -> 0 */
    {0u, 0x3f2c985du, 0x14650fb0739d0383ull, 0x14650fb0739d0383ull}, /* 109 kind=0 ratio=0.00 err=1.00 opt=0x0 -> 0.6742 */
};

/* ---- invariant helpers ---- */

static int tm_check_indices(const unsigned int* idx, size_t count, size_t vcount)
{
	if (count % 3 != 0)
		return 0;
	for (size_t i = 0; i < count; i += 3)
	{
		unsigned int a = idx[i], b = idx[i + 1], c = idx[i + 2];
		if (a >= vcount || b >= vcount || c >= vcount)
			return 0;
		if (a == b || b == c || a == c)
			return 0;
	}
	return 1;
}

static int tm_cmp_tri(const void* l, const void* r)
{
	const unsigned int* a = (const unsigned int*)l;
	const unsigned int* b = (const unsigned int*)r;
	for (int k = 0; k < 3; ++k)
		if (a[k] != b[k])
			return a[k] < b[k] ? -1 : 1;
	return 0;
}

/* sorted copy of the triangles, each rotated so the smallest index comes first (winding kept) */
static unsigned int* tm_canonical_tris(const unsigned int* idx, size_t count)
{
	unsigned int* t = (unsigned int*)malloc((count ? count : 1) * sizeof(unsigned int));
	for (size_t i = 0; i < count; i += 3)
	{
		unsigned int a = idx[i], b = idx[i + 1], c = idx[i + 2];
		if (b < a && b < c)
			t[i] = b, t[i + 1] = c, t[i + 2] = a;
		else if (c < a && c < b)
			t[i] = c, t[i + 1] = a, t[i + 2] = b;
		else
			t[i] = a, t[i + 1] = b, t[i + 2] = c;
	}
	qsort(t, count / 3, 3 * sizeof(unsigned int), tm_cmp_tri);
	return t;
}

static int tm_is_boundary(const TestMesh* m, size_t v)
{
	const float* p = m->v + v * TM_STRIDE_FLOATS;
	return p[0] == 0.f || p[0] == 1.f || p[1] == 0.f || p[1] == 1.f;
}

TEST(case_table_shape)
{
	static TestCase cases[TM_CASE_COUNT];
	ASSERT_EQ(tm_build_cases(cases), (size_t)TM_CASE_COUNT);
	ASSERT_EQ(sizeof(kExpected) / sizeof(kExpected[0]), (size_t)TM_CASE_COUNT);
}

TEST(option_values_match_upstream)
{
	ASSERT_EQ((int)meshopt_SimplifyLockBorder, 1);
	ASSERT_EQ((int)meshopt_SimplifySparse, 2);
	ASSERT_EQ((int)meshopt_SimplifyErrorAbsolute, 4);
	ASSERT_EQ((int)meshopt_SimplifyPrune, 8);
	ASSERT_EQ((int)meshopt_SimplifyRegularize, 16);
	ASSERT_EQ((int)meshopt_SimplifyPermissive, 32);
	ASSERT_EQ((int)meshopt_SimplifyRegularizeLight, 64);
	ASSERT_EQ((int)meshopt_SimplifyPreserveFolds, 128);
	ASSERT_EQ((int)meshopt_SimplifyErrorClamped, 256);
	ASSERT_EQ((int)meshopt_SimplifyVertex_Lock, 1);
	ASSERT_EQ((int)meshopt_SimplifyVertex_Protect, 2);
	ASSERT_EQ((int)meshopt_SimplifyVertex_Priority, 4);
	ASSERT_EQ(MESHOPTIMIZER_VERSION, 1030);
}

TEST(simplify_scale_matches_upstream)
{
	for (int m = 0; m < TM_MESH_COUNT; ++m)
	{
		TestMesh mesh;
		tm_make_mesh(&mesh, m);
		unsigned int bits = tm_float_bits(meshopt_simplifyScale(mesh.v, mesh.vcount, TM_STRIDE));
		tm_free(&mesh);
		if (bits != kExpectedScaleBits[m])
			printf("\n    scale mismatch %s: got 0x%08x want 0x%08x", kMeshNames[m], bits, kExpectedScaleBits[m]);
		ASSERT_EQ(bits, kExpectedScaleBits[m]);
	}
}

/* runs every case, checks invariants and compares with the upstream table */
TEST(simplify_invariants_and_reference)
{
	static TestCase cases[TM_CASE_COUNT];
	size_t n = tm_build_cases(cases);
	int mismatches = 0, invariant_failures = 0;

	for (int m = 0; m < TM_MESH_COUNT; ++m)
	{
		TestMesh mesh;
		tm_make_mesh(&mesh, m);
		unsigned int* dst = (unsigned int*)malloc(mesh.icount * sizeof(unsigned int));
		unsigned int* dst2 = (unsigned int*)malloc(mesh.icount * sizeof(unsigned int));

		for (size_t i = 0; i < n; ++i)
		{
			const TestCase* c = &cases[i];
			if (c->mesh != m)
				continue;

			TestResult r;
			tm_run_case(&mesh, c, dst, dst2, &r);

			size_t icount = c->kind == TM_KIND_SPARSE ? (mesh.icount / 2) / 3 * 3 : mesh.icount;
			float err;
			memcpy(&err, &r.error_bits, sizeof(err));

			int ok = tm_check_indices(dst, r.count, mesh.vcount) && r.count <= icount && err >= 0.f && err == err;

			/* vertex cache output must be a permutation of the simplified triangles */
			unsigned int* ta = tm_canonical_tris(dst, r.count);
			unsigned int* tb = tm_canonical_tris(dst2, r.count);
			ok = ok && memcmp(ta, tb, r.count * sizeof(unsigned int)) == 0;
			free(ta);
			free(tb);

			if (!ok)
			{
				printf("\n    invariant failure: case %zu (%s)", i, kMeshNames[m]);
				invariant_failures++;
			}

			const TestResult* e = &kExpected[i];
			if (r.count != e->count || r.error_bits != e->error_bits || r.hash_simplify != e->hash_simplify || r.hash_vcache != e->hash_vcache)
			{
				printf("\n    reference mismatch: case %zu (%s kind=%d opt=0x%x): count %zu/%zu err 0x%08x/0x%08x hash %016llx/%016llx vc %016llx/%016llx", i,
				    kMeshNames[m], c->kind, c->options, r.count, e->count, r.error_bits, e->error_bits, (unsigned long long)r.hash_simplify,
				    (unsigned long long)e->hash_simplify, (unsigned long long)r.hash_vcache, (unsigned long long)e->hash_vcache);
				mismatches++;
			}
		}

		free(dst);
		free(dst2);
		tm_free(&mesh);
	}

	ASSERT_EQ(invariant_failures, 0);
	ASSERT_EQ(mismatches, 0);
}

/* output size must not grow as the target shrinks */
TEST(simplify_monotonic_in_target)
{
	static const float ratios[4] = {0.75f, 0.5f, 0.25f, 0.1f};
	for (int m = 0; m < TM_MESH_COUNT; ++m)
	{
		TestMesh mesh;
		tm_make_mesh(&mesh, m);
		unsigned int* dst = (unsigned int*)malloc(mesh.icount * sizeof(unsigned int));
		for (int o = 0; o < 2; ++o)
		{
			size_t prev = mesh.icount;
			for (int r = 0; r < 4; ++r)
			{
				size_t target = (size_t)((float)mesh.icount * ratios[r]) / 3 * 3;
				float err = -1.f;
				size_t count = meshopt_simplify(dst, mesh.idx, mesh.icount, mesh.v, mesh.vcount, TM_STRIDE, target, 0.05f,
				    o ? meshopt_SimplifyLockBorder : 0, &err);
				ASSERT_TRUE(count <= prev);
				ASSERT_TRUE(err >= 0.f);
				ASSERT_TRUE(tm_check_indices(dst, count, mesh.vcount));
				prev = count;
			}
		}
		free(dst);
		tm_free(&mesh);
	}
}

/* LockBorder: every boundary vertex referenced by the input is still referenced by the output */
TEST(lock_border_preserves_boundary)
{
	static const int meshes[2] = {TM_MESH_FLAT_GRID, TM_MESH_NOISY_GRID};
	for (int mi = 0; mi < 2; ++mi)
	{
		TestMesh mesh;
		tm_make_mesh(&mesh, meshes[mi]);
		unsigned int* dst = (unsigned int*)malloc(mesh.icount * sizeof(unsigned int));
		unsigned char* used = (unsigned char*)malloc(mesh.vcount);

		for (int attr = 0; attr < 2; ++attr)
		{
			size_t target = mesh.icount / 4 / 3 * 3;
			float err = -1.f;
			size_t count = attr ? meshopt_simplifyWithAttributes(dst, mesh.idx, mesh.icount, mesh.v, mesh.vcount, TM_STRIDE, mesh.v + 3, TM_STRIDE,
			                          kAttrWeights, 5, NULL, target, 0.05f, meshopt_SimplifyLockBorder, &err)
			                    : meshopt_simplify(dst, mesh.idx, mesh.icount, mesh.v, mesh.vcount, TM_STRIDE, target, 0.05f, meshopt_SimplifyLockBorder, &err);
			ASSERT_TRUE(count > 0 && count < mesh.icount);

			memset(used, 0, mesh.vcount);
			for (size_t i = 0; i < count; ++i)
				used[dst[i]] = 1;

			size_t boundary = 0;
			for (size_t v = 0; v < mesh.vcount; ++v)
				if (tm_is_boundary(&mesh, v))
				{
					boundary++;
					ASSERT_TRUE(used[v]);
				}
			ASSERT_TRUE(boundary > 0);

			/* without the lock, the same reduction must drop at least one boundary vertex (proves the test can fail) */
			count = meshopt_simplify(dst, mesh.idx, mesh.icount, mesh.v, mesh.vcount, TM_STRIDE, target, 0.05f, 0, &err);
			memset(used, 0, mesh.vcount);
			for (size_t i = 0; i < count; ++i)
				used[dst[i]] = 1;
			size_t kept = 0;
			for (size_t v = 0; v < mesh.vcount; ++v)
				kept += tm_is_boundary(&mesh, v) && used[v];
			ASSERT_TRUE(kept < boundary);
		}

		free(used);
		free(dst);
		tm_free(&mesh);
	}
}

TEST(vertex_cache_in_place_and_empty)
{
	TestMesh mesh;
	tm_make_mesh(&mesh, TM_MESH_TORUS);
	unsigned int* a = (unsigned int*)malloc(mesh.icount * sizeof(unsigned int));
	unsigned int* b = (unsigned int*)malloc(mesh.icount * sizeof(unsigned int));
	meshopt_optimizeVertexCache(a, mesh.idx, mesh.icount, mesh.vcount);
	memcpy(b, mesh.idx, mesh.icount * sizeof(unsigned int));
	meshopt_optimizeVertexCache(b, b, mesh.icount, mesh.vcount);
	ASSERT_EQ(memcmp(a, b, mesh.icount * sizeof(unsigned int)), 0);

	unsigned int* ta = tm_canonical_tris(mesh.idx, mesh.icount);
	unsigned int* tb = tm_canonical_tris(a, mesh.icount);
	int same = memcmp(ta, tb, mesh.icount * sizeof(unsigned int)) == 0;
	free(ta);
	free(tb);
	ASSERT_TRUE(same);

	unsigned int sentinel = 0xdeadbeefu;
	meshopt_optimizeVertexCache(&sentinel, mesh.idx, 0, mesh.vcount);
	ASSERT_EQ(sentinel, 0xdeadbeefu);

	free(a);
	free(b);
	tm_free(&mesh);
}

TEST(simplify_empty_input)
{
	float pos[3] = {0, 0, 0};
	unsigned int dst[3] = {7, 7, 7};
	float err = -1.f;
	ASSERT_EQ(meshopt_simplify(dst, dst, 0, pos, 1, sizeof(pos), 0, 0.01f, 0, &err), (size_t)0);
	ASSERT_TRUE(err == 0.f);
}

TEST_MAIN_BEGIN()
	RUN_TEST(case_table_shape);
	RUN_TEST(option_values_match_upstream);
	RUN_TEST(simplify_scale_matches_upstream);
	RUN_TEST(simplify_invariants_and_reference);
	RUN_TEST(simplify_monotonic_in_target);
	RUN_TEST(lock_border_preserves_boundary);
	RUN_TEST(vertex_cache_in_place_and_empty);
	RUN_TEST(simplify_empty_input);
TEST_MAIN_END()

#endif
