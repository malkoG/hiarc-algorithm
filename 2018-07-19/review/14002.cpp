#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int N;
  cin >> N;
  vector<pair<int,int> > v;

  int bound = N<<2;
  vector<pair<int,int>> result(bound, {0, 0});
  vector<int> tree(N+1, 0);
  vector<int> parent(N+1, 0);
  
  for(int i=1; i<=N; ++i) {
    int tmp;
    cin >> tmp;
    v.push_back({tmp, i});
  }

  sort(v.begin(), v.end(), [](pair<int,int>& p, pair<int,int>& q) {
      if(p.first == q.first)
	return p.second > q.second;
      return p.first < q.first;
    });

  for(auto& i : v) {
    int idx = i.second;

    int len_idx = idx - 1;
    int len = 0;
    int candidate_parent = 0;

    while(len_idx > 0) {
      if(result[len_idx].first > len) {
	len = result[len_idx].first;
	candidate_parent = result[len_idx].second;	  
      }
      
      len_idx -= len_idx & -len_idx;
    }

    tree[i.second]   = i.first;
    parent[i.second] = candidate_parent;
    while(idx < bound) {
      if(result[idx].first < len+1) {
	result[idx].first  = len + 1;
	result[idx].second = i.second;
      }
      
      idx += idx & -idx; 
    }
  }
  
  int idx = 1;
  while( idx <= N )
    idx <<= 1;  

  vector<int> li;
  for(int i = result[idx].second; i != 0; i = parent[i]) {
    li.push_back(tree[i]);
  }  
  reverse(li.begin(), li.end());
  cout << li.size() << '\n';
  for(auto& i : li)
    cout << i << " ";

  return 0;
}
