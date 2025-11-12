#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#define FILE
typedef long long ll;
const int N = 423;

struct node
{
    ll p,x;
};
node dp[N][N][N];
int cnt[N][N];
ll pre[N];
int n;

bool cmp(node a,node b)
{
    if(a.p != b.p)return a.p < b.p;
    return a.x < b.x;
}

int find(int x,int y,ll d)
{
    if(x == y) return 1;
    int l = 0,r = cnt[x][y];
    while(l < r)
    {
        int mid = ((l + r) >> 1) + 1;
        if(dp[x][y][mid].p <= d)
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

int main()
{
#ifdef FILE
    freopen("I.in", "r", stdin);
    freopen("I.out", "w", stdout);
#endif

    int Tsk;
    scanf("%d",&Tsk);
    while(Tsk--)
    {
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
        {
            int x;
            scanf("%d",&x);
            pre[i] = pre[i-1] + x;
            cnt[i][i] = 1;
            dp[i][i][1] = {0,0};
        }
        for(int len = 2;len <= n;++len)
        {
            for(int l = 1,r = len;r <= n;++l,++r)
            {
                ll k = 1,w,b;
                cnt[l][r] = 0;
                int p1,p2;
                while((1ll << k) < pre[r] - pre[l-1]) ++k;
                for(int mid = l;mid < r;++mid)
                {
                    w = k * std::min(pre[r] - pre[mid],pre[mid] - pre[l-1]);
                    b = llabs(pre[r] + pre[l-1] - (pre[mid] << 1));
                    p1 = find(l,mid,b);
                    p2 = find(mid+1,r,b);
                    //printf("l:%d r:%d mid:%d b:%lld p1:%d p2:%d\n",l,r,mid,b,p1,p2);
                    if(len == n)
                    {
                       if(p1&& p2)
                            printf("%lld ",dp[l][mid][p1].x + dp[mid+1][r][p2].x + w);
                        else
                            printf("-1 ");
                    }
                    else
                    {
                         if(p1 && p2)
                            dp[l][r][++cnt[l][r]] = {b,dp[l][mid][p1].x + dp[mid+1][r][p2].x + w};
                    }
                }
                if(len < n && cnt[l][r])
                {
                    std::sort(dp[l][r] + 1,dp[l][r] + cnt[l][r] + 1,cmp);
                    //printf("l:%d r:%d cnt:%d\n",l,r,cnt[l][r]);
                    int m = 1;
                    for(int i = 2;i <= cnt[l][r];++i)
                        if(dp[l][r][i].x < dp[l][r][m].x)
                            dp[l][r][++m] = dp[l][r][i];
                    cnt[l][r] = m;
                    /*printf("l:%d r:%d c:%d\n",l,r,cnt[l][r]);
                    for(int i = 1;i <= cnt[l][r];++i)
                        printf("   p:%d x:%d\n",dp[l][r][i].p,dp[l][r][i].x);
                    printf("------------\n");*/
                }
            }
        }
        putchar('\n');
    }
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif
    return 0;
}