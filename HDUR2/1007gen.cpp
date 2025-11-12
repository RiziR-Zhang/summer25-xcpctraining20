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
    freopen("1007.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk = 1000;
    cout<<tsk<<endl;
    srand(20250721);
    while(tsk--){
        int n, R;
        n = rand() % 10 + 1;
        R = rand() % 10 + 5;
        cout << n << " " << R << endl;
        Rep(i, 1, n){
            cout<<rand() % R + 1<<' ';
        }
        cout<<endl<<endl;
    }
    fclose(stdout);
    return 0;
}
