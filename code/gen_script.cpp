#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(args...)
#else
#define debug(args...) fprintf(stderr,args)
#endif

inline int get32Int() {
  return abs(((int)rand() << 16LL) | ((int)rand()));
}

inline int getInt(int l, int r) {
  return (get32Int() % (r - l + 1)) + l;
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
  FILE *f = fopen("script_prim.sh", "w");
  for(int i = 0; i < 150; ++i) {
    //printf("Start test %d\n", i);
    fprintf(f, "echo %d\n", i);
    //fprintf(f, "g++ -O2 -w retroactive-mst.cpp && ./a.out < in2/%s > out\n", genName(i).c_str());
    //fprintf(f, "g++ -O2 -w retroactive-mst-kruskal.cpp && ./a.out < in2/%s > sol\n", genName(i).c_str());
    fprintf(f, "g++ -O2 -w retroactive-mst-prim.cpp && ./a.out < in1/%s > out\n", genName(i).c_str());
    //fprintf(f, "diff out sol\n");
    //printf("Finish test %d\n\n", i);
  }
  fclose(f);
  return 0;
}