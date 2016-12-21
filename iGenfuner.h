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
#include <vector>

namespace Imaginer{
namespace Utils {

class iGenFuner
{
    friend class iRpn;
    typedef double (*fun) (double &, double, double);
    class _funer
    {
    private:
        fun    _fun;
        double _value;
    public:
        _funer(fun f):_fun(f),_value(0){}
        _funer(fun f,double v):_fun(f),_value(v){}
    public:
        static inline double _assign(double &des, double num,double value)
        {
            return ((value) ? (des  = value) : (des  = num));
        }
        static inline double _add(double &des, double num,double value)
        {
            return ((value) ? (des += value) : (des += num));
        }
        static inline double _sub(double &des, double num,double value)
        {
            return ((value) ? (des -= value) : (des -= num));
        }
        static inline double _mut(double &des, double num,double value)
        {
            return ((value) ? (des *= value) : (des *= num));
        }
        static inline double _div(double &des, double num,double value)
        {
            return ((value) ? (des /= value) : (des /= num));
        }
        static inline double _pow(double &des, double num,double value)
        {
            return (des += pow(num,value));
        }
        inline const  double& value(){return _value;}
        inline operator fun(){return _fun;} //very important
    };
private:
    double _x;
    double _y;
    int    _curpos;
    //std::string _expname;
    char*  _expname;
    std::vector <_funer> _opstream;
public:
    iGenFuner(char *expname);
private:
    inline char next(){return /*_expname[_curpos++]*/ *_expname++;}
    inline char prev(){return /*_expname[_curpos--]*/ *_expname--;}
    void   generater();
public:
    double operator() (double x);
};
}//namespace Utils
}//namespace Imaginer

#endif // IGENFUNER_H
