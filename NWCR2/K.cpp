#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;

#define DEBUG
//#define MINI
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
//typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 10005;
constexpr int mdN = 998244353;
int n, k;
char s[mN];
int lcp[mN], d[mN], s_int[mN];
bool qual[mN];
int tot;
struct Node{
    int sz, ch[2];//, ed;
    Node() : sz(0), ch{-1, -1}/*, ed(0)*/ {}
};
struct Trie{
    vector<Node> nd;
    int sz;
    Trie() : nd(1), sz(1) {}
    int getEd(int p){
        int sz = nd[p].sz;
        if(nd[p].ch[0] != -1) sz -= nd[nd[p].ch[0]].sz;
        if(nd[p].ch[1] != -1) sz -= nd[nd[p].ch[1]].sz;
        return sz;
    }
    void insert(int l, int r, int cnt){
        int p = 0;
        nd[0].sz += cnt;
        Rep(i, l, r){
            if(nd[p].ch[s_int[i]] == -1){
                nd.push_back(Node());
                nd[p].ch[s_int[i]] = sz++;
            }
            p = nd[p].ch[s_int[i]];
            nd[p].sz += cnt;
            if(qual[i]){
//                nd[p].ed++;
                cnt--;
            }
        }
        assert(cnt == 0);
    }
    int query(int rk){
        int p = 0;
        int x = 0;
        while(p != -1){
            int ed = getEd(p);
            if(ed){
                if(rk <= ed){
                    break;
                }else{
                    rk -= ed;
                }
            }
            if(nd[p].ch[0] != -1 && rk <= nd[nd[p].ch[0]].sz){
                p = nd[p].ch[0];
                cout<<'0';
                x = x * 2;
            }else{
                if(nd[p].ch[0] != -1){
                    rk -= nd[nd[p].ch[0]].sz;
                }
                p = nd[p].ch[1];
                cout<<'1';
                x = x * 2 + 1;
            }
            if(x >= mdN) x -= mdN;
        }
        cout<<'\n';
        assert(p != -1);
        return x;
    }
}trie;
void preprocess(){
    Rep(i, 1, n){
        s_int[i] = (s[i] == '1');
    }
    for(int i = n - 1; i >= 1; --i){
        for(int j = i + 1; j <= n; ++j){
            if(s[i] == s[j]){
                lcp[j] = lcp[j + 1] + 1;
            }else{
                lcp[j] = 0;
            }
            if(j - (i + lcp[j]) <= k){
                int len = max((j - k) - i, 1);
                d[j + len - 1]++;
                len = min(lcp[j], j - i);
                d[j + len - 1 + 1]--;
            }            
        }
        int pre = 0, r = 0, cnt = 0;
        for(int j = i + 1; j <= n; ++j){
            pre += d[j];
            qual[j] = (pre > 0);
            if(qual[j]){
                r = j;
                ++cnt;
            }
        }
        tot += cnt;
        trie.insert(i, r, cnt);
        memset(d + i, 0, sizeof(int) * (n - i + 1 + 1));
    }
    assert(tot != 0);
}
int F(int rem, int v){
    return (rem + v - 1) % tot + 1;
}
int solve(int q){
    return trie.query(q);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    cin>>s;
    for(int i = n + 1; i >= 1; --i) s[i] = s[i - 1];
    preprocess();
    int Qr;
    cin>>Qr;
    int rem = 0, v, q;
    while(Qr--){
        cin>>v;
        q = F(rem, v);
        rem = solve(q);
    }
    //ALLClear();
    return 0;
}
