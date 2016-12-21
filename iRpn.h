/*
 * This is a class use  RPN(Reverse Polish notation) to parser a function expression,
 * and than use to generate a opearator stream.
 * After use the op-stream to get each number's function value;
 *
 */
#ifndef IRPN_H
#define IRPN_H
#include <iostream>
#include "iGenfuner.h"
namespace Imaginer{
namespace Utils {

//Reverse Polish notation
class iRpn
{
public:
    template<typename Type>
    class iStack
    {
    private:
        Type*   _data;
        int     _size;
        int     _top;
    public:
        iStack(const int& size = 1024):_size(size),_top(-1)
        {
            _data = new Type[_size];
        }
        iStack(iStack<Type>& rhs)
        {
            if(this != &rhs)
            {
                _size = rhs._size;
                _data = new Type[_size];
                memcpy(_data,rhs._data,_size);
            }
        }
        ~iStack()
        {
            if(_data)
            {
                delete[] _data;
                _data = NULL;
            }
        }
    public:
        inline Type& top(){ return _data[_top];}
        inline Type& bottom() {return _data[0];}
        inline Type& pop(){ return _data[_top--];}
        inline Type& push(const Type& value){ return _data[++_top] = value;}
        inline bool  empty(){ return (_top == -1);}
        inline bool  full() { return (_top == _size);}
        inline int   size() {return _top;}
        iStack<Type>& reverse()
        {
            Type tmp;
            int head = 0;
            int tail = _top;
            while(head < tail)
            {
                tmp = _data[head];
                _data[head] = _data[tail];
                _data[tail] = tmp;
                head++;
                tail--;
            }
            return *this;
        }
    public:
        iStack<Type> operator=(const iStack<Type> rhs)
        {
            if(this != &rhs)
            {
                _size = rhs._size;
                _data = new Type[_size];
                memcpy(_data,rhs._data,_size);
            }
        }
        inline  Type&  operator[](int index){ return _data[index];}
        friend  std::ostream& operator<<(std::ostream &os,iStack<Type>& stack)
        {
            int size = stack.size();
            int i = 0;
            while(i <= size)
            {
                os << stack[i++] << "  ";
            }
            return os;
        }
    };
    //save a RPN expression data node
    struct RPNnode
    {
    private:
        union
        {
            double  _value;
            char    _sign;
        }_data;
        bool  _is;          // (isnumber) ? (true) : (false)
    public:
        RPNnode():_is(false){_data._value = 0;}
        RPNnode(double value):_is(true){ _data._value = value;_data._sign = 0;}
        RPNnode(char   value):_is(false){ _data._sign  = value;}
        inline operator char()  { return _data._sign;}
        inline operator double(){ return _data._value;}
        inline operator bool()  {return _is;}
        inline bool operator==(char value) { return ( (_is) ? (false): ((value == _data._sign) ? true : false) ); }
        friend  std::ostream& operator<<(std::ostream &os,const RPNnode& node)
        {
            (node._is)? ( os << node._data._value ) : (os <<  node._data._sign );
            return os;
        }
    };
private:
    char*             _expnames;  //save expression
    iStack< char >*   _operator;  //save operator
    iStack<RPNnode>*  _operands;  //save operands
private:
    int  getPRI(char cursign);   //get a operator's PRI from operator PRI table
    bool cmpPRI(char cursign);   //compare current operator sign with top operator,bigger-equal return true,else false
    inline char next(){return *_expnames++;}
    inline char prev(){return *_expnames--;}
public:
    iRpn(char* expname);
    ~iRpn();
    void genRpn();               //generate a expression from the infix expression to suffix expression(RPN)
    void Parser(iGenFuner& genfuner);           //Parser a infix expression to a operator stream
};

}//namespace Utils
}//namespace Imaginer

#endif // IRPN_H
