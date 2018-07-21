#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1200100;
int Q;
char s[3000100];
struct LinkCutTree
{
	int fa[N],son[N][2],lazy[N],Stack[N],sum[N];
	bool isRoot(int x) { return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;}
	void pushdown(int x)
	{
		if (lazy[x])
		{
			if (son[x][0]) lazy[son[x][0]]+=lazy[x],sum[son[x][0]]+=lazy[x];
			if (son[x][1]) lazy[son[x][1]]+=lazy[x],sum[son[x][1]]+=lazy[x];
			lazy[x]=0;
		}
	}
	void Rotate(int x)
	{
		int y=fa[x],z=fa[y],l,r;
		if (son[y][0]==x) l=0;else l=1;
		r=l^1;
		if (!isRoot(y))
		{
			if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
		}
		fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
		son[y][l]=son[x][r];son[x][r]=y;
	}
	void splay(int x)
	{
		int top=0;Stack[++top]=x;
		for (int i=x;!isRoot(i);i=fa[i]) Stack[++top]=fa[i];
		for (;top;top--) pushdown(Stack[top]);
		while (!isRoot(x))
		{
			int y=fa[x],z=fa[y];
			if (!isRoot(y))
			{
				if ((son[y][0]==x)^(son[z][0]==y)) Rotate(x);
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
		}
	}
	void link(int x,int y)
	{
		fa[x]=y;
		access(y);
		splay(y);
		lazy[y]+=sum[x];
		sum[y]+=sum[x];
	}
	void cut(int x)
	{
		access(x);
		splay(x);
		if (son[x][0]) lazy[son[x][0]]-=sum[x],sum[son[x][0]]-=sum[x];
		son[x][0]=fa[son[x][0]]=0;
	}
	int query(int x)
	{
		splay(x);
		return sum[x];
	}
}LCT;
struct SAM
{
	int last,root,cnt,maxlen[N],val[N],a[N][26],father[N];
	SAM() { last=root=++cnt;}
	void extend(int c)
	{
		int p=last,np=last=++cnt;
		maxlen[np]=maxlen[p]+1;
		LCT.sum[np]=1;
		while (!a[p][c]&&p) a[p][c]=np,p=father[p];
		if (!p) father[np]=root,LCT.link(np,root);
		else
		{
			int q=a[p][c];
			if (maxlen[p]+1==maxlen[q]) father[np]=q,LCT.link(np,q);
			else
			{
				int nq=++cnt;
				maxlen[nq]=maxlen[p]+1;
				memcpy(a[nq],a[q],sizeof(a[nq]));
				father[nq]=father[q];
				LCT.link(nq,father[q]);
				father[np]=father[q]=nq;
				LCT.cut(q);
				LCT.link(q,nq);
				LCT.link(np,nq);
				while (a[p][c]==q) a[p][c]=nq,p=father[p];
			}
		}
	}
	int query()
	{
		int len=strlen(s),id=1;
		for (int i=0;i<len;i++)
		if (a[id][s[i]-'A']) id=a[id][s[i]-'A'];
				else return 0;
		return LCT.query(id);
	}
}sam;
void decode(int mask)
{
	int len=strlen(s);
	for (int i=0;i<len;i++)
	{
		mask=(mask*131+i)%len;
		swap(s[i],s[mask]);
	}
}
int main()
{
	scanf("%d",&Q);
	scanf("%s",s);
	int len=strlen(s);
	for (int i=0;i<len;i++) sam.extend(s[i]-'A');
	int mask=0;
	while (Q--)
	{
		char S[10];
		scanf("%s%s",S,s);
		decode(mask);
		if (S[0]=='Q')
		{
			int ans=sam.query();
			mask^=ans;
			printf("%d\n",ans);
		}else
		{
			int len=strlen(s);
			for (int i=0;i<len;i++) sam.extend(s[i]-'A');
		}
	}
	return 0;
}
