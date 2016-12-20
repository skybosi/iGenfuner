#include "iGenfuner.h"
#include "iStackInfix.h"
namespace Imaginer{
namespace Utils {
iGenFuner::iGenFuner(char *expname):_x(0),_y(0),_curpos(0),_expname(expname)
{
    generater();
}

void iGenFuner::generater()
{
    try
    {
        iStackInfix ist(_expname);
        std::cout << ist.Parser() << std::endl;
    }catch(FexpException& e)
    {
        std::cout << e.what() << std::endl;
    }
    /*
    bool operate = false; //
    bool pri = false;     //优先级
    bool full = false;    //控制添加函数的标志
    double number = 0;
    bool isnum = false;
    char op = '\0';
    char cur = '\0';
    while (cur = next())
    {
        if(isspace(cur))
            continue;
        switch(cur)
        {
        case '0' ... '9':
            number = number*10 + cur - '0';
            continue;
            break;
        case 'x':case 'X':
            if (!operate)
                _opstream.push_back(_funer::_assign);
            break;
        case '+':case '-':
        case '*':case '/':
            operate = true;
            op = cur;
            continue;
            break;
        case '(':case ')':
            if(cur == '(')
                pri = true;
            else
                pri = false;
            break;
        }
      }
      */
}
/*
            if(operate)
            {
                switch (op) {
                case '+':
                    _opstream.push_back(_funer::_add);
                    break;
                case '-':
                    _opstream.push_back(_funer::_sub);
                    break;
                case '*':
                    if(!pri)
                        _opstream.push_back(_funer::_assign);
                    else
                        _opstream.push_back(_funer::_mut);
                    break;
                case '/':
                    _opstream.push_back(_funer::_div);
                    break;
                default:
                    break;
                }
                op = '\0';
                operate = false;
            }

 */

double iGenFuner::operator() (double x)
{
    size_t i = 0;
    size_t opsize = _opstream.size();
    while (i < opsize)
    {
        _opstream[i](_y, x,_opstream[i].value());
        i++;
    }
    return _y;
}

}//namespace Utils
}//namespace Imaginer
