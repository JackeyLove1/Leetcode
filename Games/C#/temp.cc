for (uint64_t start = replay_start; start < replay_end; start += io_size) {
        uint64_t end = std::min(start + io_size, replay_end);
        auto log_offset_ = start - blob.start_;
        auto segment_offset_ = 0ull;
        auto size_ = end - start;
        std::unique_ptr<char[]> data_(new char[size_]);
        BSLOG(INFO) << blob_id << " start " << start << " end " << end << " size " << end - start;
        auto blob_options = GetFrontendBlobOptions();
        blob_options.blob_condition = segment_->GetBlobCondition();
        auto e =
            block_store_->LogBlobRead(blob_id, &blob_options, data_.get(), size_, log_offset_, nullptr);
        if (e != BYTENAS_OK) {
            BSLOG(ERROR) << blob_id << " read logblob start:" << start << " end:" << end
                         << GetErrorString(e);
            return BYTENAS_ERR_BLOCKSERVER_MANIFEST_ERROR;
        }

        // 4.read logheader
        size_t pos = 0;
        while (pos < size_) {
            auto* header = reinterpret_cast<LogHeader*>(reinterpret_cast<char*>(data_.get()) + pos);
            if (!header->VerifyHeader()) {
                error_code_ = BYTENAS_ERR_BLOCKSERVER_LOG_VERIFY_FAILED;
                BSLOG(ERROR) << segment_->GetSegmentIdString() << " header verify"
                             << GetErrorString(error_code_);
                return BYTENAS_ERR_BLOCKSERVER_LOG_VERIFY_FAILED;
            }
            uint32_t full_length = header->length_;
            if (header->length_ % kDefaultBlockSize != 0) {
                full_length = (header->length_ + kDefaultBlockSize - 1) / kDefaultBlockSize *
                              kDefaultBlockSize;
                header->length_ =
                    header->length_ + (header->length_ / kDefaultBlockSize + 1) * sizeof(LogHeader);
            } else {
                header->length_ = header->length_ / kDefaultBlockSize * kDefaultPhysicalBlockSize;
            }
            uint32_t block_num = full_length / kDefaultBlockSize;
            uint64_t remain_length = (block_num - header->block_index_) * kDefaultPhysicalBlockSize;
            uint64_t g_log_offset = log_offset_ + blob.start_;
            PhyRangePos range_pos(
                header->segment_offset_ - header->block_index_ * kDefaultBlockSize,
                g_log_offset - header->block_index_ * kDefaultPhysicalBlockSize,
                0,
                0,
                header->length_,
                header->timestamp_,
                blob_id,
                sibling_index);

            g_log_offset += remain_length;
            pos += remain_length;

            if (g_log_offset > replay_end) {
                BSLOG(WARNING) << blob_id
                               << " current log_offset " << g_log_offset
                               << " is larger than replay end " << replay_end << ", record header"
                               << header->ToString();
                return BYTENAS_ERR_BLOCKSERVER_MANIFEST_ERROR;
            }
            all_items->push_back(range_pos);
        }
    }