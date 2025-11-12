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
constexpr int mN = 105;
int main()
{
    srand(20250717);
    freopen("F.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk = 2000;
    while(tsk--){
        int n = rand() % 10 + 1;
        int t = rand() % 10 + 1;
        t = t * t / 10 + 1;
        int key = rand() % n + 1;
        cout<<n<<' '<<t<<endl;
        int ARR = rand() % 1024;
        ARR |= (1 << (key - 1));
        Rep(i, 1, n){
            cout<<((ARR & (1 << (i - 1))) ? 1 : 0);
        }
        cout<<endl;
    }
    fclose(stdout);
    return 0;
}
