/*XORpopcount is odd, ORpopcount is odd
* sxor, sor

odd wrong even wrong 删掉一个复点
要维护到最近复点的距离(LR)，* first, last[26]

odd wrong even right 删掉一个单点
要维护到最近单点的距离同理(LR)

odd right even wrong 删掉一个单点一个复点

\sigma nlogn*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;

#define DEBUG
#define MULTASK
#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005, Sigma = 26, INF = mN, nINF = -1;
int n, q, a[mN];
char s[mN];

struct Node{
    int l, r, sxor, sor;
    int fir[Sigma], las[Sigma], nrsin[2], nrmul[2], mlen, subans;
    inline int bit(int x){return 1 << x;}
    Node(){}
    Node(int idx, int sing){
        l = r = idx;
        sxor = sor = bit(sing);
        Rpl(i, 0, Sigma){
            fir[i] = INF;
            las[i] = nINF;
        }
        fir[sing] = las[sing] = idx;
        nrsin[0] = nrsin[1] = idx;
        nrmul[0] = INF;
        nrmul[1] = nINF;
        mlen = subans = 1;
    }
    inline bool parity(int x){
        x ^= (x >> 16);x ^= (x >> 8);x ^= (x >> 4);
        x ^= (x >> 2);x ^= (x >> 1);return x & 1;
    }
    inline int myLen(){
        return r - l + 1;
    }
// #define myLen() r - l + 1
    void upd(){
        bool ODD = parity(sxor), EVEN = parity(sor) ^ ODD ^ 1;
        nrsin[0] = nrmul[0] = INF;
        nrsin[1] = nrmul[1] = nINF;
        Rpl(i, 0, Sigma){
            if(fir[i] == INF) continue;
            if(fir[i] == las[i]){
                nrsin[0] = min(nrsin[0], fir[i]);
                nrsin[1] = max(nrsin[1], fir[i]);
            }else{
                nrmul[0] = min(nrmul[0], fir[i]);
                nrmul[1] = max(nrmul[1], las[i]);
                nrsin[0] = min(nrsin[0], las[i]);
                nrsin[1] = max(nrsin[1], fir[i]);
            }
        }
        if(ODD && EVEN){
            mlen = myLen();
        }else if(!ODD && !EVEN){
            // if(nrmul[0] == l || nrmul[1] == r){
            //     mlen = myLen() - 1;//+ 1 - 1;
            // }else{
                int moreDel = min(nrmul[0] - l, r - nrmul[1]);
                if(moreDel & 1){
                    mlen = myLen() - moreDel - 2;
                }else{
                    mlen = myLen() - moreDel - 1;
                }
            // }
        }else if(!ODD && EVEN){
            int moreDel = min(nrsin[0] - l, r - nrsin[1]);
            if(moreDel & 1){
                mlen = myLen() - moreDel - 2;
            }else{
                mlen = myLen() - moreDel - 1;
            }
        }else{
            assert(nrsin[0] == l || nrmul[0] == l);
            assert(nrsin[1] == r || nrmul[1] == r);
            bool sameSin = (l == nrsin[0] && r == nrsin[1]);
            bool sameMul = (l == nrmul[0] && r == nrmul[1]);
            if(sameSin){
                int Del = min(nrmul[0] - l, r - nrmul[1]);
                if(Del & 1){mlen = myLen() - Del - 1;}
                else{mlen = myLen() - Del - 2;}
            }else if(sameMul){
                int Del = min(nrsin[0] - l, r - nrsin[1]);
                if(Del & 1){mlen = myLen() - Del - 1;}
                else{mlen = myLen() - Del - 2;}
            }else{
                mlen = myLen() - 2;
            }
        }
        assert(mlen % 2 == 1);
    }
};
struct SGT{
    Node tr[mN << 2];
    inline int lc(int p){return p << 1;}
    inline int rc(int p){return p << 1 | 1;}
    inline void PU(int p){
        tr[p].sxor = tr[lc(p)].sxor ^ tr[rc(p)].sxor;
        tr[p].sor = tr[lc(p)].sor | tr[rc(p)].sor;
        Rpl(i, 0, Sigma){
            tr[p].fir[i] = min(tr[lc(p)].fir[i], tr[rc(p)].fir[i]);
            tr[p].las[i] = max(tr[lc(p)].las[i], tr[rc(p)].las[i]);
        }
        tr[p].upd();//nrsin, nrmul, mlen
        tr[p].subans = max(max(tr[lc(p)].subans, tr[rc(p)].subans), tr[p].mlen);
        if(p == 1&& n > 1) {assert(tr[p].mlen >= max(tr[lc(p)].subans, tr[rc(p)].subans));}
    }
    void buildtree(int p, int l, int r){
        tr[p].l = l; tr[p].r = r;
        if(l == r){
            tr[p] = Node(l, a[l]);
            return;
        }
        int mid = (l + r) >> 1;
        buildtree(p << 1, l, mid);
        buildtree(p << 1 | 1, mid + 1, r);
        PU(p);
    }
    void buildtree_asolve(){
        buildtree(1, 1, n);
        cout<<tr[1].subans<<endl;
    }
    void mdf(int p, int l, int r, int idx, int sing){
        if(l == r){
            tr[p] = Node(l, sing);
            return;
        }
        int mid = (l + r) >> 1;
        if(idx <= mid) mdf(p << 1, l, mid, idx, sing);
        else mdf(p << 1 | 1, mid + 1, r, idx, sing);
        PU(p);
    }
    void mdf_asolve(int idx, int sing){
        mdf(1, 1, n, idx, sing);
        cout<<tr[1].subans<<endl;
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
        sgt.mdf_asolve(idx, t[0] - 'a');
        a[idx] = t[0] - 'a';
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
