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
constexpr int mN = 10025;
constexpr int MU = -1, PL = -2, RR = -3;
struct DEF{
    int x, y;
    char op;
}df[mN];
int que[mN], top;
int stk[7], op[7];
constexpr LL P = 1e9 + 7;
LL qp(LL a, LL b){
    LL res = 1;
    a %= P;
    while(b > 0){
        if(b & 1) res = res * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return res;
}
void calc(){
    int cnt = 0;
    stk[cnt = 1] = que[1];
    op[1] = -4;
    assert(top % 2 == 1);
    for(int i = 2; i <= top; ++i){
        if(que[i] == MU){
            if(op[cnt] == MU){
                stk[cnt-1] *= stk[cnt];
                cnt--;
            }
            stk[++cnt] = que[++i];
            op[cnt] = MU;
        }else if(que[i] == PL){
            if(op[cnt] == MU){
                stk[cnt-1] *= stk[cnt];
                cnt--;
            }
            if(op[cnt] == PL){
                stk[cnt - 1] += stk[cnt];
                cnt--;
            }
            stk[++cnt] = que[++i];
            op[cnt] = PL;
        }else{
            if(op[cnt] == MU){
                stk[cnt-1] *= stk[cnt];
                cnt--;
            }
            if(op[cnt] == PL){
                stk[cnt - 1] += stk[cnt];
                cnt--;
            }
            if(op[cnt] == RR){
                que[i] += stk[cnt];
                cnt--;
            }
            stk[++cnt] = que[++i];
            op[cnt] = RR;
        }
    }
    if(op[cnt] == MU){
        stk[cnt-1] *= stk[cnt];
        cnt--;
    }
    if(op[cnt] == PL){
        stk[cnt - 1] += stk[cnt];
        cnt--;
    }
    if(op[cnt] == RR){
        (stk[cnt - 1] *= qp(2, stk[cnt])) %= P;
        cnt--;
    }
    assert(cnt == 1);
    cout<<stk[1]<<endl;
}
void dfs(int k){
    if(df[k].op == 'N'){
            que[++top] = df[k].x;
    }else{
        dfs(df[k].x);
        if(df[k].op == '<') que[++top] = RR;
        else if(df[k].op == '+') que[++top] = PL;
        else que[++top] = MU;
        dfs(df[k].y);
    }
}
void solve(int k){
    top = 0;
    dfs(k);
    calc();
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    char c;
    Rep(i, 1, n){
        cin>>df[i].op>>df[i].x;
        if(df[i].op != 'N') cin>>df[i].y;
    }
    Rep(i, 1, n){
        solve(i);
    }
    return 0;
}
