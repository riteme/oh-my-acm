/**
 * title: 幂级数前缀和
 * category: 数论
 * description: power-series.md
 */
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define KMAX 200
#define MOD 1000000007

typedef long long i64;

inline i64 qpow(i64 a, i64 k) {
  i64 r = 1;
  for ( ; k; k >>= 1, a = a * a % MOD)
  if (k & 1) r = r * a % MOD;
  return r;
}

inline void add(i64 &a, i64 b) {
  a += b;
  if (a >= MOD) a -= MOD;
  if (a <= -MOD) a += MOD;
}

#define ACM_BEGIN
static bool _initialized;
static int cnt;
static i64 _fi[KMAX + 10], _tmp[KMAX + 10];
struct PowerSeries {
  static void init() {
    _fi[0] = 1;
    for (int i = 2; i <= KMAX + 1; i++) _fi[0] = _fi[0] * i % MOD;
    _fi[KMAX + 1] = qpow(_fi[0], MOD - 2);
    for (int i = KMAX; i >= 0; i--) _fi[i] = _fi[i + 1] * (i + 1) % MOD;
    _initialized = true;
  }
  int K; i64 *f;
  PowerSeries() : PowerSeries(cnt++) {}
  PowerSeries(int _K) : K(_K) {
    if (!_initialized) init();
    f = new i64[K + 2]; f[0] = 0;
    for (int i = 1; i <= K + 1; i++) f[i] = (f[i - 1] + qpow(i, K)) % MOD;
  }
  ~PowerSeries() { delete[] f; }
  i64 operator()(i64 n) const {
    n %= MOD; _tmp[K + 2] = 1;
    for (int i = K + 1; i >= 1; i--) _tmp[i] = _tmp[i + 1] * (n - i) % MOD;
    i64 ret = 0, pre = 1;
    for (int i = 0, b = K & 1 ? 1 : -1; i <= K + 1; i++, b = -b) {
      add(ret, b * f[i] * pre % MOD * _tmp[i + 1] % MOD * _fi[i] % MOD * _fi[K + 1 - i] % MOD);
      pre = pre * (n - i) % MOD;
    } return ret;
  }
  i64 eval(i64 n) const { return (*this)(n); }
};
#define ACM_END

static PowerSeries F[KMAX + 1];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  i64 ans = F[k](n);
  if (ans < 0) ans += MOD;
  printf("%lld\n", ans);
  return 0;
}
