#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

// #define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;

int main()
{
    freopen("1002.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(20250808);
    int tsk = 10;
    cout<<tsk<<endl;
    Rep(i,1,tsk){
#ifdef DEBUG
cout<<"#"<<i<<endl;
#endif
int n = 1e5;
cout<<n<<endl;
Rep(i, 1, n){
    int x = rand() * rand() - 5e7,
        y = rand() * rand() - 5e7;
    cout<<x<<' '<<y<<' '<<-x-y<<endl;
}
    }
    fclose(stdout);
    return 0;
}
