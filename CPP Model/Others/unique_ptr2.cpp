#include <iostream>
#include <memory>

using namespace std;

namespace smart_pointer
{

template <typename T>
struct defaultDeleter {
  void operator()(const T *ptr) {
    if(ptr) {
    	delete ptr;
    	ptr = nullptr;
    }
  }
};

template <typename T, typename Deleter=defaultDeleter<T> >
class unique_ptr {
public:
  unique_ptr();
  unique_ptr(T *ptr);
  unique_ptr(unique_ptr &&p); //移动构造
  ~unique_ptr();

//non-copyable
private:
  unique_ptr(const unique_ptr &p);
  unique_ptr &operator=(const unique_ptr &p);

public:
  T& operator* ();
  T* operator-> ();
  unique_ptr &operator=(unique_ptr &&p); //移动赋值，右值 
  operator bool() const;

  //返回原始指针
  T* get() const;
  //返回指针，释放所有权
  T* release();
  //替换被管理的对象
  void reset(T *ptr);
  //交换被管理的对象
  void swap(unique_ptr &p);

private:
  T *ptr;
};

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr()
 : ptr(nullptr)
{}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T *_ptr)
 : ptr(_ptr) 
{}

//移交所有权
template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(unique_ptr &&p)
 : ptr(p.ptr) {
  p.ptr = nullptr;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::~unique_ptr()
{
  Deleter()(ptr);
  cout << "unique_ptr dctor" << endl;
}

template <typename T, typename Deleter>
T& unique_ptr<T, Deleter>::operator* ()
{
  return *ptr;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::operator-> ()
{
  return ptr;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter> &unique_ptr<T, Deleter>::operator=(unique_ptr &&p)
{
  std::swap(ptr, p.ptr);
  return *this;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::operator bool() const
{
  return ptr != nullptr;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::get() const 
{
  return ptr;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::release()
{
  T *pointer = ptr;
  ptr = nullptr;
  return pointer;
}

template <typename T, typename Deleter>
void unique_ptr<T, Deleter>::reset(T *_ptr)
{
  unique_ptr<T, Deleter>().swap(*this);

  ptr = _ptr;
}

template <typename T, typename Deleter>
void unique_ptr<T, Deleter>::swap(unique_ptr &p)
{
  std::swap(ptr, p.ptr);
}

}; //namespace smart_pointer

int main(int argc, char *argv[])
{
  {
    smart_pointer::unique_ptr<int> p(new int(10));
    //smart_pointer::unique_ptr<int> p1 = p; //编译不过的
    //mart_pointer::unique_ptr<int> p2(p); //编译不过的
    cout << *p << endl;
    
    int *p3 = p.release();
    if(!p) cout << "p is released" << endl;
    cout << *p3 << endl;
    delete p3; //手动释放

    p = smart_pointer::unique_ptr<int>(new int(11)); //移动赋值
    smart_pointer::unique_ptr<int> p4(new int(12));
    p4.swap(p);
    cout << *p << endl;

 	p.reset(new int(13));
 	cout << *p << endl;
  }

  return 0;
}



// others
#include <utility>
#include<iostream>


/****
 * 智能指针unique_ptr的简单实现
 * 
 * 特点：独享它指向的对象。也就是说，同时只有一个unique_ptr指向同一个对象，当这个unique_ptr被销毁时，指向的对象也随即被销毁
 * 
 * 典型用途：
 * 1. 在一个函数定义一个A* ptr = new A(), 结束还需要用delete，而用unique_ptr，就不需要自己调用delete
 * 2. 作为一个类的变量，这个变量只在本类使用，不会被其他类调用，也不会作为参数传递给某个函数
 * */
template<typename T>
class unique_ptr
{
private:
	T * ptr_resource = nullptr;

public:
    //explicit构造函数是用来防止隐式转换, 即不允许写成unique_ptr<T> tempPtr = T;
    //std::move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝所以可以提高利用效率,改善性能.
    //move之后，raw_resource内部的资源将不能再被raw_resource使用
	explicit unique_ptr(T* raw_resource) noexcept : ptr_resource(std::move(raw_resource)) {}
	unique_ptr(std::nullptr_t) : ptr_resource(nullptr) {}

	unique_ptr() noexcept : ptr_resource(nullptr) {}

	//析构时, 释放托管的对象资源
	~unique_ptr() noexcept
	{
		delete ptr_resource;
	}
	// Disables the copy/ctor and copy assignment operator. We cannot have two copies exist or it'll bypass the RAII concept.
    //重要，禁止两种拷贝的赋值方式
    //使用"=delete"修饰，表示函数被定义为deleted，也就意味着这个成员函数不能再被调用，否则就会出错。
	unique_ptr(const unique_ptr<T>&) noexcept = delete;
	unique_ptr& operator = (const unique_ptr&) noexcept = delete;
	
public:
    //&& 是右值引用，见https://zhuanlan.zhihu.com/p/107445960
	// 允许移动语义。虽然无法复制unique_ptr，但可以安全地移动。
    //例子：unique_ptr<Test> tPtr3(std::move(tPtr1));
	unique_ptr(unique_ptr&& move) noexcept
	{
        std::cout << "construct for unique_ptr&&" << std::endl;
		move.swap(*this);
	}
	// ptr = std::move(resource)
	unique_ptr& operator=(unique_ptr&& move) noexcept
	{
        std::cout << "operator= for unique_ptr&&" << std::endl;

		move.swap(*this);
		return *this;
	}

	explicit operator bool() const noexcept
	{
		return this->ptr_resource;
	}
	// releases the ownership of the resource. The user is now responsible for memory clean-up.
	T* release() noexcept
	{
		return std::exchange(ptr_resource, nullptr);
	}
	// returns a pointer to the resource
	T* get() const noexcept
	{
		return ptr_resource;
	}
	// swaps the resources
	void swap(unique_ptr<T>& resource_ptr) noexcept
	{
		std::swap(ptr_resource, resource_ptr.ptr_resource);
	}
	// reset就删除老的，指向新的
	void reset(T* resource_ptr) noexcept(false)
	{
		// ensure a invalid resource is not passed or program will be terminated
		if (resource_ptr == nullptr)
			throw std::invalid_argument("An invalid pointer was passed, resources will not be swapped");

		delete ptr_resource;

		ptr_resource = nullptr;

		std::swap(ptr_resource, resource_ptr);
	}
public:
	// overloaded operators
	T * operator->() const noexcept
	{
		return this->ptr_resource;
	}
	T& operator*() const noexcept
	{
		return *this->ptr_resource;
	}
	// 额外说明noexcept
    //noexcept C++11关键字, 告诉编译器，函数中不会发生异常,有利于编译器对程序做更多的优化
    //C++中的异常处理是在运行时而不是编译时检测的。为了实现运行时检测，编译器创建额外的代码，然而这会妨碍程序优化
};
