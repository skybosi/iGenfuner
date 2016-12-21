#include <ctype.h>
#include <cmath>
#include "iRpn.h"

namespace Imaginer{
namespace Utils {

iRpn::iRpn(char* expname):_expnames(expname)
{
    _operator = new iStack<char>;
    _operator->push('#');
    _operands = new iStack<RPNnode>;
}

iRpn::~iRpn()
{
    (_operator) ? (delete _operator,_operator = NULL) : (_operator);
    (_operands) ? (delete _operands,_operands = NULL) : (_operands);
}

bool iRpn::cmpPRI(char cursign)
{
    //must >  not >=
    return (getPRI(cursign) > getPRI(_operator->top())) ? true :false;
}

int iRpn::getPRI(char cursign)
{
    switch (cursign) {
    case '+':case '-':
        return 0;
        break;
    case '*':case '/':
        return 1;
        break;
    case '^':
        return 2;
        break;
    case ')':
        return 3;
        break;
    case '#':case '(':
        return -1;
        break;
    default:
        return -1;
        break;
    }
}

void iRpn::genRpn()
{
    char cur = '\0';
    bool ispoint = false, isnum = false;
    double number = 0,expn = 0;
    while(cur = next())
    {
        if(isspace(cur))continue;
        switch (cur)
        {
        case '.':
            if(ispoint)
            {
                //throw FexpException("function expression invaild, mutil '.'");
                std::cout << "function expression invaild, mutil '.'" << std::endl;
            }else{
                ispoint = true;
                expn = 0.1;
            }
            break;
        case '0' ... '9':
            if (ispoint)
            {
                number = number + expn * (cur - '0');
                expn *= 0.1;
            }else{
                number = number * 10 + (cur - '0');
            }
            isnum = true;
            break;
        case '+':case '-':
        case '*':case '/':
        case '^':
            if(isnum)//operand get finish
            {
                _operands->push(number);
                number = 0;
                ispoint = isnum = false;
            }
            if(cmpPRI(cur))// PRI(cur) >= PRI(topsign)
            {
                _operator->push(cur);
            }
            else
            {
                while(!cmpPRI(cur))
                {
                    _operands->push(_operator->pop());
                }
                _operator->push(cur);
            }
            break;
        case '(':
            _operator->push(cur);
            break;
        case ')':
            if(isnum)//operand get finish
            {
                _operands->push(number);
                number = 0;
                ispoint = isnum = false;
            }
            while(_operator->top() != '(')
            {
                _operands->push(_operator->pop());
            }
            _operator->pop();//丢弃')'对应的首个'('
            break;
        case 'x':case 'X':
        case 'y':case 'Y':
            _operands->push(cur);
            break;
        default:
            break;
        }
    }
    while(_operator->size() > 0)
    {
        _operands->push(_operator->pop());
    }
    //std::cout << *_operands << std::endl;
    //std::cout << (_operands->reverse()) << std::endl;
}

void iRpn::Parser(iGenFuner& genfuner)
{
    genRpn();
    //_operands->reverse();
    iStack<RPNnode> result;
    int size = _operands->size();
    int i = 0;
    RPNnode curnode;
    char op = '\0';
    double  loperand = 0;
    double  roperand = 0;
    while(i <= size)
    {
        curnode = (*_operands)[i];
        //std::cout << curnode << "\n";
        if(!curnode)//opearator
        {
            if(curnode == 'x')
            {
                std::cout << "unknowns nunber " << curnode << std::endl;
            }
            else
            {
                op = curnode;
                loperand = result.pop();
                roperand = result.pop();
                switch (op)
                {
                case '+':
                    result.push(roperand+loperand);
                    break;
                case '-':
                    result.push(roperand-loperand);
                    break;
                case '*':
                    result.push(roperand*loperand);
                    break;
                case '/':
                    result.push(roperand/loperand);
                    break;
                case '^':
                    result.push(pow(roperand,loperand));
                    break;
                default:
                    std::cout << "invalid operator" << std::endl;
                    break;
                }
            }
        }
        else//operand
        {
            result.push(curnode);
            std::cout << curnode << "\n";
        }
        i++;
    }
    std::cout << result << std::endl;
}

}//namespace Utils
}//namespace Imaginer
