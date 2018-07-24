#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n;
char s[2050];
struct SAM
{
	int last,cnt,a[4010][26],fa[4010],maxlen[4010],val[4010],ans[4010],v[4010],Q[4010],len[4010];
	SAM() { last=++cnt;}
void extend(int c)
	{
		int p=last,np=last=++cnt;
		maxlen[np]=maxlen[p]+1;
		val[np]=1;
		while (!a[p][c]&&p) a[p][c]=np,p=fa[p];
		if (!p) fa[np]=1;
		else
		{
			int q=a[p][c];
			if (maxlen[p]+1==maxlen[q]) fa[np]=q;
			else
			{
				int nq=++cnt;maxlen[nq]=maxlen[p]+1;
				memcpy(a[nq],a[q],sizeof(a[q]));
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				while (a[p][c]==q) a[p][c]=nq,p=fa[p];
			}
		}
	}
	void pre()
	{
		for (int i=1;i<=cnt;i++) ans[i]=maxlen[i];
		for (int i=1;i<=cnt;i++) v[maxlen[i]]++;
		for (int i=1;i<=cnt;i++) v[i]+=v[i-1];
		for (int i=cnt;i>=1;i--) Q[v[maxlen[i]]--]=i;
	}
	void solve()
	{
		scanf("%s",s+1);
		memset(len,0,sizeof(len));
		int Len=strlen(s+1),p=1,tmp=0;
		for (int i=1;i<=Len;i++)
		{
			int c=s[i]-'a';
			while (!a[p][c]&&p) p=fa[p];
			if (!p) p=1,tmp=0;
				else tmp=min(tmp,maxlen[p])+1,p=a[p][c];
			len[p]=max(len[p],tmp);
		}
		for (int i=cnt;i>=1;i--) len[fa[Q[i]]]=max(len[fa[Q[i]]],len[Q[i]]);
		for (int i=1;i<=cnt;i++) ans[i]=min(ans[i],len[i]);
	}

}sam;
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	int Len=strlen(s+1);
	for (int i=1;i<=Len;i++) sam.extend(s[i]-'a');
	sam.pre();
	for (int i=1;i<n;i++) sam.solve();
	int ans=0;
	for (int i=1;i<=sam.cnt;i++) ans=max(ans,sam.ans[i]);
	printf("%d\n",ans);
	return 0;
}
