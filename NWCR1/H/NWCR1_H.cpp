//#pragma GCC optimize(3,"Ofast","inline", "unroll-loops")
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
/*#pragma GCC optimize(3)
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")*/
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
    ush b[mN / BLK + 5], mask[mN / BLK + 5], bx[mN / BLK + 5], by[mN / BLK + 5];//, c[mN / BLK + 5];
    void preprocess(){
        int S = 1 << BLK;
        nd[0] = {0, 0, 0, 0};
        Rpl(i, 1, S){
            nd[i].bitrev = (nd[i >> 1].bitrev >> 1) | ((i & 1) << (BLK - 1));
            nd[i].r = (i & 1) ? nd[i >> 1].r + 1: 0;
            nd[i].constc = nd[i >> 1].constc + nd[i].r;
            nd[nd[i].bitrev].l = nd[i].r;
        }/**/
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
//        return;
        bitreverse(l);
        bitreverse(r + 1);
    }
    inline ush getBLK(int p){
        int pid = (p - 1) / BLK;
        p -= pid * BLK + 1;
        if(p == 0) return b[pid + 1];
        return ((b[pid + 1] & ((1 << (BLK - p)) - 1)) << p) | (b[pid + 2] >> (BLK - p));
    }
    inline ush getS(int p, int len){
        int pid = (p - 1) / BLK;//!
        p -= pid * BLK;//[1,20]
        int q = p + len - 1, maskp = 1 << (BLK - p + 1);
        if(q <= BLK){
            return (b[pid + 1] & (maskp - (1 << BLK - q))) >> (BLK - q);
        }else{
            q -= BLK;
            return ((b[pid + 1] & (maskp - 1)) << q) | (b[pid + 2] >> (BLK - q));
        }
    }
    LL query(int l, int x, int y){
        if(x > y) swap(x, y);
        bool pbit = 0;
        int rblk = (y + l - 1 - 1) / BLK + 1; 
        for(int i = 1; i <= rblk; ++i){
            mask[i] ^= bitCover[pbit];
            b[i] ^= mask[i];
            pbit = mask[i] & 1;
            mask[i] = 0;
        }/**/
        if(rblk < bnum) mask[rblk + 1] ^= bitCover[pbit];
        LL ans = 0;
        int len = l / BLK;
        bool res = (l % BLK != 0);
        Rep(i, 1, len){
            bx[i] = getBLK(x);
            x += BLK;
            by[i] = getBLK(y);
            y += BLK;
        }
        if(res){
            int rlen = l - len * BLK;
            len++;
            bx[len] = getS(x, rlen) << (BLK - rlen);
            by[len] = (getS(y, rlen) << (BLK - rlen)) | ((1 << (BLK - rlen)) - 1);
        }
/*        int i = 0;
        for(i = 1; i * BLK <= l; ++i){
            bx[i] = getBLK(x + (i - 1) * BLK);
            by[i] = getBLK(y + (i - 1) * BLK);
        }
        if((i - 1) * BLK < l){
            int r = i * BLK - l;
            bx[i] = getS(x + (i - 1) * BLK, l - (i - 1) * BLK) << r;
            by[i] = (getS(y + (i - 1) * BLK, l - (i - 1) * BLK) << r) | ((1 << r) - 1);
        }else{
            i--;
        }*/
        int pre = 0;
        Rep(j, 1, len){
            ush sxor = bx[j] ^ by[j] ^ bitCover[1];
            ans += nd[sxor].constc + pre * nd[sxor].l;
            if(sxor != bitCover[1]) pre = 0;
            pre += nd[sxor].r;
        }/**/
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