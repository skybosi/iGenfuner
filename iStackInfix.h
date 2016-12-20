/*
 * This is a class That parser a function expression,and  use to generate a opearator stream
 * After use the op-stream to get each number's function value;
 *
 */
#ifndef ISTACKINFIX_H
#define ISTACKINFIX_H
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "iGenfuner.h"

namespace Imaginer{
namespace Utils {

//function expression
class FexpException
{
public:
    FexpException():_msg("FexpException function expression invaild :(\n"){}
    FexpException(std::string str):_msg(str){}
    FexpException(const FexpException& rhs):_msg(rhs._msg){}
    virtual ~FexpException() throw(){}
    std::string what()const{return _msg;}
private:
    std::string _msg;
};

class iStackInfix
{
private:
    #define MAXSIZE 1024
    // 数字栈
    typedef struct operand
    {
        double data[MAXSIZE];
        int    top;
    } OPERAND;

    // 运算符栈
    typedef struct operate
    {
        char data[MAXSIZE];
        int  top;
    } OPERATE;

private:
    // 初始化栈
    #define Init(StackType, stack)                          \
    do{                                                     \
        *stack = (StackType *)malloc(sizeof(StackType));	\
        *stack->top = -1;	                                \
    }while(0);

    // 判栈空
    #define Empty(stack)  (stack->top == -1)

    // 判栈满
    #define Full(stack)	  (stack->top == MAXSIZE - 1)

    // 入栈
    #define Push(stack, value)                  \
    do{	                                        \
        if (!Full(stack)){	                    \
            stack->top++;	                    \
            stack->data[stack->top] = value;    \
        }	                                    \
        else{	                                \
            printf("栈已满,无法入栈\n");	        \
            exit(-1);	                        \
        }	                                    \
    }while(0);

    // 出栈
    #define Pop(stack, value)	                \
    do{	                                        \
        if (!Empty(stack)){	                    \
            *value = stack->data[stack->top];	\
            stack->top--;	                    \
        }	                                    \
        else{	                                \
            printf("栈已空,无法出栈\n");	        \
            exit(-1);	                        \
        }	                                    \
    }while(0);

    // 取栈顶元素
    #define Top(stack, value)	                \
    do{	                                        \
        if (!Empty(stack)){	                    \
            *value = stack->data[stack->top];	\
        }	                                    \
        else{	                                \
            printf("栈为空,无法取栈顶元素\n");	    \
        }	                                    \
    }while(0);
private:
    OPERATE* _sign;
    OPERAND* _number;
    char   * _expname;
public:
    iStackInfix(char* expname);
    ~iStackInfix();
    double Parser(void);
private:
    char   PRICMP(char cur, char top);
    inline char next(){return /*_expname[_curpos++]*/ *_expname++;}
    inline char prev(){return /*_expname[_curpos--]*/ *_expname--;}
};

}//namespace Utils
}//namespace Imaginer

#endif // ISTACKINFIX_H
