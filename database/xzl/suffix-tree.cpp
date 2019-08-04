/**
 * title: 后缀树
 * category: 字符串
 * description: /dev/null
 */

#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300000
#define ACM_BEGIN
#define SIGMA 27
#define EOFCHAR 26
#define ACM_END

typedef long long int64;

static int n;

#define ACM_BEGIN
static char str[NMAX + 10];
struct Node;
struct Edge {
  Edge(int l, int r, Node *nxt) : left(l), right(r), nxt(nxt) {}
  int left, right; Node *nxt;
  int length() const { return right - left + 1; }
};
struct Node {
  Node() : fail(NULL) { memset(trans, 0, sizeof(trans)); }
  Node *fail; Edge *trans[SIGMA];
};
struct BuildState {
  BuildState(Node *_r) : r(_r), ap(_r), dir(-1), len(0), remain(0), pos(0) {}
  Node *r, *ap; char dir; int len, remain, pos;
};
void append(char c, BuildState &state) {
  auto &cur = state.ap; auto &dir = state.dir;
  auto &len = state.len; auto &cnt = state.remain;
  auto &size = state.pos; cnt++; size++;
  Node *last = NULL, *x;
  while (cnt) {
    if (cnt - 1 <= len) {
      len = cnt - 1;
      dir = len ? str[size - len] : -1;
    }
    while (dir >= 0 && len >= cur->trans[dir]->length()) {
      len -= cur->trans[dir]->length();
      cur = cur->trans[dir]->nxt;
      dir = len ? str[size - len] : -1;
    }
    if ((dir >= 0 && c == str[cur->trans[dir]->left + len]) ||
      (dir < 0 && cur->trans[c])) {
      if (dir < 0) dir = c;
      if (last) last->fail = cur;
      len++;
      return;
    }
    if (dir < 0) {
      cur->trans[c] = new Edge(size, n, new Node);
      x = cur;
    } else {
      Edge *t = cur->trans[dir];
      x = new Node;
      x->trans[c] = new Edge(size, n, new Node);
      x->trans[str[t->left + len]] = new Edge(t->left + len, t->right, t->nxt);
      t->right = t->left + len - 1;
      t->nxt = x;
    }
    if (last) last->fail = x;
    last = x; cnt--;
    cur = cur->fail ? cur->fail : state.r;
}}
#define ACM_END

struct Info {
  Info() : count(0), max({INT_MIN, INT_MIN}), min({INT_MAX, INT_MAX}) {}

  int64 count;
  struct {
    int64 first;
    int64 second;
  } max;
  struct {
    int64 first;
    int64 second;
  } min;

  int64 count_pairs() const {
    return count * (count - 1) / 2;
  }

  int64 max_product() const {
    if (count >= 2)
      return std::max(max.first * max.second, min.first * min.second);
    return 0;
  }

  void update_max(int64 v) {
    if (v > max.first) {
      max.second = max.first;
      max.first = v;
    } else if (v > max.second)
      max.second = v;
  }

  void update_min(int64 v) {
    if (v < min.first) {
      min.second = min.first;
      min.first = v;
    } else if (v < min.second)
      min.second = v;
  }

  Info &operator+=(const Info &b) {
    count += b.count;
    update_max(b.max.first);
    update_max(b.max.second);
    update_min(b.min.first);
    update_min(b.min.second);

    return *this;
  }
};  // struct Info

static int64 w[NMAX + 10];
static Node *tree;
static int64 sum[NMAX + 10];
static int64 maxv[NMAX + 10];

Info dfs(Node *x, int depth = 0) {
  Info info;
  bool has_child = false;
  for (char c = 0; c < SIGMA; c++) {
    Edge *t = x->trans[c];

    if (!t)
      continue;

    has_child = true;
    auto data = dfs(t->nxt, depth + t->length());

    sum[depth] -= data.count_pairs();
    sum[depth + t->length()] += data.count_pairs();

    if (data.count >= 2)
      maxv[depth + t->length()] =
        max(maxv[depth + t->length()], data.max_product());

    info += data;
  }  // for

  if (!has_child) {
    info.count = 1;
    info.max.first = info.min.first = w[n - depth + 1];
  }

  return info;
}

#define ACM_BEGIN
void initialize() {
  scanf("%d%s", &n, str + 1);
#define ACM_END

  for (int i = 1; i <= n; i++) {
    scanf("%lld", w + i);
    str[i] -= 'a';
  }  // for
  for (int i = 0; i <= n + 2; i++) {
    maxv[i] = LLONG_MIN;
  }  // for

#define ACM_BEGIN
  tree = new Node;
  BuildState state(tree);
  for (int i = 1; i <= n; i++) append(str[i], state);
  append(EOFCHAR, state);
  tree->trans[EOFCHAR] = NULL;
}
#define ACM_END

int main() {
  // freopen("ex_savour3.in", "r", stdin);

  initialize();

  Info r0 = dfs(tree);

  for (int i = n + 1; i > 0; i--) {
    sum[i] += sum[i + 1];
    maxv[i] = max(maxv[i], maxv[i + 1]);
  }  // for

  printf("%lld %lld\n", r0.count_pairs(), max(maxv[1], r0.max_product()));
  for (int r = 1; r < n; r++) {
    if (sum[r] == 0)
      maxv[r] = 0;

    printf("%lld %lld\n", sum[r], maxv[r]);
  }  // for

  return 0;
}  // function main
