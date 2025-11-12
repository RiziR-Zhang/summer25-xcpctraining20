#include<iostream>
#include<cstring>
#include<cstdio>

using ll = long long;
const int N = 1e6 + 5;
const int P = 998244353;

int qpow(int a,int b){
    int res = 1;
    while(b){
        if(b & 1)res =1ll * res * a % P;
        a = 1ll * a * a % P;
        b >>= 1;
    }
    return res;
}

int f[N],g[N],F[N];
int pl[N],pr[N];
int p2[N];
char s[N];
int w[N];

int main(){
    scanf("%s",s + 1);
    int n = strlen(s + 1);
    
    p2[0] = 1;
    for(int i = 1;i <= n;++i){
        p2[i] = p2[i-1] * 2 % P;
        w[i] = w[i-1] + 1 - (s[i] ==')') * 2; 
    }

    pr[n + 1] = n + 1;
    for(int i = 1;i <= n;++i){
        if(w[i-1] == 1)
            pl[i] = i;
        else
            pl[i] = pl[i-1];
    }
    for(int i = n;i >= 1;--i){
        if(w[i] == 1)
            pr[i] = i;
        else
            pr[i] = pr[i + 1];
    }

    f[0] = 1;
    ll ans = p2[n/2];

    for(int i = 1,d = 0;i <= n;++i){
        f[i] += f[i-1];
        if(s[i] == '('){
            if(pr[i] > n)continue;
            int t = pr[i];
            ans = (ans + 1ll * f[i-1] * p2[(n - t + w[t])/2] % P) % P;
            f[t] = (f[t] + f[i-1]) % P;
            //printf("i:%d\n",i); 
        }
        if(s[i] == '(')
            ++d;
        else
            --d;
    }
    ans = (ans + p2[n/2] + P - f[n]) % P;
    g[n + 1] = 1;
    for(int i = n,d = 0;i;--i){
        g[i] += g[i + 1];
        if(s[i] == ')'){
            if(pl[i] < 1)continue;
            int t = pl[i];
            ans = (ans + 1ll * g[i + 1] * (p2[(t - 1 + w[t - 1])/2] + P - f[t-1]) % P) % P;
            g[t] = (g[t] + g[i+1]) % P;
        }
        if(s[i] == ')')
            ++d;
        else
            --d;
        //printf("%d\n",g[i]);
    }
    //printf("%lld\n",ans);
    ans = ans * qpow(qpow(2,n),P-2) % P;
    printf("%lld\n",ans);
    /*ll x;
    scanf("%lld",&x);
    printf("%lld\n",x * p2[n] % P);*/
}