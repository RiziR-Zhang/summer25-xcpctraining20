#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
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
    srand(7221411);
    ios::sync_with_stdio(0);
    int tsk = 10000;
    freopen("B.in","w",stdout);
    cout<<tsk<<endl;
    Rep(i, 1, tsk){
        cout<<(unsigned int)rand()<<' '<<(unsigned int)rand()<<' '<<(unsigned int)rand()<<endl;

    }
    fclose(stdout);
    return 0;
}