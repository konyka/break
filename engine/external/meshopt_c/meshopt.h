/**
 * meshopt_c - pure C11 port of a subset of meshoptimizer 1.3
 *
 * Upstream: https://github.com/zeux/meshoptimizer (tag v1.3, MESHOPTIMIZER_VERSION 1030)
 * Copyright (C) 2016-2026, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
 * This library is distributed under the MIT License. See LICENSE.md in this directory.
 *
 * Only the edge-collapse simplifier and the vertex cache optimizer are ported; see README.md.
 */
#ifndef MESHOPT_C_MESHOPT_H
#define MESHOPT_C_MESHOPT_H

#include <stddef.h>

/* Version of the upstream release this port is based on; major * 1000 + minor * 10 + patch */
#define MESHOPTIMIZER_VERSION 1030 /* 1.3 */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Vertex transform cache optimizer
 * Reorders indices to reduce the number of GPU vertex shader invocations
 * If index buffer contains multiple ranges for multiple draw calls, this function needs to be called on each range individually.
 *
 * destination must contain enough space for the resulting index buffer (index_count elements)
 *
 * Port note: if internal memory allocation fails, destination receives the input indices unchanged.
 */
void meshopt_optimizeVertexCache(unsigned int* destination, const unsigned int* indices, size_t index_count, size_t vertex_count);

/**
 * Simplification options
 */
enum
{
	/* Do not move vertices that are located on the topological border (vertices on triangle edges that don't have a paired triangle). Useful for simplifying portions of the larger mesh. */
	meshopt_SimplifyLockBorder = 1 << 0,
	/* Improve simplification performance assuming input indices are a sparse subset of the mesh. Note that error becomes relative to subset extents. */
	meshopt_SimplifySparse = 1 << 1,
	/* Treat error limit and resulting error as absolute instead of relative to mesh extents. */
	meshopt_SimplifyErrorAbsolute = 1 << 2,
	/* Remove disconnected parts of the mesh during simplification incrementally, regardless of the topological restrictions inside components. */
	meshopt_SimplifyPrune = 1 << 3,
	/* Produce more regular triangle sizes and shapes during simplification, at some cost to geometric and attribute quality. */
	meshopt_SimplifyRegularize = 1 << 4,
	/* Allow collapses across attribute discontinuities, except for vertices that are tagged with meshopt_SimplifyVertex_Protect in vertex_lock. */
	meshopt_SimplifyPermissive = 1 << 5,
	/* Produce more regular triangle sizes and shapes during simplification, at a small cost to geometric and attribute quality. */
	meshopt_SimplifyRegularizeLight = 1 << 6,
	/* Experimental: Try to preserve fold lines between opposite-facing triangles, at a small performance cost. */
	meshopt_SimplifyPreserveFolds = 1 << 7,
	/* Experimental: Clamp attribute error to match position error scale and avoid extreme error values in areas with high attribute variance. */
	meshopt_SimplifyErrorClamped = 1 << 8,
};

/**
 * Simplification vertex flags/locks, for use in `vertex_lock` arrays in simplification APIs
 */
enum
{
	/* Do not move this vertex. */
	meshopt_SimplifyVertex_Lock = 1 << 0,
	/* Protect attribute discontinuity at this vertex; must be used together with meshopt_SimplifyPermissive option. */
	meshopt_SimplifyVertex_Protect = 1 << 1,
	/* Increase priority for this vertex, making it more likely that it's preserved during simplification. */
	meshopt_SimplifyVertex_Priority = 1 << 2,
};

/**
 * Mesh simplifier
 * Reduces the number of triangles in the mesh, attempting to preserve mesh appearance as much as possible
 * The algorithm tries to preserve mesh topology and can stop short of the target goal based on topology constraints or target error.
 * If not all attributes from the input mesh are needed, it's recommended to reindex the mesh without them prior to simplification.
 * Returns the number of indices after simplification, with destination containing new index data
 *
 * The resulting index buffer references vertices from the original vertex buffer.
 *
 * destination must contain enough space for the target index buffer, worst case is index_count elements (*not* target_index_count)!
 * vertex_positions should have float3 position in the first 12 bytes of each vertex
 * target_error represents the error relative to mesh extents that can be tolerated, e.g. 0.01 = 1% deformation (unless absolute error option is used)
 * options must be a bitmask composed of meshopt_SimplifyX options; 0 is a safe default
 * result_error can be NULL; when it's not NULL, it will contain the resulting (relative/absolute) error after simplification
 *
 * Port note: if internal memory allocation fails, returns 0 and sets *result_error to 0 (when non-NULL).
 */
size_t meshopt_simplify(unsigned int* destination, const unsigned int* indices, size_t index_count, const float* vertex_positions, size_t vertex_count, size_t vertex_positions_stride, size_t target_index_count, float target_error, unsigned int options, float* result_error);

/**
 * Mesh simplifier with attribute metric
 * Similar to meshopt_simplify, but incorporates attribute values into the error metric used to prioritize simplification order.
 * Note that the number of attributes with non-zero weights affects memory requirements and running time.
 *
 * destination must contain enough space for the target index buffer, worst case is index_count elements (*not* target_index_count)!
 * vertex_positions should have float3 position in the first 12 bytes of each vertex
 * vertex_attributes should have attribute_count floats for each vertex
 * attribute_weights should have attribute_count floats in total; the weights determine relative priority of attributes between each other and wrt position
 * attribute_count must be <= 32
 * vertex_lock can be NULL; when it's not NULL, it should have a value for each vertex composed of meshopt_SimplifyVertex_* flags
 * target_error represents the error relative to mesh extents that can be tolerated, e.g. 0.01 = 1% deformation (unless absolute error option is used)
 * options must be a bitmask composed of meshopt_SimplifyX options; 0 is a safe default
 * result_error can be NULL; when it's not NULL, it will contain the resulting (relative/absolute) error after simplification
 *
 * Port note: if internal memory allocation fails, returns 0 and sets *result_error to 0 (when non-NULL).
 */
size_t meshopt_simplifyWithAttributes(unsigned int* destination, const unsigned int* indices, size_t index_count, const float* vertex_positions, size_t vertex_count, size_t vertex_positions_stride, const float* vertex_attributes, size_t vertex_attributes_stride, const float* attribute_weights, size_t attribute_count, const unsigned char* vertex_lock, size_t target_index_count, float target_error, unsigned int options, float* result_error);

/**
 * Returns the error scaling factor used by the simplifier to convert between absolute and relative extents
 *
 * Absolute error must be *divided* by the scaling factor before passing it to meshopt_simplify as target_error
 * Relative error returned by meshopt_simplify via result_error must be *multiplied* by the scaling factor to get absolute error.
 */
float meshopt_simplifyScale(const float* vertex_positions, size_t vertex_count, size_t vertex_positions_stride);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MESHOPT_C_MESHOPT_H */
