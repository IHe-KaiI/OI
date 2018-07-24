#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const double pi=acos(-1.0);
int n,m,L,H; 
struct complex
{
	double r,v;
	inline complex operator + (const complex a) { return (complex){r+a.r,v+a.v};}
	inline complex operator - (const complex a) { return (complex){r-a.r,v-a.v};}
	inline complex operator * (const complex a) { return (complex){r*a.r-v*a.v,r*a.v+v*a.r};}
}a[300100],b[300100],w[300100];
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
int main()
{
	scanf("%d%d",&n,&m);
	
	n++;m++;
	w[0]=(complex){1.0,0.0};
	for (int i=0;i<n;i++) scanf("%lf",&a[i].r);
	for (int i=0;i<m;i++) scanf("%lf",&b[i].r);
	L=1;H=0;
	while (L<n+m) L<<=1,H++;
	FFT(a,1);FFT(b,1);
	for (int i=0;i<L;i++) a[i]=a[i]*b[i];
	FFT(a,-1);
	for (int i=0;i<n+m-1;i++) printf("%d%c",(int)(a[i].r+0.5)," \n"[i==n+m-2]);
	return 0;
}
