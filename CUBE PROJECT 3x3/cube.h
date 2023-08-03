#include <bits/stdc++.h>
using namespace std;
map<int, string> notation = {{1, ""}, {2, "2"}, {3, "'"}};
map<char, int> repetitions = {{'2', 2}, {'\'', 3}};
map<char, vector<vector<int>>> moveEdges = {{'R', {{2, 5, 10, 6}, {3, 2, -3, -2}}}, {'U', {{0, 1, 2, 3}, {2, 1, -2, -1}}}, {'F', {{3, 6, 11, 7}, {3, 1, -3, -1}}}, {'B', {{1, 4, 9, 5}, {1, 3, -1, -3}}}, {'D', {{8, 11, 10, 9}, {1, 2, -1, -2}}}, {'L', {{0, 7, 8, 4}, {2, 3, -2, -3}}}};
map<char, map<int, int>> nextOrientation = {{'R', {{3, 2}, {2, -3}, {-3, -2}, {-2, 3}}}, {'U', {{2, 1}, {1, -2}, {-2, -1}, {-1, 2}}}, {'F', {{3, 1}, {1, -3}, {-3, -1}, {-1, 3}}}, {'B', {{1, 3}, {3, -1}, {-1, -3}, {-3, 1}}}, {'D', {{1, 2}, {2, -1}, {-1, -2}, {-2, 1}}}, {'L', {{2, 3}, {3, -2}, {-2, -3}, {-3, 2}}}};
map<char, map<int, int>> nextEdgePosition = {{'R', {{2, 5}, {5, 10}, {10, 6}, {6, 2}}}, {'U', {{0, 1}, {1, 2}, {2, 3}, {3, 0}}}, {'F', {{3, 6}, {6, 11}, {11, 7}, {7, 3}}}, {'B', {{1, 4}, {4, 9}, {9, 5}, {5, 1}}}, {'D', {{8, 11}, {11, 10}, {10, 9}, {9, 8}}}, {'L', {{0, 7}, {7, 8}, {8, 4}, {4, 0}}}};
map<char, map<int, int>> nextCornerPosition = {{'R', {{1, 5}, {5, 6}, {6, 2}, {2, 1}}}, {'U', {{0, 1}, {1, 2}, {2, 3}, {3, 0}}}, {'F', {{2, 6}, {6, 7}, {7, 3}, {3, 2}}}, {'B', {{0, 4}, {4, 5}, {5, 1}, {1, 0}}}, {'D', {{4, 7}, {7, 6}, {6, 5}, {5, 4}}}, {'L', {{0, 3}, {3, 7}, {7, 4}, {4, 0}}}};
map<int, vector<string>> crossAlgo[12] = {{{3, {"UUUFF", "UUUFF", "UUUFF", "UUUFF"}}, {-1, {"LFFF", "LFFFLLL", "LFFFLLL", "LFFFLLL"}}},
                                          {{2, {"URRRF", "URRRF", "URRRF", "URRRFR"}}, {3, {"UUFF", "UUFF", "UUFF", "UUFF"}}},
                                          {{1, {"RRRF", "RRRF", "RRRF", "RRRFR"}}, {3, {"UFF", "UFF", "UFF", "UFF"}}},
                                          {{-2, {"UUURRRF", "UUURRRF", "UUURRRF", "ULFFFLLL"}}, {3, {"FF", "FF", "FF", "FF"}}},
                                          {{2, {"LLLD", "DDDLLLD", "DDDLLLD", "DDDLLLD"}}, {-1, {"BDD", "DDBDD", "DDBDD", "DDBDD"}}},
                                          {{2, {"RDDD", "DRDDD", "DRDDD", "DRDDD"}}, {1, {"BBBDD", "DDBBBDD", "DDBBBDD", "DDBBBDD"}}},
                                          {{-2, {"RRRDDD", "DRRRDDD", "DRRRDDD", "DRRRDDD"}}, {1, {"F", "F", "F", "F"}}},
                                          {{-1, {"FFF", "FFF", "FFF", "FFF"}}, {-2, {"LD", "DDDLD", "DDDLD", "DDDLD"}}},
                                          {{-3, {"D", "D", "D", ""}}, {-1, {"LLLFFF", "D", "D", ""}}},
                                          {{-3, {"DD", "BDDBBBDD", "D", ""}}, {2, {"DDDRF", "BDRDDD", "D", ""}}},
                                          {{-3, {"DDD", "RDRRRDDD", "RDRRRDDD", ""}}, {1, {"RF", "RF", "RF", ""}}},
                                          {{-3, {"", "", "", ""}}, {-2, {"DRF", "FFFDRRRDDD", "FFFDRRRDDD", "FFFDRRRDDD"}}}};
