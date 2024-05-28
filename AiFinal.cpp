#include <bits/stdc++.h>
using namespace std;

int board[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};
int win[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

void playerMove()
{
    cout << "Enter your move:";
    int pos;
    cin >> pos;
    if (board[pos] == 2)
    {
        board[pos] = 3;
    }
    else
    {
        cout << "Position is already Filled: " << endl;
        playerMove();
    }
}
void printBoard()
{
    cout << "Current Board Position: " << endl;
    cout << "-------" << endl;
    string ele;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 3)
            ele = "O";
        if (board[i] == 5)
            ele = "X";
        if (board[i] == 2)
            ele = " ";
        cout << "|" << ele;
        if ((i + 1) % 3 == 0)
            cout << "|" << endl
                 << "-------" << endl;
    }
}
bool isWin(int x)
{
    for (int i = 0; i < 8; i++)
    {
        int c = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[win[i][j]] == x)
                c++;
        }
        if (c == 3)
            return true;
    }
    return false;
}
bool draw()
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 2)
            return false;
    }
    return true;
}
bool minmax(bool isMaximizing)
{
    if (isWin(5))
        return 1000;
    if (isWin(3))
        return -1000;
    if (draw())
        return 0;

    if (isMaximizing)
    {
        int bestScore = INT_MIN;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == 2)
            {
                board[i] = 5;
                int score = minmax(false);
                board[i] = 2;
                bestScore = max(bestScore, score);
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == 2)
            {
                board[i] = 3;
                int score = minmax(true);
                board[i] = 2;
                bestScore = min(bestScore, score);
            }
        }
        return bestScore;
    }
}
void compMove()
{
    int bestScore = INT_MIN;
    int bestPos = 0;

    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 2)
        {
            board[i] = 5;
            int score = minmax(false);
            board[i] = 2;
            if (score > bestScore)
            {
                bestScore = score;
                bestPos = i;
            }
        }
    }
    board[bestPos] = 5;
}

int main()
{
    while (1)
    {
        playerMove();
        printBoard();
        if (isWin(3))
        {
            cout << "You Won";
            break;
        };
        if (draw())
        {
            cout << "comp Won";

            break;
        };

        compMove();
        printBoard();
        if (isWin(5))
            break;
        if (draw())
            break;
    }
    return 0;
}