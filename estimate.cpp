#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<windows.h>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    DWORD dwTime = GetTickCount();
    system(".\\fix1012");
    DWORD dwTime2 = GetTickCount();
    cout<<"Time: "<<(dwTime2 - dwTime)<<"ms"<<endl;
    
    return 0;
}
