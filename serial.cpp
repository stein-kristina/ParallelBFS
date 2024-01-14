#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <string>
#include <string.h>
#include <queue>
#include <chrono>
#include <stdio.h>
#include <sstream>
#include "checker.h"
#include"Gpubfs.cuh"

using namespace std;
void bfs_serial(int start, Graph &G, std::vector<int> &distance, std::vector<bool> &visited)
{
    fill(distance.begin(), distance.end(), INT_MAX);
    distance[start] = 0;
    queue<int> to_visit;
    to_visit.push(start);

    while (!to_visit.empty())
    {
        int current = to_visit.front();
        to_visit.pop();
        for (int i = G.edgesOffset[current]; i < G.edgesOffset[current] + G.edgesSize[current]; ++i)
        {
            int v = G.adjacencyList[i];
            if (distance[v] == INT_MAX)
            {
                distance[v] = distance[current] + 1;
                to_visit.push(v);
            }
        }
    }
}

int main()
{
    Graph G(AdjacencyList, Directed);
    int startVertex;
    vector<int> distance(G.numVertices);
    vector<bool> visited(G.numVertices);
    startVertex = 98;

    // serial bfs
    auto startTime = chrono::steady_clock::now();
    bfs_serial(startVertex, G, distance, visited);
    auto endTime = std::chrono::steady_clock::now();
    long duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    printf("Elapsed time for Serial BFS : %li ms.\n", duration);

    Checker checker(distance);

    // simple bfs
    distance = vector<int>(G.numVertices);
    startTime = chrono::steady_clock::now();
	simplebfs(startVertex, G, distance, visited);
    endTime = std::chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	printf("Elapsed time for naive linear GPU implementation (with graph copying) : %li ms.\n", duration);

    // check
	checker.check(distance);

    //quadraticBFS
    distance = vector<int>(G.numVertices);
	startTime = chrono::steady_clock::now();
	quadraticbfs(startVertex, G, distance, visited);
	endTime = std::chrono::steady_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
	printf("Elapsed time for quadratic GPU implementation (with graph copying) : %li ms.\n", duration);

    // check
	checker.check(distance);

    return 0;
}
