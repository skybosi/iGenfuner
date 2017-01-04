# iGenfuner
Imaginer-Generate-function-er =>(iGenfuner)  : Function generator and parser

- From this class name,you can know this a utils for Imaginer,It's use to parser(use RPN) a input string, maybe a math function or a math expression;
- From the parser result,must Generate a operate stream (op-stream), to save/record the function or expression Each step of the process;
- Then while you want to get a Special value(eg:1,2,3...),Will use the recorded op-stream, step-by-step calculation until the final results

## Example

1. expression:  `-1.2*3-3+3+sin(-x+4*3-3+(1+5))*cos(x+7)*6+(-5+1)`
    - change to RPN : `1.2  _  3  *  3  -  3  +  ? x  _  4  3  *  +  3  -  1  5  +  +  $  ? x  7  +  $  *  6  *  +  5  _  1  +  +`    
    - ===============> calculate: 6  result: -5.35615
    - ===============> calculate: 5  result: -10.3544

2. expression: `sin(-x+cos(cos(3+x)+6))+1+cos(-x)+3`
    - change to RPN : `? x  _  ? ? 3  x  +  $  6  +  $  +  $  1  +  ? x  _  $  +  3  +`
    - ===============> calculate: 6  result: 5.56602
    - ===============> calculate: 5  result: 5.09643
3. expression: `sin(x+cos(x))/3+9`
    - change to RPN : `? x  ? x  $  +  $  3  /  9  +  `
    - ===============> calculate: 6  result: 9.20882
    - ===============> calculate: 5  result: 8.7196

## NOTE

    At Example:

    RPN  expression have this letter:
    
    ?   function's index,because the index is < 0,so std::cout will show ?
    _   minus; minus sign; negative indication; negative sign;

## Function

- provide those function, but you can bind you function with user1 and user2

```c++
iGenFuner::sysFun iGenFuner::_sysfun[] =
{
    /*cmath provide such math funtion:*/
    self,   /*self(x)=x*/zero,    /*zero(x)=0*/  one,     /*one(x)=1*/  factorial,/*阶乘*/
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
```

- bind function method:

```c++
double you(double x)
{
    return cos(x)+5;
}

iGenFuner gf("sin(x+cos(x))/3+9");
gf.bind1(you);
std::cout <<  gf.User1()(4) << std::endl;
```

- bind1 with bind a function with user1;
- bind2 with bind a function with user2;
- User1 will get the user1 function you set;
- User2 will get the user2 function you set;

Here bind example with calculate cos(4)+5, and retuen result;

- `The function's index is get from here code to get:`

```c++
#define FUNNUM  20
#define FUN_INDEX_RANGE (-128+FUNNUM)

char   iRpn::getFun(std::string funname)
{
    char index = -1;
    while(++index < FUNNUM && funname != _sysfunS[index]);
    return (index - 128);
}
```
