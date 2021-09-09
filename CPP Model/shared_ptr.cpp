#include"_shared_ptr.h"
 
template<typename T>
shared_ptr<T>::shared_ptr(T* p = nullptr) :count(new int(1)), _ptr(p) //默认构造函数，必须自己显式的开辟内存
{
	if (_ptr)
	{
		count = new int(1); //如果初始值不为空，则计数器为1
	}
	else
	{
		count = new int(0); //当初始值为空时，则计数器为0；
	}
} 
 
template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>& p) : count(&(++p.count)), _ptr(p._ptr) //拷贝构造函数，属于强制转换，显式
{
	if (this != p)
	{
		this->_ptr  = p._ptr;
		this->count = p.count;
		*(this->count)++;
	}
} 
 
template<typename T>
T& shared_ptr<T>::operator*()
{
	//assert(this->_ptr == nullptr)
	return *(this->_ptr);
}
 
template<typename T>
T* shared_ptr<T>::operator->()
{
	//assert(this->_ptr == nullptr);
	return this->_ptr;
}
 
template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>& p) //对等号进行重载，保证保存同为shared_ptr的指针能
														  //相互转换，等号左边计数器减1，右边计数器加1。
{
	++*(p.count); //等式右边引用次数加一，左边引用次数减一
	if (this->_ptr && 0 == --*this->count) //当左边引用次数为零
	{
		delete count;
		delete _ptr;
	}
	this->count = p.count;
	this->_ptr = p._ptr;
	return *this;
}
 
template<typename T>
shared_ptr<T>::~shared_ptr() //当诶空时，清除
{
	if (0 == *(this->count))
	{
		delete count;
		delete _ptr;
	}
}
 
template<typename T>
bool shared_ptr<T>::empty() //检查是否指向一个空T，当为空时，记得count也为零
{
	return _ptr == nullptr;
}
 
template<typename T>
int shared_ptr<T>::GetCount()
{
	return *count;
}