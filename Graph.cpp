// CSCI 311 lab 7

#include <iostream>
#include "Graph.h"
#include <queue>
#include <limits.h>

//do not change the headers above
//implement the functions below, but do not add new functions

//using namespace std;

Graph::Graph(){
  nodes = {};
}

void Graph::printAdjList(){
  for (int i = 0; i < nodes.size(); i++) {
    std::cout << nodes[i]->id << ": ";
    for (int j = 0; j < nodes[i]->neighbors.size(); j++) {
      std::cout << nodes[i]->neighbors[j]->id << " ";
    }
    std::cout << std::endl;
  }
}

bool Graph::isNeighbor(int u, int v){
  for (int i = 0; i < nodes[u]->neighbors.size(); i++) {
    if (nodes[u]->neighbors[i]->id == v) {
      return true;
    }
  }
  return false;
}

void Graph::DFS(){
  // this is not returning the right values
  for (int i = 0; i < nodes.size(); i++) {
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
    nodes[i]->discovered = -1;
    nodes[i]->finished = -1;
  }
  int time = 0;
  for (int i = 0; i < nodes.size(); i++) {
    if (nodes[i]->visited == false) {
      time = DFSVisit(nodes[i]->id, time);
    }
  }
}

int Graph::DFSVisit(int s, int time){
  time += 1;
  nodes[s]->discovered = time;
  nodes[s]->visited = true;
  for (int i; i < nodes[s]->neighbors.size(); i++) {
    if (nodes[s]->neighbors[i]->visited == false) {
      nodes[s]->neighbors[i]->predecessor = nodes[s];
      time = DFSVisit(i, time);
    }
  }
  time += 1;
  nodes[s]->finished = time;
  return time;
}

void Graph::BFS(int s){
  // because of distanecesFrom not working, this is not working
  for (int i = 0; i < nodes.size(); i++) {
    nodes[i]->dist = INT_MAX; // INT_MAX is basically infinity
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
  }
  nodes[s]->dist = 0;
  nodes[s]->visited = true;
  std::queue<std::shared_ptr<Node>> Q;
  Q.push(nodes[s]);
  while (Q.size() > 0) {
    std::shared_ptr<Node> u = Q.front();
    Q.pop();
    for (int i = 0; i < u->neighbors.size(); i++) {
      if (u->neighbors[i]->visited == false) {
        u->neighbors[i]->dist = u->dist + 1;
        u->neighbors[i]->visited = true;
        u->neighbors[i]->predecessor = u;
        Q.push(u->neighbors[i]);
      }
    }
  }
}

std::vector<int> Graph::distancesFrom(int s){
  std::vector<int> distances;
  BFS(s);
  for (int i = 0; i < nodes[s]->neighbors.size(); i++) {
    distances.push_back(nodes[s]->neighbors[i]->dist);
  }
  return distances;
}
