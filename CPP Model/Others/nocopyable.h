class noncopyable {
protected:
    noncopyable() = default;

    ~noncopyable() = default;

private:
    // noncopyable(noncopyable &&) = delete;                 // Move construct
    noncopyable(const noncopyable &) = delete;            // Copy construct
    noncopyable &operator=(const noncopyable &) = delete; // Copy assign
    // noncopyable &operator=(noncopyable &&) = delete;      // Move assign
};