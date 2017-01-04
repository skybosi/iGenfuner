#include <ctype.h>
#include "iReParser.h"

iReParser::iReParser(std::string exp):_exp(exp),_curIdx(0),_token(""),_tokType(NOTOKEN)
{
}

void   iReParser::parser2()
{
    switch (nextToken()) {
    case NOTOKEN:      // init a token
        std::cout << _curIdx << " current is not token" << std::endl;
        break;
    case OPERATOR:     // is operator
        std::cout << _curIdx << " current is operator:\t" << _token << std::endl;
        parser2();
        break;
    case FUNCTION:     // is a math fuction
        std::cout << _curIdx << " current is function:\t" << _token << std::endl;
        parser2();
        break;
    case VARIABLE:     // is variable
        std::cout << _curIdx << " current is variable:\t" << _token << std::endl;
        parser2();
        break;
    case NUMBERS:      // is number(double)
        std::cout << _curIdx << " current is numbers:\t" << atof(_token.c_str())  << std::endl;
        parser2();
        break;
    default:
        std::cout << _curIdx << " current is invalid token" << std::endl;
        break;
    }
}

double iReParser::parser()
{
    // Parser entry point.
    double result;
    _curIdx = 0;
    nextToken();
    if(_token == EOE)
        handleErr(NOEXPS); // no expression present
    // Parse and evaluate the expression
    result = add_sub();
    if(_token != EOE) // last _token must be EOE
        handleErr(SYNTAX);
    return result;
}

// Add or subtract two terms.
double iReParser::add_sub()
{
    char op;
    double result;
    double partialResult;
    result = mul_div();
    while((op = _token[0]) == '+' || op == '-') {
        nextToken();
        partialResult = mul_div();
        switch(op) {
        case '-':
            result = result - partialResult;
            break;
        case '+':
            result = result + partialResult;
            break;
        }
    }
    return result;
}

// Multiply or divide two factors.
double iReParser::mul_div()
{
    char op;
    double result;
    double partialResult;
    result = pows();
    while((op = _token[0]) == '*' ||
          op == '/' || op == '%') {
        nextToken();
        partialResult = pows();
        switch(op) {
        case '*':
            result = result * partialResult;
            break;
        case '/':
            if(partialResult == 0.0)
                handleErr(DIVZERO);
            result = result / partialResult;
            break;
        case '%':
            if(partialResult == 0.0)
                handleErr(DIVZERO);
            result = (int)result % (int)partialResult;
            break;
        }
    }
    return result;
}

// Process an exponent.
double iReParser::pows()
{
    double result;
    double partialResult;
    result = plus_minus();
    if(_token == "^")
    {
        nextToken();
        partialResult = pows();
        result = pow(result,partialResult);
    }
    return result;
}

// Evaluate a unary + or -.
double iReParser::plus_minus()
{
    double result;
    std::string op;
    op = "";
    if((_tokType ==  OPERATOR) &&
            (_token == "+" || _token == "-"))
    {
        op = _token;
        nextToken();
    }
    result = brackets();
    if(op == "-") result = -result;
    return result;
}

// Process a parenthesized expression.
double iReParser::brackets()
{
    double result;
    if(_token == "(") {
        nextToken();
        result = add_sub();
        if(_token != ")")
            handleErr(NOMATCH);
        nextToken();
    }
    else result = atom();
    return result;
}

// Get the value of a number.
double iReParser::atom()
{
    double result = 0.0;
    switch(_tokType) {
    case NUMBERS:
        result = atof(_token.c_str());
        nextToken();
        break;
    case VARIABLE:
        std::cout << _curIdx << " have a variable" << std::endl;
        //nextToken();
        break;
    case FUNCTION:
        //std::cout << _curIdx << " have a function" << std::endl;
        //nextToken();
        break;
    default:
        handleErr(SYNTAX);
        break;
    }
    return result;
}

// Handle an error.
void iReParser::handleErr(int error)
{
    std::string err[] = {
        "Syntax Error",
        "Unbalanced Parentheses",
        "No Expression Present",
        "Division by Zero"
    };
    throw ParserException(err[error]);
}

// Obtain the next _token.
iReParser::Token iReParser::nextToken()
{
    _tokType = NOTOKEN;
    _token = "";
    // Check for end of expression.
    if(_curIdx == _exp.size()) {
        _token = EOE;
    }
    // Skip over white space.
    while(_curIdx < _exp.size() &&
          isspace(_exp[_curIdx]))
        ++_curIdx;
    // Trailing whitespace ends expression.
    if(_curIdx == _exp.size()) {
        _token = EOE;
    }
    if(operater(_exp[_curIdx])) { // is operator
        _token += _exp[_curIdx++];
        _tokType = OPERATOR;
    }
    else if(letter(_exp[_curIdx])) { // is variable
        while(_curIdx < _exp.size() &&
              !operater(_exp[_curIdx])) {
            _token += _exp[_curIdx++];
        }
        if(_token.size() == 1)
            _tokType = VARIABLE;
        else
            _tokType = FUNCTION;
    }
    else if(digit(_exp[_curIdx])) { // is number
        while(_curIdx < _exp.size() &&
              !operater(_exp[_curIdx])) {
            _token += _exp[_curIdx++];
        }
        _tokType = NUMBERS;
    }
    else { // unknown character terminates expression
        _token = EOE;
    }
    return _tokType;
}

// Return true if c is a operator.
inline bool iReParser::operater(char c)
{
    return ('+' == c || '-' == c ||
            '*' == c || '/' == c ||
            '(' == c || ')' == c ||
            '^' == c || '%' == c ||
            '=' == c);
}

inline bool iReParser::letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool iReParser::digit(char c)
{
    return (c >= '0' && c <= '9');
}
