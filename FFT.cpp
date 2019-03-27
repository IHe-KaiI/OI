#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=100010;
const double pi=acos(-1.0);
int n,m,L;
struct Complex
{
	double r,v;
	Complex operator + (const Complex &a) { return (Complex){r+a.r,v+a.v};}
	Complex operator - (const Complex &a) { return (Complex){r-a.r,v-a.v};}
	Complex operator * (const Complex &a) { return (Complex){r*a.r-v*a.v,r*a.v+v*a.r};}
}a[N*4],b[N*4],w[N*4];
void FFT(Complex *a,int f)
{
	for (int i=0,j=0;i<L;i++)
	{
		if (i>j) swap(a[i],a[j]);
		for (int k=L>>1;(j^=k)<k;k>>=1);
	}
	for (int len=2;len<=L;len<<=1)
	{
		int l=len>>1;
		Complex W=(Complex){cos(pi/l),f*sin(pi/l)};
		for (int i=1;i<l;i++) w[i]=W*w[i-1];
		for (int i=0;i<L;i+=len)
			for (int j=0;j<l;j++)
			{
				Complex x=a[i+j],y=w[j]*a[i+j+l];
				a[i+j]=x+y;a[i+j+l]=x-y;
			}
	}
	if (f==-1)
	{
		for (int i=0;i<L;i++) a[i].r/=L;
	}
}
void pre(int l)
{
	L=1;
	while (L<l) L<<=1;
	w[0]=(Complex){1.0,0.0};
}
int main()
{
	scanf("%d%d",&n,&m);
	n++;m++;
	for (int i=0;i<n;i++) scanf("%lf",&a[i].r);
	for (int i=0;i<m;i++) scanf("%lf",&b[i].r);
	pre(n+m);
	FFT(a,1);FFT(b,1);
	for (int i=0;i<L;i++) a[i]=a[i]*b[i];
	FFT(a,-1);
	for (int i=0;i<n+m-1;i++) printf("%d%c",(int)(a[i].r+0.5)," \n"[i==n+m-2]);
	return 0;
}
