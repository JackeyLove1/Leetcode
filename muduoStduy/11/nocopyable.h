class noncopyable{
public:
    noncopyable() = default;
    virtual ~noncopyable() = default;       //构造函数和析构函数是默认的
    //使用delete关键字禁用 copy constructor 和 copy assignment
    noncopyable(const  noncopyable&) = delete;
    virtual noncopyable& operator=(const noncopyable&) = delete;

};