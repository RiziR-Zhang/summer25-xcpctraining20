#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef unsigned long long ULL;
typedef pair<int,int> pii;
constexpr int mN = 200005;
constexpr ULL bs = 998244353;
int m, fa[mN], lfnum;
vector<int> son[mN];

int cmpsub(int p, int q){
    int sp = son[p].size(), sq = son[q].size();
    if(!sp || !sq) return (sp == 0) - (sq == 0);
    int len = min(sp, sq);
    Rpl(i, 0, len){
        int now = cmpsub(son[p][i], son[q][i]);
        if(now != 0) return now;
    }
    return (sp > sq) - (sp < sq);
}
bool lesssub(int p, int q){
    return cmpsub(p, q) == 1;
}
void dfspre(int u){
    if(son[u].size() == 0){
        lfnum++;
        return;
    }
    for(auto v: son[u]){
        dfspre(v);
    }
    sort(son[u].begin(), son[u].end(), lesssub);
}
void print(int u, ULL pre){
    if(!son[u].size()){
        cout<<pre<<endl;
        return;
    }
    int c = 0;
    for(auto v: son[u]){
        ++c;
        print(v, pre * bs + c);
    }
}
void solve(){
    cin>>m;
    Rep(i, 2, m){
        cin>>fa[i];
        son[fa[i]].push_back(i);
    }
    lfnum = 0;
    dfspre(1);
    cout<<lfnum<<endl;
    print(1, 0);
}
void ALLClear(){
    Rep(i, 1, m){
        son[i].clear();
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        solve();
        ALLClear();//son, dep, sz, hson, lfnum, trie, reson
    }
    return 0;
}
