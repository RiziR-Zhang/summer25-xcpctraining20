#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
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
    freopen("1001.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk = 1000, V = 15;
    srand(20250801);
    cout<<tsk<<endl;
    Rep(t, 1, tsk){
        int n = rand() % 10 + 1, Qr = rand() % 10 + 1;
        cout<<n<<' '<<Qr<<endl;
        Rep(i, 1, n) cout<<rand() % V + 1<<' ';
        cout<<endl;
        Rep(i, 1, n) cout<<rand() % V + 1<<' ';
        cout<<endl;
        Rep(i, 2, n){
            cout<<rand() % (i - 1) + 1<<' '<<i<<endl;
        }
        Rep(i, 1, Qr){
            cout<<rand() % n + 1<<' '<<rand() % V + 1<<endl;
        }
    }
    fclose(stdout);
    return 0;
}
