/**
 * title: 点双联通 tarjan
 * category: 图论
 * description: /dev/null
 */
void tarjan(int u, int fa) {
  pre[u] = low[u] = ++dfs_clock;
  for (int i = 0; i < (int)G[u].size(); i++) {
    int v = G[u][i];
    if (!pre[v]) {
      S.push(Edge(u, v));
      tarjan(v, u);
      low[u] = min(pre[v], low[u]);
      if (low[v] >= pre[u]) {
        bcc_cnt++;
        bcc[bcc_cnt].clear();
        for(;;) {
          Edge x = S.top(); S.pop();
          if (bccno[x.u] != bcc_cnt) {
            bcc[bcc_cnt].push_back(x.u);
            bccno[x.u] = bcc_cnt;
          }
          if (bccno[x.v] != bcc_cnt) {
            bcc[bcc_cnt].push_back(x.v);
            bccno[x.v] = bcc_cnt;
          }
          if (x.u == u && x.v == v) break;
    }}}
    else if (pre[v] < pre[u] && v != fa) {
      S.push(Edge(u, v));
      low[u] = min(low[u], pre[v]);
}}}
