#include"unique_ptr.h"
 
template<typename T>
_unique_ptr<T>::_unique_ptr(T* p)
{
	_ptr = p;
}
 
template<typename T>
_unique_ptr<T>::_unique_ptr(_unique_ptr<T>& p)
{
	_ptr = p.release();
}
 
template<typename T>
T& _unique_ptr<T>::operator*()
{
	return *(this->_ptr);
}
 
template<typename T>
T* _unique_ptr<T>::operator->()
{
	return this->_ptr;
}
 
template<typename T>
_unique_ptr<T>& _unique_ptr<T>::operator=(_unique_ptr<T>& p)
{
	if (p.get() != this->get())
	{
		delete _ptr;
	}
	_ptr = p._ptr;
}
 
template<typename T>
T* _unique_ptr<T>::get()
{
	return this->_ptr;
}
 
template<typename T>
T* _unique_ptr<T>::release()
{
	T* tmp = _ptr;
	delete _ptr;
	return tmp;
}
 
template<typename T>
void _unique_ptr<T>::reset(T* p)
{
	if (p != _ptr)
	{
		delete _ptr;
	}
	_ptr = p;
}