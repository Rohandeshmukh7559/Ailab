#include <iostream>
#include <vector>
using namespace std;

int isSafe(vector<vector<int>> graph, vector<int> color, int i, int col, int m)
{
    int n = graph.size();
    for (int j = 0; j < n; j++)
    {
        if (graph[i][j] && color[j] == col)
            return 0;
    }
    return 1;
}
int solve(vector<vector<int>> graph, vector<int> color, int i, int m)
{
    int n = graph.size();
    if (i == n)
    {
        for (int j = 0; j < n; j++)
        {
            cout << color[j] << " ";
        }
        cout << endl;
        return 1;
    }

    for (int col = 1; col <= m; col++)
    {
        if (isSafe(graph, color, i, col, m))
        {
            color[i] = col;
            if (solve(graph, color, i + 1, m))
                return 1;
            color[i] = 0;
        }
    }
    return 0;
}
int main()
{
    vector<vector<int>> graph = {{1, 1, 1, 1, 0, 1},
                                 {1, 1, 1, 0, 1, 0},
                                 {1, 1, 1, 1, 0, 0},
                                 {1, 0, 1, 1, 1, 0},
                                 {0, 1, 0, 1, 1, 0},
                                 {1, 0, 0, 0, 0, 1}};

    vector<int> color(graph.size(), 0);
    if (!solve(graph, color, 0, 4))
        cout << "No Solution";
    return 0;
}