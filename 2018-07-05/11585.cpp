#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b) {
  if(a % b == 0) return b;
  else return gcd(b, a % b);
}

int main() {
  int N;
  int g;
  char tmp;
  cin >> N;
  vector<char> target(N<<1);
  vector<char> pattern(N);
  vector<int> failure(N, 0);
  vector<int> indices;
  
  int count = N<<1;
  for(int i=0; i<N; ++i) {
    cin >> tmp;
    target[i] = tmp;
    target[N+i] = tmp;
  }

  for(int i=0; i<N; ++i) {
    cin >> tmp;
    pattern[i] = tmp;
  }

  int match = 0;
  for(int i=1; i<N; ++i) {
    while(match && pattern[i] != pattern[match])
      match = failure[match-1];

    if(pattern[i] == pattern[match]) {
      match++;
      failure[i] = match;
    }      
  }

  match = 0;
  for(int i=0; i<count-1; ++i) {
    while(match && target[i] != pattern[match])
      match = failure[match-1];

    if(pattern[match] == target[i]) {
      match++;
      if(match == N) {
	indices.push_back(i-match+1);
	match = failure[match-1];
      }
    }
  }

  g = gcd(N, indices.size());

  cout << indices.size() / g << '/' << N / g;

  return 0;
}
