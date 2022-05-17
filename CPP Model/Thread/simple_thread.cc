// thread wrapper
class Thread {
private:
    Thread(const Thread &) = delete;

    Thread &operator=(const Thread &) = delete;

private:
    using Func = std::function<void(void)>;
    Func func_;
    atomic<bool> start_;
    thread t_;
public:
    explicit Thread(Func func) : func_(std::move(func)), start_(false) {}

    ~Thread() {
        if (start_ && t_.joinable()) {
            t_.detach();
        }
    }

    void start() {
        // printf("Thread Start ... \n");
        t_ = std::move(std::thread(func_));
        start_ = true;
    }

    void join() {
        if (t_.joinable()) {
            t_.join();
        }
    }

};