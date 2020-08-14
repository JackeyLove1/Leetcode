#include <iostream>
#include <vector>
using namespace std;
 
#define MAX_SIZE 5
 
void swap(vector<int> &lst, int i, int j)
{
   int tmp = lst[i];
   lst[i] = lst[j];
   lst[j] = tmp;
}
 
 
void perm(vector<int> &lst, int start, int end, vector<vector<int> > &dst)
{
    if (start >= end) {
        dst.push_back(lst);
    } else {
        for (int i=start;i<end;i++) {
            swap(lst, start, i);
            perm(lst, start+1, end, dst);
            // 回溯
            swap(lst, start, i);
        }
    }
}
 
 
int main(int argc, const char *argv[])
{
    vector<vector<int> > dst;
    vector<int> lst;
    for(int i=0;i<MAX_SIZE;i++) {
        lst.push_back(i);
    }
 
    perm(lst, 0, MAX_SIZE, dst);
    cout << "len " << (int)dst.size() << endl;
    int i=0;
    for(vector<vector<int> >::iterator lt=dst.begin();lt<dst.end();lt++){
            cout << i << ": ";
        for(vector<int>::iterator it=(*lt).begin();it < (*lt).end(); it++) {
            cout << *it;
        }
        cout << endl;
        i++;
    }
    cout << endl;
    return 0;
}