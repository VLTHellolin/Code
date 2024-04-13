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

namespace hellolin {
static constexpr int N = 1e5 + 5, S = 1e6 + 5;
static constexpr int64 B = 114514123, P = 1e9 + 7;
int n;
int64 p[S], v[S], h[S], a[S];
string ans, s;
int64 pow(int64 x, int y) {
  int64 res = 1;
  for (; y; y >>= 1, (x *= x) %= P)
    (y & 1) && ((res *= x) %= P);
  return res;
}
void add() {
  int a = ans.size(), b = s.size();
  for (int i = a; i < a + b; ++i)
    h[i] = ((i ? h[i - 1] : 0) + p[i] * s[i - a] % P) % P;
  ans += s;
}
void calc_hash() {
  for (int i = 0; i < (int) s.size(); ++i)
    a[i] = ((i ? a[i - 1] : 0) + p[i] * s[i] % P) % P;
}
int64 get_hash(int len) {
  if (len == (int) ans.size()) return h[ans.size() - 1];
  return ((h[ans.size() - 1] - h[ans.size() - len - 1]) % P + P) % P * v[ans.size() - len] % P;
}
void main() {
  p[0] = 1;
  for (int i = 1; i < S; ++i)
    p[i] = p[i - 1] * B % P;
  v[S - 1] = pow(p[S - 1], P - 2) % P;
  for (int i = S - 2; ~i; --i)
    v[i] = v[i + 1] * B % P;
  io.input(n);
  for (int i = 0; i < n; ++i) {
    io.input(s);
    if (ans.empty()) {
      add();
      continue;
    }
    calc_hash();
    int len = 0;
    for (int l = min(ans.size(), s.size()); l; --l) {
      if (a[l - 1] == get_hash(l)) {
        len = l;
        break;
      }
    }
    s = s.substr(len);
    add();
  }
  io.write(ans);
}
} // namespace hellolin