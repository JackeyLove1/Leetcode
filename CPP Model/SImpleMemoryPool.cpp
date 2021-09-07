#ifndef _OBJECTPOOL_HPP_
#define _OBJECTPOOL_HPP_

#include <iostream>
#include <list>

template<class Object>
class ObjectPool
{
public:
 ObjectPool(size_t Size)
 {
  _nSize = Size;
  for (size_t n = 0; n < _nSize; n++)
  {
   _mPool.push_back(new Object());
  }
 }
 virtual ~ObjectPool()
 {
  auto iter = _mPool.begin();
  while (iter != _mPool.end())
  {
   delete *iter;
   ++iter;
  }
  _nSize = 0;
 }

 Object* GetObject()
 {
  Object* pObj = NULL;
  if (_nSize == 0)
  {
   pObj = new Object();
  }
  else
  {
   pObj = _mPool.front();
   _mPool.pop_front();
   --_nSize;
  }
  return pObj;
 }

 void ReturnObject(Object* pObj)
 {
  _mPool.push_back(pObj);
  ++_nSize;
 }

private:
 size_t _nSize;
 std::list<Object*> _mPool;
};

#endif // !_OBJECTPOOL_HPP_

using namespace std;

class Test
{
public:
 Test() {}
 ~Test() {}
 void Print()
 {
  cout << "Test" << endl;
 }
};

int main()
{
 ObjectPool<Test> obj(10);
 Test* pA;
 pA = obj.GetObject();
 pA->Print();
 obj.ReturnObject(pA);

 return 0;
}