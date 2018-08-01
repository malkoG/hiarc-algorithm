#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;

  while(T--) {
    int N;
    cin >> N;
    vector<pii> v;


    int bound = 1;
    while(bound < N)
      bound <<= 1;
    
    vector<int> tree(bound+1,    0);
    vector<int> fenwick(bound+1, 0);
    
    for(int i=0; i<N; ++i) {
      int before, after;
      cin >> before >> after;
      v.push_back({before, after});
    }

    sort(v.begin(), v.end());

    for(auto i : v) {

      int idx  = i.second - 1;
      int rank = 0;

      while(idx > 0) {
	rank = max(fenwick[idx] + 1, rank);
	idx -= idx & -idx;
      }

      rank = max(fenwick[idx] + 1, rank);

      idx  = i.second;

      tree[idx] = rank;
      while(idx <= bound) {
	fenwick[idx] = max(fenwick[idx], rank);
	idx += idx & -idx;
      }

    }
    
    cout << count(tree.begin(), tree.begin() + N, 1) << '\n';
  }

  return 0;
}
