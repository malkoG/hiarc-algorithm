#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  string text, pattern;

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  getline(cin, text);
  cin >> pattern;
  getline(cin, pattern);

  vector<int> pi(pattern.size(), 0);
  vector<int> indices;

  int match;
  for(int i=1, match=0; i<pattern.size(); ++i) {
    while(match && pattern[match] != pattern[i])
      match = pi[match-1];

    if(pattern[match] == pattern[i]) {
      match++;
      pi[i] = match;
    }
  }

  for(int i=0, match=0; i<text.size(); ++i) {
    while(match && text[i] != pattern[match])
      match = pi[match-1];
    
    if(text[i] == pattern[match]) {
      match++;
      if(match == pattern.size() ) {
	indices.push_back(i-match+1);
	match = pi[match-1];
      }
    }
      
  }

  cout << indices.size();
  for(auto i : indices)
    cout << i+1 << ' ';
  
  return 0;
}
