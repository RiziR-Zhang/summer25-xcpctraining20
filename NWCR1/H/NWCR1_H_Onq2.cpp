#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

//#define DEBUG
#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 1000005;
int n, q;
char s[mN];
bool b[mN], df[mN], c[mN];

int main()
{
#ifdef FILE
freopen("H.in","r",stdin);
freopen("Hbf.out","w",stdout);
#endif
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    Rep(i, 1, n){
        b[i] = s[i] - '0';
    }

    int op, l, r, x, y;
#ifdef DEBUG
bool flag = 1;
#endif
    Rep(i, 1, q){
        scanf("%d", &op);
        if(op == 1){
            scanf("%d%d", &l, &r);
            df[l] ^= 1;
            df[r + 1] ^= 1;
        }else{
            scanf("%d%d%d", &l, &x, &y);
            if(x > y) swap(x, y);
            bool pre = 0;
            int cnt = 0;
            LL ans = 0;
            int R = y + l - 1;
            for(int i = 1; i <= n/* && i <= R*/; ++i){
                pre ^= df[i];
                c[i] = b[i] ^ pre;
#ifdef DEBUG
putchar(c[i] + '0');
#endif
                if(y <= i && i <= R){//&& i < y + l
                    if(c[i] == c[i - y + x]) ++cnt;
                    else cnt = 0;
                    ans += cnt;
                }
            }
#ifdef DEBUG
putchar('\n');
flag = 0;
#endif
            printf("%lld\n", ans);
        }
    }
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif   
    return 0;
}