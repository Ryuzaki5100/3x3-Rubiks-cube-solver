#include <bits/stdc++.h>
#include "cube.h"
using namespace std;
class Branches
{
public:
    Cube cube;
    string alg;
    Branches(Cube a, string x)
    {
        cube = a;
        alg = x;
        cube.performAlgorithm(x);
    }
    Branches(Branches a, string x)
    {
        cube = a.cube;
        cube.performAlgorithm(x);
        alg = a.alg + x;
    }
};
vector<string> possibilities = {"R", "U", "F", "B", "L", "D"};
vector<string> nott = {"", "2", "'"};
map<string, int> storage;
string crossSolution(Cube cube)
{
    queue<Branches> q;
    q.push(Branches(cube, ""));
    while (!q.front().cube.isCrossSolved())
    {
        Branches temp = q.front();
        q.pop();
        if (storage.count(temp.alg) == 0)
        {
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (storage.count(simplify(translate(temp.alg + possibilities[i] + nott[j]))))
                        continue;
                    q.push(Branches(temp, translate(possibilities[i] + nott[j])));
                }
            }
            storage[temp.alg]++;
        }
    }
    return q.front().alg;
}
int main()
{
    Cube a;
    string alg;
    getline(cin, alg);
    alg = translate(alg);
    a.performAlgorithm(alg);
    printAlgorithm(convert(crossSolution(a)));
}
