/**
 * title: 有向图强联通 tarjan
 * category: 图论
 * description: /dev/null
 */
int n,m;
int head[N],pos;
struct edge{int to,next;}e[N<<1];
void add(int a,int b)
{pos++;e[pos].to=b,e[pos].next=head[a],head[a]=pos;}
int dfn[N],low[N],SCC;
bool in[N];
int st[N],top,T;
vector<int>G[N];
void tarjan(int u) {
  st[++top]=u;in[u]=1;
  dfn[u]=low[u]=++T;
  for(int i=head[u];i;i=e[i].next) {
    int v=e[i].to;
    if(!dfn[v]) {
      tarjan(v);
      low[u]=min(low[u],low[v]);
    }
    else if(in[v])low[u]=min(low[u],dfn[v]);
  }
  if(low[u]==dfn[u]) {
    int v;
    ++SCC;
    do {
      v=st[top--];
      in[v]=false;
      G[SCC].push_back(v);
    }while(v!=u);
}}
int main() {
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++) {
    int x,y;
    scanf("%d%d",&x,&y);
    add(x,y);
  }
  for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
}
