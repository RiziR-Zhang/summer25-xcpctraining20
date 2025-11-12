#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("1003.in","w",stdout);
    int tsk = 1000;
    cout<<tsk<<endl;
    Rep(t,1,tsk){
        int n = rand() % 10 + 2;
        int m = rand() % 10 + 1;
        cout<<n<<" "<<m<<endl;
        Rep(i, 1, m){
            int x = rand() % n + 1, y = rand() % (n - 1) + 1, w = rand() % 100 + 1;
            if(y >= x) y++;
            if(x > y) swap(x, y);
            cout<<x<<" "<<y<<' '<<w<<endl;
        }
    }
    fclose(stdout);
    return 0;
}
