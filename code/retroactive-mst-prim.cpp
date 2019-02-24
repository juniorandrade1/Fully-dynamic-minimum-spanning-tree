#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

#ifdef ONLINE_JUDGE
#define debug(args...)
#else
#define debug(args...) fprintf(stderr,args)
#endif

#define INF 0x3f3f3f3f

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

struct Prim {
public:
  int n;
  vector< vector< ii > > g;
  Prim(int _n){
    n = _n;
    g.resize(n, vector< ii > ());
  };
  void addEdge(Edge e) {
    int x = e.x;
    int y = e.y;
    int w = e.w;
    g[x].push_back(ii(y, w));
    g[y].push_back(ii(x, w));
  }

  int doIt(int s, vector< bool > &vis, vector< int > &c) {
    priority_queue< ii > q; 
    c[s] = 0;
    vis[s] = 1;
    for(int i = 0; i < g[s].size(); ++i) {
      int x = s;
      int y = g[x][i].first;
      int w = g[x][i].second;
      if(c[y] > w) {
        c[y] = w;
        q.push(ii(-w, y));
      }  
    }
    int sum = 0;
    while(!q.empty()) {
      ii foo = q.top(); q.pop();
      int x = foo.second;
      int w = -foo.first;
      if(vis[x]) continue;
      sum += c[x];
      vis[x] = 1;
      for(int i = 0; i < g[x].size(); ++i) {
        int y = g[x][i].first;
        if(vis[y]) continue;
        int w = g[x][i].second;
        if(c[y] > w) {
          c[y] = w;
          q.push(ii(-w, y));
        }  
      }
    }
    return sum;
  }

  int MST() {
    vector< bool > vis(n, 0);
    vector< int > c(n, INF);
    int sol = 0;
    for(int i = 0; i < n; ++i) {
      if(!vis[i]) {
        sol += doIt(i, vis, c);
      }
    }
    return sol;
  }
};

int n, m, q;
set< Edge > s;

int getMST(int t) {
  Prim p(n);
  int sol = 0;
  vector< Edge > all;
  for(set< Edge > :: iterator it = s.begin(); it != s.end(); it++) {
    if(it->t <= t) p.addEdge(*it);
    else break;
  }
  return p.MST();
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
  
  debug("Brute Prim: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  return 0;
}