#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 500005;
int n;
LL a[mN];
int ctop[65];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        Rep(i, 1, n){
            cin>>a[i];
        }
        if(n > 60){
            cout<<"NO"<<endl;
            continue;
        }
        bool fg = 1;
        Rep(i, 1, n){
            LL x = a[i];
            for(int d = 0; x; ++d, x >>= 1){
                if(x & 1){
                    if((ctop[d] & 2) || ((ctop[d] & 1) && (x == 1))){
                        fg = 0;
                        break;
                    }
                    if(x == 1) ctop[d] |= 2;
                    else ctop[d] |= 1;
                }
            }
            if(!fg) break;
        }
        if(fg == 0){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
        memset(ctop, 0, sizeof(ctop));
    }
    return 0;
}
