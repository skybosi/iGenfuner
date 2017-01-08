#include "iGenfuner.h"
#include "iStack.h"
#include "iRpn.h"
#include "iReParser.h"
using namespace Imaginer::Utils;

double   gen2(std::string exp,double x)
{
    char cur = '\0';
    int i = 0;
    int num = 0;
    while((cur = exp[i++]))
    {
        switch (cur) {
        case '0' ... '9':
            num = cur - '0';
            break;
        case '+':
            (num)?(x+=num):(x += 1);
            num = 0;
            break;
        case '-':
            (num)?(x-=num):(x -= 0);
            num = 0;
            break;
        case '*':
            (num)?(x*=num):(x *= 1);
            num = 0;
            break;
        case '/':
            (num)?(x/=num):(x /= 1);
            num = 0;
            break;
        default:
            break;
        }
    }
    return x;
}

double you(double x)
{
    return cos(x)+5;
}

int main()
{
    /*
    std::cout << "Testing iRpn&iGenfuner " << std::endl;
    iGenFuner gf("-1.2*3-3+3+sin(-x+4*3-3+(1+5))*cos(x+7)*6+(-5+1)");
    iGenFuner gf("sin(-x+cos(cos(3+x)+6))+1+cos(-x)+3");
    iGenFuner gf("sin(x+cos(x))/3+9");
    iGenFuner gf("sin(-x+4*3-3+cos(1+5))");
    iGenFuner gf("sin(-x+3");
    std::cout << gf(6)<< std::endl;
    std::cout << gf(5)<< std::endl;
    */

    std::cout << "Testing bind1&user1 " << std::endl;
    iGenFuner gf;
    gf.bind1(you);
    gf.genRpn("1+user1(x)");
    std::cout <<  gf.User1()(4) << std::endl;
    std::cout <<  gf(4) << std::endl;

    /*
    std::cout << "Testing iStack " << std::endl;
    iStack<int> stack;
    int i = 0;
    while(i < 10)
    {
        stack.push(i++);
    }
    std::cout << stack << std::endl;
    iRpn rpn("1.2-x*((4+7)*6)+(1-5)");
    rpn.genRpn();
    rpn.Parser();
    */
    /*
    std::cout << "Testing parser:iReParser " << std::endl;
    iReParser ip("1.2-2 + tan(x)+ sin(x)");
    try
    {
        ip.parser2();
        std::cout << ip.parser() << std::endl;
    }
    catch(ParserException& e)
    {
        std::cout << e.what() << std::endl;
    }
    */
    /*
    std::cout << "Testing parser:iRpn " << std::endl;
    iRpn rpn("1.2-x*((x+7)*6)+(1+5)");
    rpn.genRpn();
    rpn.Parser();
    */
    return 0;
}
