#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(args...)
#else
#define debug(args...) fprintf(stderr,args)
#endif

#define mp make_pair

typedef pair<int, int> ii;

struct Edge {
  int x, y, w, i;
  Edge(){};
  Edge(int _x, int _y, int _w, int _i) {
    x = _x;
    y = _y;
    w = _w;
    i = _i;
  }
};


class LinkCutTree {

  struct Node {
    int id, maxVal, val, idMax;
    Node *left, *right, *parent;
    bool evert;
    Node(){
      left = right = parent = 0;
      evert = false;
    }
    Node(int x, int v){
      left = right = parent = 0;
      evert = false;
      id = idMax = x;
      maxVal = val = v; 
    }
    bool is_root() {
      return parent == 0 || (parent->left != this && parent->right != this);
    }
    void update() {
      if (evert) {
        evert = false;
        swap(left, right);
        if (left != 0) left->evert ^= 1;
        if (right != 0) right->evert ^= 1;
      }
    }
    void refresh(){
      maxVal = val;
      idMax = id;
      if(left && left->maxVal > maxVal) maxVal = left->maxVal, idMax = left->idMax;
      if(right && right->maxVal > maxVal) maxVal = right->maxVal, idMax = right->idMax;
    }
  };


public:
  int n;
  vector< Node > lct;
  vector< int > x, y, w;
  int sum;
  LinkCutTree(){};
  LinkCutTree(int _n) {
    n = _n;
    lct.resize(n, Node(-1, -1));
    x.resize(n);
    y.resize(n);
    w.resize(n);
    sum = 0;
  }
  void add_edge(Node* p, Node* u, bool is_left) {
    if (u != 0) u->parent = p;
    if (is_left) p->left = u;
    else p->right = u;
  }

  void rotate(Node* u) {
    Node* p = u->parent;
    Node* q = p->parent;
    bool proot = p->is_root();
    bool is_left = (u == p->left);
    add_edge(p, is_left ? u->right : u->left, is_left);
    add_edge(u, p, !is_left);
    if (!proot) add_edge(q, u, p == q->left);
    else u->parent = q;
    p->refresh();
  }

  void splay(Node* u) {
    while (!u->is_root()) {
      Node* p = u->parent;
      Node* q = p->parent;
      if (!p->is_root()) q->update();
      p->update();
      u->update();
      if (!p->is_root()) {
        if ((p->left == u) != (q->left == p)) rotate(u);
        else rotate(p); 
      }
      rotate(u);
    }
    u->update();
    u->refresh();
  }

  Node* access(Node* v) {
    Node* prev = 0;
    for (Node* u = v; u != 0; u = u->parent) {
      splay(u);
      u->right = prev;
      prev = u;
    }
    splay(v);
    return prev;
  }

  void reroot(Node* v) {
    access(v);
    v->evert ^= 1;
  }

  bool connected(Node* u, Node* v) {
    if (u == v) return true;
    access(u);
    access(v);
    return u->parent != 0;
  }

  void link(Node* v, Node* u) {
    reroot(u);
    u->parent = v;
  }

  void cut(Node* u) {
    access(u);
    u->left->parent = 0;
    u->left = 0;
  }

  void cut(Node* u, Node* v) {
    reroot(u);
    cut(v);
  }

  int find(Node* u, Node* v){
    reroot(u);
    access(v);
    return v->idMax;
  }

  void updateNode(int i, int u, int v, int weight) {
    x[i] = u;
    y[i] = v;
    w[i] = weight;
    lct[i] = Node(i, weight);
    
    if(!connected(x[i], y[i])) {
       link(x[i], i);
       link(y[i], i);
       sum += w[i];
     }
     else {
      int id = find(x[i], y[i]);
      int c = getVal(id);
      if(c > w[i]) {
        int u = x[id], v = y[id];
        sum -= c;
        cut(u, id);
        cut(v, id);
        sum += w[i];
        link(x[i], i);
        link(y[i], i);
        
      }
      
    }
    
  }

  bool connected(int x, int y) {
    return connected(&lct[x], &lct[y]);
  }

  void link(int x, int y) {
    link(&lct[x], &lct[y]);
  }

  void cut(int x, int y) {
    cut(&lct[x], &lct[y]);
  }

  int find(int x, int y) {
    return find(&lct[x], &lct[y]);
  }

  int getVal(int x) {
    if(x < 0) return -1000000000;
    return lct[x].val;
  }

  int getMSTAfterAddEdges(vector< Edge > added) {
    if(!added.size()) return sum;
    vector< pair<int, ii> > ev;
    for(int p = 0; p < (int)added.size(); ++p) {
      int i = added[p].i;
      x[i] = added[p].x;
      y[i] = added[p].y;
      w[i] = added[p].w;  
      lct[i] = Node(i, w[i]);
    }
    int atualMST = sum;
    for(int p = 0; p < (int)added.size(); ++p) {
      int i = added[p].i;
      if(!connected(x[i], y[i])) {
         link(x[i], i);
         link(y[i], i);
         ev.push_back(mp(0, mp(x[i], i)));
         ev.push_back(mp(0, mp(y[i], i)));
         atualMST += w[i];
       }
       else {
        int id = find(x[i], y[i]);
        int c = getVal(id);
        if(c > w[i]) {
          atualMST -= c;
          cut(x[id], id);
          cut(y[id], id);
          ev.push_back(mp(1, mp(x[id], id)));
          ev.push_back(mp(1, mp(y[id], id)));
          atualMST += w[i];
          link(x[i], i);
          link(y[i], i);
          ev.push_back(mp(0, mp(x[i], i)));
          ev.push_back(mp(0, mp(y[i], i)));
        }
      }

    }

    reverse(ev.begin(), ev.end());
    for(int i = 0; i < (int)ev.size(); ++i) {
      if(ev[i].first == 0) cut(ev[i].second.first, ev[i].second.second);
      else link(ev[i].second.first, ev[i].second.second);
    }

    return atualMST; 
  }
};

const int N = 100010;
const int M = 2000;


int tp;
int n, m, q;
LinkCutTree lct[N];
vector< Edge > que[N];

int getMST(int t) {
  vector< Edge > needAdd;
  int bkt = t / M;
  for(int i = bkt * M + 1; i <= t; ++i) {
    if(!que[i].empty()) needAdd.push_back(que[i][0]);
  }
  return lct[bkt].getMSTAfterAddEdges(needAdd);
}

inline void addEdge(int x, int y, int w, int t, int id) {
  que[t].push_back(Edge(x, y, w, id));
  for(int i = (t + M - 1) / M; i < tp; ++i) {
    lct[i].updateNode(id, x, y, w);
  }
}

int main() {
  clock_t tStart = clock();

  tp = N / M + 2;
  scanf("%d %d %d", &n, &m, &q);
  for(int i = 0; i < tp; ++i) lct[i] = LinkCutTree(n + m + q);
  for(int i = n; i < n + m; ++i) {
    int x, y, w; scanf("%d %d %d", &x, &y, &w); x--; y--;
    addEdge(x, y, w, 0, i);
  }

  for(int i = n + m; i < n + m + q; ++i) {
    int op; scanf("%d", &op);
    if(!op) {
      int t; scanf("%d", &t);
      printf("%d\n", getMST(t));
    }
    else {
      int x, y, w, t; scanf("%d %d %d %d", &x, &y, &w, &t); x--; y--;
      addEdge(x, y, w, t, i);
    }
  }

  debug("LinkCut + sqrt(n): %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  return 0;
}