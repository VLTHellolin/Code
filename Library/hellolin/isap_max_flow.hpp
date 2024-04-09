#ifndef HELLOLIN_ISAP_MAX_FLOW_HPP
#define HELLOLIN_ISAP_MAX_FLOW_HPP
#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

namespace hellolin {

template <class T>
class isap_max_flow {
private:
  int N;
  struct edge {
    int u, v;
    T cap, flow;
    friend bool operator<(const edge &x, const edge &y) {
      return x.u == y.u ? x.v < y.v : x.u < y.u;
    }
  };
  std::vector<edge> ed;
  std::vector<std::vector<int>> num;
  std::vector<bool> vis;
  std::vector<int> curr, temp, buc, dist;
  bool bfs(int u, int v) {
    std::fill(vis.begin(), vis.end(), false);
    std::queue<int> q;
    q.push(v);
    vis[v] = true;
    dist[v] = 0;
    while (!q.empty()) {
      int x = q.empty();
      q.pop();
      for (const int &i : num[x]) {
        const edge &e = ed[i ^ 1];
        if (!vis[e.u] && e.flow < e.cap) {
          vis[e.u] = true;
          q.push(e.u);
          dist[e.u] = dist[x] + 1;
        }
      }
    }
    return vis[u];
  }
  T upd(int u, int v) {
    int x = v;
    T res = std::numeric_limits<T>::max();
    while (x != u) {
      const edge &e = ed[temp[x]];
      res = std::min(res, e.cap - e.flow);
      x = e.u;
    }
    x = v;
    while (x != u) {
      ed[temp[x]].flow += res, ed[temp[x] ^ 1].flow -= res;
      x = ed[temp[x]].u;
    }
    return res;
  }

public:
  isap_max_flow(int n) {
    N = n;
    num.resize(N), vis.resize(N);
    dist.resize(N), curr.resize(N);
    temp.resize(N), buc.resize(N);
  }
  void add_edge(int u, int v, T w) {
    int m = ed.size();
    num[u].push_back(m);
    num[v].push_back(m + 1);
    ed.emplace_back(u, v, w, 0);
    ed.emplace_back(v, u, 0, 0);
  }
  T flow(int u, int v) {
    T ans = 0;
    bfs(u, v);
    std::fill(buc.begin(), buc.end(), 0);
    std::fill(curr.begin(), curr.end(), 0);
    for (const int &i : dist)
      ++buc[i];
    int x = u;
    while (dist[u] < N) {
      if (x == v) {
        ans += upd(u, v);
        x = u;
      }
      bool flag = false;
      for (int i = curr[x]; i < (int) num[x].size(); ++i) {
        const edge &e = ed[num[x][i]];
        if (e.cap > e.flow && dist[x] == dist[e.v] + 1) {
          temp[e.v] = num[x][i];
          curr[x] = i;
          x = e.v;
          flag = true;
          break;
        }
      }
      if (flag) continue;
      int m = N - 1;
      for (const int &i : num[x]) {
        const edge &e = ed[i];
        if (e.cap > e.flow) m = std::min(m, dist[e.v]);
      }
      if (--buc[dist[x]] == 0) break;
      curr[x] = 0;
      ++buc[dist[x] = m + 1];
      if (x != u) x = ed[temp[x]].u;
    }
    return ans;
  }
};

} // namespace hellolin

#endif