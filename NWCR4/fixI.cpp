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
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 55;
constexpr int TARG = 1, BOX = 2, WALL = 4;
#define EXS(v, w) ((v & w) == w)
int n, m, mp[mN][mN], on[mN][mN];
char s[mN][mN];
pii pos[mN];
int totb, minDisN0, minId;

int nwt, nwb;
bool vis[mN][mN];
constexpr int dx[4] = {-1, 0, 0, 1}, dy[4] = {0, -1, 1, 0};
inline bool chkis(int st, int mdl){return st & mdl;}
inline bool chkLegal(int i, int j){
    return 1 <= i && i <= n && 1 <= j && j <= m && mp[i][j] != WALL && !vis[i][j];
}
void dfs(int x, int y){
    vis[x][y] = 1;
    if(chkis(mp[x][y], TARG)) nwt++;
    if(chkis(mp[x][y], BOX)){
        nwb++;
    }
    Rpl(t, 0, 4){
        int nx = x + dx[t], ny = y + dy[t];
        if(chkLegal(nx, ny))
            dfs(nx, ny);
    }
}

int que[mN * mN], dis[mN][mN], fa[mN][mN], mfa[mN][mN];
int bfs(int id){
    memset(vis, 0, sizeof(vis));
    int fd = 0;
    int hd = 1, tl = 0, sx = pos[id].first, sy = pos[id].second;
    auto ID = [&](int i, int j){return i * m + j - 1;};
    que[++tl] = ID(sx, sy);
    
    dis[sx][sy] = 0;
    vis[sx][sy] = 1;
    while(!fd && hd <= tl){
        int x = que[hd] / m, y = que[hd] % m + 1;
        hd++;
        Rpl(t, 0, 4){
            int nx = x + dx[t], ny = y + dy[t];
            if(chkLegal(nx, ny)){
                vis[nx][ny] = 1;
                dis[nx][ny] = dis[x][y] + 1;
                fa[nx][ny] = ID(x, y);
                que[++tl] = ID(nx, ny);
                if(chkis(mp[nx][ny], TARG) && !on[nx][ny]){
                    fd = ID(nx, ny);
                    break;
                }
            }
        }
    }
    int tx = fd / m, ty = fd % m + 1;
    dis[sx][sy] = dis[tx][ty];
    return fd;
}
bool schedule(){
    int cnt = 0;
    minDisN0 = mN * mN;
    minId = 0;
    Rep(i, 1, totb){
        int x = pos[i].first, y = pos[i].second;
        if(chkis(mp[x][y], TARG)) cnt++;
        else{
            int id = bfs(i),
                thatDis = dis[id / m][id % m + 1];
            if(thatDis <= minDisN0){
                minDisN0 = thatDis;
                minId = id;
                memcpy(mfa, fa, sizeof(fa));
            }
        }
    }
    if(cnt == totb) return 0;
    return 1;
}

pii tt[mN * mN];
int tlen;
struct OP{
    pii pos;
    char op;
}opList[200005];
int opnum;
void GOOOO(){
    int id = minId;//bfs(minId);
    int xy = id, x = xy / m, y = xy % m + 1;
    for(int i = tlen = minDisN0; i >= 0; --i){
        tt[i] = pii(x, y);
        if(i != 0) xy = mfa[x][y];
        x = xy / m;
        y = xy % m + 1;
    }
    assert(on[x][y]);
    
    int nx, ny;
    for(int i = 1; i <= tlen; ++i, x = nx, y = ny){
        nx = tt[i].first, ny = tt[i].second;
        if(!on[nx][ny]){
            char c = 'R';
            if(nx == x - 1) c = 'U';
            else if(nx == x + 1) c = 'D';
            else if(ny == y - 1) c = 'L';
            opList[++opnum] = {{x, y}, c};
            pos[on[x][y]] = pii(nx, ny);
            on[nx][ny] = on[x][y];
            on[x][y] = 0;
        }
    }
    
    int lx, ly;
    for(int i = tlen - 1; i >= 0; --i, x = lx, y = ly){
        lx = tt[i].first, ly = tt[i].second;
        if(on[lx][ly]){
            char c = 'R';
            if(x == lx - 1) c = 'U';
            else if(x == lx + 1) c = 'D';
            else if(y == ly - 1) c = 'L';
            opList[++opnum] = {{lx, ly}, c};
            pos[on[lx][ly]] = pii(x, y);
            on[x][y] = on[lx][ly];
            on[lx][ly] = 0;
        }
    }
    
}
void printSol(){
    cout<<opnum<<endl;//added
    Rep(i, 1, opnum){
        cout<<opList[i].pos.first<<' '<<opList[i].pos.second<<' '<<opList[i].op<<endl;
    }
}
//#define FILE
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
        cin>>s[0];
        Rep(j, 1, m){
            char sij = s[0][j - 1];
            if(sij == '#') mp[i][j] = WALL;
            else{
                if(sij == '*' || sij == '!') mp[i][j] |= TARG;
                if(sij == '@' || sij == '!'){
                    mp[i][j] |= BOX;
                    on[i][j] = ++totb;
                    pos[totb] = pii(i, j);
                }
            }
        }
    }
    bool solvable = 1;
    Rep(i, 1, n){Rep(j, 1, n){
        if(mp[i][j] != WALL && !vis[i][j]){
            nwt = 0;
            nwb = 0;
            dfs(i, j);
            if(nwt != nwb){
                solvable = 0;
                break;
            }
        }
    }
    if(!solvable) break;
    }
    if(!solvable){
        cout<<-1<<endl;
        return 0;
    }
    
    while(schedule() != 0){
        GOOOO();//upd st, pos
    }
    printSol();
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif
    return 0;
}
/*
4 5
@#...
.#@#.
.#!#*
...#*

*/