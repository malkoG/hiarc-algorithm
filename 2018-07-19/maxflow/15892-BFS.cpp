#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define MAX_V 301
using namespace std;

// capacity 를 (이미 흘려보낸 시점에서) 각 간선에 흘려보낼 수 있는 용량으로 가정 
struct edge { int to, capacity, reverse_link; };

vector<edge> G[MAX_V];

void add_edge(int u, int v, int cap) {
  // Get indices of reverse edges in adjacency list
  int reverse_uv_idx = G[v].size();
  int reverse_vu_idx = G[u].size();
  G[u].push_back((edge){v, cap, reverse_uv_idx});
  G[v].push_back((edge){u, cap, reverse_vu_idx});
}

int max_flow(int s, int t) {
  int flow = 0;
  for(;;) {
    int parent[MAX_V];
    edge* path[MAX_V];
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
      int u = q.front(); q.pop();
      for(auto& e : G[u]) {
	int v = e.to;
	if(e.capacity > 0 && parent[v] == -1) {
	  q.push(v);
	  parent[v] = u;
	  path[v]   = &e;
	  if(v == t) break;
	}
      }
    }
    
    if(parent[t] == -1) return flow;

    // 경로를 역으로 타고 올라가면서 흘려보낼 수 있는 최대 유량을 구한다.
    int f = 1e+9;
    for(int i = t; i != s; i=parent[i])
      f = min(f, path[i]->capacity);

    // 정방향 간선에서는 용량에서 유량을 빼주고, 역방향 간선에서는 유량을 더해줌
    for(int i = t; i != s; i=parent[i]) {
      edge* e = path[i];      
      e->capacity -= f;
      G[e->to][e->reverse_link].capacity += f;
    }
    
    flow += f;
  }
}

int main() {
  int N, M;
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);

  cin >> N >> M;
  while(M--) {
    int from, to, cap;
    cin >> from >> to >> cap;
    
    add_edge(from, to, cap);
  }

  // 1번방에서 N번방으로 이동
  cout << max_flow(1, N);

  return 0;
}
