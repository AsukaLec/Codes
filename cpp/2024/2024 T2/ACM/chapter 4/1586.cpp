#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int N=3e3+10;
int fu[N],fee[N],d[N][N];
struct node{
	int u,v,w;
}p[N*N];
bool cmp(node a,node b)
{
	return a.w<b.w;
}
int find(int x)
{
	if(x!=fu[x]) fu[x]=find(fu[x]);
	return fu[x];
}
int main()
{
	int T,n;
	cin>>T;
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&fee[i]);
			fu[i]=i;
		}
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&d[i][j]);
		int cnt=0;
		for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			p[++cnt]={i,j,d[i][j]+fee[i]+fee[j]};
		sort(p+1,p+cnt+1,cmp);
		int count=0,ans=0;
		for(int i=1;i<=cnt;i++)
		{
			int f1=find(p[i].u),f2=find(p[i].v);
			if(f1==f2) continue ;
			ans+=p[i].w;
			fu[f1]=f2;
			count++;
			if(count==n-1) break;
		}
		printf("%d\n",ans);
	}
	return 0;
}