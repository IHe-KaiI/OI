#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;

int ch[N][2], S[N], n, m, x, y, fa[N], Size[N], MAXL[N], MAX[N], L, R, nowDis, MAXR[N];
bool rev[N];
multiset <int> Xs[N];

#define lc (ch[x][0])
#define rc (ch[x][1])

bool isroot(int x) {
  return ch[fa[x]][1] != x && ch[fa[x]][0] != x;
}

bool dir(int x) {
  return ch[fa[x]][1] == x;
}

#define Erase(x, y) x.erase(x.find(y))

int get(multiset <int> &S, int Rk) {
  if(S.size() < Rk) return 0;
  multiset < int > :: reverse_iterator it = S.rbegin();
  for(int i = 1; i < Rk; ++ i) ++ it;
  return *it;
}

void pd(int x);

void up(int x) {
  pd(x);
  Size[x] = Size[lc] + Size[rc] + 1;
  MAX[x] = max(get(Xs[x], 1), max(MAX[lc], MAX[rc]));
  MAXL[x] = max(Size[lc] + max(get(Xs[x], 1), Size[rc]), max(MAXL[lc], MAXL[rc] + Size[lc] + 1));
  MAXR[x] = max(Size[rc] + max(get(Xs[x], 1), Size[lc]), max(MAXR[rc], MAXR[lc] + Size[rc] + 1));
}

void add(int x, int y, int val) {
  if(val == 1) {
    Xs[x].insert(MAXL[y] + 1);
    up(x);
    return;
  }
  else {
    Erase(Xs[x], MAXL[y] + 1);
    up(x);
    return;
  }
}

void rotate(int x) {
  int F = fa[x], GF = fa[F], Dx = dir(x), Df = dir(F), Son = ch[x][!Dx];
  if(!isroot(F)) ch[GF][Df] = x;
  fa[x] = GF; fa[F] = x; if(Son) fa[Son] = F;
  ch[F][Dx] = Son; ch[x][!Dx] = F;
  up(F); up(x);
}

void pt(int x) {
  if(!x) return;
  swap(lc, rc);
  rev[x] ^= 1;
  swap(MAXL[x], MAXR[x]);
}

void pd(int x) {
  if(rev[x]) {
    pt(lc);
    pt(rc);
    rev[x] = 0;
    up(x);
  }
}

void put(int x) {
  if(!isroot(x)) put(fa[x]);
  pd(x);
}

void splay(int x) {
  put(x);
  while(!isroot(x)) {
    if(isroot(fa[x])) return (void)rotate(x);
    if(dir(x) == dir(fa[x])) rotate(fa[x]), rotate(x);
    else rotate(x), rotate(x);
  }
}

void access(int x) {
  int t = 0;
  while(x) {
    splay(x);
    if(rc) {
      add(x, rc, 1);
    }
    if(t) {
      add(x, t, -1);
    }
    rc = t;
    up(x);
    t = x, x = fa[x];
  }
}

void makeroot(int x) {
  access(x);
  splay(x);
  pt(x);
}

void link(int x, int y) {
  makeroot(x);  makeroot(y);
  fa[x] = y;
  add(y, x, 1);
  pd(y);
}

void cut(int x, int y) {
  makeroot(x);
  access(y); access(x);
  add(x, y, -1);
}

int query(int x, int y) {
  makeroot(x);
  access(y);
  splay(y);
  return max(Size[y] + MAX[y] - 2, Size[y] - 1);
}

int Qdis(int x, int y) {
  makeroot(x);
  access(y);
  splay(y);
  return Size[y] - 1;
}

void re(int x, int y, int w) {
  int dA = Qdis(x, y), dB = Qdis(x, w), dC = Qdis(y, w);
  L = x, R = y;
  if(dB > dA) L = x, R = w, dA = dB;
  if(dC > dA) L = w, R = y, dA = dC;
}

int main() {
  freopen("forest.in","r",stdin);
  freopen("forest.out","w",stdout);
  int t; cin >> t;
  MAXL[0] = MAXR[0] = MAX[0] = -1e9;
  cin >> n;
  up(1);
  L = 1, R = 1, nowDis = 0;
  for(int i = 2; i <= n; ++ i) {
    up(i);
    int x; scanf("%d", &x); x ^= nowDis;
    fff[i] = x;
    link(x, i);
    re(L, R, i);
    printf("%d\n", nowDis = query(L, R));
  }
}

