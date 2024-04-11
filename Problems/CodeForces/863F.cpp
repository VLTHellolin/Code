// Hellolin v4.9.3

// clang-format off
#include <bits/stdc++.h>
#ifdef LOCAL
#include "hellolin/all/debug_tools.hpp"
#endif
#ifdef ATCODER
#include "atcoder/all"
#endif
using namespace std;
namespace hellolin {
using int64 = long long; using uint64 = unsigned long long; using real32 = double; using real64 = long double;
using comp = complex<real32>; template <class T> using spair = pair<T, T>;
#define cTr const T&
template <class T> bool chmax(T &x, cTr y) { return y > x ? x = y, 1 : 0; }
template <class T> bool chmin(T &x, cTr y) { return y < x ? x = y, 1 : 0; }
template <class T> bool range(cTr l, cTr r, cTr x) { return l <= x && x <= r; }
template <class T> bool range(cTr l, cTr r, cTr x, cTr y) { return l <= x && x <= y && y <= r; }
#undef cTr
class IO {
private:
  static constexpr int Buffer = 1<<19; char ib[Buffer], ob[Buffer], *is, *it, *os = ob, *ot = ob + Buffer - 1; FILE *inf, *ouf; vector<string> dt;
  void fl() { fwrite(ob, 1, os - ob, ouf), os = ob; } void pc(char x) { ((*os++ = x, os) == ot) ? fl() : void(); }
  char gc() { return is == it && ((it = (is = ib) + fread(ib, 1, Buffer, inf)), is == it) ? EOF : *is++; }
  template <class T> void up(T x) { dt.push_back(to_string(x)); } template <class T, class...A> void up(T x, A...a) { up(x), up(a...); }
public:
  void flush() { fl(), fflush(ouf); } IO(FILE *_i = stdin, FILE *_o = stdout) : inf(_i), ouf(_o) {} ~IO() { flush(); }
  void reopen(FILE *_i = stdin, FILE *_o = stdout) { flush(); inf = _i, ouf = _o; }
  void reopen(const char *i, const char *o) { FILE *_i = fopen(i, "r"), *_o = fopen(o, "w"); reopen(_i, _o); }
  template <class T> void input(T &x) {
    x = 0; bool f = 0; char c = gc(); while (!isdigit(c)) f ^= c == '-', c = gc(); while (isdigit(c)) x = x * 10 + c - 48, c = gc(); x = f ? -x : x;
  }
  void input(char &x) { do { x = gc(); } while (!isgraph(x)); } void input(char *x) { char c = gc(); while (!isgraph(c)) c = gc(); while (isgraph(c)) *x++ = c, c = gc(); *x = '\0'; }
  void input(string &x) { char c = gc(); x = ""; while (!isgraph(c)) c = gc(); while (isgraph(c)) x += c, c = gc(); }
  template <class T, class...A> void input(T &x, A &...a) { input(x), input(a...); } template <class T1, class T2> void input(pair<T1, T2> &x) { input(x.first, x.second); }
  template <class T> void write(T x) { if (x < 0) pc('-'), x = -x; if (x > 9) write(x / 10); pc(x % 10 + 48); }
  void write(char x) { pc(x); } void write(const char *x) { size_t l = strlen(x); for (size_t i = 0; i < l; ++i) pc(x[i]); }
  void write(const string &x) { for(const char &i : x) pc(i); } template <class T, class...A> void write(T x, A...a) { write(x), write(a...); }
  template <class...A> void print(const string &x, A...a) {
    dt.clear(); up(a...); string r = ""; int tp = 0; for (size_t i = 0; i < x.size(); ++i) if (x[i] == '%') r += dt[tp++]; else r += x[i]; write(r);
  }
} io;
void main();
} // namespace hellolin
int main() {
#ifndef LOCAL
  // hellolin::io.reopen(".in", ".out");
#endif
  hellolin::main();
}
// clang-format on

#ifndef HELLOLIN_COST_FLOW_HPP
#define HELLOLIN_COST_FLOW_HPP
#include <array>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

