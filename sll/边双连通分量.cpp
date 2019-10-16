/**
 * title: 边双联通 tarjan
 * category: 图论
 * description: /dev/null
 */
void tarjan(int x, int f) {
    dfn[x] = low[x] = ++tot;
    sta[++tp] = x; vis[x] = true;
    for (int i = head[x]; i; i = e[i].next) if (i != (f ^ 1)) {
        if (!dfn[e[i].to]) {
            tarjan(e[i].to, i);
            low[x] = min(low[x], low[e[i].to]);
        }
        else if (vis[e[i].to]) low[x] = min(low[x], dfn[e[i].to]);
    }
    if (dfn[x] == low[x]) {
        scc++;
        while(1) {
            int pos = sta[tp--];
            vis[pos] = false;
            belong[pos] = scc;
            if (pos == x) break;
        }
    }
}
