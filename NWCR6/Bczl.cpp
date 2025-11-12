#include<iostream>
#include<cstdio>
#include<vector>

using ll = long long;
const int N = 2e5 + 5;
const int M = 1e9 + 1;

std::vector<int> A[N];
int len[N];
int n,y,m;
int tag[N];

ll calc(int u,ll x){
    ll res = 0,d = 1;
    for(int i = 0;i < len[u];++i){
        res = res + d * A[u][i];
        if(res > M)return M + 1;
        d = d * x;
        if(d > M)d = M + 1;
    }
    printf("%lld %lld\n",x,res);
    return res;
}

int bf(int u,ll x){
    int l = 0,r = M + 1;
    while(l < r){
        int mid = l + r >> 1;
        if(calc(u,mid) >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main(){
    int Tsk;
    scanf("%d",&Tsk);
    while(Tsk--){
        scanf("%d%d%d",&n,&y,&m);
        for(int i = 1;i <= n;++i){
            scanf("%d",len + i);
            A[i].resize(len[i]);
            int cnt = 0;
            for(int j = 0;j < len[i];++j){
                scanf("%d",&A[i][j]);
                if(!A[i][j])++cnt;
            }
            tag[i] = (cnt == len[i] - 1);
        }
        int flag = 0;
        ll L = y,R = y + 1;
        for(int i = n;i > 0;++i){
            if(tag[i]){
                if(L <= A[i][0] && A[i][0] < R){
                    L = A[i][0] + 1;
                    R = M + 1;
                }
                else{
                    flag = 1;
                    break;
                }
            }
            else{
                L = bf(i,L);
                R = bf(i,R);
                //printf("%lld %lld\n",L,R);
                //printf("A[%d]:",i);
                //for(int j = 0;j < len[i];++j)
                //    printf("%d ",A[i][j]);putchar('\n');
                if(L >= R){
                    flag = 1;
                    break;
                }
            }
        }
        if(L > m)
            flag = 1;
        if(!flag)
            printf("%lld %lld\n",L,std::min(R,(ll)m+1)-1);
        else
            printf("-1 -1\n");
    }
}