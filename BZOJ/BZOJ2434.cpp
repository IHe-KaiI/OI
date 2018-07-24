#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstring>
#include<vector>
#define mp make_pair
using namespace std;
const int N=100010;
char s[N];
int len,cnt,n,Time,danger[N],a[N][26],fa[N],Q[N],fail[N],ans[N],In[N],Out[N],f[N];
vector<pair<int,int> >M[N];
vector<int>E[N];
void build_fail()
{
	fail[1]=0;
	for (int i=0;i<26;i++) a[0][i]=1;
	int t=0,w=1;
	Q[1]=1;
	while (t<w)
	{
		int u=Q[++t];
		for (int i=0;i<26;i++)
		if (a[u][i])
		{
			fail[a[u][i]]=a[fail[u]][i];
			E[a[fail[u]][i]].push_back(a[u][i]);
			Q[++w]=a[u][i];
		}else a[u][i]=a[fail[u]][i];
	}
}
void Insert()
{
	int id=1,num=0;
	for (int i=1;i<=len;i++)
	{
		if (s[i]=='P') { danger[++num]=id;continue;}
		if (s[i]=='B') { id=fa[id];continue;}
		if (!a[id][s[i]-'a']) a[id][s[i]-'a']=++cnt,fa[cnt]=id;
		id=a[id][s[i]-'a'];
	}
}
void dfs(int u)
{
	In[u]=++Time;
	for (int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		dfs(v);
	}
	Out[u]=Time;
}
inline int lowbit(int x) { return x&(-x);}
void add(int x,int y)
{
	for (int i=x;i<=Time;i+=lowbit(i)) f[i]+=y;
}
int query(int x)
{
	int ans=0;
	for (int i=x;i>=1;i-=lowbit(i)) ans+=f[i];
	return ans;
}
void solve()
{
	int num=0,id=1;
	for (int i=1;i<=len;i++)
	{
		if (s[i]=='P')
		{
			num++;
			for (int j=0;j<M[num].size();j++)
			{
				int k=M[num][j].first;
				ans[M[num][j].second]+=query(Out[danger[k]])-query(In[danger[k]]-1);
			}
			continue;
		}
		if (s[i]=='B') { add(In[id],-1);id=fa[id];continue;}
		id=a[id][s[i]-'a'];
		add(In[id],1);
	}
}
int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	cnt=1;
	Insert();
	build_fail();
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		M[y].push_back(mp(x,i));
	}
	dfs(1);
	solve();
	for (int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
