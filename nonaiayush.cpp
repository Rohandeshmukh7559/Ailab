#include <iostream>
#include <vector>
using namespace std;

vector<int> board = {2, 2, 2, 2, 2, 2, 2, 2, 2};
vector<vector<int>> win = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 4, 8}, {2, 4, 6}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}};

// 3 - player  5- computer
void player()
{
    int pos;
    cout << "Player Turn" << endl;
    cin >> pos;
    if (board[pos] == 2)
        board[pos] = 3;
    else
        player();
}
void print()
{
    for (int i = 0; i < 9; i++)
    {
        cout << board[i] << "|";
        if ((i + 1) % 3 == 0)
            cout << "\n";
    }
}
int possWin(int x)
{
    for (int i = 0; i < 8; i++)
    {

        int idx = -1;
        int count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[win[i][j]] == x)
                count++;
            else if (board[win[i][j]] == 2)
                idx = win[i][j];
            else
                count--;
        }
        if (count == 2)
            return idx;
    }
    return -1;
}

int isWin(int x)
{

    for (int i = 0; i < 8; i++)
    {
        int count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[win[i][j]] == x)
                count++;
        }
        if (count == 3)
            return 1;
    }
    return 0;
}
int draw()
{
    int count = 0;
    for (int j = 0; j < 9; j++)
    {
        if (board[j] == 2)
            return 0;
    }
    return 1;
}

void go()
{
    int temp;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 2)
        {
            board[i] = 5;
            temp = i;
            if (possWin(5) != -1)
                return;
            board[i] = 2;
        }
    }
    board[temp] = 5;
}
void bot()
{
    int i = possWin(5);
    if (i != -1)
    {
        board[i] = 5;
        return;
    }

    i = possWin(3);
    if (i != -1)
    {
        board[i] = 5;
        return;
    }

    go();
}
int main()
{
    while (1)
    {
        player();
        print();
        if (isWin(3))
        {
            printf("Player wins!\n");
            return 0;
        }
        if (draw())
        {
            printf("Draw\n");
            return 0;
        }
        cout << "Bot Turn:" << endl;
        bot();
        print();
        if (isWin(5))
        {
            printf("Bot wins!\n");
            return 0;
        }
        if (draw())
        {
            printf("Draw\n");
            return 0;
        }
    }

    return 0;
}