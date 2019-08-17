/**
 * title: 单纯型
 * category: 杂项
 * description: /dev/null
 */
// #define NDEBUG

#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <algorithm>

using namespace std;

#define double long double
#define NMAX 20

#define ACM_BEGIN
#define EPS 1e-10
#define INF 1e100

class Simplex {
 public:
  void initialize() {
    scanf("%d%d%d", &n, &m, &t);
    memset(A, 0, sizeof(A));
    for (int i = 1; i <= n; i++) {
      idx[i] = i;
      scanf("%Lf", A[0] + i);
    }
    for (int i = 1; i <= m; i++) {
      idy[i] = n + i;
      for (int j = 1; j <= n; j++) {
        scanf("%Lf", A[i] + j);
        A[i][j] *= -1;
      }
      scanf("%Lf", A[i]);
  }}
  void solve() {
    srand(time(0));
    while (true) {
      int x = 0, y = 0;
      for (int i = 1; i <= m; i++)
        if (A[i][0] < -EPS && (!y || (rand() & 1))) y = i;
      if (!y) break;
      for (int i = 1; i <= n; i++)
        if (A[y][i] > EPS && (!x || (rand() & 1))) x = i;
      if (!x) {
        puts("Infeasible");
        return;
      }
      pivot(x, y);
    }
    while (true) {
      double k = INF;
      int x, y;
      for (x = 1; x <= n; x++)
    if (A[0][x] > EPS) break;
      if (x > n) break;
      for (int i = 1; i <= m; i++) {
        double d = A[i][x] > -EPS ? INF : -A[i][0] / A[i][x];
        if (d < k) {
          k = d;
          y = i;
      }}
      if (k >= INF) {
        puts("Unbounded");
        return;
      }
      pivot(x, y);
    }
    printf("%.10Lf\n", A[0][0]);
    if (t) {
      static double ans[NMAX + 10];
      for (int i = 1; i <= m; i++)
        if (idy[i] <= n) ans[idy[i]] = A[i][0];
      for (int i = 1; i <= n; i++)
        printf("%.10Lf ", ans[i]);
      printf("\n");
  }}
 private:
  void pivot(int x, int y) {
    swap(idx[x], idy[y]);
    double r = -A[y][x];
    A[y][x] = -1;
    for (int i = 0; i <= n; i++) A[y][i] /= r;
    for (int i = 0; i <= m; i++) {
      if (i == y) continue;
      r = A[i][x];
      A[i][x] = 0;
      for (int j = 0; j <= n; j++)
        A[i][j] += r * A[y][j];
  }}
  int n, m, t;
  double A[NMAX + 10][NMAX + 10];
  int idx[NMAX + 10], idy[NMAX + 10];
};
#define ACM_END

int main() {
  // freopen("data.in", "r", stdin);
  Simplex solver;
  solver.initialize();
  solver.solve();

  return 0;
}
