//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// buffer_pool_manager_instance.cpp
//
// Identification: src/buffer/buffer_pool_manager.cpp
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/buffer_pool_manager_instance.h"

#include "common/macros.h"

/**
 * caution: the frame in the replacer which its pin_count == 0
 *
 **/
namespace bustub {

BufferPoolManagerInstance::BufferPoolManagerInstance(size_t pool_size, DiskManager *disk_manager,
                                                     LogManager *log_manager)
    : BufferPoolManagerInstance(pool_size, 1, 0, disk_manager, log_manager) {}

BufferPoolManagerInstance::BufferPoolManagerInstance(size_t pool_size, uint32_t num_instances, uint32_t instance_index,
                                                     DiskManager *disk_manager, LogManager *log_manager)
    : pool_size_(pool_size),
      num_instances_(num_instances),
      instance_index_(instance_index),
      next_page_id_(instance_index),
      disk_manager_(disk_manager),
      log_manager_(log_manager) {
  BUSTUB_ASSERT(num_instances > 0, "If BPI is not part of a pool, then the pool size should just be 1");
  BUSTUB_ASSERT(
      instance_index < num_instances,
      "BPI index cannot be greater than the number of BPIs in the pool. In non-parallel case, index should just be 1.");
  // We allocate a consecutive memory space for the buffer pool.
  pages_ = new Page[pool_size_];
  replacer_ = new LRUReplacer(pool_size);

  // Initially, every page is in the free list.
  for (size_t i = 0; i < pool_size_; ++i) {
    free_list_.emplace_back(static_cast<int>(i));
  }
}

BufferPoolManagerInstance::~BufferPoolManagerInstance() {
  delete[] pages_;
  delete replacer_;
}

bool BufferPoolManagerInstance::FlushPgImp(page_id_t page_id) {
  // Make sure you call DiskManager::WritePage!
  std::lock_guard locker(latch_);
  if (page_table_.count(page_id)) {
    auto frame_id = page_table_[page_id];
    Page *page = &pages_[frame_id];
    disk_manager_->WritePage(page->GetPageId(), page->GetData());
    return true;
  }
  return false;
}

void BufferPoolManagerInstance::FlushAllPgsImp() {
  // You can do it!
}

Page *BufferPoolManagerInstance::NewPgImp(page_id_t *page_id) {
  // 0.   Make sure you call AllocatePage!
  // 1.   If all the pages in the buffer pool are pinned, return nullptr.
  // 2.   Pick a victim page P from either the free list or the replacer. Always pick from the free list first.
  // 3.   Update P's metadata, zero out memory and add P to the page table.
  // 4.   Set the page ID output parameter. Return a pointer to P.
  // 利用FindReplace函数在我们的缓冲池找到合适的地方建立page_id --> frame_id的映射
  // 新页的元数据,这里注意新创建的页要写回磁盘
  page_id_t new_page_id = AllocatePage();  // atomic operation
  std::lock_guard locker(latch_);
  bool all_pinned = true;
  for (int i = 0; i < static_cast<int>(pool_size_); ++i) {
    if (pages_[i].GetPinCount() == 0) {
      all_pinned = false;
      break;
    }
  }
  if (all_pinned) {
    return nullptr;
  }
  frame_id_t victim_frame_id = -1;
  if (FindReplace(&victim_frame_id)) {
    std::cerr << "use victim frame: " << victim_frame_id << std::endl;
    Page *new_page = &pages_[victim_frame_id];
    new_page->page_id_ = new_page_id;
    new_page->pin_count_++;
    new_page->is_dirty_ = false;
    disk_manager_->WritePage(new_page->GetPageId(), new_page->GetData());
    *page_id = new_page_id;
    page_table_[new_page_id] = victim_frame_id;
    std::cerr << "new_page_id: " << new_page_id << " frame_id: " << victim_frame_id << std::endl;
    return new_page;
  }
  return nullptr;
}

Page *BufferPoolManagerInstance::FetchPgImp(page_id_t page_id) {
  // 1.     Search the page table for the requested page (P).
  // 1.1    If P exists, pin it and return it immediately.
  // 1.2    If P does not exist, find a replacement page (R) from either the free list or the replacer.
  //        Note that pages are always found from the free list first.
  // 2.     If R is dirty, write it back to the disk.
  // 3.     Delete R from the page table and insert P.
  // 4.     Update P's metadata, read in the page content from disk, and then return a pointer to P.
  std::lock_guard locker(latch_);       // lock and the lock will auto release after the function
  auto it = page_table_.find(page_id);  // search for the frame
  if (it != page_table_.end()) {        // P  exists
    // get the page
    auto frame_id = it->second;  // 表示这个page在页表pages中的偏移量
    Page *page = &pages_[frame_id];
    // pin the page
    page->pin_count_++;
    // return it
    return page;
  }
  // P doest exist, find a replacer
  frame_id_t frame_id = -1;
  if (FindReplace(&frame_id)) {
    page_table_[page_id] = frame_id;
    Page *page = &pages_[frame_id];
    page->pin_count_++;
    return page;
  }
  return nullptr;
}

bool BufferPoolManagerInstance::DeletePgImp(page_id_t page_id) {
  // 0.   Make sure you call DeallocatePage!
  // 1.   Search the page table for the requested page (P).
  // 1.   If P does not exist, return true.
  // 2.   If P exists, but has a non-zero pin-count, return false. Someone is using the page.
  // 3.   Otherwise, P can be deleted. Remove P from the page table, reset its metadata and return it to the free list.
  std::lock_guard locker(latch_);
  if (page_table_.find(page_id) != page_table_.end()) {
    auto frame_id = page_table_[page_id];
    Page *page = &pages_[frame_id];
    if (page->GetPinCount() > 0) {
      return false;
    }
    page->is_dirty_ = false;
    page_table_.erase(page_id);
    free_list_.push_back(frame_id);
  }
  return true;
}

/**
 * Unpin the target page from the buffer pool.
 * @param page_id id of page to be unpinned
 * @param is_dirty true if the page should be marked as dirty, false otherwise
 * @return false if the page pin count is <= 0 before this call, true otherwise
 */
bool BufferPoolManagerInstance::UnpinPgImp(page_id_t page_id, bool is_dirty) {
  // 如果这个页的pin_count>0 直接--
  // 如果这个页的pin_count==0 我们需要给它加到Lru_replacer中。
  // 因为没有人引用它。所以它可以成为被替换的候选人
  std::lock_guard locker(latch_);
  if (page_table_.find(page_id) != page_table_.end()) {
    std::cerr << "find page_id: " << page_id << std::endl;
    auto frame_id = page_table_[page_id];
    Page *page = &pages_[frame_id];
    if (is_dirty) {
      page->is_dirty_ = true;
    }
    if (page->GetPinCount() == 0) {
      return false;
    }
    if (--(page->pin_count_) == 0) {
      replacer_->Unpin(frame_id);
      std::cerr << "Unpin frame: " << frame_id << std::endl;
      page_table_.erase(page_id);
    }
    return true;
  }
  return false;
}

page_id_t BufferPoolManagerInstance::AllocatePage() {
  const page_id_t next_page_id = next_page_id_;
  next_page_id_ += num_instances_;
  ValidatePageId(next_page_id);
  return next_page_id;
}

void BufferPoolManagerInstance::ValidatePageId(const page_id_t page_id) const {
  assert(page_id % num_instances_ == instance_index_);  // allocated pages mod back to this BPI
}

// find a replacer frame
bool BufferPoolManagerInstance::FindReplace(frame_id_t *frame_id) {
  // firstly find the free frame from the list
  if (!free_list_.empty()) {
    // std::cerr <<"Get frame_id from list: " <<free_list_.front() << std::endl;
    *frame_id = free_list_.front();
    free_list_.pop_front();
    return true;
  }
  // if free_list_ is empty, find from the repalcer_
  // if the frame is dirty , should be flush
  if (replacer_->Victim(frame_id)) {
    // use frame_if to find page_id
    std::cerr << "replacer find victim frame: " << *frame_id << std::endl;
    page_id_t replace_page_id = -1;
    for (const auto &[pid, fid] : page_table_) {
      if (fid == *frame_id) {
        replace_page_id = pid;
        break;
      }
    }
    if (replace_page_id != -1) {
      Page *page = &pages_[replace_page_id];
      if (page->IsDirty()) {
        // write into disk
        disk_manager_->WritePage(page->GetPageId(), page->GetData());
        page->pin_count_ = 0;
      }
      page_table_.erase(replace_page_id);
      // replacer_->Pin(replace_page_id);  // remove from the replacer_
    }
    return true;
  }
  return false;  // not avlidable frame
}

}  // namespace bustub
