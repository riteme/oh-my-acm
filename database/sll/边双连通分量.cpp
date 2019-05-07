/**
 * title: 边双联通 tarjan
 * category: 图论
 * description: /dev/null
 */
const int N = 5010; // 3352只用1010即可
struct node{
  int v,w,id;
  node(int v = 0,int w = 0,int id = 0):v(v),w(w),id(id){};
};
vector<node>G[N];
int pre[N];
int low[N];
int dfs_num;int ans ;int n,m;
void init(){
  mem(pre,0); mem(low,0);
  for(int i=0;i<=n;i++) G[i].clear();
  dfs_num = 0;ans = INF;
}
int dfs(int u,int fa){
  low[u] = pre[u] = ++dfs_num;
  for(int i=0;i<G[u].size();i++){
    int v = G[u][i].v;
    int id = G[u][i].id;
    if(id == fa) continue;
    if(!pre[v]){
      dfs(v,id);//注意这里 第二个参数是 id
      low[u] = min(low[u],low[v]);//用后代的low更新当前的
    }
    else
      low[u] = min(low[u],pre[v]);//利用后代v的反向边更新low
}}
int main(){
  int t;
  while(scanf("%d%d",&n,&m)!=EOF&& (n || m)){
    int a,b,c;
    init();
    for(int i=1;i<=m;i++){
      scanf("%d%d",&a,&b);
      G[a].push_back(node(b,0,i));
      G[b].push_back(node(a,0,i));
    }
    for(int i=1;i<=n;i++){
      if(!pre[i])
        dfs(i,0);
      //cout<<i<<endl;
    }
    int degree[N];mem(degree,0);
    for(int i=1;i<=n;i++){
      for(int j=0;j<G[i].size();j++){
        int v = G[i][j].v;
        if(low[i] != low[v]){
          degree[low[v]]++; degree[low[i]]++;
    }}}
    int l = 0;
    for(int i=1;i<=dfs_num;i++)
      if(degree[i] == 2)
      l++;
    printf("%d\n",(l+1)/2);
  }
  return 0;
}
