#include <ctype.h>
#include "iStackInfix.h"

namespace Imaginer{
namespace Utils {
iStackInfix::iStackInfix(char* expname):_expname(expname)
{
    Init(OPERATE, &_sign);
    Init(OPERAND, &_number);
}

iStackInfix::~iStackInfix()
{
    if(_sign)
    {
        free(_sign);
        _sign = NULL;
    }
    if(_number)
    {
        free(_number);
        _number = NULL;
    }
}

char iStackInfix::PRICMP(char cur, char top)
{
    switch (cur)
    {
    case '+':
    case '-':
        if (top == '+' || top == '-' || top == '*' || top == '/')
            return '<';			// 扫描的小于栈顶
        else
            return '>';			// 扫描的大于栈顶
        break;
    case '*':
    case '/':
        if (top == '*' || top == '/')
            return '<';
        else
            return '>';
        break;
    case '(':
        if (top == ')')
        {
            throw FexpException("function expression invaild,'(' not match");
        }
        return '>';
        break;
    case ')':
        if (top == '(')
            return '=';
        else if (top == '#')
        {
            throw FexpException("function expression invaild,')' not match");
        }
        else
        {
            return '<';
        }
        break;
    case '#':
        return '<';
        break;
    }
    return '\0';
}

double iStackInfix::Parser(void)
{
    double result, loperand, roperand;
    double data = 0, expn;
    char cur, topSign;
    bool ispoint = false, isnum = false;
    Push(_sign, '#');
    cur = next();
    Top(_sign, &topSign);
    while (cur != '#' || topSign != '#')
    {
        if(isspace(cur))
        {
            cur = next();
            continue;
        }
        switch (cur) {
        case '.':
            if(ispoint)
            {
                throw FexpException("function expression invaild, mutil '.'");
            }else{
                ispoint = true;
                expn = 0.1;
            }
            cur = next();
            break;
        case '0' ... '9':
            if (ispoint)
            {
                data = data + expn * (cur - '0');
                expn *= 0.1;
            }else{
                data = data * 10 + (cur - '0');
            }
            isnum = true;
            cur = next();
            break;
        case '+':case '-':
        case '*':case '/':
        case '(':case ')':
        case '#':
            if (isnum)
            {
                Push(_number, data);
                isnum = false;
                ispoint = false;
                data = 0;
            }
            Top(_sign, &topSign);
            switch (PRICMP(cur, topSign))
            {
            case '<':			// 扫描运算符优先级小于栈顶元素
                Pop(_sign, &topSign);
                Pop(_number, &loperand);
                Pop(_number, &roperand);
                switch (topSign)
                {
                case '+':
                    result = roperand + loperand;
                    break;
                case '-':
                    result = roperand - loperand;
                    break;
                case '*':
                    result = roperand * loperand;
                    break;
                case '/':
                    result = roperand / loperand;
                    break;
                }
                Push(_number, result);
                break;
            case '>':			// 扫描运算符优先级大于栈顶元素
                Push(_sign, cur);
                cur = next();
                break;
            case '=':			// 扫描运算符为右括号,匹配到了左括号
                Pop(_sign, &topSign);
                cur = next();
                break;
            }
            break;
        case '\0':case '\n':
            cur = '#';
            break;
        default:
            throw FexpException("function expression invaild, invaild letter");
            break;
        }
        Top(_sign, &topSign);
    }
    Pop(_number, &result);	// 将结果从栈中取出来
    if (!Empty(_number))
    {					    // 如果取出后栈不为空则表示输入的表达式不正确
        throw FexpException("function expression invaild, operand is not empty");
    }
    return result;
}

}//namespace Utils
}//namespace Imaginer
