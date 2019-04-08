#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
int n,m,f[210];
struct node{int u,v,a,b;ll w;}E[20010],a[20010];
struct Point { ll x,y;}ANS;
ll Ans;
Point operator - (Point a,Point b) { return (Point){a.x-b.x,a.y-b.y};}
bool cmp(node a,node b) { return a.w<b.w;}
ll cross(Point a,Point b) { return a.x*b.y-a.y*b.x;}
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
Point MST()
{
	for (int i=1;i<=n;i++) f[i]=i;
	Point ans=(Point){0,0};
	sort(a+1,a+m+1,cmp);
	int cnt=0;
	for (int i=1;i<=m;i++)
	{
		int x=get(a[i].u),y=get(a[i].v);
		if (x!=y)
		{
			f[x]=y;
			ans.x+=a[i].a;
			ans.y+=a[i].b;
			cnt++;
		}
		if (cnt==n-1) break;
	}
	if (ans.x*ans.y<Ans||(ans.x*ans.y==Ans&&ans.x<ANS.x)) Ans=ans.x*ans.y,ANS=ans;
	return ans;
}
void solve(Point A,Point B)
{
	for (int i=1;i<=m;i++) a[i].w=(A.y-B.y)*a[i].a+(B.x-A.x)*a[i].b;
	Point C=MST();
	if (cross(C-A,C-B)>=0) return;
	solve(A,C);solve(C,B);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].a,&E[i].b);
		E[i].u++;E[i].v++;
	}
	Ans=1LL<<60;
	ANS=(Point){1LL<<60,1LL<<60};
	for (int i=1;i<=m;i++) a[i]=E[i],a[i].w=a[i].a;
	Point A=MST();
	for (int i=1;i<=m;i++) a[i].w=a[i].b;
	Point B=MST();
	solve(A,B);
	printf("%lld %lld\n",ANS.x,ANS.y);
	return 0;
}
