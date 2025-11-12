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
constexpr int dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin>>n>>m;
    int rS = m * n;
    vector<int> cx(n + m + 2), cy(n + m + 2);
    vector<pii> que(n * m + 1);
    vector<vector<int>> a(n + 1, vector<int>(m + 1)),
                        clk(n + 1, vector<int>(m + 1));
    int hd = 0, tl = -1;
    Rep(i, 1, n)Rep(j, 1, m){
        cin>>a[i][j];
        clk[i][j] = -1;
        cx[i + j]++;
        cy[i - j + m + 1]++;
        if(a[i][j]){
            que[++tl] = pii(i, j);
            clk[i][j] = 0;
        }
    }
    if(tl == -1){
        cout<<(n + m - 2 + 1) / 2<<endl;
        return 0;
    }
    int xmn = 2, xmx = n + m, ymn = 2, ymx = n + m;
    int t = 0, ans = 1e9;
    while(rS){
        int t0 = t;
        while(hd <= tl){
            int x = que[hd].first, y = que[hd].second;
            if(clk[x][y] != t0) break;
            hd++;
            cx[x + y]--;
            cy[x - y + m + 1]--;
            rS--;
            Rpl(dir, 0, 4){
                int nx = x + dx[dir], ny = y + dy[dir];
                if(1 <= nx && nx <= n && 1 <= ny && ny <= m && !a[nx][ny]){
                    a[nx][ny] = 1;
                    clk[nx][ny] = t0 + 1;
                    que[++tl] = pii(nx, ny);
                }
            }
        }
        while(xmn <= xmx && cx[xmn] == 0) xmn++;
        while(xmn <= xmx && cx[xmx] == 0) xmx--;
        while(ymn <= ymx && cy[ymn] == 0) ymn++;
        while(ymn <= ymx && cy[ymx] == 0) ymx--;
        ans = min (ans, max(t, max((xmx - xmn + 1) / 2, (ymx - ymn + 1) / 2)));
        t++;
    }
    cout<<ans<<endl;
    return 0;
}
