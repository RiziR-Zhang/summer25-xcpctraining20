#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005, INF = 1e9 + 1;
constexpr LL Bs = 1ll<<60, PER = 60, mask = Bs - 1;
int n, Qr, a[mN], bid[mN], Bsz, Bnum;// note next (a[i], u) = (u + a[i] + 1) / 2
struct Blk{
    LL unit[8];
    int step, L, R;
    void build(int l, int r){
        L = l, R = r;
        step = r - l + 1;
        Rep(i, l, r){
            LL x = a[i] + 1;
            int mov = i - l;
            int j = 0;
            while(mov >= PER){
                mov -= PER;
                j++;
            }
            while(x){
                if(mov){
                    unit[j] += (x & ((1 << (PER - mov)) - 1)) << mov;
                    x >>= (PER - mov);
                    mov = 0;
                }else{
                    unit[j] += x & mask;
                    x >>= PER;
                }
                if(unit[j] >= Bs){
                    unit[j] -= Bs;
                    x++;
                }
                j++;
            }
        }
    }
    int qr(LL x){
        LL vnit[8];
        memcpy(vnit, unit, sizeof(unit));
        Rpl(i, 0, 8){
            vnit[i] += x;
            if(vnit[i] >= Bs){
                vnit[i] -= Bs;
                x = 1;
            }else x = 0;
        }
        x = 0;
        Rpl(i, 0, 8){
            int bias = i * PER - step;
            if(vnit[i] != 0 && -60 <= bias && bias <= 60){
                if(bias < 0){
                    x |= vnit[i] >> (-bias);
                }else{
                    x |= vnit[i] << bias;
                }
            }
        }
        return x;
    }
}b[505];
int BS(int x){
    int l = 1, r = n + 1;
    a[r] = INF;
    while(l < r){
        int mid = (l + r) >> 1;
        if(x <= a[mid]) r = mid;
        else l = mid + 1;
    }
    return l;
}
void solve(int x, int y){
    int valx = x;
    int nowpos = BS(x + 1), nowblk = bid[nowpos];
    int exppos = n + 1 - y;
    if(nowpos > exppos){
        cout<<0<<endl;
        return;
    }
    for(; nowpos != b[nowblk].L && nowpos <= exppos; ++nowpos){
        x = (x + a[nowpos] + 1) / 2;
        if(nowpos == b[nowblk].R) ++nowblk;
    }
    for(; nowblk < Bnum && b[nowblk].R <= exppos; nowpos = b[nowblk++].R + 1){
        x = b[nowblk].qr(x);
    }
    for(; nowpos <= exppos; ++nowpos){
        x = (x + a[nowpos] + 1) / 2;
    }
    cout<<x - valx<<endl;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>Qr;
    Bsz = min((int)sqrt(n), 2);
    Rep(i, 1, n){
        cin>>a[i];
        bid[i] = i / Bsz;
    }
    Bnum = bid[n] + 1;
    Rpl(i, 0, Bnum){
        b[i].build(max(1, Bsz * i), min(Bsz * (i + 1) - 1, n));
    }
    int x, y;
    while(Qr--){
        cin>>x>>y;
//        int nowrk = BS(x);
//        int exprk = y;
        solve(x, y);
    }
    return 0;
}
