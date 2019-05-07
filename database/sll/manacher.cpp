/**
 * title: manacher
 * category: 字符串
 * description: /dev/null
 */
void manacher() {
  //max(p[i])-1即为最大回文子串长
  int mx=0,id=0;n=strlen(ch);
  for(int i=n;i;i--)ch[i]=ch[i-1];
  for(int i=1;i<=n;i++)c[i<<1]=ch[i],c[i<<1|1]='#';
  m=n<<1|1;c[0]='-',c[1]='#',c[m+1]='+';
  for(int i=1;i<=m;i++) {
    if(mx>i)p[i]=min(p[2*id-i],mx-i);
    while(c[p[i]+i]==c[i-p[i]])p[i]++;
    if(i+p[i]>mx)mx=i+p[i],id=i;
}}
