#ifndef IREPARSER_H
#define IREPARSER_H
#include <iostream>
#include <string>
#include <cmath>

// Exception class for parser errors.

class ParserException
{
public:
    ParserException(){}
    ParserException(const char* str)
    {
        _msg = str;
    }
    ParserException(std::string str)
    {
        _msg = str;
    }
    ParserException(const ParserException& rhs)
    {
        _msg = rhs._msg;
    }
    inline std::string what(){return _msg;}
private:
    std::string _msg;
    //std::string _type;
};

class iReParser
{
private:
    typedef enum
    {
        // These are the types of syntax errors.
        SYNTAX,       // syntax error
        NOMATCH,      // not match bracket
        NOEXPS,       // not a vaild expression
        DIVZERO,      // div a 0
        // These are the token types.
        NOTOKEN,      // init a token
        OPERATOR,     // is operator
        FUNCTION,     // is a math fuction
        VARIABLE,     // is variable
        NUMBERS,      // is number(double)
    }Token;
private:
    // This token indicates end-of-expression.
    std::string   EOE = "$";
    std::string   _exp;      // refers to expression string
    unsigned int  _curIdx;   // current index into the expression
    std::string   _token;    // holds current token
    Token         _tokType;  // holds token's type
public:
    iReParser(std::string exp);
    double parser();
    void   parser2();
private:
    double add_sub();
    double mul_div();
    double pows();
    double plus_minus();
    double brackets();
    double atom();
private:
    Token  nextToken();
    bool   operater(char c);
    bool   letter(char ch);
    bool   digit(char ch);
    void   handleErr(int error);
};

#endif // IREPARSER_H
