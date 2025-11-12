//#pragma GCC optimize(3,"Ofast","inline", "unroll-loops")
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

//#define DEBUG
#define FILE
//#define MINI
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef unsigned short ush;
#ifdef MINI
constexpr int mN = 25;
constexpr int BLK = 5;
#else
constexpr int mN = 1000025;
constexpr int BLK = 16;
constexpr ush bitCover[2] = {0, (1 << BLK) - 1};
#endif
char s[mN];
struct Node{
    int l, r, constc, bitrev;
};
struct StrBlk{
    int len, bnum;
//    int mask[mN / BLK + 5];
    Node nd[1 << BLK | 5];
    ush b[mN / BLK + 5], mask[mN / BLK + 5];//, c[mN / BLK + 5];
    void preprocess(){
        int S = 1 << BLK;
        nd[0] = {0, 0, 0, 0};
        Rpl(i, 1, S){
            nd[i].bitrev = (nd[i >> 1].bitrev >> 1) | ((i & 1) << (BLK - 1));
            nd[i].r = (i & 1) ? nd[i >> 1].r + 1: 0;
            nd[i].constc = nd[i >> 1].constc + nd[i].r;
            nd[nd[i].bitrev].l = nd[i].r;
        }
    }
    void trans(char *s, int n){
        bnum = (n - 1) / BLK + 1;
        len = bnum * BLK;
        memset(s + n + 1, '0', sizeof(char) * (len - n));
        Rep(i, 1, bnum){
            b[i] = 0;
            mask[i] = 0;
            int st = (i - 1) * BLK;
            Rep(j, 1, BLK){
                b[i] |= (s[st + j] - '0') << (BLK - j);
            }
        }
        preprocess();
    }
    inline void bitreverse(int p){
        int id = (p - 1) / BLK + 1;
        mask[id] ^= (1 << (id * BLK - p + 1)) - 1;
    }
    void reverse(int l, int r){
        bitreverse(l);
        bitreverse(r + 1);
    }
    inline int getS(int p, int len){
        int pid = (p - 1) / BLK + 1;
        p -= (pid - 1) * BLK;//[1,20]
        int q = p + len - 1, maskp = 1 << (BLK - p + 1);
        if(q <= BLK){
            return (b[pid] & (maskp - (1 << BLK - q))) >> (BLK - q);
        }else{
            q -= BLK;
            return ((b[pid] & (maskp - 1)) << q) | (b[pid + 1] >> (BLK - q));
        }
/*        int q = p + len - 1;
        int pid = (p - 1) / BLK + 1;
        p -= (pid - 1) * BLK;//[1,20]
        int qid = (q - 1) / BLK + 1;
        q -= (qid - 1) * BLK;
        if(pid == qid){
            return (c[pid] & ((1 << (BLK - p + 1)) - (1 << (BLK - q)))) >> (BLK - q);
        }else{
            return ((c[pid] & ((1 << (BLK - p + 1)) - 1)) << q)
                 | (c[qid] >> (BLK - q));
        }*/
    }
    inline int process(int x, int y, int now, int len, int &pre){
        ush Sx = getS(now - y + x, len),
            Sy = getS(now, len);
        ush Sxor = ((Sx ^ Sy) ^ ((1 << len) - 1)) << (BLK - len);
        int ans = nd[Sxor].constc + pre * nd[Sxor].l;
        if(Sxor != bitCover[1]) pre = 0;
        pre += nd[Sxor].r;
        return ans;
    }
    LL query(int l, int x, int y){
        if(x > y) swap(x, y);
        bool pbit = 0;
        for(int i = 1; i <= bnum; ++i){
            mask[i] ^= bitCover[pbit];
            b[i] ^= mask[i];
            pbit = mask[i] & 1;
            mask[i] = 0;
        }
        int pre = 0;
        LL ans = 0;
        for(int i = y; i < y + l; i += BLK){
            ans += process(x, y, i, min(BLK, y + l - i), pre);
        }
        return ans;
    }
}strBlk;
int main()
{
#ifdef FILE
freopen("H.in","r",stdin);
freopen("H.out","w",stdout);
#endif
    int n, q;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>q;
    cin>>s;
    for(int i = n; i >= 1; --i)
        s[i] = s[i - 1];
    strBlk.trans(s, n);

    int op, l, r, x, y;
    Rep(i, 1, q){
        cin >> op;
        if(op == 1){
            cin >> l >> r;
            strBlk.reverse(l, r);
        }else{
            cin >> l >> x >> y;
            cout << strBlk.query(l, x, y) << '\n';
        }
    }
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif   
    return 0;
}