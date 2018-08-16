#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

vector<long long> v;
vector<long long> buckets;

int B;

void init() {
  B = int(sqrt(v.size()));
  buckets = vector<int>(B<<1, 0);
  for(int i=0; i<v.size(); ++i)     
    buckets[ i / B ] += v[i];
 
}

void query(int L, int R) {
  long long acc = 0;
  
  int lo = L - 1;
  int hi = R - 1;
  
  // handling ambiguous left range
  while(lo % B != 0 && lo <= hi)
    acc += v[lo++];

  // handling ambiguous right range
  while((hi + 1) % B != 0 && lo <= hi)
    acc += v[hi--];

  for( ;lo <= hi; lo += B)
    acc += buckets[lo / B];

  cout << acc;
}

void update(int pos, long long val) {
  int idx = pos - 1;
  v[idx] = val;

  int bucket_idx = idx / B;
  int lo = bucket_idx * B;
  int hi = min(lo + B - 1, int(v.size()) - 1);

  long long acc = 0;
  for(; lo <= hi ; ++lo)
    acc += v[lo];  

  buckets[bucket_idx] = acc;
}

int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  
  int N, R;
  while(cin >> N >> R) {
    int I, J;
    string s;

    v = vector<int>(N);
    for(int i=0; i<N; ++i)
      cin >> v[i];

    init();

    int A, B, C, D;
    while(R--) {
      cin >> A >> B >> C >> D;
      update(A, B);
      query(C, D);
    }

    cout << '\n';
  }

  return 0;
}
