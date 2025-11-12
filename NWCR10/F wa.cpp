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
priority_queue<int, vector<int>, greater<int> > pq;
struct BIT{
    int tr[mN];
    inline int lb(int p){return p & (-p);}
    void add(int p, int d){
        while(p <= n) tr[p] += d, p += lb(p);
    }
    int qry(int p){
        int s = 0;
        while(p) s += tr[p], p ^= lb(p);
        return s;
    }
}bit;
int ansl, ansr, num;
bool ava(int x){
    ansl = -1, ansr = -1;
    bool flag = 0;
    int nowL = 0, nowR = 0, vis = 0;
    for(int i = 1; i <= shn; ++i){//e[i]: col, pos, ls, nx; fir, las
        nowL = e[i].pos;
        if(now[e[i].col] == e[i].pos){
            bit.add(i, -1);
        }
        if(e[i].nx && e[e[i].nx].nx){
            bit.add(e[i].nx, 1);
            now[e[i].col] = e[i].nx;
        }else{
            now[e[i].col] = 0;
        }
        if(e[i].pos == fir[e[i].col]){
            ++vis;
            pq.push(las[e[i].col]);
            if(vis >= x){
                if(vis > x){
                    pq.pop();
                }
                nowR = pq.top();
                if(nowL >= nowR) continue;
                else if(bit.qry(nowR - 1) - bit.qry(nowL) >= x){
                    flag = 1;
                    ansl = nowL;
                    ansr = nowR;
                    break;
                }
            }
        }
    }
    while(!pq.empty()) pq.pop();
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
        // disk();
        // Rep(i, 1, n){
        //     pos[a[i]].push_back(i);
        //     if(++cnt[a[i]] == 3){
        //         ++num;
        //     }
        // }
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
