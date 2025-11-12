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
constexpr int mN = 200005, stdN = 200000;
constexpr LL mdN = 1e9 + 7, Q = 10, invQ = (mdN * 7 + 1) / 10;
int n, m, tol[mN];
LL invp[11], fac[mN], ifac[mN];

LL p[mN], np[mN];// pre[mN], ipre[mN];
LL initVal[mN], sum, ans;
struct SeqMul{
    LL preMul[mN], ipreMul[mN];
    int preSum0[mN], len;
    void init(){
        len = 0;
        ipreMul[0] = preMul[0] = 1;
        preSum0[0] = 0;
    }
    void add(LL fracp){
        ++len;
        if(fracp == 0){
            preSum0[len] = preSum0[len - 1] + 1;
            ipreMul[len] = preMul[len] = 1;
        }else{
            preSum0[len] = preSum0[len - 1];
            preMul[len] = preMul[len - 1] * fracp % mdN * invQ % mdN;
            ipreMul[len] = ipreMul[len - 1] * invp[fracp] % mdN * Q % mdN;
        }
    }
    LL qr(int l, int r){//(l,r]
        if(preSum0[r] - preSum0[l] > 0) return 0;
        return preMul[r] * ipreMul[l] % mdN;
    }
}seqMul;
LL inv(LL a){
    LL pw = 1, b = mdN - 2;
    while(b){
        if(b & 1) pw = pw * a % mdN;
        a = a * a % mdN;
        b >>= 1;
    }
    return pw;
}
void mathinit(int len = stdN){
    Rep(i, 1, 10) invp[i] = inv(i);
}
void ALLClear(){
    memset(initVal + 1, 0, sizeof(LL) * n);
    memset(tol + 1, 0, sizeof(int) * n);
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
        cin>>n>>m;
        seqMul.init();
        Rep(i, 1, n){
            cin>>p[i];
            np[i] = 10 - p[i];
            seqMul.add(np[i]);
        }
        int l, r;
        Rep(i, 1, m){
            cin>>l>>r;
            tol[r] = max(tol[r], l);
        }
        Rep(i, 1, n){
            tol[i] = max(tol[i - 1], tol[i]);
        }

        int nowl = 0;
        initVal[0] = 1;
        sum = 1;
        Rep(x, 1, n){
            initVal[x] = sum * p[x] % mdN * invQ % mdN;
            sum = (sum * (np[x] * invQ % mdN) + initVal[x]) % mdN;
            for(;nowl < tol[x]; ++nowl){
                sum = (sum - initVal[nowl] * seqMul.qr(nowl, x) % mdN + mdN) % mdN;
                initVal[nowl] = 0;
            }
        }

        cout<<sum<<endl;
        ALLClear();//tol,initVal
    }
    return 0;
}
