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
At The Example:

RPN  expression have this letter:
- ? : function's index,because the index is < 0,so std::cout will show ?
- _ : minus; minus sign; negative indication; negative sign;
- $ : The end flag of the math function's arguments;

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
    "sqrt",   /*开方*/      "tan",    /*正切*/        "user1",  /*自定义函数1*/  "user2"   /*自定义函数2*/
};
```

- bind function usage:

    - `user1` & `user2` is Custom math function,you can set you want math function,but you need bind at first
Here is a example or usge;

    - NOTE:
    Here is just provide two entry:`user1` & `user2` ,you just bind with `bind1` to `user1`; `bind2` to `user2`.
You can get `user1` with `User1`,`user2` with `User2`. 
        - bind1 ： bind a function with user1;
        - bind2 ： bind a function with user2;
        - User1 ： get the user1 function you set;
        - User2 ： get the user2 function you set;

- Add [js version Genfuner](https://github.com/skybosi/wx-Canvas/tree/master/lib) for [wx-Canvas](https://github.com/skybosi/wx-Canvas),Just want to use at WeChat-small-program 
    - NOTE:The [binduser](https://github.com/skybosi/iGenfuner/blob/master/README.md#function) function is missing
```c++
//A example you Custom math function's implement
double you(double x)
{
    return cos(x)+5;
}
//======at main========
iGenFuner gf;
gf.bind1(you);                //bind you function with function point
gf.setExp("sin(x)+user1(x)"); //set expression for parser and generator
std::cout << "cos(4)+5: " << gf.User1()(4) << std::endl;
std::cout << "sin(4)+user1(4) = sin(4)+cos(4)+5: " << gf(4) << std::endl;
```
- Here bind example with calculate cos(4)+5, and retuen result;

## Function index
- `The function's index is get from here code :`

```c++
#define FUNNUM  20   //this is number of sysFun,now(2017-1-8 10:00),It's 20
#define FUN_INDEX_RANGE (-128+FUNNUM)

char   iRpn::getFun(std::string funname)
{
    char index = -1;
    while(++index < FUNNUM && funname != _sysfunS[index]);
    return (index - 128);
}
```
