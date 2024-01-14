#ifndef BFS_GPU_SIMPLE
#define BFS_GPU_SIMPLE

#include<iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <limits>
#include<chrono>

#include "graph.h"

/*
start vertex
G graph
distance to check
visited 
 */
void simplebfs(int start, Graph &G, std::vector<int> &distance, std::vector<bool> &visited);
void quadraticbfs(int start, Graph &G, std::vector<int> &distance, std::vector<bool> &visited);

#endif // BFS_GPU_CUH
