#include<iostream>
#include<cmath>
#include<cstdio>

int n;
int calc(int s,int t,int k){
    int d = (s^t)&1;
    int res = (abs(s-t) + k - 1)/k;
    if(k & 1 && (res ^ d) & 1)
        ++res;
    if(res == 1){
        int d = (k + s - t)/2;
        if(d > s || k - d > n - s)
            return 3;
    }
    return res;
}

int main(){
    int Tsk;
    scanf("%d",&Tsk);
    while(Tsk--){
        int k,s,t;
        int ans;
        scanf("%d%d%d%d",&n,&k,&s,&t);
        if(k == n){
            if(s == t)
                printf("0\n");
            else if(s + t == n)
                printf("1\n");
            else
                printf("-1\n");
            continue;
        }        
        if(k & 1){
            int d = ((s^t)&1);
            if(k * 2 <= n){
                ans = calc(s,t,k);
                if((ans ^ d) & 1)
                    ++ans;
            }
            else{
                if(d)
                    ans = calc(s,n - t,n - k);
                else
                    ans = calc(s,t,n - k);
                if((ans ^ d) & 1)
                    ++ans;
            }
        }
        else{
            if((s^t)&1){
                printf("-1\n");
                continue;
            }
            if(k * 2 <= n){
                ans = calc(s,t,k);
            }
            else{
                int ans1 = calc(s,t,n - k);
                int ans2 = calc(s,n - t,n - k);
                ans = std::min(ans1,ans2);  
            }
        }
        printf("%d\n",ans);
    }
}