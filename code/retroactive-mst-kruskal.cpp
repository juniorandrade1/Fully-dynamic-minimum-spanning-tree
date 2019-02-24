#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(args...)
#else
#define debug(args...) fprintf(stderr,args)
#endif


struct Edge {
  int x, y, w, t;
  Edge(){};
  Edge(int _x, int _y, int _w, int _t) {
    x = _x;
    y = _y;
    w = _w;
    t = _t;
  }
  bool operator < (Edge o) const {
    if(t != o.t) return t < o.t;
    if(w != o.w) return w < o.w;
    if(x != o.x) return x < o.x;
    return y < o.y;
  }
};

struct Kruskal {
  int n;
  vector< int > pset;
  Kruskal(){};
  Kruskal(int _n) {
    n = _n;
    pset.resize(n);
    for(int i = 0; i < n; ++i) pset[i] = i;
  }
  int fnd(int i) { return (pset[i] == i) ? pset[i] : (pset[i] = fnd(pset[i])); }
  int uni(int i, int j) { return pset[fnd(i)] = fnd(pset[j]); }
  int addEdge(int x, int y, int w) {
    if(fnd(x) != fnd(y)) {
      uni(x, y);
      return w;
    }
    return 0;
  }
};

bool cmpWeight(Edge a, Edge b) {
  return a.w < b.w;
}

int n, m, q;
set< Edge > s;

int getMST(int t) {
  Kruskal k(n);
  int sol = 0;
  vector< Edge > all;
  for(set< Edge > :: iterator it = s.begin(); it != s.end(); it++) {
    if(it->t <= t) all.push_back(*it);
    else break;
  }
  sort(all.begin(), all.end(), cmpWeight);
  for(int i = 0; i < all.size(); ++i) sol += k.addEdge(all[i].x, all[i].y, all[i].w);
  return sol;
}

int main() {
  clock_t tStart = clock();
  scanf("%d %d %d", &n, &m, &q);
  for(int i = 0; i < m; ++i) {
    int x, y, w; scanf("%d %d %d", &x, &y, &w); x--; y--;
    s.insert(Edge(x, y, w, 0)); 
  }
  for(int i = 0; i < q; ++i) {
    int op; scanf("%d", &op);
    if(!op) {
      int t; scanf("%d", &t);
      printf("%d\n", getMST(t));
    }
    else {
      int x, y, w, t; scanf("%d %d %d %d", &x, &y, &w, &t); x--; y--;
      s.insert(Edge(x, y, w, t));
    }
  }
  
  debug("Brute Kruskal: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  return 0;
}