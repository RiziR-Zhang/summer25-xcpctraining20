#include<iostream>
#include<cstring>
#include<cstdio>

using ll = long long;
const ll P = 998244353;

ll qpow(ll a,ll b){
    ll res = 1;
    while(b){
        if(b & 1)res = res * a % P;
        b >>= 1;
        a = a * a % P;
    }
    return res;
}

struct Mat{
    ll f[32][32];
    Mat(){
        memset(f,0,sizeof(f));
    }

    Mat operator* (const Mat v)const{
        Mat res;
        for(int i = 0;i < 32;++i){
            for(int j = 0;j < 32;++j){
                for(int k = 0;k < 32;++k){
                    (res.f[i][j] += f[i][k] * v.f[k][j]) %= P;
                }
            }
        }
        return res;
    }
};
Mat a,af; 
ll n,k;
int D[10];

Mat Mpow(Mat a,ll b){
    Mat res;
    for(int i = 0;i < 32;++i)res.f[i][i] = 1;
    while(b){
        if(b & 1)res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main(){
    int Tsk;
    scanf("%d",&Tsk);
    while(Tsk--){
        scanf("%lld %lld",&n,&k);
        for(int i = 1;i <= k;++i)
            scanf("%d",D + i);
        ll d = qpow(k*5,P-2);
        memset(a.f,0,sizeof(a.f));
        for(int u = 0;u <= 15;++u){
            int _u = u | 16;
            int v,_v;
            for(int j = 1;j <= k;++j){
                v = (u + D[j]) & 15;
                _v = v | 16;
                (a.f[u][v] += d) %= P;
                (a.f[u][_v] += d * ((u + D[j]) >> 4) % P) %= P;
                (a.f[_u][_v] += d) %= P;
            }
            for(int j = 1;j <= k;++j){
                v = (u * D[j]) & 15;
                _v = v | 16;
                (a.f[u][v] += d) %= P;
                (a.f[u][_v] += d * ((u * D[j]) >> 4) % P) %= P;
                (a.f[_u][_v] += d * D[j] % P) %=P;
            }
            for(int j = 1;j <= k;++j){
                v = u | D[j];
                _v = v | 16;
                (a.f[u][v] += d) %= P;
                (a.f[_u][_v] += d) %= P;
            }
            for(int j = 1;j <= k;++j){
                v = u & D[j];
                _v = v | 16;
                (a.f[u][v] += d) %= P;
                (a.f[_u][_v] += d) %= P;
            }
            for(int j = 1;j <= k;++j){
                v = u ^ D[j];
                _v = v | 16;
                (a.f[u][v] += d) %= P;
                (a.f[_u][_v] += d) %= P;
            }
        }
        af = Mpow(a,n - 1);
        ll ans = 0;
        d = qpow(k,P-2);
        for(int i = 1;i <= k;++i){
            int u = D[i];
            for(int v = 0;v < 16;++v){
                (ans += (af.f[u][v] * v + (af.f[u][v|16] * 16) % P) * d % P) %= P;
            }
        }
        printf("%lld\n",ans);
    }
}