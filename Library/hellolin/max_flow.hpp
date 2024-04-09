#ifndef HELLOLIN_MAX_FLOW_HPP
#define HELLOLIN_MAX_FLOW_HPP
#include <algorithm>
#include <array>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

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