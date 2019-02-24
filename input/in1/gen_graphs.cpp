#include <bits/stdc++.h>

using namespace std;

inline int get32Int() {
  return abs(((int)rand() << 16LL) | ((int)rand()));
}

inline int getInt(int l, int r) {
  int x =  (get32Int() % (r - l + 1)) + l;
  assert(x >= l && x <= r);
  return x;
}

string genName(int x) {
  string suff = "";
  for(int i = 0; i < 3; ++i) {
    suff.push_back((x % 10) + '0');
    x /= 10;
  }
  reverse(suff.begin(), suff.end());
  return "in" + suff;
}

int main() {
  srand(time(NULL));
  int qtd = 0;
  for(int N = 200; N <= 30000; N += 200) {
    FILE *f = fopen(genName(qtd++).c_str(), "w");
    int n = N;//getInt(1, N);
    int m = getInt(n - 1, 30000);
    int q = getInt(1, N);
    fprintf(f, "%d %d %d\n", n, m, q);
    for(int i = 0; i < m; ++i) {
      int x = getInt(1, n);
      int y = getInt(1, n);
      while(x == y) y = getInt(1, n);
      assert(x != y);
      int w = getInt(1, 10000);
      fprintf(f, "%d %d %d\n", x, y, w);
    }
    vector< int > p(q);
    for(int i = 0; i < q; ++i) p[i] = i;
    random_shuffle(p.begin(), p.end());
    for(int i = 0; i < q; ++i) {
      int op = getInt(1, 10);
      if(op <= 5) fprintf(f, "0 %d\n", p[i] + 1);
      else {
        int x = getInt(1, n);
        int y = getInt(1, n);
        while(x == y) y = getInt(1, n);
        fprintf(f, "1 %d %d %d %d\n", x, y, getInt(1, 10000), p[i] + 1);
        assert(x != y);
      }
    }
    printf("%s gerado\n", genName(qtd - 1).c_str());
    fclose(f);
  }
  
  return 0;
}