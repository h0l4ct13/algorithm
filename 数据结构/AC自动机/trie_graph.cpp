#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

//AC自动机的trie图优化

//AC自动机处理next的逻辑就是用当前节点的next来同时更新子节点的next 同时延长前后缀匹配

const int N = 10010, S = 55;
const int M = 1000010;

int n, tr[N * S][26]; //trie
int cnt[N * S]; //每个节点结尾的单词的数量
char str[M];
int q[N * S]; //bfs宽搜队列
int ne[N * S];
int idx; //trie idx

void insert() {
    int p = 0; //根节点
    for (int i = 0; str[i]; i ++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) tr[p][t] = ++idx;
        p = tr[p][t];
    }
    cnt[p] ++;
}

//bfs构建AC自动机

void build() {
    int hh = 0, tt = -1;
    for (int i = 0 ; i < 26; i++) {
        //将根节点的子节点全部入队 就是第一层
        if (tr[0][i]) q[++tt] = tr[0][i];
    }

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int c = tr[t][i];

            //trie图优化：

            //如果j的子节点c不存在 那么就让c直接跳到j的next节点的相同字母的子节点
            if (!c)  tr[t][i] = tr[ne[t]][i];
            else {
                //如果子节点c存在 那就和朴素的写法一样 更新子节点的next
                ne[c] = tr[ne[t]][i];
                q[++tt] = c;
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T --) {
        memset(tr, 0, sizeof tr);
        idx = 0;
        memset(cnt, 0, sizeof cnt);
        memset(ne, 0, sizeof ne);

        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            insert();
        }

        build();

        scanf("%s", str); //待匹配的长串
        int res = 0;
        for (int i = 0, j = 0; str[i]; i++) {
            int t = str[i] - 'a';

            //trie图优化:
            //不再需要while循环了，因为如果子节点不存在，子节点就已经指向父节点的next节点的子节点了
            //如果子节点存在 那就直接指向子节点 相当于合并了2个操作
            j = tr[j][t];

            int p = j;
            while (p) { //会破坏复杂度
                res += cnt[p];
                cnt[p] = 0;
                p = ne[p];
            }
        }

        printf("%d\n", res);
    }
    return 0;
}