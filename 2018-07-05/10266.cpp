#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N;
  cin >> N;

  vector<int> in1;
  vector<int> in2;

  vector<int> target(2*N, 0);
  vector<int> pattern(N, 0);
  vector<int> indices;
  vector<int> failure(N, 0);

  int tmp;
  for(int i=0; i<N; ++i) {
    cin >> tmp;
    in1.push_back(tmp);
  }

  for(int i=0; i<N; ++i) {
    cin >> tmp;
    in2.push_back(tmp);
  }

  for(int i=0; i<2*N; ++i)
    target[i] = (in1[(i+1) % N] - in1[i % N] + 360000) % 360000;
  
  for(int i=0; i<N; ++i) 
    pattern[i] = (in2[(i+1) % N] - in2[i % N] + 360000) % 360000;

  int match = 0;
  for(int i=1; i<N; ++i) {
    while(match && pattern[i] != pattern[match])
      match = failure[match - 1];

    if(pattern[match] == pattern[i]) {
      match++;
      failure[i] = match;
    } 
  }

  match = 0;
  for(int i=0; i<2*N; ++i) {
    while(match && target[i] != pattern[match])
      match = failure[match - 1];

    if(target[i] == pattern[match]) {
      match++;
      if(match == N) {
	indices.push_back(i - match + 1);
	match = failure[match - 1];
      }
    }
  }

  if(indices.size() > 0) {
    cout << "possible";
  } else {
    cout << "impossible";
  }

  return 0;
}
