#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=300100;
const double pi=acos(-1.0);
int n,m,L,H,A[N<<2],B[N<<2],Ans[N];
char s1[N],s2[N];
struct complex
{
	double r,v;
	inline complex operator + (const complex &a) { return (complex){r+a.r,v+a.v};}
	inline complex operator - (const complex &a) { return (complex){r-a.r,v-a.v};}
	inline complex operator * (const complex &a) { return (complex){r*a.r-v*a.v,r*a.v+v*a.r};}
}a[N<<2],b[N<<2],w[N<<2],C1[N],c[N<<2];
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
void CALC_FFT(complex *a,complex *b)
{
	w[0]=(complex){1.0,0.0};
	FFT(a,1);FFT(b,1);
	for (int i=0;i<L;i++) a[i]=a[i]*b[i];
	FFT(a,-1);
	for (int i=0;i<L;i++) c[i]=a[i];
}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s1);
	scanf("%s",s2);
	for (int i=0;i<n;i++) if (s1[i]!='*') A[n-1-i]=s1[i]-'a'+1;
	for (int i=0;i<m;i++) if (s2[i]!='*') B[i]=s2[i]-'a'+1;
	L=1;H=0;
	while (L<n+m) L<<=1,H++;
	for (int i=0;i<L;i++) a[i]=(complex){(double)A[i]*A[i]*A[i],0},b[i]=(complex){B[i],0};
	CALC_FFT(a,b);
	for (int i=0;i<m;i++) C1[i]=c[i];
	for (int i=0;i<L;i++) a[i]=(complex){(double)A[i]*A[i],0},b[i]=(complex){(double)B[i]*B[i],0};
	CALC_FFT(a,b);
	for (int i=0;i<m;i++) C1[i]=C1[i]-c[i]*(complex){2.0,0.0};
	for (int i=0;i<L;i++) a[i]=(complex){A[i],0},b[i]=(complex){(double)B[i]*B[i]*B[i],0};
	CALC_FFT(a,b);
	for (int i=0;i<m;i++) C1[i]=C1[i]+c[i];
	int num=0;
	for (int i=n-1;i<m;i++) if (C1[i].r<0.5) Ans[++num]=i-n+2;
	printf("%d\n",num);
	for (int i=1;i<=num;i++) printf("%d%c",Ans[i]," \n"[i==num]);
	return 0;
}
