#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
using namespace std;
const int N=1100010;
int n,m,q,fa[N],rev[N],son[N][2],Stack[N],ans[N],ID[N],f[N],Use[N];
struct node{int x,y,z;}E[1000100];
struct Ques{int op,x,y;}Q[100010];
struct A{int x,y,i;}S[N];
pair<int,int>Max[N],val[N];
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
void Union(int x,int y)
{
	f[get(x)]=get(y);
}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool isRoot(int x) { return (son[fa[x]][0]!=x&&son[fa[x]][1]!=x);}
void up(int id)
{
	Max[id]=max(max(Max[son[id][0]],Max[son[id][1]]),val[id]);
}
void down(int id)
{
	if (rev[id])
	{
		swap(son[id][0],son[id][1]);
		if (son[id][0]) rev[son[id][0]]^=1;
		if (son[id][1]) rev[son[id][1]]^=1;
		rev[id]=0;
	}
}
void Rotate(int x)
{
	int y=fa[x],z=fa[y],l,r;
	if (son[y][0]==x) l=0;else l=1;
	r=l^1;
	if (!isRoot(y))
	{
		if (son[z][0]==y) son[z][0]=x;
        		else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	up(y);up(x);
}
void splay(int x)
{
	int top=0;Stack[++top]=x;
	for (int i=x;!isRoot(i);i=fa[i])
	{
		Stack[++top]=fa[i];
	}
	for (;top;top--) down(Stack[top]);
	while (!isRoot(x))
	{
        	int y=fa[x],z=fa[y];
		if (!isRoot(y))
        	{
        		if ((son[z][0]==y)^(son[y][0]==x)) Rotate(x);
               			else Rotate(y);
        	}
        	Rotate(x);
	}
}
void access(int x)
{
	for (int i=0;x;i=x,x=fa[x])
	{
		splay(x);
		son[x][1]=i;
		up(x);
	}
}
void MakeRoot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}
void link(int x,int y)
{
	MakeRoot(x);
	fa[x]=y;
}
void cut(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	son[y][0]=0;
	fa[x]=0;
	up(y);
}
pair<int,int> GetMax(int x,int y)
{
	MakeRoot(x);
	access(y);
	splay(y);
	return Max[y];
}
void add_edge(int id)
{
     int x=E[id].x,y=E[id].y,z=E[id].z;
     Max[n+id]=val[n+id]=make_pair(z,id);
     if (get(x)!=get(y)) link(x,n+id),link(n+id,y),Union(x,y);
     else
     {
        pair<int,int> Max=GetMax(x,y);
        if (Max.first>z)
	{
		cut(E[Max.second].x,n+Max.second),cut(n+Max.second,E[Max.second].y);
		link(x,n+id),link(n+id,y);
	}
     }
}
bool cmp(int a,int b) { return E[a].z<E[b].z;}
bool CMP(A a,A b) { return (a.x==b.x)?a.y<b.y:a.x<b.x;}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for (int i=1;i<=n+m;i++) f[i]=i;
    for (int i=1;i<=m;i++)
    {
	E[i].x=read();E[i].y=read();E[i].z=read();
        if (E[i].x>E[i].y) swap(E[i].x,E[i].y);
    }
    int cnt=0;
    for (int i=1;i<=q;i++)
    {
	Q[i].op=read();Q[i].x=read();Q[i].y=read();
        if (Q[i].x>Q[i].y) swap(Q[i].x,Q[i].y);
	if (Q[i].op==2) S[++cnt]=(A){Q[i].x,Q[i].y,i};
    }
    sort(S+1,S+cnt+1,CMP);
    int num=0;
    for (int i=1;i<=m;i++)
    {
	int id=lower_bound(S+1,S+cnt+1,(A){E[i].x,E[i].y,0},CMP)-S;
	if (S[id].x==E[i].x&&S[id].y==E[i].y) ID[S[id].i]=i;
		else Use[++num]=i;
    }
    sort(Use+1,Use+num+1,cmp);
    for (int i=1;i<=num;i++)
    {
	int x=E[Use[i]].x,y=E[Use[i]].y;
	if (get(x)!=get(y))
	{
		add_edge(Use[i]);
		f[get(x)]=get(y);
	}
    }
    for (int i=q;i>=1;i--)
    {
        if (Q[i].op==2) add_edge(ID[i]);
            else ans[i]=GetMax(Q[i].x,Q[i].y).first;
    }
    for (int i=1;i<=q;i++)
	    if (Q[i].op==1) printf("%d\n",ans[i]);
    return 0;
}

