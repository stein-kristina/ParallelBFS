#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    cout << "-- this is a random graph" << endl;
    cout << "please input vertex's size:" << endl;
    long long n, m;
    cin >> n;
    n = clamp(n, 0ll, 100000ll);
    cout << "please input edge's size:" << endl;
    cin>>m;
    m = clamp(m, 0ll, n * (n - 1) / 2);

    // 使用 std::random_device 生成种子
    std::random_device rd;
    // 使用 引擎，将种子传递给它
    std::ranlux48 gen(rd());
    // 使用 std::uniform_int_distribution 定义随机数范围
    std::uniform_int_distribution<int> dis(0, n * (n - 1));
    // 边集
    vector<vector<int>> x(n);

    int realm = 0;
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            int tp = dis(gen);
            if (tp < 2 * m)
            {
                // 一定概率有边，有向图
                realm += 1;
                x[i].push_back(j);
            }
        }
    }
    cout << "please input file name:" << endl;
    string file;
    cin >> file;
    ofstream fout("data/"+file+".graph", ios::out);
    fout << n << ' ' << realm << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < int(x[i].size())-1; j++)
        {
            fout<<x[i][j]<<' ';
        }
        if(x[i].size()>=1) fout<<x[i].back();
        fout<<'\n';
    }
    fout.close();
    cout<<"Vertexs: "<<n<<" edges: "<<realm<<endl;
    cout << "-- generate successfully --" << endl;
}