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
int st[55][55];
int main()
{
    freopen("I.in","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout<<50<<' '<<50<<endl;
    srand(20250727);
    for(int i = 1; i <= 50; ++i){
        int x,y;
        do{
            x = rand() % 50 + 1, y = rand() % 50 + 1;
        }while(st[x][y]&1);
        st[x][y]|=1;
    }
    for(int i = 1; i <= 50; ++i){
        int x,y;
        do{
            x = rand() % 50 + 1, y = rand() % 50 + 1;
        }while(st[x][y]&2);
        st[x][y]|=2;
    }
    Rep(i, 1, 50){
        Rep(j, 1, 50){
            if(st[i][j]){
                if(st[i][j] == 1) cout<<'*';
                else if(st[i][j] == 2)cout<<'@';
                else cout<<'!';
            }else{
            int rd = rand() % 100;
            if(rd < 10) cout<<'#';else cout<<'.';
            }
        }
        cout<<endl;
    }
    fclose(stdout);
    return 0;
}
