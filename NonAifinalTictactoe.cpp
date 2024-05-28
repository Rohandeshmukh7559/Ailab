#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

vector<int> BOARD(10, 2);
int TURN = 1;

int posswin(int pl)
{
    int req = pl * pl * 2;
    // rows
    if (BOARD[1] * (BOARD[2] * BOARD[3]) == req)
    {
        for (int i = 1; i <= 3; i++)
        {
            if (BOARD[i] == 2)
                return i;
        }
    }
    if (BOARD[4] * (BOARD[5] * BOARD[6]) == req)
    {
        for (int i = 4; i <= 6; i++)
        {
            if (BOARD[i] == 2)
                return i;
        }
    }
    if (BOARD[7] * (BOARD[8] * BOARD[9]) == req)
    {
        for (int i = 7; i <= 9; i++)
        {
            if (BOARD[i] == 2)
                return i;
        }
    }

    // columns
    if (BOARD[1] * (BOARD[4] * BOARD[7]) == req)
    {
        if (BOARD[1] == 2)
            return 1;
        if (BOARD[4] == 2)
            return 4;
        if (BOARD[7] == 2)
            return 7;
    }
    if (BOARD[2] * (BOARD[5] * BOARD[8]) == req)
    {
        if (BOARD[2] == 2)
            return 2;
        if (BOARD[5] == 2)
            return 5;
        if (BOARD[8] == 2)
            return 8;
    }
    if (BOARD[3] * (BOARD[6] * BOARD[9]) == req)
    {
        if (BOARD[3] == 2)
            return 3;
        if (BOARD[6] == 2)
            return 6;
        if (BOARD[9] == 2)
            return 9;
    }

    // diagonals
    if (BOARD[1] * (BOARD[5] * BOARD[9]) == req)
    {
        if (BOARD[1] == 2)
            return 1;
        if (BOARD[5] == 2)
            return 5;
        if (BOARD[9] == 2)
            return 9;
    }
    if (BOARD[3] * (BOARD[5] * BOARD[7]) == req)
    {
        if (BOARD[3] == 2)
            return 3;
        if (BOARD[5] == 2)
            return 5;
        if (BOARD[7] == 2)
            return 7;
    }

    // if not found
    return 0;
}

int make2()
{
    if (BOARD[5] == 2)
    {
        return 5;
    }
    vector<int> make = {2, 4, 6, 8};
    int r = rand() % 4;
    return make[r];
}

void GO(int pl, int n)
{
    TURN++;
    BOARD[n] = pl;
    for (int i = 1; i <= 9; i++)
    {
        if (BOARD[i] == 2)
        {
            cout << "-"
                 << " ";
        }
        else if (BOARD[i] == 5)
        {
            cout << "O"
                 << " ";
        }
        else if (BOARD[i] == 3)
        {
            cout << "X"
                 << " ";
        }
        if (i % 3 == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
}

void game()
{
    while (TURN <= 9)
    {
        cout << "Turn " << TURN << endl;
        switch (TURN)
        {
        case 1:
            GO(3, 1);
            break;
        case 2:
            if (BOARD[5] == 2)
            {
                GO(5, 5);
            }
            else
            {
                GO(5, 3);
            }
            break;
        case 3:
            if (BOARD[9] = 2)
            {
                GO(3, 9);
            }
            else
            {
                GO(3, 3);
            }
            break;
        case 4:
            if (posswin(3) != 0)
            {
                GO(5, posswin(3));
            }
            else
            {
                GO(5, make2());
            }
            break;
        case 5:
            if (posswin(3) != 0)
            {
                GO(3, posswin(3));
                cout << "X wins" << endl;
                TURN = 10;
                break;
            }
            else if (posswin(5) != 0)
            {
                GO(3, posswin(5));
            }
            else if (BOARD[7] == 2)
            {
                GO(3, 7);
            }
            else
            {
                GO(3, 3);
            }
            break;
        case 6:
            if (posswin(5) != 0)
            {
                GO(5, posswin(5));
                cout << "O wins" << endl;
                TURN = 10;
                break;
            }
            else if (posswin(3) != 0)
            {
                GO(5, posswin(3));
            }
            else
            {
                GO(5, make2());
            }
            break;
        case 7:
            if (posswin(3) != 0)
            {
                GO(3, posswin(3));
                cout << "X wins" << endl;
                TURN = 10;
                break;
            }
            else if (posswin(5) != 0)
            {
                GO(3, posswin(5));
            }
            else
            {
                for (int i = 1; i < 10; i++)
                {
                    if (BOARD[i] == 2)
                    {
                        GO(3, i);
                        break;
                    }
                }
            }
            break;
        case 8:
            if (posswin(5) != 0)
            {
                GO(5, posswin(5));
                cout << "O wins" << endl;
                TURN = 10;
                break;
            }
            else if (posswin(3) != 0)
            {
                GO(5, posswin(3));
            }
            else
            {
                for (int i = 1; i < 10; i++)
                {
                    if (BOARD[i] == 2)
                    {
                        GO(5, i);
                        break;
                    }
                }
            }
            break;
        case 9:
            if (posswin(3) != 0)
            {
                GO(3, posswin(3));
                cout << "X wins" << endl;
                TURN = 10;
                break;
            }
            else if (posswin(5) != 0)
            {
                GO(3, posswin(5));
            }
            else
            {
                for (int i = 1; i < 10; i++)
                {
                    if (BOARD[i] == 2)
                    {
                        GO(3, i);
                        break;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    if (TURN == 10)
    {
        cout << "Game Draw" << endl;
    }
    cout << endl;
}

int main()
{
    game();
    return 0;
}