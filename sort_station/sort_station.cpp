#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

map<string, int> priority = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};

bool isNumber(const string& tok) 
{
    int length = tok.size();
    for (int i = 0; i < length; i++) 
    {
        if (!isdigit(tok[i]) && tok[i] != '.')
        {
            return false;
        }
    }
    if (!tok.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool hpriority(const string& op1, const string& op2)
{
    if (priority[op1] > priority[op2])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void convert(const string& exp) 
{
    vector<string> vec = {};
    stack<string> operators;
    stringstream ss(exp);
    string tok;

    while (ss >> tok) 
    {
        if (isNumber(tok))
        {
            vec.push_back(tok);
        }
        else if (priority.find(tok) != priority.end()) 
        {
            while (!operators.empty() && operators.top() != "(" && hpriority(operators.top(), tok)) 
            {
                vec.push_back(operators.top());
                operators.pop();
            }
            operators.push(tok);
        }
        else if (tok == "(") 
        {
            operators.push(tok);
        }
        else if (tok == ")") 
        {
            while (!operators.empty() && operators.top() != "(")
            {
                vec.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) 
            {
                operators.pop();
            }
        }
    }
    
    while (!operators.empty()) 
    {
        vec.push_back(operators.top());
        operators.pop();
    }

    for (size_t i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    return;
}

int main() 
{
    string exp1 = "1 + 2 * 3";
    string exp2 = "1 * 2 + 3";
    string exp3 = "1 + 2 * 3 / ( 4 - 5 ) * 6";
    string exp4 = "( 1 + 3 ) / 10 * 5 - ( ( 2 + 3 ) * 2 + 3 )";

    cout << "Выражение: " << exp1 << endl;
    convert(exp1);
    cout << "Выражение: " << exp2 << endl;
    convert(exp2);
    cout << "Выражение: " << exp3 << endl;
    convert(exp3);
    cout << "Выражение: " << exp4 << endl;
    convert(exp4);

    return 0;
}