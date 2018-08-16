#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define INF 1e+9

int bucket_size;

vector<int> v;
vector<int> min_bucket;
vector<int> max_bucket;

void init() {
  bucket_size = int(sqrt(v.size()));

  min_bucket = vector<int>(bucket_size<<1, INF);
  max_bucket = vector<int>(bucket_size<<1, 0);
  
  for(int i=0; i<v.size(); ++i) {
    int bucket_idx = i / bucket_size;
    max_bucket[bucket_idx] = max(max_bucket[bucket_idx], v[i]);
    min_bucket[bucket_idx] = min(min_bucket[bucket_idx], v[i]);
  }
}

void query(int L, int R) {
  int lo = L - 1;
  int hi = R - 1;

  int ans1 = INF;
  int ans2 = 0;

  while(lo % bucket_size != 0 && lo <= hi) {
    ans1 = min(ans1, v[lo]);
    ans2 = max(ans2, v[lo]);
    ++lo;
  }

  while((hi + 1) % bucket_size != 0 && lo <= hi) {
    ans1 = min(ans1, v[hi]);
    ans2 = max(ans2, v[hi]);
    --hi;
  }

  while(lo <= hi) {
    int bucket_idx = lo / bucket_size;
    ans1 = min(ans1, min_bucket[bucket_idx]);
    ans2 = max(ans2, max_bucket[bucket_idx]);
    lo += bucket_size;
  }

  cout << ans1 << " " << ans2;
}


int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  
  int N, Q;
  cin >> N >> Q;
  v = vector<int>(N);
  for(int i=0; i<N; ++i)
    cin >> v[i];

  init();

  while(Q--) {
    int L, R;
    cin >> L >> R;
    query(L, R);
    cout << '\n';
  }

  return 0;
}
