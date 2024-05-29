#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int heuristic(vector<vector<int>> curr, vector<vector<int>> goal)
{
    int c = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (curr[i][j] != goal[i][j])
                c++;
        }
    }
    return c;
}
pair<int, int> find_empty(vector<vector<int>> curr)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (curr[i][j] == 0)
                return {i, j};
        }
    }
    return {-1, -1};
}
int isValid(int x, int y)
{
    if (x >= 0 && x < 3 && y >= 0 && y < 3)
    {
        return 1;
    }
    return 0;
}

void print(vector<vector<int>> temp)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << temp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int solve(vector<vector<int>> start, vector<vector<int>> goal)
{
    priority_queue<pair<int, vector<vector<int>>>, vector<pair<int, vector<vector<int>>>>, greater<pair<int, vector<vector<int>>>>> pq;
    map<vector<vector<int>>, vector<vector<int>>> parent;
    int h = heuristic(start, goal);
    pq.push({h, start});
    parent[start] = {};
    int t = 0;
    while (!pq.empty())
    {
        vector<vector<int>> curr = pq.top().second;
        pq.pop();

        if (curr == goal)
        {
            while (parent.find(curr) != parent.end())
            {
                print(curr);
                curr = parent[curr];
            }

            return 1;
        }
        vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        pair<int, int> temp = find_empty(curr);
        int x = temp.first;
        int y = temp.second;
        for (auto i : dir)
        {
            int xnew = x + i.first;
            int ynew = y + i.second;

            if (isValid(xnew, ynew))
            {

                vector<vector<int>> next = curr;
                swap(next[x][y], next[xnew][ynew]);
                if (parent.find(next) == parent.end())
                {
                    parent[next] = curr;
                    int h = heuristic(next, goal);
                    pq.push({h, next});
                }
            }
        }
    }
    return 0;
}

int main()
{

    vector<vector<int>> start = {{1, 2, 3}, {0, 4, 5}, {7, 8, 6}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    if (!solve(start, goal))
        cout << "No Solution";

    return 0;
}