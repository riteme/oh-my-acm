#define NDEBUG

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define KMAX 15
#define MOD 998244353

typedef long long i64;

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

static int n, m, K;
static vector<int> G[NMAX + 10];
static i64 f[NMAX + 10][KMAX + 1];
static i64 g[KMAX + 1], h[KMAX + 1];

inline void dp(i64 *a, i64 *b, bool t = false) {
    i64 sum = 0;
    if (t) for (int j = 0; j <= K; j++) add(sum, a[j]);
    for (int j = K; j >= 2; j--) {
        a[j] = 0;
        for (int k = 1; k < j; k++) add(a[j], a[j - k] * b[k] % MOD);
    }
    a[1] = 0;
    if (t) for (int j = 1; j <= K; j++) add(a[j], sum * b[j] % MOD);
}

#define ACM_BEGIN
int dfn[NMAX + 10], low[NMAX + 10], now, cnt;
int ed[NMAX + 10], fa[NMAX + 10], a[NMAX + 10];
void dfs(int x) {
  dfn[x] = low[x] = ++now;
  for (int v : G[x]) if (v != fa[x]) {
    if (dfn[v]) {
      ed[v] = x, low[x] = min(low[x], dfn[v]);
      continue;
    } fa[v] = x;
    dfs(v);
    if (low[v] > dfn[x]) ; // 割边
    else if (low[v] == dfn[x]) {
      a[1] = x;
      for (cnt = 1, v = ed[x]; v != x; v = fa[v])
        a[++cnt] = v;
      // 环 a[1]...a[cnt]
    } else low[x] = min(low[x], low[v]);
}}
#define ACM_END

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &K);
        for (int i = 1; i <= n; i++) G[i].clear();
        now = 0;
        memset(dfn + 1, 0, sizeof(int) * n);
        //memset(low + 1, 0, sizeof(int) * n);
        memset(fa + 1, 0, sizeof(int) * n);
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        i64 ans = 1;
        for (int i = 1; i <= n; i++) if (!dfn[i]) {
            dfs(i);
            i64 sum = 0;
            for (int j = 1; j <= K; j++) add(sum, f[i][j]);
            ans = ans * sum % MOD;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
