#include "iGenfuner.h"
#include "iStackInfix.h"
using namespace Imaginer::Utils;
int main()
{
    char xx[10];
    iGenFuner gf("1+1+3+4");
    std::cout << gf(6)<< std::endl;
    //iStackInfix s("((1-3)*5)+(9-3)");
    //std::cout << s.Parser();
    return 0;
}
