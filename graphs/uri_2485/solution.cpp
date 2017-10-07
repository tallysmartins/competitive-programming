/*
----------------------------------------------------------------------------
  Name: Tallys Gustavo Martins
  Email: tallys@ime.usp.br
  Degree in Software Engineering from University of Brasília
  URL: https://www.urionlinejudge.com.br/judge/pt/problems/view/2485
  LEVEL: 2
  Timelimit: 1
  Subject: Elementary Graph Algorithms
  Algorithm: BFS

  Time.now('mm/yyyy')
  >> 10/2017

  Problem: Count how many days to heal all the trees in a grid
  Solution: Simple BFS to count the max distance to tje furthest tree
----------------------------------------------------------------------------
*/

#include <bits/stdc++.h>

using namespace std;

#define MAX_A 102
#define MAX_B 102
#define CONTAIN_TREE 1

int grid[MAX_A][MAX_B];
int visited[MAX_A][MAX_B];
int days_counter;
int remaining_sick_trees;

bool has_tree(pair <int, int> coordinate) {
  return grid[coordinate.first][coordinate.second] == CONTAIN_TREE;
}

// return the trees in the neighborhood
list<pair <int,int> > get_neighborhood(int x, int y) {

  list<pair <int,int> > all_neighbors;

  all_neighbors.push_back(make_pair(x-1, y));   //left
  all_neighbors.push_back(make_pair(x-1, y+1)); //diagonal top-let
  all_neighbors.push_back(make_pair(x, y+1));   //up
  all_neighbors.push_back(make_pair(x+1, y+1)); //diagonal top-right
  all_neighbors.push_back(make_pair(x+1, y));   //right
  all_neighbors.push_back(make_pair(x+1, y-1)); //diagonal bottom-right
  all_neighbors.push_back(make_pair(x, y-1));   //down
  all_neighbors.push_back(make_pair(x-1, y-1)); //diagonal bottom-left

  list<pair <int,int> > valid_neighbors;

  for(auto it : all_neighbors) {
    if(has_tree(it)) {
      valid_neighbors.push_back(it); 
    }
  }

  return valid_neighbors;
}

//simple bfs to walk through the grid and get the max distance
void bfs(int x, int y) {
  queue<tuple <int, int, int> > Q;
  Q.emplace(x, y, 0);

  int u_x, u_y, u_d;
  while(not Q.empty()) {

    tie(u_x, u_y, u_d) = Q.front();
    Q.pop(); 
     
    visited[u_x][u_y] = 1;
    for(auto it : get_neighborhood(u_x,u_y)) {
      if(not visited[it.first][it.second]){
        Q.emplace(it.first, it.second, u_d + 1);
        visited[it.first][it.second] = 1;

        //save the MAX distance, until the furthest tree
        days_counter = max(days_counter, u_d + 1);
      }
    }
  }
}

int main() {
  int T; // Number of test cases
  int A; // Number of lines in the grid
  int B; // Number of columns in the grid
  int X; // X position of the first tree to be cured
  int Y; // Y position of the first tree to be cured
  int element; // Current element being read from the input

  cin >> T;

  while(T--) {
    cin >> A >> B;

    memset(grid, 0 , sizeof(grid));
    memset(grid[0], -1, sizeof(grid[0]));
    memset(grid[A+1], -1, sizeof(grid[A+1]));
    memset(visited, 0, sizeof(visited));
    days_counter = 0;

    for(int i=0; i<=A+1; ++i) {
      grid[i][0] = -1;
      grid[i][B+1] = -1;
    }

    for(int i=1; i<=A; ++i){
      for(int j=1; j<=B; ++j){
          cin >> element;
          grid[i][j] = element;
          if(element == 1) {
            remaining_sick_trees++;
          }
      }
    }
    cin >> X >> Y;
    bfs(X,Y);
    cout << days_counter << endl;
  }

  return 0;
}
