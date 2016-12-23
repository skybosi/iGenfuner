#include "iGenfuner.h"
#include "iRpn.h"

namespace Imaginer{
namespace Utils {
iGenFuner::iGenFuner(char *expname):_x(0),_y(0),_curpos(0),_expname(expname)
{
    //generater();
}

bool iGenFuner::generater()
{
    iRpn rpn(_expname);
    if(! rpn.genRpn())
        return false;
    iStack<iRpn::RPNnode> result;
    iStack<iRpn::RPNnode>* _operands = rpn.getOperands();
    int size = _operands->size();
    iRpn::RPNnode curnode;    
    char op = '\0';
    bool haveXY = false;
    iRpn::RPNnode  loperand;
    iRpn::RPNnode  roperand;
    double  value = 0;
    bool top_bottom = false;//flag to record a unkowns value is top(true) or bottom(false)
    for(int i = 0;i <= size; ++i)
    {
        curnode = (*_operands)[i];
        if(!curnode)//opearator
        {
            op = curnode;
            if(rpn.isVariable(op))//未知数
            {
                haveXY = true;
                result.push(op);
                if(!result.empty())
                {
                    top_bottom = true;
                }
            }else
            {
                if(result.size() < 1)
                {
                    std::cout << "expression invaild: " << op  <<
                                 " need two operands" << std::endl;
                    return false;
                }
                loperand = result.pop();
                roperand = result.pop();
                switch (op) {
                case '+':
                    if(haveXY)
                    {
                        if(top_bottom)
                            _opstream.push(_funer(_funer::_add,loperand));
                        else
                            _opstream.push(_funer(_funer::_add,loperand));
                        break;
                    }
                    result.push(loperand+roperand);
                    break;
                case '-':
                    if(haveXY)
                    {
                        if(top_bottom)
                            _opstream.push(_funer(_funer::_add,loperand));
                        else
                            _opstream.push(_funer(_funer::_add,loperand));
                        break;
                    }
                    result.push(loperand-roperand);
                    break;
                case '*':
                    if(haveXY)
                    {
                        if(top_bottom)
                            _opstream.push(_funer(_funer::_add,loperand));
                        else
                            _opstream.push(_funer(_funer::_add,loperand));

                        break;
                    }
                    result.push(loperand*roperand);
                    break;
                case '/':
                    if(haveXY)
                    {
                        if(top_bottom)
                            _opstream.push(_funer(_funer::_add,loperand));
                        else
                            _opstream.push(_funer(_funer::_add,loperand));
                        break;
                    }
                    result.push(loperand/roperand);
                    break;
                case '^':
                    if(haveXY)
                    {
                        if(top_bottom)
                            _opstream.push(_funer(_funer::_add,loperand));
                        else
                            _opstream.push(_funer(_funer::_add,loperand));
                        break;
                    }
                    result.push(loperand^roperand);
                    break;
                default:
                    break;
                }
            }
        }
        else//operand
        {
            result.push(curnode);
            std::cout << curnode << "\n";
        }
    }
    std::cout << result << std::endl;
    //result.destroy();
    return true;
}

double   iGenFuner::generater(double x)
{
    iRpn rpn(_expname);
    if(! rpn.genRpn())
        return false;
    iStack<iRpn::RPNnode> result;
    iStack<iRpn::RPNnode>* _operands = rpn.getOperands();
    int size = _operands->size();
    iRpn::RPNnode curnode;
    char op = '\0';
    double  loperand = 0;
    double  roperand = 0;
    for(int i = 0;i <= size; ++i)
    {
        curnode = (*_operands)[i];
        if(!curnode)//opearator
        {
            op = curnode;
            if(rpn.isVariable(op))
            {
                result.push(x);
                //std::cout << "unknowns nunber " << curnode << std::endl;
            }
            else
            {
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
            //std::cout << curnode << "\n";
        }
    }
    return result.top();
}

double iGenFuner::operator() (double x)
{
    return generater(x);
    /*
    size_t i = 0;
    size_t opsize = _opstream.size();
    while (i <= opsize)
    {
        _opstream[i](_y, x,_opstream[i].value());
        i++;
    }
    return _y;
    */
}

}//namespace Utils
}//namespace Imaginer
