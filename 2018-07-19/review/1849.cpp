#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int leftmostbit(int n) {
  int bit = 1;
  while( (bit<<1) <= n )
    bit <<= 1;

  return bit;
}

int main() {
  int N;
  cin >> N;

  int boundary = 1;
  while(boundary <= N)
    boundary <<= 1;
  
  vector<int> fenwick(boundary, 0);
  vector<int> zeros(N+1, 0);
  vector<int> trees(N+1, 0);
  vector<pair<int,int> > infos;
  
  for(int i=1; i<=N; ++i) {
    int query;
    cin >> query;
    infos.push_back({i, query});
  }

  for(int i=1; i<=N; ++i) {
    zeros[i] = 1;
    int idx = i;
    while(idx <= boundary) {
      fenwick[idx] += 1;
      idx += idx & -idx;
    }
  }

  for(auto a : infos) {

    int mask = leftmostbit(N);
    int idx  = 0;


    while(mask > 0) {
      int inspecting_idx   = idx + mask - 1;
      int saving_idx       = inspecting_idx;
      int inspecting_value = 0;


      while(inspecting_idx > 0) {
	inspecting_value += fenwick[inspecting_idx]; 
	inspecting_idx   -= inspecting_idx & -inspecting_idx;
      }
	
      if(inspecting_value == a.second) {
	if(trees[saving_idx+1] == 0) {
	  idx = saving_idx;
	  break;
	} else {
	  idx += mask;
	}
      } else if (inspecting_value < a.second ) {
	idx += mask;
      }
	
      mask >>= 1;
    }

    idx += 1;
    trees[idx] = a.first;
    zeros[idx] = 0;
    while(idx <= boundary) {
      fenwick[idx] -= 1;
      idx += idx & -idx;
    }

  }


  for(int i=1; i<=N; ++i) {
    cout << trees[i] << endl;
  }

  return 0;
}
