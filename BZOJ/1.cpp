#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1010,
          MAXM = 100010;

struct Edge {
    int u, v;
    int ne;
} e[MAXM * 2];

int pre[MAXN], bcc_cnt, dfs_clock, bccno[MAXN];
// 用bcc_cnt来记录有多少个双连通分量 bccno则是每一个点处于哪一个双连通分量中，对于割点bccno无意义，储存的是最后一个双连通分量的编号
bool iscut[MAXN];

int head[MAXN];

vector<int> bcc[MAXN];
stack<Edge>S;

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;

    for(int i = head[u]; ~i; i = e[i].ne) {
        int v = e[i].v;
        if(!pre[v]) { // 未访问 
            S.push(e[i]);
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u]) { // 如果找到了双连通分量 
                iscut[u] = 1;
                ++bcc_cnt;
                bcc[bcc_cnt].clear();
                for(;;) { // 出栈
                    Edge x = S.top();
                    S.pop();
                    if(bccno[x.u] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u] = bcc_cnt;
                    }
                    if(bccno[x.v] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }
                    if(x.u == u && x.v == v) {
                        break;
                    }
                }
            }
        } else {
            if(pre[v] < pre[u] && v != fa) {
                S.push(e[i]);
                lowu = min(lowu, pre[v]); // 用反向边更新自己
            }
        }
    }

    if(fa < 0 && child == 1) {
        iscut[u] = 0;
    }
    return lowu;
}

void find_bcc(int n) {
    memset(pre, 0, sizeof pre);
    memset(iscut, 0, sizeof iscut);
    memset(bccno, 0, sizeof bccno);
    dfs_clock = bcc_cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(!pre[i]) {
            dfs(i, -1);
        }
    }
}

int main(void) {
    int n, m;
    int cnt = 0;
    memset(head, -1, sizeof head);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[cnt].u = u;
        e[cnt].v = v;
        e[cnt].ne = head[u];
        head[u] = cnt++;
        e[cnt].u = v;
        e[cnt].v = u;
        e[cnt].ne = head[v];
        head[v] = cnt++;
    }
    find_bcc(n);
    printf("%d\n", bcc_cnt);
    for(int i = 1; i <= bcc_cnt; ++i) {
        printf("%d : ", i);
        for(int j = 0; j < bcc[i].size(); j++) {
            printf("%d ", bcc[i][j]);
        }
        puts("");
    }
    return 0;
}