map<int, vector<string>> firstLayerAlgo[8] = {{{3, {"LLULLUUULL", "URRUUURRURR", "UURRURRUUURR", "UUULLUUULLULL"}}, {2, {"ULUUULLL", "URRRUUUR", "RUURRR", "UUULLLUUUL"}}, {-1, {"LULLL", "RRRUR", "UURURRR", "UULLLUL"}}},
                                              {{3, {"UUULLULLUUULL", "RRUUURRURR", "URRURRUUURR", "UULLUUULLULL"}}, {1, {"LUUULLL", "RRRUUUR", "UUURUURRR", "UULLLUUUL"}}, {2, {"UUULULLL", "UUURRRUR", "URURRR", "ULLLUL"}}},
                                              {{3, {"UULLULLUUULL", "UUURRUUURRURR", "RRURRUUURR", "ULLUUULLULL"}}, {-2, {"UUULUUULLL", "UUURRRUUUR", "UURUURRR", "ULLLUUUL"}}, {1, {"UULULLL", "UURRRUR", "RURRR", "LLLUL"}}},
                                              {{3, {"ULLULLUUULL", "UURRUUURRURR", "UUURRURRUUURR", "LLUUULLULL"}}, {-1, {"UULUUULLL", "UURRRUUUR", "RUUURRR", "LLLUUUL"}}, {-2, {"ULULLL", "URRRUR", "UUURURRR", "UUULLLUL"}}},
                                              {{2, {"LUUULLLULUUULLL", "LURRUUURRURRLLL", "LUURRURRUUURRLLL", "LUUULLLUUULLLUUUL"}}, {-3, {"", "LURRRUUURLLL", "LRUURRRLLL", "LULLLUULLLUUUL"}}, {-1, {"LULLLUUULULLL", "LRRRURLLL", "LUURURRRLLL", "LULLUUL"}}},
                                              {{2, {"RRRUUULLULLUUULL", "RRRURUUURRRUR", "RRRURURURRR", "RRRUULLUUULLULLR"}}, {1, {"RRRLUUULLLR", "RRRUUURURRRUUUR", "RRRUUURRUURRR", "RRRUULLLUUULR"}}, {-3, {"RRRUUULULLLR", "", "RRRURUURUUURRR", "RRRULLLULR"}}},
                                              {{-2, {"RUULLULLUUULLRRR", "RUUURRRUUURRRUUUR", "RUUURRRURUUURRR", "RULLUUULLULLRRR"}}, {-3, {"RUUULUUULLLRRR", "RURRRUURRRUUUR", "", "RULLLUUULRRR"}}, {1, {"RUULULLLRRR", "RURRUUR", "RURRRUUURURRR", "RLLLULRRR"}}},
                                              {{-2, {"LLLULULULLL", "LLLUURRUUURRURRL", "LLLUUURRURRUUURRL", "LLLULUUULLLUL"}}, {-1, {"LLLUUULLUULLL", "LLLUURRRUUURL", "LLLURUURRRL", "LLLUUULULLLUUUL"}}, {-3, {"LLLUUULUULULLL", "LLLURRRURL", "LLLUUURURRRL", ""}}}};
