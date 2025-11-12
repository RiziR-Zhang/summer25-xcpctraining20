#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdlib>
#include<ctime>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;
int a[200005];
//bool st1[55][55], st2[55][55];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(0));
    freopen("1007.in","w",stdout);
    int tsk = 2000;
    cout<<tsk<<endl;
    while(tsk--){
        int n = rand() % 10 + 1, q = rand() % 10 + 1;
        cout<<n<<' '<<q<<endl;
        Rep(i, 1, n){
            cout<<rand() % (n + 1)<<' ';
        }
        cout<<endl;
        Rep(i, 1, q){
            int op = rand();
            if(op & 1){
                int p = (op >> 1) & 31;
                p %= (n + 1);
                int x = (op >> 6) & 31;
                x = x % n + 1;
                cout<<1<<' '<<x<<' '<<p<<endl;
            }else{
                int l = rand() % n + 1, r = rand() % n + 1;
                if(l > r) swap(l, r);
                cout<<2<<' '<<l<<' '<<r<<endl;
            }
        }
    }
    fclose(stdout);
    return 0;
}
