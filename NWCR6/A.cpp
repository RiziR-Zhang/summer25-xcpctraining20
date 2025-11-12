#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<cassert>
using namespace std;

//#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005;
int n, fa[mN], hson[mN], sz[mN];
pii dom[mN];
vector<int> e[mN];
struct Node{int deg, isSing;Node(int D = 0, int I = 0): deg(D), isSing(I){}};
map<int, Node> mp[mN];
int oddn[mN], singn[mN], mlen, bel[mN];
void dfspre(int u){
    sz[u] = 1;
    hson[u] = 0;
    for(auto v: e[u]){
        if(v == fa[u]) continue;
        fa[v] = u;
        dfspre(v);
        if(!hson[u] || sz[v] > sz[hson[u]]){
            hson[u] = v;
        }
    }
}
int ans[mN], len;
inline Node merge(int id, Node u, Node v){
    if(u.isSing && v.deg > 0) singn[id]--;
    else if(v.isSing &&u.deg == 0) singn[id]++;
    u.isSing = (u.isSing && v.deg == 0) || (v.isSing && u.deg == 0);
    if(v.deg & 1){
        if(u.deg & 1) oddn[id]--;
        else oddn[id]++;
    }
    u.deg += v.deg;
    return u;
}
void dfssolve(int u, int mpid){
    bel[u] = mpid;
    if(hson[u]){
        int hs = hson[u];
        dfssolve(hs, mpid);
        for(auto v: e[u]){
            if(v == fa[u] || v == hs) continue;
            ++mlen;
            dfssolve(v, mlen);
            for(auto ele: mp[bel[v]]){
                int k = ele.first;
                Node nd = ele.second;
                Node tar = merge(mpid, mp[mpid][k], nd);
                mp[mpid][k] = tar;
            }
            mp[bel[v]].clear();
        }
    }
    int k = dom[u].first;
    if(dom[u].first == dom[u].second){
        Node tar = merge(mpid, mp[mpid][k], Node(2, 1));
        mp[mpid][k] = tar;
    }else{
        Node tar = merge(mpid, mp[mpid][k], Node(1, 0));
        mp[mpid][k] = tar;
        k = dom[u].second;
        tar = merge(mpid, mp[mpid][k], Node(1, 0));
        mp[mpid][k] = tar;
    }
    ans[u] = oddn[mpid] / 2 + singn[mpid];
#ifdef DEBUG
    cout<<"#"<<u<<endl;
    for(auto ele: mp[mpid]){
        cout<<ele.first<<":"<<ele.second.deg<<' '<<ele.second.isSing<<endl;
    }
#endif
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    Rep(i, 1, n){
        cin>>dom[i].first;//>>dom[i].second;
    }
    Rep(i, 1, n){
        cin>>dom[i].second;
    }
    int u, v;
    Rpl(i, 1, n){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    mlen = 1;
    dfspre(1);
    dfssolve(1, mlen);
    Rep(i, 1, n){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
    return 0;
}
