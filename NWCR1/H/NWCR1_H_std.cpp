#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

//#define DEBUG
//#define FILE
//#define MINI
/*qr 458, 629, 779, 893
2 10 9 3
2 11 3 9
2 15 1 6
2 12 3 9
*/
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
#ifdef MINI
constexpr int mN = 25;
constexpr int BLK = 5;
#else
constexpr int mN = 1000025;
constexpr int BLK = 17;
#endif
char s[mN];
struct Node{
    int l, r, constc;
};
struct StrBlk{
    int len, b[mN / BLK + 5], c[mN / BLK + 5], bnum;
    int mask[mN / BLK + 5];
    Node nd[1 << BLK | 5];
    void preprocess(){
        int S = 1 << BLK;
        vector<int> bitrev(S, 0);
        bitrev[0] = 0;
        nd[0] = {0, 0, 0};
        Rpl(i, 1, S){
            bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (BLK - 1));
            nd[i].r = (i & 1) ? nd[i >> 1].r + 1: 0;
            nd[i].constc = nd[i >> 1].constc
                         + ((i & 1) ? nd[i >> 1].r + 1: 0);
        }
        Rpl(i, 1, S){
            nd[i].l = nd[bitrev[i]].r;//WAed here: deal all r firstly
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
    void bitreverse(int p){
        int id = (p - 1) / BLK + 1;
        mask[id] ^= (1 << (BLK - (p - 1) % BLK)) - 1;
    }
    void reverse(int l, int r){
        bitreverse(l);
        bitreverse(r + 1);
    }
    int getS(int p, int len){
        int q = p + len - 1;
        int pid = (p - 1) / BLK + 1;
        p -= (pid - 1) * BLK;//[1,20]
        int qid = (q - 1) / BLK + 1;
        q -= (qid - 1) * BLK;
        if(pid == qid){
            return (c[pid] & ((1 << (BLK - p + 1)) - (1 << (BLK - q)))) >> (BLK - q);
        }else{
            return ((c[pid] & ((1 << (BLK - p + 1)) - 1)) << q)
                 | (c[qid] >> (BLK - q));
        }
    }
    LL process(int x, int y, int now, int len, int &pre){
        int Sx = getS(now - y + x, len),
            Sy = getS(now, len);
        int Sxor = (Sx ^ Sy) ^ ((1 << len) - 1);
        if(len < BLK){
            Sxor <<= (BLK - len);
        }
        LL ans = nd[Sxor].constc + pre * nd[Sxor].l;
        if(Sxor == (1 << BLK) - 1) pre += nd[Sxor].l;
        else pre = nd[Sxor].r;
        return ans;
    }
    LL query(int l, int x, int y){
        if(x > y) swap(x, y);
        int Mask = 0;
        Rep(i, 1, bnum){
            Mask ^= mask[i];
            c[i] = b[i] ^ Mask;
            if(Mask & 1) Mask = (1 << BLK) - 1;
            else Mask = 0;
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
//    cin>>s+1;
//    scanf("%d%d", &n, &q);
//    scanf("%s", s + 1);
    strBlk.trans(s, n);

    int op, l, r, x, y;
    Rep(i, 1, q){
//        scanf("%d", &op);
        cin >> op;
        if(op == 1){
//            scanf("%d%d", &l, &r);
            cin >> l >> r;
            strBlk.reverse(l, r);
        }else{
//            scanf("%d%d%d", &l, &x, &y);
//            printf("%lld\n", strBlk.query(l, x, y));
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