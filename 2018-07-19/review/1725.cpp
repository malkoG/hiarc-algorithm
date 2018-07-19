#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> root;

int find_root(int u) {
  if(root[u] == u) return u;
  else return root[u] = find_root(root[u]);
}

int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  
  int N;
  cin >> N;

  vector<int> widths(N+2, 0);
  vector<pair<int,int> > v;
  root = vector<int>(N+2, 0);

  for(int i=0; i<=N+1; ++i)
    root[i] = i;

  for(int i=1; i<=N; ++i) {
    int height;
    cin >> height;
    v.push_back({height, i});
  }

  sort(v.begin(), v.end());
  
  reverse(v.begin(), v.end());

  int ans = -1;
  for(auto i : v) {

    int left  = i.second - 1;
    int right = i.second + 1;

    int left_root  = find_root(left);
    int right_root = find_root(right);

    widths[i.second] = widths[left_root] + widths[right_root] + 1;
    ans = max(ans, widths[i.second] * i.first);

    root[left_root]  = widths[left_root] == 0 ? left_root : find_root(i.second);
    root[right_root] = widths[right_root] == 0 ? right_root : find_root(i.second);
  }

  cout << ans;
  return 0;
}
