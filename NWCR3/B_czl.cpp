#include<iostream>
#include<cstdio>

typedef long long ll;

#define FILE
ll a,b,c,d;
int n1,n2,n3,n4;
int ans[101],cnt;

int maxbit(ll x){
    int n = 0;
    while((1ll<<(n+1)) <= x)++n;
    return n;
}

void op1(int k){
    for(int i = 1;i <= k;++i)
        ans[++cnt] = 1;
    a <<= k;
    n1 += k;
}

void op2(int k){
    for(int i = 1;i <= k;++i)
        ans[++cnt] = 2;
    b >>= k;
    n2 -= k;
}

void op3(){
    a ^= b;
    ans[++cnt] = 3;
}

void op4(){
    b ^= a;
    ans[++cnt] = 4;
}

int main(){
#ifdef FILE
    freopen("B.in","r",stdin);
    freopen("B.out","w",stdout);
#endif
    int Tsk;
    scanf("%d",&Tsk);
    while(Tsk--){
        scanf("%lld%lld%lld",&a,&b,&c);
        if(b == 0){
            int k = 0;
            while(a && a < c)++k,a<<=1;
            if(a == c){
                printf("%d\n",k + 1);
                for(int i = 1;i <= k;++i)
                    printf("1 ");
                printf("4\n");
            }
            else
                printf("-1\n");
            continue;
        }
        cnt = d = 0;
        n1 = maxbit(a);
        n2 = maxbit(b);
        n3 = maxbit(c);
        n4 = 0;
        //printf("%d\n",n1);
        n1 = std::max(n1,n2);
        if(n3 > n1){
            n4 = n3 - n1;
            d = c & ((1ll << n4) - 1);
            c >>= n4;
        }
        int flag = 0;
        for(int i = n1;i >= 0;--i){
            int x = (1 << i);
            if((a ^ c) & x){
                if(n2 < i){
                    flag = 1;
                    break;
                }
                else if(n2 > i)
                    op2(n2 - i);
                op3();
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        op2(n2);
        for(int i = n4 - 1;i >= 0;--i){
            int x = (1 << i);
            op1(1);
            if(x & d)
                op3();
        }
        op2(1);
        op4();

        printf("%d\n",cnt);
        for(int i = 1;i <= cnt;++i)
            printf("%d ",ans[i]);
        putchar('\n');
    }
#ifdef FILE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}