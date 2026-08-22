#include "myr/my_vgcanvas_quality_transaction.h"

static int ops_are_valid(const my_vgcanvas_sample_transaction_ops_t* ops) {
  return ops != NULL && ops->create != NULL && ops->validate != NULL &&
         ops->submit != NULL && ops->activate != NULL && ops->retire != NULL &&
         ops->destroy != NULL;
}

void my_vgcanvas_sample_transaction_init(
    my_vgcanvas_sample_transaction_t* tx, uint32_t active_sample_count,
    uint32_t active_width, uint32_t active_height, void* active_candidate,
    uint32_t supported_sample_counts) {
  if (tx == NULL) {
    return;
  }
  tx->active_sample_count = active_sample_count;
  tx->active_width = active_width;
  tx->active_height = active_height;
  tx->active_candidate = active_candidate;
  tx->supported_sample_counts = supported_sample_counts;
}

my_ret_t my_vgcanvas_sample_transaction_set(
    my_vgcanvas_sample_transaction_t* tx, uint32_t sample_count,
    uint32_t width, uint32_t height,
    const my_vgcanvas_sample_transaction_ops_t* ops, void* ctx) {
  void* candidate = NULL;
  my_ret_t ret;

  if (tx == NULL || my_vgcanvas_sample_count_bit(sample_count) == 0u ||
      width == 0u || height == 0u ||
      tx->supported_sample_counts == 0u || !ops_are_valid(ops)) {
    return MY_RET_INVALID_PARAMS;
  }
  if ((tx->supported_sample_counts &
       my_vgcanvas_sample_count_bit(sample_count)) == 0u) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (tx->active_candidate != NULL &&
      tx->active_sample_count == sample_count &&
      tx->active_width == width && tx->active_height == height) {
    return MY_RET_OK;
  }

  ret = ops->create(ctx, sample_count, width, height, &candidate);
  if (ret != MY_RET_OK) {
    return ret;
  }
  if (candidate == NULL) {
    return MY_RET_FAIL;
  }
  if (candidate == tx->active_candidate) {
    return MY_RET_FAIL;
  }
  ret = ops->validate(ctx, candidate);
  if (ret != MY_RET_OK) {
    ops->destroy(ctx, candidate);
    return ret;
  }
  ret = ops->submit(ctx, candidate);
  if (ret != MY_RET_OK) {
    ops->destroy(ctx, candidate);
    return ret;
  }
  ops->activate(ctx, candidate);
  if (tx->active_candidate != NULL) {
    ops->retire(ctx, tx->active_candidate);
  }
  tx->active_candidate = candidate;
  tx->active_sample_count = sample_count;
  tx->active_width = width;
  tx->active_height = height;
  return MY_RET_OK;
}
