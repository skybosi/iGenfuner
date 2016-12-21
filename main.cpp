#include "iGenfuner.h"
#include "iStackInfix.h"
#include "iRpn.h"
using namespace Imaginer::Utils;
int main()
{
    //char xx[10];
    iGenFuner gf("1+1+3+4");
    //std::cout << gf(6)<< std::endl;
    //iStackInfix s("((1-3)*5)+(9-3)");
    //std::cout << s.Parser();
    iRpn::iStack<int> stack;
    int i = 0;
    while(i < 10)
    {
        stack.push(i++);
    }
    //std::cout << stack << std::endl;
    iRpn rpn("1.2-2*((4+7)*6)+(1-5)");
    //rpn.genRpn();
    rpn.Parser(gf);
    return 0;
}
