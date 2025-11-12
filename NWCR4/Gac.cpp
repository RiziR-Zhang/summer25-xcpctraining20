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

ll p2[N];
ll ans = 0;
char s[N];
int w[N];

int main(){
    scanf("%s",s + 1);
    int n = strlen(s + 1);
    
    p2[0] = 1;
    for(int i = 1;i <= n;++i)
        p2[i] = p2[i-1] * 2 % P;
    
    ll las = 0;
    for(int i = 1;i <= n;++i){
        w[i] = w[i-1] + 1 - (s[i] == ')') * 2;
        if(w[i] == 1){
            ans = (ans + 1ll * (p2[(i+1)/2] + P - las) * p2[(n - i + 1)/2] % P)%P;
            las = p2[(i+1)/2];
        }
    }
    ans = ans * qpow(qpow(2,n),P-2) % P;
    printf("%lld\n",ans);
}