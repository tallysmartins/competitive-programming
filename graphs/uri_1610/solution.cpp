/*
----------------------------------------------------------------------------
  Name: Tallys Gustavo Martins
  Email: tallys@ime.usp.br
  Degree in Software Engineering from University of Brasília
  URL: https://www.urionlinejudge.com.br/judge/pt/problems/view/1610
  LEVEL: 2
  Timelimit: 1
  Subject: Elementary Graph Algorithms
  Algorithm: DFS

  Time.now('mm/yyyy')
  >> 10/2017

  Problem: Find cycles in a graph
  Solution: DFS with stack vector
----------------------------------------------------------------------------
*/

#include <bits/stdc++.h>

using namespace std;

//Defining constants for the given problem
#define MAX_N_NODES 10004
#define MAX_M_EDGES 10004
#define LOOP_FOUND 1


int visited[MAX_N_NODES];
int mystack[MAX_N_NODES];
vector<int> adj[MAX_N_NODES];
int has_loop = 0;


//DFS implementation to check if there's a loop in a graph G
void find_loop(int s) {

  if(has_loop) return;

  visited[s] = 1;
  mystack[s] = 1;

  for(auto it : adj[s]) {
    if(mystack[it]) {
      has_loop = 1;
      return;
    }

    if(not visited[it])
      find_loop(it);
  }

  mystack[s] = 0;
  return;
}

int main() {

  int T;    // Number of test cases
  int N;    // Number of documents
  int M;    // Number of edges that describe dependencies between the documents
  int A, B; // Document A depends on B

  cin >> T;
  int total = T;

  while(T--) {
    cin >> N >> M;
    has_loop = 0;
    memset(visited, 0, sizeof(visited));
    memset(mystack, 0, sizeof(mystack));
    memset(adj, 0, sizeof(adj));

    while(M--) {
      cin >> A >> B;
      if(A == B) {
        has_loop = 1;
      }
      adj[A].push_back(B);
    }

    for(int k=1; k <= N; ++k) {
      if(not visited[k])
        find_loop(k);
    }

    if(has_loop)
      cout << "SIM" << endl;
    else
      cout << "NAO" << endl;
  }
  
  return 0;
}

