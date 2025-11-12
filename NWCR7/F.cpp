#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
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
    int n;
    LL a, co = 0, ce = 0;
    cin>>n;
    Rep(i, 1, n){
        cin>>a;
        if(a & 1) co++;
        else ce++;
    }
    cout<<co * ce<<endl;
    return 0;
}
