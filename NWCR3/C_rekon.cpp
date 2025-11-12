#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;

#define DEBUG
//#define MULTASK
//#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005, Sigma = 26, INF = mN, nINF = -1;
int n, q, a[mN];
char s[mN];
int st_ls[Sigma + 3], st_rs[Sigma + 3];
bool exs[Sigma];
struct Node{
    int l, r;//, sxor, sor;
    int fir[Sigma + 3], las[Sigma + 3], sans, nfir, nlas;//, nrsin[2], nrmul[2], mlen, subans;
    inline int bit(int x){return 1 << x;}
    Node(){}
    Node(int idx, int sing){
        l = r = idx;
        sans = 1;
        nfir = nlas = 1;
        fir[nfir] = las[nlas] = l;
        fir[2] = r + 1;
        las[2] = l - 1;
    }
    inline bool parity(int x){
        x ^= (x >> 16);x ^= (x >> 8);x ^= (x >> 4);
        x ^= (x >> 2);x ^= (x >> 1);return x & 1;
    }
    inline int myLen(){
        return r - l + 1;
    }
// #define myLen() r - l + 1
    void upd(const Node& L, const Node& R){
        l = L.l, r = R.r;
        sans = max(L.sans, R.sans);
        int llas = L.nlas, rfir = R.nfir;
        Rep(i, 1, llas){
            st_rs[i] = st_rs[i - 1] | bit(a[L.las[i]]); 
        }
        Rep(i, 1, rfir){
            st_ls[i] = st_ls[i - 1] | bit(a[R.fir[i]]);
        }
        for(int i = llas; i >= 1; --i){
            for(int j = rfir; j >= 1; --j){
                int len = R.fir[j + 1] - L.las[i + 1] - 1;
                if(len < sans) break;
                if(parity(st_rs[i] | st_ls[j])){
                    if(len & 1) sans = max(sans, len);
                    else if(R.fir[j + 1] - R.fir[j] != 1 || L.las[i] - L.las[i + 1] != 1){
                        sans = max(sans, len - 1);
                    }
                }
            }
        }
        nfir = nlas = 0;
        memset(exs, 0, sizeof(exs));
        Rep(i, 1, L.nfir){
            exs[a[L.fir[i]]] = 1;
            fir[++nfir] = L.fir[i];
        }
        Rep(i, 1, rfir){
            if(!exs[a[R.fir[i]]]){
                exs[a[R.fir[i]]] = 1;
                fir[++nfir] = R.fir[i];
            }
        }
        memset(exs, 0, sizeof(exs));
        Rep(i, 1, R.nlas){
            exs[a[R.las[i]]] = 1;
            las[++nlas] = R.las[i];
        }
        Rep(i, 1, llas){
            if(!exs[a[L.las[i]]]){
                exs[a[L.las[i]]] = 1;
                las[++nlas] = L.las[i];
            }
        }
        fir[nfir + 1] = r + 1;
        las[nlas + 1] = l - 1;
    }
};
struct SGT{
    Node tr[mN << 2];
    inline int lc(int p){return p << 1;}
    inline int rc(int p){return p << 1 | 1;}
    void buildtree(int p, int l, int r){
        if(l == r){
            tr[p] = Node(l, a[l]);
            return;
        }
        int mid = (l + r) >> 1;
        buildtree(p << 1, l, mid);
        buildtree(p << 1 | 1, mid + 1, r);
        tr[p].upd(tr[lc(p)], tr[rc(p)]);//PU(p);
    }
    void buildtree_asolve(){
        buildtree(1, 1, n);
        cout<<tr[1].sans<<endl;
    }
    void mdf(int p, int l, int r, int idx, int sing){
        if(l == r){
            tr[p] = Node(l, sing);
            return;
        }
        int mid = (l + r) >> 1;
        if(idx <= mid) mdf(p << 1, l, mid, idx, sing);
        else mdf(p << 1 | 1, mid + 1, r, idx, sing);
        tr[p].upd(tr[lc(p)], tr[rc(p)]);//PU(p);
    }
    void mdf_asolve(int idx, int sing){
        mdf(1, 1, n, idx, sing);
        cout<<tr[1].sans<<endl;
    }
}sgt;
int main()
{
#ifdef FILE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef MULTASK
Rep(tsk, 1, 1000){
#endif
    cin>>n>>q;
    cin>>s;
    Rep(i, 1, n){
        a[i] = s[i - 1] - 'a';
    }
    int idx;
    char t[3];
    sgt.buildtree_asolve();//&solve
    while(q--){
        cin>>idx>>t;
        a[idx] = t[0] - 'a';
        sgt.mdf_asolve(idx, t[0] - 'a');
    }
#ifdef MULTASK
}
#endif
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif
    return 0;
}
