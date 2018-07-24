#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;
int n,K,now;
ll X,Y;
struct node
{
	int ls,rs;
	ll x,y,minx,maxx,miny,maxy;
}Tree[100010];
priority_queue<ll,vector<ll>,greater<ll> >Q;
bool cmp(node a,node b) { return (now)?a.y<b.y:a.x<b.x;}
void up(int id)
{
	int l=Tree[id].ls,r=Tree[id].rs;
	if (l)
	{
		Tree[id].minx=min(Tree[id].minx,Tree[l].minx);
		Tree[id].maxx=max(Tree[id].maxx,Tree[l].maxx);
		Tree[id].miny=min(Tree[id].miny,Tree[l].miny);
		Tree[id].maxy=max(Tree[id].maxy,Tree[l].maxy);
	}
	if (r)
	{
		Tree[id].minx=min(Tree[id].minx,Tree[r].minx);
		Tree[id].maxx=max(Tree[id].maxx,Tree[r].maxx);
		Tree[id].miny=min(Tree[id].miny,Tree[r].miny);
		Tree[id].maxy=max(Tree[id].maxy,Tree[r].maxy);
	}
}
int build(int l,int r,int d)
{
	if (l>r) return 0;
	int mid=(l+r)>>1;
	now=d;
	nth_element(Tree+l,Tree+mid+1,Tree+r+1,cmp);
	Tree[mid].ls=build(l,mid-1,d^1);
	Tree[mid].rs=build(mid+1,r,d^1);
	up(mid);
	return mid;
}
inline ll Sqr(ll X) { return X*X;}
ll Get_MaxDis(int id)
{
	return max(Sqr(Tree[id].minx-X),Sqr(Tree[id].maxx-X))+max(Sqr(Tree[id].miny-Y),Sqr(Tree[id].maxy-Y));
}
void query(int id)
{
	ll dis=Sqr(Tree[id].x-X)+Sqr(Tree[id].y-Y);
	if (dis>Q.top()) { Q.pop();Q.push(dis);}
	int l=Tree[id].ls,r=Tree[id].rs;
	ll disL=0,disR=0;
	if (l) disL=Get_MaxDis(l);
	if (r) disR=Get_MaxDis(r);
	if (disL>disR)
	{
		if (disL>Q.top()) query(l);
		if (disR>Q.top()) query(r);
	}else
	{
		if (disR>Q.top()) query(r);
		if (disL>Q.top()) query(l);
	}
}
int main()
{
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&Tree[i].x,&Tree[i].y);
		Tree[i].minx=Tree[i].maxx=Tree[i].x;
		Tree[i].miny=Tree[i].maxy=Tree[i].y;
	}
	int root=build(1,n,0);
	K<<=1;
	for (int i=1;i<=K;i++) Q.push(0);
	for (int i=1;i<=n;i++)
	{
		X=Tree[i].x;Y=Tree[i].y;
		query(root);
	}
	printf("%lld\n",Q.top());
	return 0;
}
