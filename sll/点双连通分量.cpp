/**
 * title: 点双联通 tarjan
 * category: 图论
 * description: /dev/null
 */
void tarjan(ll u)
{
    dfn[u]=low[u]=++tim;
    sz[u]=1;
    ll t=0;
    for(ll i=head[u];i;i=e[i].next)
        {
            ll v=e[i].to;
            if(dfn[v])low[u]=min(low[u],dfn[v]);
            else
                {
                    tarjan(v);
                    sz[u]+=sz[v];
                    low[u]=min(low[u],low[v]);
                    if(dfn[u]<=low[v])
                        {
                            ans[u]+=t*sz[v];
                            t+=sz[v];
                        }
                }
        }
    ans[u]+=t*(n-t-1);
}
