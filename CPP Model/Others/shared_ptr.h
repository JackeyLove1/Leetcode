#ifndef _SHARED_PTR_H
#define _SHARED_PTR_H
/*
  一个模板T* ptr,指向实际的对象
  一个引用次数
  重载operator*和operator->,使得能像指针一样使用share_ptr
  重载copy constructer，使其引用次数加一
  重载operator=，如果原来的shared_ptr已经有对象
*/
 
template<typename T>
class shared_ptr
{
public:
	shared_ptr(T* p) :count(new int(1)), _ptr(p); //默认构造函数，必须自己显式的开辟内存
	shared_ptr(shared_ptr<T>& p) :count(&(++p.count)), _ptr(p._ptr); //拷贝构造函数，属于强制转换，显式
 
	T& operator*(); //
	T* operator->();
	shared_ptr<T> & operator=(shared_ptr<T>& p); //对等号进行重载，保证保存同为shared_ptr的指针能相互转换，等号
												 //左边计数器减1，右边计数器加1。
	~shared_ptr();
	bool empty();  //检查是否指向一个空T
	int GetCount();
private:
	int* count;  //引用计数器
	T* _ptr;   //每创建一个对象，则有一个指针指向一个shared_ptr类型 
};
 
#endif