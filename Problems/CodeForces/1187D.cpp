// Hellolin v4.9.2

// clang-format off
#include <bits/stdc++.h>
#ifdef LOCAL
#include "hellolin/all/debug_tools.hpp"
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
static constexpr int N = 3e5 + 5, Inf = INT_MAX;
int T, n, a[N], b[N];
int buc[N], pos[N];
int tr[N << 2];

void pushup(int x) {
  tr[x] = min(tr[x << 1], tr[x << 1 | 1]);
}

void build(int l = 1, int r = n, int x = 1) {
  if (l == r) {
    tr[x] = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, x << 1), build(mid + 1, r, x << 1 | 1);
  pushup(x);
}

void modify(int pos, int l = 1, int r = n, int x = 1) {
  if (l == r) {
    tr[x] = Inf;
    return;
  }
  int mid = (l + r) >> 1;
  if (pos <= mid) modify(pos, l, mid, x << 1);
  if (pos > mid) modify(pos, mid + 1, r, x << 1 | 1);
  pushup(x);
}

int query(int lx, int rx, int l = 1, int r = n, int x = 1) {
  if (range(lx, rx, l, r)) return tr[x];
  int mid = (l + r) >> 1;
  int ans = Inf;
  if (lx <= mid) chmin(ans, query(lx, rx, l, mid, x << 1));
  if (rx > mid) chmin(ans, query(lx, rx, mid + 1, r, x << 1 | 1));
  return ans;
}

void solve() {
  io.input(n);
  vector <queue<int>> que(n + 1);
  for (int i = 1; i <= n; ++i) io.input(a[i]);
  for (int i = 1; i <= n; ++i) io.input(b[i]);
  for (int i = 1; i <= n; ++i) que[a[i]].push(i);
  for (int i = 1; i <= n; ++i) {
    if (que[b[i]].empty()) return io.write("NO\n");
    pos[i] = que[b[i]].front();
    que[b[i]].pop();
  }
  build();
  for (int i = 1; i <= n; ++i) {
    if (query(1, pos[i]) != b[i]) return io.write("NO\n");
    modify(pos[i]);
  }
  io.write("YES\n");
}

void main() {
  for (io.input(T); T--; solve());
}
} // namespace hellolin