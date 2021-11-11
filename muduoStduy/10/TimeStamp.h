//
// Created by Jacky on 2021/11/10.
//

#ifndef STUDY_TIMESTAMP
#define STUDY_TIMESTAMP

#include <cstdint>
#include "copyable.h"
#include <string>
#include <sys/time.h>

namespace Study {
    class TimeStamp : public Study::copyable {
    private:
        int64_t microSecondsSinceEpoch_;
    public:
        TimeStamp() : microSecondsSinceEpoch_(0) {}

        explicit TimeStamp(const int64_t &microSecondsSinceEpoch) :
                microSecondsSinceEpoch_(microSecondsSinceEpoch) {}

        void swap(TimeStamp &rhs) {
            std::swap(microSecondsSinceEpoch_, rhs.microSecondsSinceEpoch_);
        }

        int64_t getMicroSecond() const { return microSecondsSinceEpoch_; }

        std::string toString() const;

        std::string toFormattdString() const;

        static TimeStamp now();

        static TimeStamp invalid();

        static constexpr int kMicroSecondPerSecond = 1000 * 1000;
    };

    TimeStamp TimeStamp::now() {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        int64_t seconds = tv.tv_sec;
        return TimeStamp(seconds * kMicroSecondPerSecond + tv.tv_usec);
    }

    std::string TimeStamp::toString() const {
        char buf[32] = {0};
        int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondPerSecond;
        int64_t microSeconds = microSecondsSinceEpoch_ % kMicroSecondPerSecond;
        snprintf(buf, sizeof(buf) - 1, "%lld %lld", seconds, microSeconds);
        return buf;
    }

    inline bool operator==(const Study::TimeStamp &lhs, const Study::TimeStamp &rhs) {
        return lhs.getMicroSecond() == rhs.getMicroSecond();
    }

    inline bool operator<(const Study::TimeStamp &lhs, const Study::TimeStamp &rhs) {
        return lhs.getMicroSecond() < rhs.getMicroSecond();
    }

    inline double timeDifference(TimeStamp &high, TimeStamp &low) {
        int64_t diff = high.getMicroSecond() - low.getMicroSecond();
        return static_cast<double>(diff) / TimeStamp::kMicroSecondPerSecond;
    }
}


#endif // STUDY_TIMESTAMP