/*
 *
 * This class is used to input the string function of the identification and analysis tools clase,
 * Which uses the class iStackInfix parser function, in order to obtain the expression corresponding to
 * the operation stream;
 * And when you want to get the math function a ( X -> Y )
 * will use operation stream to change X to Y
 * At last to get Y
 *
 */
#ifndef IGENFUNER_H
#define IGENFUNER_H

#include <iostream>
#include <cmath>
#include <string>
#include "iStack.h"

namespace Imaginer{
namespace Utils {

class iGenFuner
{
    friend class iRpn;
    typedef double (*Fun) (double &, double, double);
    class _funer
    {
    private:
        Fun    _fun;
        double _value;
    public:
        _funer():_fun(NULL),_value(0){}
        _funer(const Fun& f,double v = 0):_fun(f),_value(v){}
    public:
        static inline double _assign(double &y, double x,double value)
        {
            return (y += (x+value));
        }
        static inline double _add(double &y, double x,double value)
        {
            return (y += (x+value));
        }
        static inline double _sub(double &y, double x,double value)
        {
            return (y += (x-value));
        }
        static inline double _mut(double &y, double x,double value)
        {
            return (y += (x*value));
        }
        static inline double _div(double &y, double x,double value)
        {
            return (y += (x/value));
        }
        static inline double _pow(double &y, double x,double value)
        {
            return (y += pow(x,value));
        }
        inline double value()const{return _value;}//get value
        inline double& value(){return _value;}    //set value
        inline operator Fun(){return _fun;} //very important,default type conversion(_funer->Fun)
    };
private:
    double _x;
    double _y;
    int    _curpos;
    //std::string _expname;
    char*  _expname;
    iStack<_funer> _opstream;
public:
    iGenFuner(char *expname);
private:
    inline char next(){return /*_expname[_curpos++]*/ *_expname++;}
    inline char prev(){return /*_expname[_curpos--]*/ *_expname--;}
    inline void push(const Fun& fun){_opstream.push(fun);}
    inline Fun  pop(){return _opstream.pop();}
    bool   generater();
    double generater(double x);
public:
    double operator() (double x);
};
}//namespace Utils
}//namespace Imaginer

#endif // IGENFUNER_H
