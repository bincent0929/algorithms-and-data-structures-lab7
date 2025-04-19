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
    std::shared_ptr<Node> u = nodes[i];
    u->visited = false;
    u->predecessor = nullptr;
    u->discovered = -1;
    u->finished = -1;
  }
  int time = 0;
  for (int i = 0; i < nodes.size(); i++) {
    std::shared_ptr<Node> u = nodes[i];
    if (u->visited == false) {
      time = DFSVisit(u->id, time);
    }
  }
}

int Graph::DFSVisit(int s, int time){
  time += 1;
  std::shared_ptr<Node> sNode;
  for (int i; i < nodes.size(); i++) {
    if (nodes[i]->id == s) {
      sNode = nodes[i];
    }
  }
  sNode->discovered = time;
  sNode->visited = true;
  for (int i; i < sNode->neighbors.size(); i++) {
    std::shared_ptr<Node> v = sNode->neighbors[i];
    if (v->visited == false) {
      v->predecessor = sNode;
      time = DFSVisit(v->id, time);
    }
  }
  time += 1;
  sNode->finished = time;
  return time;
}

void Graph::BFS(int s){
  // because of distanecesFrom not working, this is not working
  std::shared_ptr<Node> sNode;
  for (int i = 0; i < nodes.size(); i++) {
    if (nodes[i]->id == s) {
      sNode = nodes[i];
      sNode->dist = 0;
      sNode->visited = true;
      sNode->predecessor = nullptr;
    }
    else {
      nodes[i]->dist = INT_MAX; // INT_MAX is basically infinity
      nodes[i]->visited = false;
      nodes[i]->predecessor = nullptr;
    }
  }
  std::queue<std::shared_ptr<Node>> Q;
  Q.push(sNode);
  while (Q.size() > 0) {
    std::shared_ptr<Node> u = Q.front();
    Q.pop();
    for (int i = 0; i < u->neighbors.size(); i++) {
      std::shared_ptr<Node> v = u->neighbors[i];
      if (v->visited == false) {
        v->dist = u->dist + 1;
        v->visited = true;
        v->predecessor = u;
        Q.push(v);
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
