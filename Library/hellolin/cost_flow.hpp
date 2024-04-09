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