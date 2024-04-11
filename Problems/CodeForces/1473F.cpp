#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
// #pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
// #pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
// #pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
// #pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

// Hellolin v4.9.2

// clang-format off
// #include <bits/stdc++.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
#ifdef LOCAL
#include "hellolin/all/debug_tools.hpp"
#endif
using namespace std;
namespace hellolin {
// using int64 = long long; using uint64 = unsigned long long; using real32 = double; using real64 = long double;
// using comp = complex<real32>; template <class T> using spair = pair<T, T>;
// #define cTr const T&
// template <class T> bool chmax(T &x, cTr y) { return y > x ? x = y, 1 : 0; }
// template <class T> bool chmin(T &x, cTr y) { return y < x ? x = y, 1 : 0; }
// template <class T> bool range(cTr l, cTr r, cTr x) { return l <= x && x <= r; }
// template <class T> bool range(cTr l, cTr r, cTr x, cTr y) { return l <= x && x <= y && y <= r; }
// #undef cTr
// class IO {
// private:
//   static constexpr int Buffer = 1<<19; char ib[Buffer], ob[Buffer], *is, *it, *os = ob, *ot = ob + Buffer - 1; FILE *inf, *ouf; vector<string> dt;
//   void fl() { fwrite(ob, 1, os - ob, ouf), os = ob; } void pc(char x) { ((*os++ = x, os) == ot) ? fl() : void(); }
//   char gc() { return is == it && ((it = (is = ib) + fread(ib, 1, Buffer, inf)), is == it) ? EOF : *is++; }
//   template <class T> void up(T x) { dt.push_back(to_string(x)); } template <class T, class...A> void up(T x, A...a) { up(x), up(a...); }
// public:
//   void flush() { fl(), fflush(ouf); } IO(FILE *_i = stdin, FILE *_o = stdout) : inf(_i), ouf(_o) {} ~IO() { flush(); }
//   void reopen(FILE *_i = stdin, FILE *_o = stdout) { flush(); inf = _i, ouf = _o; }
//   void reopen(const char *i, const char *o) { FILE *_i = fopen(i, "r"), *_o = fopen(o, "w"); reopen(_i, _o); }
//   template <class T> void input(T &x) {
//     x = 0; bool f = 0; char c = gc(); while (!isdigit(c)) f ^= c == '-', c = gc(); while (isdigit(c)) x = x * 10 + c - 48, c = gc(); x = f ? -x : x;
//   }
//   void input(char &x) { do { x = gc(); } while (!isgraph(x)); } void input(char *x) { char c = gc(); while (!isgraph(c)) c = gc(); while (isgraph(c)) *x++ = c, c = gc(); *x = '\0'; }
//   void input(string &x) { char c = gc(); x = ""; while (!isgraph(c)) c = gc(); while (isgraph(c)) x += c, c = gc(); }
//   template <class T, class...A> void input(T &x, A &...a) { input(x), input(a...); } template <class T1, class T2> void input(pair<T1, T2> &x) { input(x.first, x.second); }
//   template <class T> void write(T x) { if (x < 0) pc('-'), x = -x; if (x > 9) write(x / 10); pc(x % 10 + 48); }
//   void write(char x) { pc(x); } void write(const char *x) { size_t l = strlen(x); for (size_t i = 0; i < l; ++i) pc(x[i]); }
//   void write(const string &x) { for(const char &i : x) pc(i); } template <class T, class...A> void write(T x, A...a) { write(x), write(a...); }
//   template <class...A> void print(const string &x, A...a) {
//     dt.clear(); up(a...); string r = ""; int tp = 0; for (size_t i = 0; i < x.size(); ++i) if (x[i] == '%') r += dt[tp++]; else r += x[i]; write(r);
//   }
// } io;
void main();
} // namespace hellolin
int main() {
#ifndef LOCAL
  // hellolin::io.reopen(".in", ".out");
#endif
  hellolin::main();
}
// clang-format on

#ifndef HELLOLIN_MAX_FLOW_HPP
#define HELLOLIN_MAX_FLOW_HPP

namespace hellolin {

template <class T, int N>
class max_flow {
private:
  struct edge {
    int to, p;
    T cap;
  };
  std::vector<std::pair<int, int>> mp;
  std::array<std::vector<edge>, N> ed;
  std::array<int, N> dis, num;
  std::array<bool, N> vis;

  void bfs(int u, int v) {
    std::queue<int> q;
    q.push(u);
    std::fill(dis.begin(), dis.end(), -1);
    dis[u] = 0;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (const auto &[y, p, w] : ed[x]) {
        if (w && dis[y] < 0) {
          dis[y] = dis[x] + 1;
          if (v == y) return;
          q.push(y);
        }
      }
    }
  }
  T dfs(int tgt, int x, T p) {
    if (x == tgt) return p;
    T ans = 0;
    int dist = dis[x];
    for (int &i = num[x]; i < (int) ed[x].size(); ++i) {
      edge &e1 = ed[x][i], &e2 = ed[e1.to][e1.p];
      if (dist > dis[e1.to] && e2.cap) {
        T nxt = dfs(tgt, e1.to, std::min(e2.cap, p - ans));
        if (nxt <= 0) continue;
        e1.cap += nxt, e2.cap -= nxt;
        ans += nxt;
        if (ans == p) return ans;
      }
    }
    dis[x] = N;
    return ans;
  }

public:
  max_flow() {}
  void add_edge(int u, int v, T w) {
    int x = ed[u].size(), y = ed[v].size();
    if (u == v) ++y;
    mp.emplace_back(u, x);
    ed[u].emplace_back(v, y, w);
    ed[v].emplace_back(u, x, 0);
  }
  T flow(int u, int v, T limit = std::numeric_limits<T>::max()) {
    T ans = 0;
    std::fill(dis.begin(), dis.end(), 0);
    std::fill(num.begin(), num.end(), 0);
    while (ans < limit) {
      bfs(u, v);
      if (dis[v] == -1) return ans;
      std::fill(num.begin(), num.end(), 0);
      T nxt = dfs(u, v, limit - ans);
      if (!nxt) break;
      ans += nxt;
    }
    return ans;
  }
  std::vector<bool> min_cut(int x) {
    std::fill(vis.begin(), vis.end(), false);
    std::queue<int> q;
    q.push(x);
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      if (vis[x]) continue;
      vis[x] = true;
      for (const auto &[y, p, w] : ed[x])
        if (w && !vis[y]) q.push(y);
    }
    return vis;
  }
};

} // namespace hellolin

#endif

namespace hellolin {
static constexpr int N = 3003, Inf = 2e9;
int n, *a, *b, s, t, sum;
max_flow<int, N> e;
void main() {
  // io.input(n);
  scanf("%d", &n);
  s = n, t = n + 1;
  a = new int[N];
  b = new int[N];
  for (int i = 0; i < n; ++i)
    // io.input(a[i]);
    scanf("%d", a + i);
  for (int i = 0; i < n; ++i) {
    // io.input(b[i]);
    scanf("%d", b + i);
    if (b[i] < 0)
      e.add_edge(i, t, -b[i]);
    else {
      e.add_edge(s, i, b[i]);
      sum += b[i];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (a[j] % a[i] == 0 && b[i] < 0 && b[j] > 0) e.add_edge(j, i, Inf);
    }
  }
  delete[] a;
  delete[] b;
  // io.write(sum - e.flow(s, t));
  printf("%d\n", sum - e.flow(s, t));
}
} // namespace hellolin
