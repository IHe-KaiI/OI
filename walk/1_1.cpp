#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#define ll long long
#define mo 998244353
using namespace std;
const int N=3010,M=5010;
int n,m,T,tot,Next[M*2],head[M],tree[M*2],f[2][N],fail[N+N],delta[N+N];
vector<int>A,B;
char s[100010];
void add(int x,int y)
{
	tot++;
	Next[tot]=head[x];
	head[x]=tot;
	tree[tot]=y;
}
ll mi(ll x,int y)
{
	ll ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
void Add(int &x,int y) { x+=y;if (x>=mo) x-=mo;}
vector<int> BM(vector<int> &A)
{
	vector<int> B,S;
	int best=0,cnt=0;
	for (int i=0;i<(int)A.size();i++)
	{
		ll x=A[i];
		for (int j=0;j<(int)B.size();j++)
			x=(x-(ll)B[j]*A[i-j-1]%mo+mo)%mo;
		delta[i]=x;
		if (!x) continue;
		fail[cnt++]=i;
		if (B.empty())
		{
			B.resize(i+1);
			best=cnt-1;
			continue;
		}
		ll k=x*mi(delta[fail[best]],mo-2)%mo;
		vector<int> C;
		C.resize(i-fail[best]-1);
		C.push_back(k);
		for (int j=0;j<(int)S.size();j++)
			C.push_back((mo-k*S[j]%mo)%mo);
		if (C.size()<B.size()) C.resize(B.size());
		for (int j=0;j<(int)B.size();j++)
			C[j]=(C[j]+B[j])%mo;
		if (B.size()<=i-fail[best]+S.size()) best=cnt-1,S=B;
		B=C;
	}
	return B;
}
void DP()
{
	f[0][1]=1;
	int sum=1,now=0;
	for (int t=1;t<=n+n+5;t++)
	{
		now^=1;
		for (int i=1;i<=n;i++) f[now][i]=f[now^1][i];
		for (int i=1;i<=n;i++)
			for (int j=head[i];j;j=Next[j])
			{
				int v=tree[j];
				Add(f[now][v],f[now^1][i]);
			}
		for (int i=1;i<=n;i++) Add(sum,f[now][i]);
		A.push_back(sum);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	scanf("%s",s);
	int len=strlen(s);
	for (int i=len-1;i>=0;i--) T=T*2+s[i]-'0';
	DP();
	B=BM(A);
	int L=B.size();
	for (int i=n+n+6;i<=T;i++)
	{
		int x=0;
		for (int j=0;j<L;j++) Add(x,(ll)A[i-j-2]*B[j]%mo);
		A.push_back(x);
	}
	printf("%d\n",A[T-1]);
	return 0;
}
