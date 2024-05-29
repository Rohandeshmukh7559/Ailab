#include <iostream>
#include <vector>
#include <string>
#include <climits>

class Node
{
public:
    std::string name;
    int heuristic;
    int cost;
    bool isAndNode;
    std::vector<Node *> children;

    Node(std::string name, int heuristic, int cost, bool isAndNode)
        : name(name), heuristic(heuristic), cost(cost), isAndNode(isAndNode) {}

    void addChild(Node *child)
    {
        children.push_back(child);
    }
};

class AOStar
{
private:
    Node *startNode;
    Node *goalNode;

    int f(Node *node)
    {
        return g(node) + h(node);
    }

    int g(Node *node)
    {
        return node->cost;
    }

    int h(Node *node)
    {
        return node->heuristic;
    }

    void runAOStar(Node *node)
    {
        if (node == goalNode)
        {
            return;
        }

        if (node->children.empty())
        {
            return;
        }

        if (node->isAndNode)
        {
            int sumCost = 0;
            for (Node *child : node->children)
            {
                runAOStar(child);
                sumCost += f(child);
            }
            node->heuristic = sumCost;
        }
        else
        {
            Node *bestChild = nullptr;
            int minCost = INT_MAX;
            for (Node *child : node->children)
            {
                runAOStar(child);
                int currentCost = f(child);
                if (currentCost < minCost)
                {
                    minCost = currentCost;
                    bestChild = child;
                }
            }
            node->heuristic = minCost;
            node->children.clear();
            if (bestChild != nullptr)
            {
                node->addChild(bestChild);
            }
        }
    }

public:
    AOStar(Node *startNode, Node *goalNode) : startNode(startNode), goalNode(goalNode) {}

    Node *findPath()
    {
        runAOStar(startNode);
        return startNode;
    }

    void printSolution(Node *node, std::string indent = "")
    {
        if (node == nullptr)
        {
            return;
        }
        std::cout << indent << node->name << " (h=" << node->heuristic << ")" << std::endl;
        for (Node *child : node->children)
        {
            printSolution(child, indent + "  ");
        }
    }
};

int main()
{
    // Create nodes as per the given example
    Node A("A", INT_MAX, 0, false);
    Node B("B", 5, 1, false);
    Node C("C", 2, 1, true);
    Node D("D", 4, 1, false);
    Node E("E", 7, 1, false);
    Node F("F", 9, 1, false);
    Node G("G", 3, 1, false);
    Node H("H", 0, 1, false);
    Node I("I", 0, 1, false);
    Node J("J", 0, 1, false);

    // Build the AND-OR graph
    A.addChild(&B);
    A.addChild(&C);
    A.addChild(&D);
    B.addChild(&E);
    B.addChild(&F);
    C.addChild(&G);
    C.addChild(&H);
    C.addChild(&I);
    D.addChild(&J);

    // Set goal node
    Node *goalNode = &J;

    // Create an instance of AOStar and find the path
    AOStar aoStar(&A, goalNode);
    Node *path = aoStar.findPath();

    // Print the solution path
    std::cout << "Solution path:" << std::endl;
    aoStar.printSolution(path);

    return 0;
}
