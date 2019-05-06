/**
 * title: AC 自动机
 * category: 字符串
 * description: ac.md
 */
#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define SIGMA 26

#define ACM_BEGIN
struct Node {
  Node() : mark(false), suf(NULL), nxt(NULL) {
    memset(ch, 0, sizeof(ch));
  }
  bool mark;
#define ACM_END
  char *data;
#define ACM_BEGIN
  Node *suf, *nxt, *ch[SIGMA];
};
#define ACM_END

#define ACM_BEGIN
void insert(Node *x, char *s) {
  for (int i = 0; s[i]; i++) {
    int c = s[i] - 'a';
    if (!x->ch[c]) x->ch[c] = new Node;
    x = x->ch[c];
  }
#define ACM_END
  x->data = s;
#define ACM_BEGIN
  x->mark = true;
}
void build_automaton(Node *r) {
  queue<Node *> q;
  for (int c = 0; c < SIGMA; c++) {
    if (!r->ch[c]) continue;
    r->ch[c]->suf = r;
    q.push(r->ch[c]);
  }
  while (!q.empty()) {
    Node *x = q.front();
    q.pop();
    for (int c = 0; c < SIGMA; c++) {
      Node *v = x->ch[c]; if (!v) continue;
      Node *y = x->suf;
      while (y != r && !y->ch[c]) y = y->suf;
      if (y->ch[c]) y = y->ch[c];
      v->suf = y;
      if (y->mark) v->nxt = y;
      else v->nxt = y->nxt;
      q.push(v);
}}}
#define ACM_END

void print(int pos, char *s) {
  printf("[%d] Matched: %s\n", pos, s);
}

#define ACM_BEGIN
void search(Node *x, char *s) {
  for (int i = 0; s[i]; i++) {
    int c = s[i] - 'a';
    while (x->suf && !x->ch[c]) x = x->suf;
    if (x->ch[c]) x = x->ch[c];
    if (x->mark) print(i + 1, x->data);
    for (Node *y = x->nxt; y; y = y->nxt) print(i + 1, y->data);
}}
#define ACM_END

static int n;
static char buf[50][NMAX + 10], str[NMAX + 10];
static Node *trie;

int main() {
  trie = new Node;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", buf[i]);
    insert(trie, buf[i]);
  }
  build_automaton(trie);
  scanf("%s", str);
  search(trie, str);
  return 0;
}
