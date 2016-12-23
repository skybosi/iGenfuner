#include "iGenfuner.h"
#include "iStack.h"
#include "iRpn.h"

using namespace Imaginer::Utils;
int main()
{
    //char xx[10];
    //1.2-2*((4+7)*6)+(1-5)
    iGenFuner gf("1.2-x*((4+7)*6)+(1-5)");
    std::cout << gf(3)<< std::endl;
    /*
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
    return 0;
}
