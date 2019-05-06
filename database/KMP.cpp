/**
 * title: KMP
 * category: ×Ö·û´®
 * description: /dev/null
 */
int p[101];
int main()
{
    string a,b;
    cin>>a>>b;
    int n=a.length(),m=b.length();
    a=" "+a;b=" "+b;
    int j=0;
    for(int i=2;i<=m;i++)
    {
            while(j>0&&b[j+1]!=b[i])j=p[j];
            if(b[j+1]==b[i])j++;
            p[i]=j;
            }
    j=0;
    for(int i=1;i<=n;i++)
    {
            while(j>0&&b[j+1]!=a[i])j=p[j];
            if(b[j+1]==a[i])j++;
            if(j==m){printf("%d",i-m+1);break;}
            }
    return 0;
}
