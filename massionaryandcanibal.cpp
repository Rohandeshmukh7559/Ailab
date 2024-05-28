#include <iostream>
#include <vector>

using namespace std;

struct State
{
    int missionariesLeft;
    int cannibalsLeft;
    int boat; // 0 for left, 1 for right
    int missionariesRight;
    int cannibalsRight;
    vector<State> path;
};

bool isValidState(int missionaries, int cannibals)
{
    if (missionaries < 0 || cannibals < 0 || missionaries > 3 || cannibals > 3)
        return false;
    if ((missionaries < cannibals && missionaries > 0) || (missionaries > cannibals && missionaries < 3))
        return false;
    return true;
}

bool isGoalState(State state)
{
    return state.missionariesLeft == 0 && state.cannibalsLeft == 0;
}

bool isVisited(State state, vector<State> &visited)
{
    for (int i = 0; i < visited.size(); ++i)
    {
        if (visited[i].missionariesLeft == state.missionariesLeft && visited[i].cannibalsLeft == state.cannibalsLeft &&
            visited[i].boat == state.boat && visited[i].missionariesRight == state.missionariesRight &&
            visited[i].cannibalsRight == state.cannibalsRight)
            return true;
    }
    return false;
}

void printState(State state)
{
    cout << "Left Bank -> ";
    cout << state.missionariesLeft << " Missionaries, " << state.cannibalsLeft << " Cannibals, Boat: ";
    if (state.boat == 0)
        cout << "Left Bank -> ";
    else
        cout << "Right Bank -> ";
    cout << state.missionariesRight << " Missionaries, " << state.cannibalsRight << " Cannibals" << endl;
}

void printPath(State state)
{
    for (const State &s : state.path)
    {
        printState(s);
    }
    printState(state);
}

void solve(State currentState, vector<State> &visited)
{
    if (isGoalState(currentState))
    {
        printPath(currentState);
        return;
    }

    visited.push_back(currentState);

    for (int m = 0; m <= 2; ++m)
    {
        for (int c = 0; c <= 2; ++c)
        {
            if (m + c <= 2 && m + c > 0)
            {
                State nextState = currentState;
                if (currentState.boat == 0)
                {
                    nextState.missionariesLeft -= m;
                    nextState.cannibalsLeft -= c;
                    nextState.missionariesRight += m;
                    nextState.cannibalsRight += c;
                    nextState.boat = 1;
                }
                else
                {
                    nextState.missionariesLeft += m;
                    nextState.cannibalsLeft += c;
                    nextState.missionariesRight -= m;
                    nextState.cannibalsRight -= c;
                    nextState.boat = 0;
                }

                if (isValidState(nextState.missionariesLeft, nextState.cannibalsLeft) &&
                    isValidState(nextState.missionariesRight, nextState.cannibalsRight) &&
                    !isVisited(nextState, visited))
                {
                    nextState.path.push_back(currentState); // Add current state to the path
                    solve(nextState, visited);
                }
            }
        }
    }

    visited.pop_back();
}

int main()
{
    State initialState = {3, 3, 0, 0, 0};
    vector<State> visited;
    cout << "Possible Solutions:\n";
    solve(initialState, visited);
    return 0;
}
