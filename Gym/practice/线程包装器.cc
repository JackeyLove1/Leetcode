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
        // printf("Start ... \n");
        // this_thread::sleep_for(300ms);
        t_ = std::move(std::thread(func_));
        start_ = true;
    }

    void join() {
        if (t_.joinable()) {
            t_.join();
        }
    }

};

// using std::bind to bind a concrete function as follows:
// explicit AsyncWriter() : count_(0), stop_(false), write_(std::bind(&AsyncWriter::threadFunc, this)) {}