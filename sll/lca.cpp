/**
 * title: 倍增lca
 * category: 图论
 * description: /dev/null
 */
int lca(int x,int y) {
  if(deep[x]<deep[y])swap(x,y);
  int t=deep[x]-deep[y];
  for(int i=0;bin[i]<=t;i++)
    if(t&bin[i])x=fa[x][i];
  for(int i=16;i>=0;i--)
    if(fa[x][i]!=fa[y][i])
      x=fa[x][i],y=fa[y][i];
  if(x==y)return x;
  return fa[x][0];
}
