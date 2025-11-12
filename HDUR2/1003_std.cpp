#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

constexpr int P = 998244353;

int power(int a, int b) {
    int res = 1;
    for (; b; b /= 2, a = i64(a) * a % P) {
        if (b % 2) {
            res = i64(res) * a % P;
        }
    }
    return res;
}

void chmax(int &a, int b) {
    if (a < b) {
        a = b;
    }
}

constexpr i64 inf = 1E18;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    std::vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        int x, y, p;
        std::cin >> x >> y >> p;
        x--;
        y--;
        adj[x].emplace_back(y, p);
        deg[y]++;
    }
    
    std::vector<int> q;
    for (int i = 0; i < n; i++) {
        if (!deg[i]) {
            q.push_back(i);
        }
    }
    
    std::vector<int> max(n);
    
    auto shift = [&](auto &f, int x) {
        for (int i = 39; i >= 0; i--) {
            if (i >= x) {
                f[i] = f[i - x];
            } else {
                f[i] = 0;
            }
        }
    };
    
    std::vector<int> dp(n), dp1(n, -n);
    std::vector<std::array<int, 40>> f(n);
    
    for (int _ = 0; _ < n; _++) {
        int x = q[_];
        for (int i = 0; i < 40 && dp1[x] - i > 0; i++) {
            chmax(max[dp1[x] - i], f[x][i]);
        }
        
        for (auto adjx : adj[x]) {
            int y = adjx.first,
                w = adjx.second;
            chmax(dp[y], dp[x] + 1);
            if (dp1[x] + 1 > dp1[y]) {
                shift(f[y], dp1[x] + 1 - dp1[y]);
                dp1[y] = dp1[x] + 1;
            }
            for (int i = 0; i < 40; i++) {
                int j = dp1[y] - (dp1[x] + 1 - i);
                if (j < 40) {
                    chmax(f[y][j], f[x][i] + w);
                }
            }
            if (w) {
                if (dp[x] + 1 > dp1[y]) {
                    shift(f[y], dp[x] + 1 - dp1[y]);
                    dp1[y] = dp[x] + 1;
                }
                int j = dp1[y] - (dp[x] + 1);
                if (j < 40) {
                    chmax(f[y][j], w);
                }
            }
            if (!--deg[y]) {
                q.push_back(y);
            }
        }
    }
    
    int l = 1;
    int s = 0;
    
    auto cmp = [&](int l1, i64 s1, int l2, i64 s2) {
        assert(l1 >= l2);
        assert(s1);
        if (l1 - l2 > 60) {
            return true;
        }
        i128 d = i128(1LL << (l1 - l2)) * s1 - s2;
        l2 = std::min(l2, 60);
        for (int i = 0; i < l2; i++) {
            d *= 2;
            if (d < -inf) {
                d = -inf;
            }
            if (d > inf) {
                d = inf;
            }
        }
        return d > s1 - s2;
    };
    
    for (int i = 1; i < n; i++) {
        if (!max[i]) {
            continue;
        }
        if (cmp(i, i64(max[i]) * l, l, i64(s) * i)) {
            l = i;
            s = max[i];
        }
    }
    
    int ans = i64(power(2, l) - 1) * s % P * power(10000 * l, P - 2) % P;
    std::cout << ans << "\n";
}

int main() {
freopen("1003.in", "r", stdin);
    freopen("1003std.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    fclose(stdin);fclose(stdout);
    return 0;
}
