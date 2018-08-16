#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define MOD 1000000007

int B;
vector<long long> v;
vector<long long> bucket;

void init() {
  B = int(sqrt(v.size()));
  bucket = vector<long long>(B<<1, 1);

  for(int i=0; i<v.size(); ++i) {
    bucket[i / B] *= v[i];
    bucket[i / B] %= MOD;
  }
}

void update(int pos, long long val) {
  int idx = pos - 1;
  v[idx] = val;

  int bucket_idx = idx / B;
  int lo = bucket_idx * B;
  int hi = min(lo + B - 1, int(v.size()) - 1);

  long long acc = 1;
  while(lo <= hi) {
    acc *= v[lo];
    acc %= MOD;
    lo++;
  }

  bucket[bucket_idx] = acc;
}


void query(int L, int R) {
  int lo = L - 1;
  int hi = R - 1;

  long long acc = 1;
  while(lo % B != 0 && lo <= hi) {
    acc *= v[lo++];
    acc %= MOD;
  }

  while((hi + 1) % B != 0 && lo <= hi) {
    acc *= v[hi--];
    acc %= MOD;
  }

  while(lo <= hi) {
    acc *= bucket[lo/B];
    acc %= MOD;
    lo += B;
  }
  
  cout << acc << '\n';
}


int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int N, M, K;
  cin >> N >> M >> K;
  v = vector<long long>(N);
  for(int i=0; i<N; ++i)
    cin >> v[i];

  init();
  for(int i=0; i<M+K; ++i) {
    int A,B, C;
    cin >> A >> B >> C;
    if(A == 1)
      update(B, C);
    else
      query(B, C);
  }

  return 0;
}
