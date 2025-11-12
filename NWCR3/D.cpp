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
constexpr int mN = 200005;
int n, a;
char s[mN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>a>>s;
        int maxcon[2] = {0, 0}, con[2] = {0, 0}, cnt = 0;
        Rpl(i, 0, n){
            int b = s[i] - '0';
            con[b]++;
            maxcon[b] = max(maxcon[b], con[b]);
            con[b ^ 1] = 0;
            cnt += (b == 1);
        }
        if(maxcon[0] >= a + 1 || maxcon[1] >= a){
            cout<<n<<endl;
        }else{
            cout<<cnt<<endl;
        }
    }
    return 0;
}
