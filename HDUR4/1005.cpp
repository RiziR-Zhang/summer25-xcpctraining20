#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<bitset>
using namespace std;

//#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 305, mS = 305;
constexpr LL mdN = 998244353;
int n, sonn[mN], fa[mN], lfson[mN];
char s[mS];
vector<int> son[mN];
LL inv[mN];
struct Flush{
    LL f;
    int nowId, visNum, kId;
    bitset<mN> visd;
    Flush(){}
    Flush(LL initVal, int initId):f(initVal), nowId(0), visNum(0), kId(initId), visd(bitset<mN>()){}
    void tryPush(){
        if(visd[nowId]) return;
        if(visNum >= lfson[kId]){
            f = 0;
            return;
        }
        visd[nowId] = 1;
        f = f * (lfson[kId] - visNum) % mdN * inv[sonn[kId] - visNum] % mdN;
        ++visNum;
    }
    LL pushFlow(){
        if(visd[nowId]) return 0;
        return f * inv[sonn[kId] - visNum] % mdN;
    }
};
struct Node{
    vector<Flush> flush;
    LL pushableF;
    void floodin(LL initVal, int initId){
        Flush newFl(initVal, initId);
        pushableF = (pushableF + newFl.pushFlow()) % mdN;
        flush.push_back(newFl);
    }
    void reset(){
        flush.clear();
        pushableF = 0;
    }
}node[mN];
void swing(int u, bool dir){
    LL pushF = 0;
    for(auto &fl: node[u].flush){
        if(dir){
            if(fl.nowId < sonn[u] - 1) fl.nowId++;
        }else{
            if(fl.nowId > 0) fl.nowId--;
        }
        pushF += fl.pushFlow();
        // if(!fl.visd[fl.nowId]) pushF += fl.f * inv[sonn[u] - fl.visNum] % mdN;
    }
    node[u].pushableF = pushF % mdN;

    for(auto v: son[u]){
        swing(v, dir);
    }
}
void distribute(int u){
    if(sonn[u] == 0) return;
    for(auto v: son[u]){
        distribute(v);
    }

    LL pushF = 0;
    for(auto &fl: node[u].flush){
        fl.tryPush();
        // if(!fl.visd[fl.nowId]) pushF += fl.f;
        pushF += fl.pushFlow();
    }
    node[u].pushableF = pushF % mdN;
    if(u != 1 && node[fa[u]].pushableF != 0){
        node[u].floodin(node[fa[u]].pushableF, u);
    }
}
LL qp(LL a, LL b){
    LL pw = 1;
    while(b){
        if(b & 1) pw = pw * a % mdN;
        a = a * a % mdN;
        b >>= 1;
    }
    return pw;
}
void mathinit(int len = 300){
    vector<LL> fac(len + 1), ifac(len + 1);
    fac[0] = ifac[0] = 1;
    for(int i = 1; i <= len; ++i) fac[i] = fac[i - 1] * i % mdN;
    ifac[len] = qp(fac[len], mdN - 2);
    for(int i = len - 1; i; --i) ifac[i] = ifac[i + 1] * (i + 1) % mdN;
    Rep(i, 1, len) inv[i] = ifac[i] * fac[i - 1] % mdN;
}
inline void ALLClear(){
    Rep(i, 1, n){
        node[i].reset();
        son[i].clear();
    }
    memset(sonn, 0, sizeof(int) *(n + 1));
    memset(lfson, 0, sizeof(int) *(n + 1));
    memset(fa, 0, sizeof(int) * (n + 1));
}
void calcAns(){
    LL ans = 0;
    vector<LL> sson(n + 1), slf(n + 1);
    Rep(i, 1, n){
        sson[fa[i]] += i;
        if(sonn[i] == 0){
            slf[fa[i]] += i;
        }
    }
    Rep(i, 1, n) sson[i] %= mdN, slf[i] %= mdN;
    Rep(u, 1, n){
        for(auto fl: node[u].flush){
            if(fl.f == 0) continue;
            if(fl.visd[fl.nowId]){
                ans += fl.f * inv[lfson[u]] % mdN * slf[u] % mdN;
            }else{//+= Flow * ((s)/(s+f-v)*sumson+ (f-v)/(s+f-v)*sumlf)
                int nlf = sonn[u] - lfson[u];
                // LL E = (1ll * nlf * (sson[u] - slf[u] + mdN) + 1ll * (lfson[u] - fl.visNum) * slf[u]) % mdN * inv[sonn[u] - fl.visNum] % mdN;
                LL E = (1ll * (sson[u] - slf[u] + mdN) + 1ll * slf[u] * inv[lfson[u]] % mdN * (lfson[u] - fl.visNum)) % mdN * inv[sonn[u] - fl.visNum] % mdN;
                ans += fl.f * E % mdN;
            }
        }
    }
    ans %= mdN;
    cout<<ans<<endl;
}
void chk(int u){
    cout<<"##"<<u<<endl;
    for(auto fl: node[u].flush){
        cout<<fl.nowId<<' '<<fl.visd.to_ulong()<<' '<<fl.visNum<<' '<<fl.f * 12 % mdN<<"/12"<<endl;
    }
    for(auto v: son[u]){
        chk(v);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    mathinit();
    while(tsk--){
        cin>>n;
        cin>>s;
        int len = strlen(s);
        Rep(i, 1, n){
            cin>>sonn[i];
            son[i].resize(sonn[i]);
            // vis[i].resize(sonn[i]);
            // visd[i] = 0;
            // nowSonId[i] = 0;
            Rpl(j, 0, sonn[i]){
                cin>>son[i][j];
                fa[son[i][j]] = i;
            }
        }
        int rt = 0;
        Rep(i, 1, n){
            if(sonn[i] == 0) lfson[fa[i]]++;
            if(fa[i] == 0) rt = i;
        }

        int now = 0;
        for(; now < len && s[now] != 'D'; ++now);
        if(n == 1 || now == len){
            cout<<rt<<endl;
            ALLClear();
            //allclear()
            continue;
        }
        node[rt].floodin(1, rt);
        for(++now; now < len; ++now){
            if(s[now] == 'D'){
                distribute(rt);
            }else{
                swing(rt, s[now] == 'R');
            }
#ifdef DEBUG
// if(n==4)
//chk(1);
#endif
        }
#ifdef DEBUG
chk(1);
#endif
        calcAns();
        ALLClear();//node
        //no allclear()
    }
    return 0;
}
