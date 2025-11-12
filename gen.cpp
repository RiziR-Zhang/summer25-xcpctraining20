#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mdN = 998244353;
int n, m;
int rd(){
    return (rand() << 15) + rand();
}
void gen(){
    cout<<n<<' '<<m<<endl;
    LL s = 0, x;
    Rep(i, 1, n){
        Rep(j, 1, m * 2){
            x = rd();
            cout<<x<<' ';
            s = (s + x) % mdN;
        }
        cout<<(1 + mdN - s) % mdN<<endl;
        s = 0;
    }
}
int main()
{
    freopen("1004.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk = 3;
    cout<<tsk<<endl;
    srand(20250818);
    n = 200, m = 1000;
    gen();
    n = 1000, m = 200;
    gen();
    n = 100, m = 1000;
    gen();
    fclose(stdout);
    return 0;
}
