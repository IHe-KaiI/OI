#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
#define ull unsigned long long
#define P 29
using namespace std;
int n,root,tot,size[250010],Tree[250010],son[250010][2],fa[250010];
char ch;
char s1[100],s[100],s2[100],S[250010][15];
map<ull,int>M;
void newnode(int id,int x) { Tree[id]=x;size[id]=1;son[id][0]=son[id][1]=0;fa[id]=0;return;}
void update(int x)
{
	size[x]=size[son[x][0]]+size[son[x][1]]+1;
}
void Rotate(int x,int &k)
{
	int y=fa[x],z=fa[y],l,r;
	if (son[y][0]==x) l=0;else l=1;
	r=l^1;
	if (y==k) k=x;
	else
	{
		if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
	}
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	update(y);update(x);
}
void splay(int x,int &k)
{
	while (x!=k)
	{
		int y=fa[x],z=fa[y];
		if (y!=k)
		{
			if ((son[z][0]==y)^(son[y][0]==x)) Rotate(x,k);
				else Rotate(y,k);
		}
		Rotate(x,k);
	}
}
void Insert(int x,int y)
{
	if (!root) { root=x;newnode(x,y);return;}
	int i=root,j=0;
	while (i)
	{
		j=i;
		if (y<=Tree[i]) i=son[i][1];
			else i=son[i][0];
	}
	newnode(x,y);
	son[j][y<=Tree[j]]=x;
	fa[x]=j;
	splay(x,root);
}
void Del(int id)
{
	splay(id,root);
	if (size[id]==1) { root=0;fa[id]=son[id][0]=son[id][1]=0;return;}
	if (!son[id][0]||!son[id][1])
	{
		root=son[id][0]^son[id][1];
		son[id][0]=son[id][1]=fa[id]=0;
		return;
	}
	int i=son[id][0];
	while (son[i][1]) i=son[i][1];
	splay(i,son[id][0]);
	root=i;
	son[i][1]=son[id][1];
	fa[son[id][1]]=i;
	fa[id]=son[id][0]=son[id][1]=0;
	update(root);
}
int Rank(int x)
{
	splay(x,root);
	return size[son[x][0]]+1;
}
int find(int x)
{
	int i=root;
	while (i)
	{
		if (size[son[i][0]]+1==x) return i;
		if (size[son[i][0]]>=x) i=son[i][0];	
			else x-=size[son[i][0]]+1,i=son[i][1];
	}
}
void print(int id)
{
	if (!id) return;
	print(son[id][0]);
	printf("%s ",S[id]);
	print(son[id][1]);
}
void Kth(int x)
{
	int y=min(size[root],x+9);
	x=find(x);y=find(y);
	if (x==y) { printf("%s",S[x]);return;}
	splay(x,root);
	splay(y,son[x][1]);
	printf("%s ",S[x]);
	print(son[y][0]);
	printf("%s",S[y]);
}
int main()
{
	scanf("%d",&n);
	root=tot=0;
	while (n--)
	{
		scanf("%s",s1);
		int L=strlen(s1);
		for (int i=1;i<L;i++) s[i-1]=s1[i];
		if (s1[0]=='+')
		{
			int x;ull SUM=0;
			scanf("%d",&x);
			int len=L-1;
			for (int i=1;i<=len;i++) SUM=SUM*P+s[i-1]-'A'+1;
			if (!M[SUM]) { M[SUM]=++tot;Insert(tot,x);}
			else
			{
				Del(M[SUM]);
				M[SUM]=++tot;
				Insert(tot,x);
			}
			for (int i=0;i<=len-1;i++) S[tot][i]=s[i];
		}else
		{
			int I=0,i=0,x=0;ull SUM=0;
			while (I<L-1&&((s[I]>='0'&&s[I]<='9')||(s[I]>='A'&&s[I]<='Z')))
			{
				if (s[I]>='0'&&s[I]<='9') x=x*10+s[I]-'0';
					else s2[i++]=s[I];
				I++;
			}
			if (i)
			{
				for (int j=0;j<i;j++) SUM=SUM*P+s2[j]-'A'+1;
				int id=M[SUM];
				printf("%d\n",Rank(id));
			}else
			{
				Kth(x);
				puts("");
			}
		}
	}
	return 0;
}	
