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
    srand(20250718);
    freopen("1007.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk = 1000;
    cout<<tsk<<endl;
    while(tsk--){
//cout<<"#"<<1000-tsk<<endl;
        int n = rand() % 10 + 1;
        int x = rand() % 20 + 2;
        cout<<n<<' '<<x<<endl;
        Rpl(i, 1, n){
            cout<<i + 1<<' '<<rand() % i + 1<<endl;
        }
        Rep(i,1,n){
            cout<<rand() % 20 + 1<<' ';
        }
        cout<<endl<<endl;
    }
    fclose(stdout);
    return 0;
}
