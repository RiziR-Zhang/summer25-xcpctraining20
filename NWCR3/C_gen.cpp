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
    srand(7221805);
freopen("C.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    Rep(tsk,1,1000){
        n = rand() % 10 + 1;
        m = rand() % 10 + 1;
        cout<<n<<" "<<m<<endl;
        Rep(i,1,n){
            cout<<char('a' + rand() % 26);
        }
        cout<<endl;
        Rep(i, 1, m){
            cout<<rand() % n + 1<<" "<<char('a' + rand() % 26)<<endl;
        }
    }
fclose(stdout);
    return 0;
}
