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
constexpr int mN = 200005;
string s;
int n;
struct Node{
    int lestR, restL, mgd;
    Node():lestR(0), restL(0), mgd(0){}
    Node(int lR, int rL, int mg): lestR(lR), restL(rL), mgd(mg){}
    Node(char sing): lestR(sing=='R'), restL(sing=='L'), mgd(0){}
    int numR(){return lestR + mgd;}
    int numL(){return restL + mgd;}
    void MG(Node ls, Node rs){
        lestR = ls.lestR + max(0, rs.lestR - ls.restL);
        restL = rs.restL + max(0, ls.restL - rs.lestR);
        mgd = ls.mgd + rs.mgd + min(ls.restL, rs.lestR);
    }
}nd;
struct SGT{
    Node nd[mN << 2];
    inline int lc(int p){return p << 1;}
    inline int rc(int p){return p << 1 | 1;}
    inline void PU(int p){
        nd[p].MG(nd[lc(p)], nd[rc(p)]);
        // nd[p] = Node(nd[lc(p)].lestR + max(0, nd[rc(p)].lestR - nd[lc(p)].restL),
        //              nd[rc(p)].restL + max(0, nd[lc(p)].restL - nd[rc(p)].lestR),
        //              nd[lc(p)].mgd + nd[rc(p)].mgd + min(nd[lc(p)].restL, nd[rc(p)].lestR));
    }
    void buildtree(int p, int l, int r){
        if(l == r){
            nd[p] = Node(s[l]);
            return;
        }
        int mid = (l + r) >> 1;
        buildtree(lc(p), l, mid);
        buildtree(rc(p), mid + 1, r);
        PU(p);
    }
    void mdf(int p, int l, int r, int pos){
        if(l == r){
            nd[p] = Node(s[l]);
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) mdf(lc(p), l, mid, pos);
        else mdf(rc(p), mid + 1, r, pos);
        PU(p);
    }
    Node qry(int p, int l, int r, int ql, int qr){
        if(ql <= l && r <= qr) return nd[p];
        int mid = (l + r) >> 1;
        Node res;
        if(ql <= mid && mid < qr) res.MG(qry(lc(p), l, mid, ql, qr), qry(rc(p), mid + 1, r, ql, qr));
        else if(ql <= mid) res = qry(lc(p), l, mid, ql, qr);
        else res = qry(rc(p), mid + 1, r, ql, qr);
        return res; 
    }
    int solve(){
        if(nd[1].numL() == 0 || nd[1].numR() == 0) return 0;
        int u = 1, l = 1, r = n;// first R
        while(l < r){
            int mid = (l + r) >> 1;
            if(nd[lc(u)].numR()) u = lc(u), r = mid;
            else u = rc(u), l = mid + 1;
        }
        int firstR = l;
        int v = 1;
        l = 1, r = n;
        while(l < r){
            int mid = (l + r) >> 1;
            if(nd[rc(v)].numL()) v = rc(v), l = mid + 1;
            else v = lc(v), r = mid;
        }
        int lastL = l;
        if(firstR > lastL) return 0;
        
        Node qr = qry(1, 1, n, firstR, lastL);
        return qr.lestR + qr.restL - 1 + qr.mgd;
    }
}sgt;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int Qr;
    cin>>n>>Qr;
    cin>>s;
    s = " " + s;
    sgt.buildtree(1, 1, n);
    while(Qr--){
        int pos;
        cin>>pos;
        s[pos] = 'L' + 'R' - s[pos];
        sgt.mdf(1, 1, n, pos);
        cout<<sgt.solve()<<endl;
    }
    return 0;
}
