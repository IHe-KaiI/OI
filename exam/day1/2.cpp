#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=2100000;
int n,X[300],maxlen[N],a[N][4],fa[N],top,Case,cnt,last;
char Y[300],s[N],Stack[N];
void extend(int c)
{
    int p=last,np;last=np=++cnt;
    maxlen[np]=maxlen[p]+1;
    while (!a[p][c]&&p) a[p][c]=np,p=fa[p];
    if (!p) fa[np]=1;
    else
    {
        int q=a[p][c];
        if (maxlen[q]==maxlen[p]+1) fa[np]=q;
        else
        {
            int nq=++cnt;
            maxlen[nq]=maxlen[p]+1;
            memcpy(a[nq],a[q],sizeof(a[q]));
            fa[nq]=fa[q];
            fa[np]=fa[q]=nq;
            while (a[p][c]==q) a[p][c]=nq,p=fa[p];
        }
    }
}
void dfs(int id)
{
	Stack[top]='\0';
	if (id!=1) printf("%s\n",Stack);
	for (int i=0;i<4;i++)
	if (a[id][i])
	{
		Stack[top++]=Y[i];
		dfs(a[id][i]);
		top--;
	}
}
int main()
{
	freopen("copy.in","r",stdin);
	freopen("copy.out","w",stdout);
	scanf("%d",&n);
	X['A']=0;X['C']=1;X['G']=2;X['T']=3;
	Y[0]='A';Y[1]='C';Y[2]='G';Y[3]='T';
	last=cnt=1;
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		int len=strlen(s+1);
		for (int j=1;j<=len;j++) extend(X[s[j]]);
	}
	scanf("%d",&Case);
	ll ans=0;
	for (int i=1;i<=cnt;i++) ans+=maxlen[i]-maxlen[fa[i]];
	if (Case)
	{
		dfs(1);
	}
	printf("%lld\n",ans);
	return 0;
}
