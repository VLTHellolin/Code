// Hellolin v4.10.1

// clang-format off
#include <bits/stdc++.h>
#ifdef LOCAL
#include "hellolin/all/debug_tools.hpp"
#endif
using namespace std;
namespace hellolin {
using int64 = long long;
using uint64 = unsigned long long;
using real32 = double;
using real64 = long double;
using comp = complex<real32>;
template <class T> using spair = pair<T, T>;
template <class T1, class T2> bool chmax(T1 &x, const T2 &y) { return y > x ? x = y, 1 : 0; }
template <class T1, class T2> bool chmin(T1 &x, const T2 &y) { return y < x ? x = y, 1 : 0; }
template <class T> bool range(T l, T r, T x) { return l <= x && x <= r; }
template <class T> bool range(T l, T r, T x, T y) { return l <= x && x <= y && y <= r; }
template <unsigned Mod>
class mint {
private:
  void mod(unsigned y) { x = y >= Mod ? y - Mod : y; }
public:
  unsigned x;
  mint() : x(0) {}
  template <class T> mint(T y) { mod(y % Mod + Mod); }
  static mint raw(unsigned x) { mint a; return a.x = x, a; }
  friend string to_string(mint x) { return to_string(x.x); }
  mint operator+() const { return *this; };
  mint operator-() const { return mint() - *this; }
  mint &operator++() { x = x + 1 == Mod ? 0 : x + 1; return *this; }
  mint &operator--() { x = x == 0 ? Mod : x - 1; return *this; }
  mint operator++(int) { mint a = *this; ++*this; return a; }
  mint operator--(int) { mint a = *this; --*this; return a; }
  mint &operator+=(const mint &y) { mod(x + y.x); return *this; }
  mint &operator-=(const mint &y) { mod(x - y.x + Mod); return *this; }
  mint &operator*=(const mint &y) { x = 1ull * x * y.x % Mod; return *this; }
  mint &operator/=(const mint &y) { return *this = *this * ~y; }
  mint &operator^=(uint64 y) { mint a = 1; for (; y; y >>= 1, *this *= *this) if (y & 1) a *= *this; return *this = a; }
  mint operator+(const mint &y) const { return mint(*this) += y; }
  mint operator-(const mint &y) const { return mint(*this) -= y; }
  mint operator*(const mint &y) const { return mint(*this) *= y; }
  mint operator/(const mint &y) const { return mint(*this) /= y; }
  mint operator^(const mint &y) const { return mint(*this) ^= y; }
  mint operator~() const { return mint(*this) ^= Mod - 2; }
  bool operator==(const mint &y) const { return x == y.x; }
  bool operator!=(const mint &y) const { return x != y.x; }
};
using mint998 = mint<998244353>;
using mint197 = mint<1000000007>;
class IO {
private:
  static constexpr int Buffer = 1<<19;
  char ib[Buffer], ob[Buffer], *is, *it, *os = ob, *ot = ob + Buffer - 1;
  FILE *inf, *ouf;
  vector<string> dt;
  void fl() { fwrite(ob, 1, os - ob, ouf), os = ob; }
  void pc(char x) { ((*os++ = x, os) == ot) ? fl() : void(); }
  char gc() { return is == it && ((it = (is = ib) + fread(ib, 1, Buffer, inf)), is == it) ? EOF : *is++; }
  template <class T> void up(T x) { dt.push_back(to_string(x)); }
  template <class T, class...A> void up(T x, A...a) { up(x), up(a...); }
public:
  void flush() { fl(), fflush(ouf); }
  IO(FILE *_i = stdin, FILE *_o = stdout) : inf(_i), ouf(_o) {}
  ~IO() { flush(); }
  void reopen(FILE *_i = stdin, FILE *_o = stdout) { flush(); inf = _i, ouf = _o; }
  void reopen(const char *i, const char *o) { FILE *_i = fopen(i, "r"), *_o = fopen(o, "w"); reopen(_i, _o); }
  template <class T> void read(T &x) { x = 0; bool f = 0; char c = gc(); while (!isdigit(c)) f ^= c == '-', c = gc(); while (isdigit(c)) x = x * 10 + c - 48, c = gc(); x = f ? -x : x; }
  template <unsigned M> void read(mint<M> &x) { read(x.x); }
  void read(char &x) { do { x = gc(); } while (!isgraph(x)); }
  void read(char *x) { char c = gc(); while (!isgraph(c)) c = gc(); while (isgraph(c)) *x++ = c, c = gc(); *x = '\0'; }
  void read(string &x) { char c = gc(); x = ""; while (!isgraph(c)) c = gc(); while (isgraph(c)) x += c, c = gc(); }
  template <class T, class...A> void read(T &x, A &...a) { read(x), read(a...); }
  template <class T1, class T2> void read(pair<T1, T2> &x) { read(x.first, x.second); }
  void write(char x) { pc(x); }
  void write(const char *x) { size_t l = strlen(x); for (size_t i = 0; i < l; ++i) pc(x[i]); }
  void write(const string &x) { for(const char &i : x) pc(i); }
  template <class T> void write(T x) { write(to_string(x)); }
  template <class T, class...A> void write(T x, A...a) { write(x), write(a...); }
  template <class...A> void writeln(A...a) { write(a...), write('\n'); }
  template <class...A> void print(const string &x, A...a) { dt.clear(); up(a...); string r = ""; int tp = 0; for (size_t i = 0; i < x.size(); ++i) if (x[i] == '%') r += dt[tp++]; else r += x[i]; write(r); }
  template <class...A> void println(A...a) { print(a...), write('\n'); }
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

// ! Note that modint does not support bitwise operations, ^ is for powers and ~ is for inverses.
namespace hellolin {
static constexpr int N = 105;
int n;
int64 sum, res[N], siz[N], dep[N], a[N];
void main() {
  io.read(n);
  vector<vector<int>> g(n + 1);
  for (int i = 1, x, u, v; i <= n; ++i) {
    io.read(x, u, v);
    a[i] = x, sum += a[i];
    if (u) g[i].emplace_back(u), g[u].emplace_back(i);
    if (v) g[i].emplace_back(v), g[v].emplace_back(i);
  }
  function<void(int, int)> dfs1 = [&](int x, int f) {
    dep[x] = dep[f] + 1;
    siz[x] = a[x];
    for (const int &y : g[x]) {
      if (y == f) continue;
      dfs1(y, x);
      siz[x] += siz[y];
    }
  };
  function<void(int, int, int64)> dfs2 = [&](int x, int f, int64 ans) {
    res[x] = ans;
    for (const int &y : g[x]) {
      if (y == f) continue;
      dfs2(y, x, ans + sum - siz[y] * 2);
    }
  };
  dep[0] = -1;
  dfs1(1, 0);
  for (int i = 2; i <= n; ++i)
    res[1] += dep[i] * a[i];
  dfs2(1, 0, res[1]);
  io.writeln(*min_element(&res[1], &res[n + 1]));
}
} // namespace hellolin