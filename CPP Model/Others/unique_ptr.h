#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
 
template<typename T>
class _unique_ptr
{
public:
	_unique_ptr(T* p = nullptr) :_ptr(p);        //默认构造函数
	_unique_ptr(_unique_ptr<T>& p) :_ptr(p._ptr); //拷贝构造函数
 
	T& operator*();
	T* operator->();
	_unique_ptr<T>& operator=(_unique_ptr<T>& p); //赋值操作符重载
 
	T* get();
	T* release();
	void reset(T* p);
 
private:
	T * _ptr;
};
 
#endif