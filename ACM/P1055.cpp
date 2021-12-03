#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_set>

using namespace std;

int main(){
	char a[14],mod[12]="0123456789X";
	scanf("%s",a);
	/*
	   for(int i=0;i<12;i++){
	       cin>>a[i];
	   }
	*/
	int i,j=1,t=0;
	for(i=0;i<12;i++){
		if(a[i]=='-') continue;
		t+=(a[i]-48)*j++;
	}
	if(mod[t%11]==a[12])
	    cout<<"Right";
	else{
		a[12]=mod[t%11];
		printf("%s",a);
		/*for(int i=0;i<13;i++){
		    cout<<a[i];
		}
		*/
	}
	return 0;
}