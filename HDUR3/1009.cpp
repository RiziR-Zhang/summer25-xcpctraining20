#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
//using namespace std;
// #define FILE
#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005, mSeg = 200005;
constexpr LL mdN = 1e9 + 7, inv10 = 700000005;
int n, m, st[mN], ed[mN];
LL a[mN], p[mN], f[mN], g[mN];
vector<int> ls[mN];
struct Seg{
    int l, r;
}seg[mSeg];
inline void ALLClear(){
    memset(st + 1, 0, sizeof(int) * n);
    memset(ed + 1, 0, sizeof(int) * n);
    Rep(i, 1, n){
        ls[i].assign(0, 0);
    }
}
int main()
{
#ifdef FILE
freopen("1009.in","r",stdin);
freopen("1009.out","w",stdout);
#endif
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>m;
        Rep(i, 1, n){
            cin>>a[i];
            p[i] = a[i] * inv10 % mdN;
        }
        Rep(i, 1, m){
            cin>>seg[i].l>>seg[i].r;
            // seg[i].l--;

            st[seg[i].l]++;
            ed[seg[i].r]++;
            ls[seg[i].r].push_back(i);
        }
        f[0] = 1;
        g[0] = 1;
        int seql = 0, seqr = -1, seqNum = 0;
        f[0] = g[0] = 1;
        LL sinceBegin = 0, untilEnd = 0, mulP = 1;
        LL lastEnd = 0, lastId = 0;
        if(st[1] != 0){
            seqr = 0;
            ++seqNum;
            f[1] = g[1] = 1;
            seql = 1; seqr = -1;
        }
        Rep(x, 1, n){
            mulP = mulP * (1 - p[x] + mdN) % mdN;
            sinceBegin += st[x];
            untilEnd += ed[x];
            if(ed[x] || st[x + 1]){
                seqr = x;
                ++seqNum;
                LL pSeqCol = (1 - mulP + mdN) % mdN;
                int miniSeg = 0;
                for(auto id: ls[x]){
                    miniSeg = max(miniSeg, seg[id].l);
                }
                f[seqNum] = (pSeqCol * g[seqNum - 1]
                         + (1 - pSeqCol + mdN) * (sinceBegin ? 0 : f[seqNum - 1])) % mdN;
                if(!untilEnd){
                    g[seqNum] = g[seqNum - 1];
                }else{
                    g[seqNum] = f[lastId] * 
                    lastEnd = ;
                }
                seql = x + 1; seqr = -1;
                mulP = 1;
                sinceBegin = 0;
                untilEnd = 0;
            }
        }
#ifdef DEBUG
cout<<"tsk"<<tsk<<' ';
#endif
        assert(f[seqNum] == g[seqNum]);
        cout<<g[seqNum]<<endl;
        ALLClear();
    }
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif
    return 0;
}
