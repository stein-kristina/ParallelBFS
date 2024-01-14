#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include<fstream>

using namespace std;
enum Direction
{
    Directed
};
enum Format
{
    AdjacencyList
};
inline void print_vector(string title, vector<int> &v)
{
    cout << title << " { ";
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i];
        if (i < v.size() - 1)
            cout << ", ";
    }
    cout << " }" << endl;
}
class Graph
{
public:
    Graph(Format format = AdjacencyList, Direction direction = Directed)
    {
        std::cout << "File name :" << std::endl;
        string file;
        cin >> file;
        string file_in = "data/" + file+".graph";
        ifstream fin(file_in, ios::in);
        if(fin.is_open() == false){
            cout<<"Read error!\n";
            return;
        }
        int numVertices, numEdges;
        cout << "Started reading graph" << endl;
        fin >> numVertices >> numEdges;
        vector<vector<int>> adjacencyList(numVertices);
        string line;
        getline(fin,line);
        for (int v = 0; v < numVertices; ++v)
        {
            // cout<<v<<"::"<<endl;
            getline(fin, line);
            stringstream splitter(line);
            int w;
            while (splitter >> w)
            {
                adjacencyList[v].push_back(w);
            }
        }
        this->init(adjacencyList, numEdges);
        cout << "Finished reading graph" << endl;
    }
    std::vector<int> adjacencyList; //连续顶点的边
    std::vector<int> edgesOffset;   //每个顶点的边偏移量
    std::vector<int> edgesSize;     //每个顶点的边数
    int numVertices;
    int numEdges;

    void print()
    {
        printf("Graph(numVertices = %i, numEdges = %i)\n", numVertices, numEdges);
        print_vector("AdjacencyList:", adjacencyList);
        print_vector("edgesOffset:", edgesOffset);
        print_vector("edgesSize:", edgesSize);
    }

private:
    Graph(std::vector<std::vector<int>> adjacencyList);
    void init(std::vector<std::vector<int>> adjacencyList, int numEdges)
    {
        const int numVertices = adjacencyList.size();
        // Creation of single vector adjacency list
        for (int i = 0; i < numVertices; ++i)
        {
            this->edgesOffset.push_back(this->adjacencyList.size());
            this->edgesSize.push_back(adjacencyList[i].size());//节点有多少边
            for (int v : adjacencyList[i])
            {
                this->adjacencyList.push_back(v);//点的邻居有哪些
            }
        }
        this->numVertices = numVertices;
        this->numEdges = numEdges;
    }
};

#endif // GRAPH_H
