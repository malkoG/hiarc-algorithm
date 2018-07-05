#include <iostream>
#include <algorithm>
using namespace std;

int N;
int lis[1000]; // LIS array 
int lds[1000]; // LDS array
int dp[1000];  // LIS length 
int dp2[1000]; // LDS length

int solve() {
  int lis_length;
  int lds_length;

  for(int i=0; i<N; ++i) {
    lis_length = 0;
    lds_length = 0;
    
    for(int j=0; j<i; ++j) {
      if(lis[j] < lis[i])
	lis_length = max(lis_length, dp[j]);

      if(lds[j] < lds[i])
	lds_length = max(lds_length, dp2[j]);
    }

    dp[i] = lis_length + 1;
    dp2[i] = lds_length + 1;
  }

  int ans = 0;
  for(int i=0; i<N; ++i) 
    ans = max(ans, dp[i] + dp2[N-i-1] - 1); // See inclusion-exclusion law  
  /*
  for(int i=0; i<N; ++i)
    cout << dp[i] << " ";
  cout << endl;

  for(int i=0; i<N; ++i)
    cout << dp2[N-i-1] << " ";
  cout << endl;
  */
  return ans;
}

int main() {
  cin >> N;

  for(int i=0; i<N; ++i) {
    int tmp;
    cin >> tmp;
    lis[i] = tmp;
    lds[N-i-1] = tmp; // get reverse of the sequence
  }

  cout << solve();

  return 0;
}
