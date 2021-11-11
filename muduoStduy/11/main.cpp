#include "AtomicIntegetT.h"
#include <cassert>

using namespace std;

int main() {
    Study::AtomicInt<int> t(10);
    assert(t.get() == 10);
    assert(t.getAndAdd(10) == 10);
    assert(t.get() == 20);
    return 0;
}