class Cube
{
public:
    vector<vector<int>> edge;
    vector<vector<int>> corner;
    Cube()
    {
        edge = {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 2}, {5, 2}, {6, -2}, {7, -2}, {8, -3}, {9, -3}, {10, -3}, {11, -3}};
        corner = {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, -3}, {5, -3}, {6, -3}, {7, -3}};
    }
    Cube(vector<vector<int>> E, vector<vector<int>> C)
    {
        edge = E;
        corner = C;
    }
    void move(char a)
    {
        for (int i = 0; i < 12; i++)
        {
            if (nextEdgePosition[a].count(edge[i][0]))
            {
                edge[i][0] = nextEdgePosition[a][edge[i][0]];
                if (nextOrientation[a].count(edge[i][1]))
                    edge[i][1] = nextOrientation[a][edge[i][1]];
            }
        }
        for (int i = 0; i < 8; i++)
        {
            if (nextCornerPosition[a].count(corner[i][0]))
            {
                corner[i][0] = nextCornerPosition[a][corner[i][0]];
                if (nextOrientation[a].count(corner[i][1]))
                    corner[i][1] = nextOrientation[a][corner[i][1]];
            }
        }
    }
    void performAlgorithm(string algorithm)
    {
        for (int i = 0; i < algorithm.length(); i++)
            move(algorithm[i]);
    }
    string performCrossPiece(int x, int i)
    {
        string algorithm = crossAlgo[edge[x][0]][edge[x][1]][i];
        performAlgorithm(algorithm);
        return algorithm;
    }
    string performCross()
    {
        string algorithm = "";
        algorithm += performCrossPiece(10, 0) + "DDD";
        performAlgorithm("DDD");
        algorithm += performCrossPiece(9, 1) + "DDD";
        performAlgorithm("DDD");
        algorithm += performCrossPiece(8, 2) + "DDD";
        performAlgorithm("DDD");
        algorithm += performCrossPiece(11, 3);
        return algorithm;
    }
    bool isCrossSolved()
    {
        Cube a;
        for (int i = 8; i <= 11; i++)
            if (a.edge[i] != edge[i])
                return false;
        return true;
    }
    string performfirstLayerPiece(int x)
    {
        string algorithm = firstLayerAlgo[corner[x][0]][corner[x][1]][x - 4];
        performAlgorithm(algorithm);
        return algorithm;
    }
    string performFirstLayer()
    {
        string algorithm = "";
        for (int i = 4; i <= 7; i++)
            algorithm += performfirstLayerPiece(i);
        return algorithm;
    }
    void printCubeCorners()
    {
        cout << "Corners -- > {";
        for (int i = 0; i < 8; i++)
            printf(" { %d, %d }", corner[i][0], corner[i][1]);
        cout << " }\n";
    }
    void printCubeEdge()
    {
        cout << "Edges -- > {";
        for (int i = 0; i < 12; i++)
            printf(" { %d, %d }", edge[i][0], edge[i][1]);
        cout << " }\n";
    }
    void printCubeStats()
    {
        cout << endl;
        printCubeEdge();
        printCubeCorners();
        cout << endl;
    }
};
vector<string> convert(string input)
{
    stack<char> temp;
    vector<string> result;
    input += " ";
    for (int i = 0; i < input.length(); i++)
    {
        if (temp.empty() || temp.top() == input[i])
            temp.push(input[i]);
        else
        {
            int n = 0;
            char x = temp.top();
            while (!temp.empty() && temp.top() == x)
            {
                n++;
                temp.pop();
            }
            for (int i = 0; i < n % 4; i++)
                temp.push(x);
            temp.push(input[i]);
        }
    }
    while (!temp.empty())
    {
        int n = 0;
        char x = temp.top();
        while (!temp.empty() && temp.top() == x)
        {
            n++;
            temp.pop();
        }
        result.push_back(x + notation[n]);
    }
    reverse(result.begin(), result.end());
    result.pop_back();
    return result;
}
bool isAmong(char a, string s)
{
    for (int i = 0; i < s.length(); i++)
        if (s[i] == a)
            return true;
    return false;
}
string translate(string alg)
{
    string res = "";
    for (int i = 0; i < alg.length(); i++)
        if (!isAmong(alg[i], "()[]{} "))
            res += alg[i];
    string temp = "";
    stack<char> s;
    for (int i = res.length() - 1; i >= 0; i--)
        if (isAmong(res[i], "2'"))
        {
            for (int j = 0; j < repetitions[res[i]]; j++)
                s.push(res[i - 1]);
            i--;
        }
        else
            s.push(res[i]);
    while (!s.empty())
    {
        temp += s.top();
        s.pop();
    }
    return temp;
}
void printAlgorithm(vector<string> alg)
{
    for (auto i : alg)
        cout << i << " ";
    cout << endl;
}
string simplify(string alg)
{
    vector<string> algo = convert(alg);
    string p = "";
    for (int i = 0; i < algo.size(); i++)
        p += algo[i];
    return translate(p);
}
string simplify(vector<string> algo)
{
    string p = "";
    for (int i = 0; i < algo.size(); i++)
        p += algo[i];
    return translate(p);
}
int devilNumber(string alg)
{
    Cube a, b;
    int i = 0;
    do
    {
        b.performAlgorithm(alg);
        i++;
        if (a.edge == b.edge && a.corner == b.corner)
            break;
    } while (true);
    return i;
}