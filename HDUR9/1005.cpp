#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<cmath>
using namespace std;

//#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 500005;
constexpr double eps = 1e-6;
const double PI = acos(-1.0);
constexpr char inner[2][5] = {"NO", "YES"};
int n;
pii ori[mN];
double len[mN];
struct Coor{
    LL x, y;
    Coor(LL X = 0, LL Y = 0): x(X), y(Y){}
    double len(){
        return sqrt(1.0*(x * x + y * y));
    }
}o[mN];
Coor operator+(Coor a, Coor b){
    return Coor(a.x + b.x, a.y + b.y);
}
Coor operator-(Coor a, Coor b){
    return Coor(a.x - b.x, a.y - b.y);
}
Coor operator*(double a, Coor b){
    return Coor(a * b.x, a * b.y);
}
double operator*(Coor a, Coor b){
    return a.x * b.x + a.y * b.y;
}
double operator^(Coor a, Coor b){
    return a.x * b.y - a.y * b.x;
}
typedef pair<pii, bool> ofmt;
ofmt ans[mN];
bool pin[mN], atR[mN];
int cnt;

void solve(){
    o[0] = o[n];
    o[n + 1] = o[1];
    Rep(i, 0, n){
        len[i] = (o[i + 1] - o[i]).len();
    }
    double sa = 0;
    Rep(i, 1, n){
        LL cx = (o[i + 1] - o[i]) ^ (o[i] - o[i - 1]);
        pin[i] = (abs(cx) > eps);
        double theta = 1.0 * ((o[i + 1] - o[i]) * (o[i - 1] - o[i])) / len[i - 1] / len[i];
        if(theta < -1.0) theta = -1.0;
        if(theta > 1.0) theta = 1.0;
        theta = acos(theta);
        if(!pin[i]){
            atR[i] = 0;
            sa += PI;
        }else if(cx > 0){
            atR[i] = 1;
            sa += PI * 2 - theta;
        }else{
            atR[i] = 0;
            sa += theta;
        }
    }
    bool assertPass;
    cnt = 0;
    if(abs(sa - PI * (n + 2)) < eps){
        assertPass = 1;
        Rep(i, 1, n){
            if(pin[i]){
                ans[++cnt] = {ori[i], atR[i]};
            }
        }
    }else{
        assertPass = 0;
        Rep(i, 1, n){
            if(pin[i]){
                ans[++cnt] = {ori[i], !atR[i]};
            }
        }
    }
    sort(ans + 1, ans + cnt + 1, [](const ofmt p, ofmt q){
        if(p.first.first != q.first.first) return p.first.first < q.first.first;
        return p.first.second < q.first.second;
    });
    cout<<cnt<<endl;
    Rep(i, 1, cnt){
        cout<<ans[i].first.first<<' '<<ans[i].first.second<<' '<<inner[ans[i].second]<<endl;
    }
}
void ALLClear(){
    cnt = 0;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        Rep(i, 1, n){
            cin>>ori[i].first>>ori[i].second;
            o[i].x = ori[i].first;
            o[i].y = ori[i].second;
        }
        solve();
        ALLClear();
    }
    return 0;
}
