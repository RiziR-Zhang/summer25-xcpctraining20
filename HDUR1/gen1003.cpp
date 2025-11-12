#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdlib>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;

int main()
{
    freopen("1003.in","w",stdout);
    srand(20250718);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout<<1<<endl;
    int n = 3000;
    cout<<n<<endl;
    Rep(i, 1, n){
        cout<<char(rand() % 17 + 'a');
    }
    Rep(i, 1, 17){
        cout<<(rand() % 1000000 + 1)<<' ';
    }
    cout<<endl<<1<<endl;
    fclose(stdout);
    return 0;
}
