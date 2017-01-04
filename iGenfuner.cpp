#include "iGenfuner.h"
#include "iRpn.h"

namespace Imaginer{
namespace Utils {
iGenFuner::iGenFuner(char *expname):_x(0),_y(0),_curpos(0),_expname(expname),_rpn(_expname)
{
    std::cout << _expname << std::endl;
    if(! _rpn.genRpn())
        return;
    else
        std::cout << "genrate RPN OK" << std::endl;
    //generater();
    //gen();
}

iGenFuner::sysFun iGenFuner::user1 = NULL;

iGenFuner::sysFun iGenFuner::user2 = NULL;

iGenFuner::sysFun iGenFuner::_sysfun[] =
{
    /*cmath provide such math funtion:*/
    self,   /*self(x)=x*/zero,    /*zero(x)=0*/ one,     /*one(x)=1*/  factorial,/*阶乘*/
    acos,   /*反余弦*/    asin,   /*反正弦*/      atan,   /*反正切*/      ceil,   /*上取整*/
    cos,    /*余弦*/      cosh,   /*双曲余弦*/    exp,    /*指数值*/      fabs,   /*绝对值*/
    floor,  /*下取整*/    log,    /*对数*/        log10,  /*对数*/        sin,    /*正弦*/
    sqrt,   /*开方*/      tan,    /*正切*/        user1,  /*自定义函数1*/  user2   /*自定义函数2*/
};

std::string       iGenFuner::_sysfunS[] =
{
    "self",   /*self(x)=x*/ "zero",   /*zero(x)=0*/ "one",     /*one(x)=1*/  "factorial",/*阶乘*/
    "acos",   /*反余弦*/    "asin",   /*反正弦*/      "atan",   /*反正切*/      "ceil",   /*上取整*/
    "cos",    /*余弦*/      "cosh",   /*双曲余弦*/    "exp",    /*指数值*/      "fabs",   /*绝对值*/
    "floor",  /*下取整*/    "log",    /*对数*/        "log10",  /*对数*/        "sin",    /*正弦*/
    "sqrt",   /*开方*/      "tan",    /*正切*/        "user1"  /*自定义函数1*/  "user2"   /*自定义函数2*/
};

void   iGenFuner::gen()
{
    _opstream.push(_funer(_funer::_add,3));
    _opstream.push(_funer(_funer::_mut,5));
    _opstream.push(_funer(_funer::_pow,2));
}

bool   iGenFuner::generater()
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

double iGenFuner::Parser(iStack<iRpn::RPNnode>& result,double x,int& curpos)
{
    int size = _operands->size();
    if(curpos > size)
        return 0;
    iRpn::RPNnode curnode;
    char op = '\0';
    iRpn::RPNnode  loperand;
    iRpn::RPNnode  roperand;
    double r  = 0;
    for(int& i = curpos;curnode != '$' && i <= size; ++i)
    {
        curnode = (*_operands)[i];
        if(!curnode)//opearator
        {
            op = curnode;
            if(_rpn.isVariable(op))
            {
                result.push(x);
                //std::cout << "unknowns nunber " << curnode << std::endl;
            }
            else
            {
                switch (op)
                {
                case '+':
                    roperand = result.pop();
                    loperand = result.pop();
                    result.push(loperand+roperand);
                    break;
                case '_':
                    result.push(-result.pop());
                    break;
                case '-':
                    roperand = result.pop();
                    loperand = result.pop();
                    result.push(loperand-roperand);
                    break;
                case '*':
                    roperand = result.pop();
                    loperand = result.pop();
                    result.push(loperand*roperand);
                    break;
                case '/':
                    roperand = result.pop();
                    loperand = result.pop();
                    result.push(loperand/roperand);
                    break;
                case '^':
                    roperand = result.pop();
                    loperand = result.pop();
                    result.push(pow(loperand,roperand));
                    break;
                case -128 ... FUN_INDEX_RANGE://function index
                    std::cout << "Function: " << _sysfunS[op+128] << std::endl;
                    Parser(result,x,++i);
                    r = result.pop();
                    //r = _sysfun[op+128](x);
                    result.push(_sysfun[op+128](r));
                    i--;
                    break;
                case '!':
                    result.push(factorial(result.pop()));
                    break;
                default:
                    std::cout << "invalid operator: " << op << std::endl;
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

double iGenFuner::generater(double x)
{
    iStack<iRpn::RPNnode> result;
    _operands = _rpn.getOperands();
    int start = 0;
    Parser(result,x,start);
    return result.top();
}

double iGenFuner::operator() (double x)
{
    std::cout << ">>>>>>>>>>>>>>> calculate: " << x << std::endl;
    return generater(x);
    /*
    size_t i = 0;
    size_t opsize = _opstream.size();
    while (i <= opsize)
    {
        _opstream[i](_y, x,_opstream[i].value());
        i++;
    }*/
    return _y;   
}

}//namespace Utils
}//namespace Imaginer
