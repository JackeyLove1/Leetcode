//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) : lru_capacity_(num_pages) { lru_map_.reserve(lru_capacity_); }

// STL container needn't destructor
LRUReplacer::~LRUReplacer() = default;

// remove_oldest the page, and store the page_id into frame_id
bool LRUReplacer::Victim(frame_id_t *frame_id) {
  if (lru_list_.empty()) {
    return false;
  }
  auto iter = lru_map_[lru_list_.back()];
  *frame_id = *iter;
  lru_map_.erase(lru_list_.back());
  lru_list_.pop_back();
  return true;
}

// get and remove the frame from the buffer pool
void LRUReplacer::Pin(frame_id_t frame_id) {
  if (lru_map_.count(frame_id)) {
    auto iter = lru_map_[frame_id];
    lru_list_.erase(iter);
    lru_map_.erase(frame_id);
  }
}

// Unpin -> insert/put the frame, if the frame in the lru, don't change the frame's place
void LRUReplacer::Unpin(frame_id_t frame_id) {
  if (lru_map_.count(frame_id)) {
    return;
  }
  if (lru_list_.size() >= lru_capacity_) {
    // remove the oldest
    frame_id_t old_frame_id = -1;
    Victim(&old_frame_id);
  }
  lru_list_.emplace_front(frame_id);
  lru_map_[frame_id] = lru_list_.begin();
}

size_t LRUReplacer::Size() { return lru_list_.size(); }

}  // namespace bustub
