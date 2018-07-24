#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
int n,m,k,p[50][50],a[2],cnt,ans,vis[50][50];
struct node{int x,y;}match[50][50];
int calc(int x,int y) { return (x+y)%2;}
bool find(int x,int y)
{
	for (int i=0;i<=3;i++)
	{
		int X=x+dx[i],Y=y+dy[i];
		if (X<1||Y<1||X>n||Y>m||p[X][Y]) continue;
		if (vis[X][Y]!=cnt)
		{
			vis[X][Y]=cnt;
			if (match[X][Y].x==0||find(match[X][Y].x,match[X][Y].y))
			{
				match[X][Y]=(node){x,y};
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&y,&x);
		p[x][y]=1;
		a[calc(x,y)]++;
	}
	if (a[0]!=a[1]) { puts("NO");return 0;}
	cnt=ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		if (!p[i][j]&&calc(i,j)==1)
		{
			cnt++;
			if (find(i,j)) ans++;
		}
	if (ans*2==n*m-k) puts("YES");else puts("NO");
	return 0;
}
