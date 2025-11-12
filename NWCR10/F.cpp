#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 150005, mV = 1000005;
int n, a[mN], shn, fir[mN], las[mN], now[mN];
struct Ele{
    int pos, col, nx;
    Ele(){}
    Ele(int p, int c): pos(p), col(c), nx(0){}
}e[mN];
int ansl, ansr, num;
struct SGT{
    pii nd[mN << 2];
    int lz[mN << 2];
    inline int lc(int p){return p << 1;}
    inline int rc(int p){return p << 1 | 1;}
    inline void PU(int p){
        nd[p] = max(nd[lc(p)], nd[rc(p)]);
    }
    inline void assn(int p, int Lz){
        nd[p].first += Lz;
        lz[p] += Lz;
    }
    inline void PD(int p){
        if(lz[p]){
            assn(lc(p), lz[p]);
            assn(rc(p), lz[p]);
            lz[p] = 0;
        }
    }
    void buildtree(int p, int l, int r){
        lz[p] = 0;
        if(l == r){
            nd[p] = pii(0, l);
            lz[p] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        buildtree(lc(p), l, mid);
        buildtree(rc(p), mid + 1, r);
        PU(p);
    }
    void add(int p, int l, int r, int al, int ar,int dt){
        if(al <= l && r <= ar){
            assn(p, dt);
            return;
        }
        PD(p);
        int mid = (l + r) >> 1;
        if(al <= mid) add(lc(p), l, mid, al, ar, dt);
        if(mid < ar) add(rc(p), mid + 1, r, al, ar, dt);
        PU(p);
    }
    pii qry(int p, int l, int r, int ql, int qr){
        if(ql <= l && r <= qr){
            return nd[p];
        }
        PD(p);
        int mid = (l + r) >> 1;
        pii res(-1, -1);
        if(ql <= mid) res = max(res, qry(lc(p), l, mid, ql, qr));
        if(mid < qr) res = max(res, qry(rc(p), mid + 1, r, ql, qr));
        return res;
    }
}sgt;
bool ava(int x){
    ansl = -1, ansr = -1;
    bool flag = 0;
    int nowL = 0, nowR = 0, vis = 0;
    sgt.buildtree(1, 1, n);
    for(int i = 1; i <= shn; ++i){//e[i]: col, pos, ls, nx; fir, las
        nowL = e[i].pos;
        if(e[i].pos != fir[e[i].col]){
            // if(e[i].nx == las[e[i].col]){
            //     sgt.add(1, 1, n, e[i].pos, e[i].nx, -1);
            // }else{
                sgt.add(1, 1, n, e[i].pos + 1, e[i].nx, -1);
            // }
        }

        if(e[i].pos == fir[e[i].col]){
            sgt.add(1, 1, n, e[i].nx + 1, las[e[i].col], 1);
            pii res = sgt.qry(1, 1, n, nowL + 1, n);
            if(res.first >= x){
                flag = 1;
                ansl = nowL;
                ansr = res.second;
                break;
            }
        }
    }
    return flag;
}
pii b[mN];
void arr_init(){
    Rep(i, 1, n){
        b[i] = pii(a[i], i);
    }
    sort(b + 1, b + n + 1);
    // int col = 0;
    shn = 0;
    num = 0;
    for(int i = 1, j = 1; i <= n;i = j){
        // ++col;
        for(j = i; j <= n && b[j].first == b[i].first; ++j);
        if(j - i >= 3){
            ++num;
            fir[num] = b[i].second;
            las[num] = b[j - 1].second;
            Rpl(k, i, j){
                e[++shn] = Ele(b[k].second, num);
                if(k != j - 1) e[shn].nx = b[k + 1].second;
            }
        }
    }
    sort(e + 1, e + shn + 1, [](Ele p, Ele q){
        return p.pos < q.pos;
    });
}
void ALLClear(){
    memset(fir + 1, 0, sizeof(int) * num);
    memset(las + 1, 0, sizeof(int) * num);

}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        num = 0;
        Rep(i, 1, n){
            cin>>a[i];
        }
        arr_init();
        int l = 0, r = num;
        while(l < r){
            int mid = (l + r + 1) >> 1;
            if(ava(mid)){
                l = mid;
            }else{
                r = mid - 1;
            }
        }
        if(l == 0){
            cout<<0<<endl<<2<<' '<<3<<endl;
        }else{
        assert(ava(l));
        cout<<l<<endl<<ansl + 1<<' '<<ansr<<endl;
        }
        ALLClear();//cnt, pos, num
    }
    return 0;
}
