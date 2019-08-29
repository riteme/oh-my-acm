/**
 * title: 后缀排序：倍增算法
 * category: 字符串
 * description: sa-nlogn.md
 * rank: 999
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

#define ACM_BEGIN
static int sa[NMAX + 10], rk[NMAX + 10], lcp[NMAX + 10];
void suffix_sort(const char *s, int n, int m) {
  static int x[NMAX + 10], y[NMAX + 10], cnt[NMAX + 10], i;
  //memset(cnt, 0, sizeof(int) * (m + 1));
  for (i = 0; i < n; i++) cnt[s[i]]++;
  for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
  for (i = 0; i < n; i++) sa[--cnt[s[i]]] = i;
  for (i = 1, m = 1, rk[sa[0]] = 1; i < n; i++) {
    if (s[sa[i - 1]] != s[sa[i]]) m++;
    rk[sa[i]] = m;
  }
  for (int l = 1; l < n; l <<= 1) {
    memset(cnt, 0, sizeof(int) * (m + 1));
    for (i = 0; i < n; i++) cnt[y[i] = i + l < n ? rk[i + l] : 0]++;
    for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (i = n - 1; i >= 0; i--) x[--cnt[y[i]]] = i;
    memset(cnt, 0, sizeof(int) * (m + 1));
    for (i = 0; i < n; i++) cnt[rk[i]]++;
    for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--cnt[rk[x[i]]]] = x[i];
    for (i = 1, m = 1, x[sa[0]] = 1; i < n; i++) {
      if (rk[sa[i - 1]] != rk[sa[i]] || y[sa[i - 1]] != y[sa[i]]) m++;
      x[sa[i]] = m;
    }
    memcpy(rk, x, sizeof(int) * n);
}}
#define ACM_END

#define ACM_BEGIN
void compute_lcp(const char *s, int n) {
  int j = 0, p;
  for (int i = 0; i < n; i++, j = max(0, j - 1)) {
    if (rk[i] == 1) {
      j = 0;
      continue;
    }
    p = sa[rk[i] - 2];
    while (p + j < n && i + j < n && s[p + j] == s[i + j]) j++;
    lcp[rk[i]] = j;
}}
#define ACM_END

static char buf[NMAX + 10];

int main() {
  scanf("%s", buf);
  int n = strlen(buf);
  suffix_sort(buf, n, 255);
  compute_lcp(buf, n);
  for (int i = 0; i < n; i++) printf("%d ", sa[i] + 1);
  putchar('\n');
  for (int i = 2; i <= n; i++) printf("%d ", lcp[i]);
  putchar('\n');
  return 0;
}
