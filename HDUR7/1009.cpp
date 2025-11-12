#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

//#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mD = 51 * 366 + 1;
int wkd[53][369], a[369];
void pre(){
    int c = 3, L = 2025-2024, R = 2075-2024;
    memset(wkd[0], 0, sizeof(int) * 367);
    Rep(i, L, R){
        Rep(j, 1, 366){
            if(i % 4 != 0 && j == 31 + 29){
                wkd[i][j] = wkd[i - 1][j] + 1;
            }else{
                wkd[i][j] = wkd[i - 1][j] + (c == 6 || c == 0);
                c = (c + 1) % 7;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk, k, l, r;
    cin>>tsk;
    pre();
    while(tsk--){
        cin>>k>>l>>r;
        l -= 2024, r -= 2024;
        Rep(i, 1, 366){
            a[i] = wkd[r][i] - wkd[l - 1][i];
        }
        sort(a + 1, a + 366 + 1, greater<int>());
        int sum = 0;
        Rep(i, 1, k){
            sum += a[i];
        }
        cout<<k * (r - l + 1) - sum<<endl;
    }
    return 0;
}
