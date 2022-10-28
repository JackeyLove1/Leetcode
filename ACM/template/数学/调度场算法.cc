#include <bits/stdc++.h>
/*
依次按顺序读入，
读到数字：直接输出；
读到左结合运算符：如果栈顶的运算符优先级不低于该运算符，则输出栈顶运算符并使之出栈，直到栈空或不满足上述条件为止；然后入栈；
读到右结合运算符：如果栈顶的运算符优先级高于该运算符，则输出栈顶运算符并使之出栈，直到栈空或不满足上述条件为止；然后入栈；
读到左括号：直接入栈；
读到右括号：输出栈顶运算符并使之出栈，直到栈顶为左括号为止；令左括号出栈。
当读入完毕时，依次输出并弹出栈顶运算符，直到栈被清空
*/
using namespace std;
// 这里定义Token主要是为了使数字和运算符可以存到同一个容器里
// 其实op和num同时只用得上一个值，但用Union的话，判断类型反而麻烦。C++17的话可以考虑std::variant
struct Token 
{
    char op;
    int num;
};
map<char, int> pre{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}}; // 优先级
int main()
{
    string expr;
    vector<Token> infix, suffix;
    stack<Token> oper;
    cin >> expr;
    for (auto c : expr) // 将字符串解析成若干Token存入vector
    {
        if (isdigit(c))
            infix.push_back(Token{0, c - '0'});
        else
            infix.push_back(Token{c, 0});
    }
    for (auto t : infix)
    {
        if (!t.op)
            suffix.push_back(t);
        else if (t.op == '(')
            oper.push(t);
        else if (t.op == ')')
        {
            while (!oper.empty() && oper.top().op != '(')
            {
                suffix.push_back(oper.top());
                oper.pop();
            }
            oper.pop();
        }
        else
        {
            while (!oper.empty() && pre[oper.top().op] >= pre[t.op])
            {
                suffix.push_back(oper.top());
                oper.pop();
            }
            oper.push(t);
        }
    }
    while (!oper.empty())
    {
        suffix.push_back(oper.top());
        oper.pop();
    }
    // 这里对后缀表达式的计算，因为要输出中间结果，就直接开二重循环了，没有使用栈
    while (suffix.size() > 1)
    {
        for (auto t : suffix)
            if (t.op)
                cout << t.op << " ";
            else
                cout << t.num << " ";
        cout << endl;
        for (int i = 2; i < suffix.size(); ++i)
        {
            int res;
            Token a = suffix[i - 2], b = suffix[i - 1];
            switch (suffix[i].op)
            {
            case 0:
                continue;
            case '+':
                res = a.num + b.num;
                break;
            case '-':
                res = a.num - b.num;
                break;
            case '*':
                res = a.num * b.num;
                break;
            case '/':
                res = a.num / b.num;
                break;
            case '^':
                res = pow(a.num, b.num);
                break;
            }
            suffix.insert(suffix.begin() + i + 1, Token{0, res});
            suffix.erase(suffix.begin() + i - 2, suffix.begin() + i + 1);
            break;
        }
    }
    cout << suffix[0].num; // 输出最后结果
    return 0;
}