#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 1000000007
#define ll long long
using namespace std;
const double pi=acos(-1.0);
const int N=200100;
int n,L,H,c[N<<1],RL[N<<1];
ll f[N<<1],ans;
char s[N<<1],S[N<<1];
struct complex
{
	double r,v;
	inline complex operator + (const complex &a) { return (complex){r+a.r,v+a.v};}
	inline complex operator - (const complex &a) { return (complex){r-a.r,v-a.v};}
	inline complex operator * (const complex &a) { return (complex){r*a.r-v*a.v,r*a.v+v*a.r};}
}a[400100],b[400100],w[400100];
void FFT(complex *a,int f)
{
	for (int i=0,j=0;i<L;i++)
	{
		if (i>j) swap(a[i],a[j]);
		for (int k=L>>1;(j^=k)<k;k>>=1); 
	}
	for (int len=2;len<=L;len<<=1)
	{
		int l=len>>1;
		complex W=(complex){cos(pi/l),f*sin(pi/l)};
		for (int i=1;i<l;i++) w[i]=w[i-1]*W;
		for (int i=0;i<L;i+=len)
			for (int j=0;j<l;j++)
			{
				complex x=a[i+j],y=w[j]*a[i+j+l];
				a[i+j]=x+y;a[i+j+l]=x-y;
			}
	}
	if (f==-1)
	{
		for (int i=0;i<L;i++) a[i].r/=L;
	}
}
void manacher(char *s,int len)
{
	int maxright=0,pos=0;
	for (int i=2;i<=len;i++)
	{
		if (maxright>=i) RL[i]=min(RL[pos+pos-i],maxright-i);
		while (s[i-RL[i]]==s[i+RL[i]]) RL[i]++;
		if (i+RL[i]>maxright) pos=i,maxright=i+RL[i];
		if (i&1) (ans-=RL[i]>>1)%=mo;else (ans-=(RL[i]+1)>>1)%=mo;
	}
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for (int i=1;i<=n;i++) S[i<<1]=s[i],S[i<<1|1]='#';
	S[1]='!';S[(n+1)<<1]='?';
	manacher(S,n<<1|1);
	w[0]=(complex){1.0,0.0};
	L=1;H=0;
	while (L<n+n) L<<=1,H++;
	for (int i=0;i<L;i++) a[i]=(complex){(s[i+1]=='a'),0.0};
	FFT(a,1);
	for (int i=0;i<L;i++) a[i]=a[i]*a[i];
	FFT(a,-1);
	for (int i=0;i<n+n;i++) c[i+1]=(int)(a[i].r+0.5);
	for (int i=0;i<L;i++) a[i]=(complex){(s[i+1]=='b'),0.0};
	FFT(a,1);
	for (int i=0;i<L;i++) a[i]=a[i]*a[i];
	FFT(a,-1);
	for (int i=0;i<n+n;i++) c[i+1]+=(int)(a[i].r+0.5);
	f[0]=1;
	for (int i=1;i<=n+n;i++) f[i]=(f[i-1]<<1)%mo;
	for (int i=1;i<=n+n;i++) (ans+=f[c[i]+1>>1]-1)%=mo;
	printf("%lld\n",(ans+mo)%mo);
	return 0;
}
