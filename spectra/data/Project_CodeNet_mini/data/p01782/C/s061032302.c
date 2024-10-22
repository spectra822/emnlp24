// AOJ 2679 Decoding Ancient Messages
// 2018.3.15 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { signed char a[52]; } T;
T mx[10000]; int sz;
#define mx_zero   0
#define mx_inf    1

int  mx_new() { return sz++; }
void mx_clear(int a) { memset(mx+a, 0, sizeof(T)); }
void mx_add1(int a, int b) { int i; for (i = 0; i < 52; i++) mx[a].a[i] += mx[b].a[i]; }
void mx_add2(int s, int a, int b) { int i; for (i = 0; i < 52; i++) mx[s].a[i] = mx[a].a[i]+mx[b].a[i]; }
void mx_sub1(int a, int b) { int i; for (i = 0; i < 52; i++) mx[a].a[i] -= mx[b].a[i]; }
void mx_sub2(int d, int a, int b) { int i; for (i = 0; i < 52; i++) mx[d].a[i] = mx[a].a[i]-mx[b].a[i]; }
void mx_mul2(int m, int a, int k) { int i; for (i = 0; i < 52; i++) mx[m].a[i] = mx[a].a[i] * k; }
void mx_cpy(int a, int b) { memcpy(mx+a, mx+b, sizeof(T)); }
int  mx_cmp(int a, int b) {
	int k, i; for (i = 0; i < 52; i++) if (k = mx[a].a[i] - mx[b].a[i]) return k; return 0; }

#define MAX 105
typedef struct { int to, rev; int cap; int cost; } EDGE;
EDGE edge[MAX][MAX]; int hi[MAX];
int  V;				// 頂点数
int  dist[MAX], prevv[MAX], preve[MAX];

void add_edge(int from, int to, int cap, int cost, int rcost)
{
	int f, t;
	EDGE *e;

	f = hi[from]++, t = hi[to]++;
	e = &edge[from][f], e->to = to, e->cap = cap, e->cost = cost, e->rev = t;
	e = &edge[to][t], e->to = from, e->cap = 0, e->cost = rcost, e->rev = f;
}

int minCostFlow(int S, int T, int F)
{
	int i, v, nv, d, update;
	int t = mx_new(), ret;
	EDGE *e;

	for (i = 0; i < V; i++) dist[i] = mx_new(); 
	ret = mx_new();
	while (F > 0) {
		for (v = 0; v < V; v++) mx_cpy(dist[v], mx_inf);
		mx_clear(dist[S]);
		do {
			update = 0;
			for (v = 0; v < V; v++) {
				if (mx_cmp(dist[v], mx_inf) == 0) continue;
				for (i = 0; i < hi[v]; i++) {
					e = &edge[v][i];
					if (e->cap <= 0) continue;
					nv = e->to;
					mx_add2(t, dist[v], e->cost);
					if (mx_cmp(dist[nv], t) > 0) {
						mx_cpy(dist[nv], t), prevv[nv] = v, preve[e->to] = i;
						update = 1;
					}
				}
			}
		} while (update);

		d = F;
		for (v = T; v != S; v = prevv[v]) {
			e = &edge[prevv[v]][preve[v]];
			if (d > e->cap) d = e->cap;
		}
		F -= d;

		mx_mul2(t, dist[T], d);
		mx_add1(ret, t);
		for (v = T; v != S; v = prevv[v]) {
			e = &edge[prevv[v]][preve[v]];
			e->cap -= d;
			edge[v][e->rev].cap += d;
		}
	}
	return ret;
}

char map[53][53];

int main()
{
	int N, i, j, a, b;
	int source, sink;
	char buf[10], c;

	fgets(buf, 10, stdin), N = atoi(buf);
	for (i = 0; i < N; i++) fgets(map[i], 53, stdin);

	for (i = 0; i < 52; i++) mx[mx_inf].a[i] = 60;
	sz = 2,	source = N << 1, sink = source + 1, V = sink + 1;

	for (i = 0; i < N; i++) {
		add_edge(source, i, 1, mx_new(), mx_new());
		for (j = 0; j < N; j++) {
			c = map[i][j], a = mx_new(), b = mx_new();
			if (c < 'a') mx[a].a[   c-'A'] = -1, mx[b].a[   c-'A'] = 1;
			else         mx[a].a[26+c-'a'] = -1, mx[b].a[26+c-'a'] = 1;
			add_edge(i, N+j, 1, a, b);
		}
		add_edge(N+i, sink, 1, mx_new(), mx_new());
	}

	a = minCostFlow(source, sink, N);

	for (i = 0; i < 26; i++) {
		b = -mx[a].a[i];
		while (b) putchar('A'+i), b--;
	}
	for (i = 0; i < 26; i++) {
		b = -mx[a].a[i+26];
		while (b) putchar('a'+i), b--;
	}
	putchar('\n');
	return 0;
}
