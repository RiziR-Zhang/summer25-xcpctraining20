#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<unordered_map>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;
int a[9], n, m, res;
//bool fd[700005];
unordered_map<int,bool> fd;
void dfs(){
    Rep(st, 1, n - m + 1){
        int b = a[st + m - 1];
        for(int i = st + m - 1; i > st; --i){
            a[i] = a[i - 1];
        }
        a[st] = b;
        int S = a[1] + a[2] * 10 + a[3] * 100 + a[4] * 1000
                + a[5] * 10000 + a[6] * 100000 + a[7] * 1000000 + a[8] * 10000000;
        if(!fd[S]){
            fd[S] = 1;
            res--;
            dfs();
        }
        for(int i = st; i < st + m - 1; ++i){
            a[i] = a[i + 1];
        }
        a[st + m - 1] = b;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(n = 3; n <= 8; ++n){
        for(m = 2; m <= n; ++m){
//            memset(fd, 0, sizeof(fd));
fd.clear();
            res = 1; Rep(i, 1, n) res *= i;
            Rep(i, 1, n) a[i] = i;
            dfs();
            cout<<n<<','<<m<<":"<<res<<endl;
        }
    }
    return 0;
}
