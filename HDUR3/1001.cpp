#include<iostream>
#include<cstring>
#include<cstdio>
#define FILE
const int P = 998244353;
int n,K;

struct M{
    int f[55][55];    

    M(){
        memset(f,0,sizeof(f));
    }
    M operator* (const M &v)const{
        M res;
        for(int i = 1; i <= K; ++i){
            for(int k = 1; k <= K; ++k){
                long long fik = f[i][k];
                for(int j = 1; j <= K; ++j){
                    res.f[i][j] =(res.f[i][j] +  fik * v.f[k][j]) % P;
                }
            }
        }
/*        for(int i = 1; i <= K; ++i)for(int j = 1; j <= K; ++j){
            res.f[i][j] %= P;
        }*/
        return res;
    }

    void print(){
        for(int i = 1;i <= K;++i){
            for(int j = 1;j <= K;++j)
                printf("%d ",f[i][j]);
            putchar('\n');
        }
    }
};
M d,ans;

M qpow(M a,int b){
    M res;
    for(int i = 1;i <= K;++i)res.f[i][i] = 1;
    while(b){
        if(b & 1)res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main(){
#ifdef FILE
freopen("1001.in","r",stdin);
#endif
    scanf("%d%d",&n,&K);
    for(int i = 1;i <= K;++i){
        int x;
        scanf("%d",&x);
        if(i < K)d.f[i + 1][i] = 1;
        d.f[1][i] = x;
        ans.f[i][i] = 1;
    }
    for(int i = 1;i <= n;++i){
        int x;
        scanf("%d",&x);
        M a = qpow(d,x);
        for(int j = 1;j <= K;++j)
            ++a.f[j][j],a.f[j][j] %= P;
        ans = ans * a;
        //a.print();
    }
    printf("%d\n",ans.f[1][1]);
#ifdef FILE
fclose(stdin);
#endif
}