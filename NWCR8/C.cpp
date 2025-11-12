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
    int tsk;
    cin>>tsk;
    vector<pii> h;
    int n, H;
    while(tsk--){
        cin>>n>>H;
        h.resize(n);
        Rpl(i, 0, n){
            cin>>h[i].first;
            h[i].first = -labs(H - h[i].first * 2);
            h[i].second = i + 1;
        }
        sort(h.begin(), h.end());
        Rpl(i, 0, n){
            cout<<h[i].second<<' ';
        }
        cout<<endl;
    }
    return 0;
}
