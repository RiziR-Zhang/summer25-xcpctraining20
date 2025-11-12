#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;

//#define DEBUG
//#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;
typedef long long ll;

constexpr int mN = 55;
int n, m;
char s[mN][mN];
vector<pair<pii, char> > op;
bool exs[mN][mN], meet[mN][mN][mN];
pii nowxy[mN];
inline int ID(int x, int y){return (x - 1) * m + y;}
inline pii coor(int id){int x = (id - 1) / m + 1;return pii(x, id - (x - 1) * m);}

namespace Flow{
#define Vis(u) for(int i = fir[u]; i; i = e[i].nxt)
//#define FlowDebug
typedef int FlowScale;///< modify available
constexpr int N = 2505, M = 15005;///< modify available
constexpr FlowScale INF = 1e9;///< modify available
template<typename T>T mn(T P, T Q){return P<Q?P:Q;}

int _V_, _E_, targ, dep[N], cur[N], fir[N], flow_egn = 1;
bool initted = 0;
struct Eg{
    int v, nxt;
    FlowScale cap, flow;
}e[(M << 1) + 5];
inline void addSingleEg(int u, int v, FlowScale cap){
    e[++flow_egn] = Eg{v, fir[u], cap, 0};
    fir[u] = flow_egn;
}
inline void addEdge(int u, int v, FlowScale cap){
    addSingleEg(u, v, cap);
    addSingleEg(v, u, 0);
}
void init(int _v_){
    initted = 1;
    _V_ = _v_;
    flow_egn = 1;
    memset(fir, 0, sizeof(int) * (_V_ + 1));
}
int que[N], hd, tl;
bool bfs(int S, int T){
    memset(dep, 0xff, sizeof(int) * (_V_ + 1));
    assert(dep[0] == -1);
    dep[S] = 0;
    que[hd = tl = 0] = S;
    int u, v;
    while(hd <= tl){
        u = que[hd++];
#ifdef FlowDebug
        cout<<"#"<<u<<" dep:"<<dep[u]<<endl;
#endif
        Vis(u){
            v = e[i].v;
#ifdef FlowDebug
            cout<<'\t'<<v<<" //"<<e[i].flow<<' '<<e[i].cap<<endl;
#endif
            if(e[i].flow < e[i].cap && dep[v] == -1){
                dep[v] = dep[u] + 1;
                que[++tl] = v;
            }
        }
    }
    return dep[T] != -1;
}
FlowScale dfs(int u, FlowScale sflow){
    if(!sflow || u == targ) return sflow;
    FlowScale uzflow = 0, dflow;
    int v;
    for(int &i = cur[u]; i; i = e[i].nxt){
        v = e[i].v;
        if(dep[v] == dep[u] + 1 && e[i].flow < e[i].cap && (dflow = dfs(v, mn(sflow - uzflow, (FlowScale)(e[i].cap - e[i].flow)))) != 0){
            uzflow += dflow;
            e[i].flow += dflow;
            e[i ^ 1].flow -= dflow;
            if(uzflow == sflow) break;
        }
    }
    return uzflow;
}
FlowScale dinic(int S, int T){
    assert(initted);
    FlowScale maxflow = 0;
    targ = T;
    while(bfs(S, T)){
#ifdef FlowDebug
        cout<<dep[T]<<"after maxflow = "<<maxflow<<endl;
#endif
        memcpy(cur, fir, sizeof(int) * (_V_ + 1));
        maxflow += dfs(S, INF);
    }
    initted = 0;
    return maxflow;
}
void printSol(int S, int T){
    int num = 0;

    Vis(S){
        int v = e[i].v;
        auto co = nowxy[++num] = coor(v);
        exs[co.first][co.second] = 1;
        meet[num][co.first][co.second] = 1;
    }
    bool movable = 1;
    while(movable){
        movable = 0;
        Rep(id, 1, num){
            Vis(ID(nowxy[id].first, nowxy[id].second)){
                int v = e[i].v;
                if(v == S || v == T) continue;
                auto co = coor(v);
                if(e[i].flow && !exs[co.first][co.second] && !meet[id][co.first][co.second]){
                    exs[co.first][co.second] = 1;
                    exs[nowxy[id].first][nowxy[id].second] = 0;
                    char dir = 0;
                    if(co.first > nowxy[id].first) dir = 'D';
                    else if(co.first < nowxy[id].first) dir = 'U';
                    else if(co.second > nowxy[id].second) dir = 'R';
                    else dir = 'L';
                    op.push_back(make_pair(nowxy[id], dir));
                    nowxy[id] = co;
                    e[i].flow--;
                    e[i ^ 1].flow++;
                    movable = 1;
                    meet[id][co.first][co.second] = 1;
                    break;
                }
            }
        }

    }
    cout<<op.size()<<endl;
    for(auto opi: op){
        cout<<opi.first.first<<' '<<opi.first.second<<' '<<opi.second<<endl;
    }
}

}
using Flow::init;
using Flow::addEdge;


int main()
{
#ifdef FILE
freopen("I.in","r",stdin);
freopen("I.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    Rep(i, 1, n){
        cin>>s[i];
        for(int j = m; j >= 1; --j) s[i][j] = s[i][j - 1];
    }
    init(n * m + 2);
    int S = n * m + 1, T = n * m + 2, cnt = 0;
    Rep(i, 1, n)Rep(j, 1, m){
        if(s[i][j] == '#') continue;
        if(i > 1 && s[i - 1][j] != '#') addEdge(ID(i, j), ID(i - 1, j), Flow::INF);
        if(j > 1 && s[i][j - 1] != '#') addEdge(ID(i, j), ID(i, j - 1), Flow::INF);
        if(i < n && s[i + 1][j] != '#') addEdge(ID(i, j), ID(i + 1, j), Flow::INF);
        if(j < m && s[i][j + 1] != '#') addEdge(ID(i, j), ID(i, j + 1), Flow::INF);
        if(s[i][j] == '@' || s[i][j] == '!') addEdge(S, ID(i, j), 1), ++cnt;
        if(s[i][j] == '*' || s[i][j] == '!') addEdge(ID(i, j), T, 1);
    }
    if(Flow::dinic(S, T) != cnt){
        cout<<-1<<endl;
    }else{
#ifdef DEBUG
cout<<"exist"<<endl;
#endif
        Flow::printSol(S, T);
    }
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif
    return 0;
}
