#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
#include<cassert>
using namespace std;

//#define DEBUG
//#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 1e5 + 5, mM = 4e5 + 5, PARAM = 30 + 5;
int n, m;
struct Edge{
    int u, v, a;
}e[mM];
vector<int> out[mN];
int in[mN], que[mN], hd, tl, longst[mN], longstn0[mN], sp[mN][PARAM];
void ALLClear(){
    Rep(i, 1, n){
        out[i].clear();
        //assert(out[i].size() == 0);
        in[i] = 0;
    }
}
inline bool judgegt(pii a, pii b){
    LL P = a.first, Q = b.first;
    LL L = a.second, M = b.second;
    if(P == 0) return 0;
    if(Q == 0) return 1;
    if(L < 40 && M < 40){
        return 1.0 * P * (pow(2, L) - 1) / L > 1.0 * Q * (pow(2, M) - 1) / M;
    }else{
        double lnpm = log2(P * M), lnql = log2(Q * L);
        return lnpm * L > lnql * M;
    }
}
typedef __int128 i128;

pii gmax(pii x,pii y)
{
	if(!x.first||!x.second) return y;
	if(!y.first||!y.second) return x;
	if(x.second<y.second) swap(x,y);
	if(x.second-y.second>40) return x;
	if(x.second<=80){
		i128 cx=((((i128)1)<<x.second)-1)*x.first*y.second;
		i128 cy=((((i128)1)<<y.second)-1)*y.first*x.second;
		if(cx>cy) return x;else return y;
	}
	i128 tx=1ll*x.first*y.second;
	i128 ty=1ll*y.first*y.second;
	i128 cx=(tx<<(x.second-y.second)),cy=ty;
	if(cx>cy) return x;
	if(cx<cy) return y;
	return tx<ty?x:y;
}
constexpr LL mdN = 998244353;
LL qpow(LL a, LL b){
    LL ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mdN;
        a = a * a % mdN;
        b >>= 1;
    }
    return ans;
}
LL Ans(pii base){
#ifdef DEBUG
    cout<<"base = "<<base.first<<" "<<base.second<<endl;
#endif
    return qpow(10000, mdN - 2) * base.first % mdN
        * (qpow(2, base.second) - 1) % mdN * qpow(base.second, mdN - 2) % mdN;
}
int main()
{
#ifdef FILE
    freopen("1003.in", "r", stdin);
    freopen("1003.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>m;
        Rep(i, 1, m){
            cin>>e[i].u>>e[i].v>>e[i].a;
            out[e[i].u].push_back(i);
            in[e[i].v]++;
        }
        int hd = 1, tl = 0;
        Rep(i, 1, n){
            longst[i] = longstn0[i] = -1;
            memset(sp[i], 0xff, sizeof(int) * 31);//sigma_p
            if(in[i] == 0){
                longst[i] = 0;
                longstn0[i] = -1;
//                f[i][0] = 0;
                que[++tl] = i;
            }
        }
        while(hd <= tl){
            int u = que[hd++];
            for(auto i: out[u]){
                int v = e[i].v,
                    p = e[i].a;
                longst[v] = max(longst[v], longst[u] + 1);

                int tp = longstn0[u];
                if(p != 0 && longst[u] > longstn0[u]){
                    tp = longst[u];
                }
                if(tp == -1){
                    if(--in[v] == 0) que[++tl] = v;
                    continue;
                }
                
                if(longstn0[v] == -1){
                    longstn0[v] = tp + 1;
                }else if(longstn0[v] < tp + 1){
                    int delta = (tp + 1) - longstn0[v];
                    for(int j = 30; j >= delta; --j){
                        sp[v][j] = sp[v][j - delta];
                    }
                    for(int j = min(delta - 1, 30); j >= 0; --j){
                        sp[v][j] = -1;
                    }
                }
                longstn0[v] = max(longstn0[v], tp + 1);

                int bias;
                if(longst[u] > longstn0[u] && p != 0){
                    bias = longstn0[v] - (longst[u] + 1);
                    if(bias <= 30)
                    sp[v][bias] = max(sp[v][bias], p);
                }
                bias = longstn0[v] - (longstn0[u] + 1);
                for(int j = 0; j <= 30 && j + bias <= 30 && j < longstn0[u]; ++j){
                    if(sp[u][j] != -1)
                    sp[v][j + bias] = max(sp[v][j + bias], sp[u][j] + p);
                }
                if(--in[v] == 0){
                    que[++tl] = v;
                }
            }
        }
        pii ans(0, 1);
        double refer = 0;
        Rep(i, 1, n){
            if(out[i].size() == 0){
                //updans();
#ifdef DEBUG
cout<<"#"<<i<<','<<longstn0[i]<<endl;
#endif
                for(int j = 0; j <= 30 && j < longstn0[i]; ++j){
#ifdef DEBUG
cout<<j<<":"<<sp[i][j]<<endl;
#endif
                    if(sp[i][j] > 0){// && judgegt(pii(sp[i][j], longstn0[i] - j), ans)){
//                        ans = pii(sp[i][j], longstn0[i] - j);
                        ans = gmax(ans, pii(sp[i][j], longstn0[i] - j));
                    }
                    // if(sp[i][j] > 0)
                //    ans = max(ans, pii(sp[i][j], longstn0[i] - j));
                }
            }
        }
        cout<<Ans(ans)<<endl;
        ALLClear();
    }
#ifdef FILE
    fclose(stdin); fclose(stdout);
#endif
    return 0;
}
