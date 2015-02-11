//
//  eval.cpp
//  eval
//


#include <string>
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;




int precedence(char a, char b);


char operation(const bool values[], char op1, char op2, char erator);
char operation(const bool values[], char op);

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    // INFIX CHECK: empty
    if (infix == "")
        return 1;
    
    // INFIX TO POSTFIX
    postfix = "";
    stack<char> opStack;
    
    // INFIX CHECK: tracking!
    char prevCh = ' ';
    char next;
    int k = 0;
    int opPar = 0;
    int clPar = 0;
    
    
    for (char& ch : infix)
    {
        if (k < infix.length())
            next = infix[k+1];
        else
            next = '9';
        
        switch (ch) {
            case '0': case '1':
            case '2': case '3':
            case '4': case '5':
            case '6': case '7':
            case '8': case '9':
                if (isdigit(prevCh)) // format check
                    return 1;
                postfix += ch;
                break;
            case '(':
                if (isdigit(prevCh)) // format check
                    return 1;
                opStack.push(ch);
                opPar++;
                break;
            case ')':
                if (!isdigit(prevCh) && prevCh != ')') // format check
                    return 1;
                while (opStack.top() != '(' && !opStack.empty()) {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.pop();
                clPar++;
                break;
            case '&':
            case '|':
                if (!isdigit(prevCh) && prevCh != ' ' && prevCh != ')') // format check
                    return 1;
                if (!isdigit(next) && next != '(' && next != '!' && next != ' ') // format check
                    return 1;
                while (!opStack.empty() && opStack.top() != '(' && (precedence(ch, opStack.top()) == 2 || precedence(ch, opStack.top() == 0))) {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                break;
            case '!':
                opStack.push(ch);
                break;
        }
        if (ch != ' ' && k < infix.length())
            prevCh = ch;
        
        k++;
        
    }
    // empty the stack into the postfix
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    // make sure all parens are paired
    if (opPar != clPar)
        return 1;
    
    // EVALUATE POSTFIX
    stack<char> opandStack;
    for (char& ch : postfix)
    {
        if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
            opandStack.push(ch);
        else {
            char operand1;
            operand1 = opandStack.top();
            opandStack.pop();
            
            if (ch == '&'){
                char operand2;
                operand2 = opandStack.top();
                opandStack.pop();
                
                opandStack.push(operation(values, operand1, operand2, ch));
            }
            if (ch == '|'){
                char operand2;
                operand2 = opandStack.top();
                opandStack.pop();
                
                opandStack.push(operation(values, operand1, operand2, ch));
            }
            if (ch == '!')
            {
                opandStack.push(operation(values, operand1));
            }
            
        }
    }
    
    result = values[opandStack.top() - '0'];
    return 0;
}

char operation(const bool values[], char op1, char op2, char erator)
{
    char truNum = '2';
    char falseNum = '2';
    for (char i = '0'; i <= '9'; i++) {
        if (values[i - '0'] == true)
            truNum = i;
        if (values[i - '0'] == false)
            falseNum = i;
        if ((truNum == '0' || truNum == '1') && (falseNum == '0' || falseNum == '1'))
            break;
    }
    int one = op1 - '0';
    int two = op2 - '0';
    if (erator == '&') {
        if (values[one] && values[one]) {
            return truNum;
        } else {
            return falseNum;
        }
    }
    else if (erator == '|') {
        if (values[one] || values[two]) {
            return truNum;
        }
        else {
            return falseNum;
        }
    }
    // should never make it down here
    return 0; // eehhhhhhhhh
}

char operation(const bool values[], char op)
{
    char truNum = '2';
    char falseNum = '2';
    for (char i = '0'; i <= '8'; i++) {
        if (values[i - '0'] == 1)
            truNum = i;
        else if (values[i - '0'] == 0)
            falseNum = i;
        if ((truNum == '0' || truNum == '1') && (falseNum == '0' || falseNum == '1'))
            break;
    }
    int only = op - '0';
    if (values[only])
        return falseNum;
    else
        return truNum;
}

int precedence(char a, char b)
{
    // !    &   |
    // 0 is equal precedence
    // 1 is first item
    // 2 is second item
    if (a == '!' && b == '!')
        return 0;
    else if (a == '!')
        return 1;
    else if (b == '!')
        return 2;
    else if (a == '&' && b == '&')
        return 0;
    else if (a == '|' && b == '|')
        return 0;
    else if (a == '&' && b == '|')
        return 1;
    else if (b == '&' && a == '|')
        return 2;
    return false;
}


int main()
{
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0  &&  pf == "43!03&&|"  &&  !answer);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
}