namespace hellolin {

template <class T1, class T2, int N, class Comp = std::less<T2>>
class cost_flow {
private:
  Comp comp = Comp{};
  struct edge {
    int to, p;
    T1 cap;
    T2 cst;
  };
  struct node {
    int p1, p2;
    T1 cap;
    T2 cst;
  };
  T1 ans1;
  T2 ans2;
  static inline T2 Inf;
  std::vector<std::pair<int, int>> mp;
  std::array<std::vector<edge>, N> ed;
  std::array<node, N> gr;
  std::array<bool, N> vis;
  bool spfa(int u, int v) {
    for (int i = 0; i < N; ++i) {
      gr[i].cst = Inf >> 1;
      vis[i] = false;
    }
    vis[u] = 1;
    std::queue<int> q;
    q.push(u);
    gr[u].cap = std::numeric_limits<T1>::max();
    gr[u].cst = 0;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      vis[x] = false;
      int ind = -1;
      for (const edge &i : ed[x]) {
        ++ind;
        if (i.cap > 0 && comp(i.cst + gr[x].cst, gr[i.to].cst)) {
          gr[i.to].cst = i.cst + gr[x].cst;
          gr[i.to].cap = std::min(i.cap, gr[x].cap);
          gr[i.to].p1 = x, gr[i.to].p2 = ind;
          if (!vis[i.to]) {
            vis[i.to] = true;
            q.push(i.to);
          }
        }
      }
    }
    return gr[v].cst != (Inf >> 1);
  }
  void upd(int u, int v) {
    int x = v, a = -1, b = -1;
    while (x != u) {
      a = gr[x].p1, b = gr[x].p2;
      ed[a][b].cap -= gr[v].cap;
      ed[x][ed[a][b].p].cap += gr[v].cap;
      x = a;
    }
    ans1 += gr[v].cap, ans2 += gr[v].cap * gr[v].cst;
  }

public:
  cost_flow() {
    Inf = comp(0, 1) ? std::numeric_limits<T2>::max() : std::numeric_limits<T2>::min();
  }
  void add_edge(int u, int v, T1 w, T2 k) {
    int x = ed[u].size(), y = ed[v].size();
    if (u == v) ++y;
    mp.emplace_back(u, x);
    ed[u].emplace_back(v, y, w, k);
    ed[v].emplace_back(u, x, 0, -k);
  }
  std::pair<T1, T2> flow(int u, int v, T1 limit1 = std::numeric_limits<T1>::max(), T2 limit2 = Inf) {
    ans1 = ans2 = 0;
    while (spfa(u, v) && ans1 < limit1 && comp(ans2, limit2))
      upd(u, v);
    return {ans1, ans2};
  }
};

} // namespace hellolin

#endif

namespace hellolin {
static constexpr int N = 55;
int n, q, s, t;
int up[N], dw[N];
cost_flow<int, int, N * 2> e;
void main() {
  io.input(n, q);
  s = 0, t = n * 2 + 1;
  for (int i = 1; i <= n; ++i)
    dw[i] = 1, up[i] = n;
  for (int i = 1, p, l, r, x; i <= q; ++i) {
    io.input(p, l, r, x);
    for (int j = l; j <= r; ++j)
      if (p == 1)
        chmax(dw[j], x);
      else
        chmin(up[j], x);
  }
  for (int i = 1; i <= n; ++i)
    if (dw[i] > up[i]) return io.write(-1);
  for (int i = 1; i <= n; ++i)
    e.add_edge(s, i, 1, 0);
  for (int i = 1; i <= n; ++i)
    for (int j = dw[i] + n; j <= up[i] + n; ++j)
      e.add_edge(i, j, 1, 0);
  for (int i = n + 1; i <= n * 2; ++i)
    for (int j = 1; j <= n; ++j)
      e.add_edge(i, t, 1, 2 * j - 1);
  io.write(e.flow(s, t).second);
}
} // namespace hellolin