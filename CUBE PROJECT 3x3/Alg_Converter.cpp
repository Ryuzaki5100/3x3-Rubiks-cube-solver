#include <bits/stdc++.h>
using namespace std;
map<char, int> repetitions = {{'2', 2}, {'\'', 3}};
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
int main()
{
    string alg;
    getline(cin, alg);
    cout << translate(alg);
}