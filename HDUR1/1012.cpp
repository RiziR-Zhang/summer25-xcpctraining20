#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<unordered_set>
using namespace std;

//#define DEBUG
//#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 11;
int a[mN], m, n;

// 函数来计算循环长度
int simul() {
    // 复制输入数组
    std::vector<int> piles(a + 1, a + m + 1);
    
    // 用于存储出现过的局面
    std::unordered_set<std::string> seenStates;
    
    // 用于存储当前局面
    std::string currentState;
    
    // 循环直到检测到重复局面
    while (true) {
        // 将当前局面转换为字符串形式，以便存储和比较
        currentState = "";
        for (int ball : piles) {
            currentState += std::to_string(ball) + " ";
        }
        
        // 检查当前局面是否已经出现过
        if (seenStates.find(currentState) != seenStates.end()) {
            break; // 如果出现过，说明进入了循环，跳出循环
        }
        
        // 记录当前局面
        seenStates.insert(currentState);
        
        // 从每堆中取一个球，形成新的堆
        std::vector<int> newPiles;
        for (int i = 0; i < piles.size(); ++i) {
            if (piles[i] > 0) {
                piles[i]--;
                newPiles.push_back(1);
            }
        }
        
        // 移除为0的堆
        piles.erase(std::remove(piles.begin(), piles.end(), 0), piles.end());
        
        // 将新堆加入到局面中
        piles.insert(piles.end(), newPiles.begin(), newPiles.end());
    }
    
    // 返回循环长度
    return seenStates.size();
}
void dfs(int p, int r){
    if(p == m){
        a[p] = r;
        simul();
        return;
    }
    if(r == 0){
        return;
    }
    Rpl(t, 1, r){
        a[p] = t;
        dfs(p+1, r-t);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    Rep(i, 2, 10){
        Rep(j, 1, i){
            n = i;
            m = j;
            dfs(1, n);
        }
        Rep(k, 1, i){
            if(exs[k]){
                print(vec[i][k]);
            }else{
                cout << "-1";
            }
        }
        cout<<endl;
    }
    return 0;
}
