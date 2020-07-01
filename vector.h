/*******************************************************************
 *          基于西安交通大学 M.Zhang 的vector类
 *          北京交通大学 王子龙 wangzilong@bjtu.edu.cn
 *          用于小学期综合训练大作业
 *******************************************************************/

/*******************************************************************
 *                            vector.h
 * vector类被设计用来进行基础的线性代数运算，例如：
 *    v + k    k + v    v += k    v1 + v2    v1 += v2
 *    v - k    k - v    v -= k    v1 - v2    v1 -= v2
 *    v * k    k * v    v *= k    v1 * v2    v1 *= v2
 *    v / k    k / v    v /= k    v1 / v2    v1 /= v2
 *    mum,     min,     max       swap       reverse
 *    norm     dotProd
 * 这些运算和函数可以被应用在实向量和虚向量上。
 *
 * 此vector类同时还提供了基础的数学函数，例如：
 *    cos    sin    tan    acos   asin   atan
 *    abs    exp    log    log10  sqrt   pow
 * 这应该包含 "matrixmath.h" 文件。
 *
 * 当调试时，在"#include vector.h"上方一行写上： #define BOUNDS_CHECK。
 * 当完成调试，将"#define BOUNDS_CHECK"注释掉以获得更好的性能。
 *
 * 代码来源：Zhang Ming, zmjerry@163.com, 编写与2010年01月
 * 代码修改：王子龙, wangzilong@bjtu.edu.cn, CS1804, SCIT, BJTU
 * 代码修改日期：2020年07月01日
 *******************************************************************/

#ifndef VECTOR_H
#define VECTOR_H


#include <iostream>
#include <cassert>
#include <cmath>
#include <complex>
#include "usingdeclare.h"
#include "constants.h"


namespace splab
{

    template <typename Type>
    class Vector
    {

    public:

        typedef         Type*   iterator;
        typedef const   Type*   const_iterator;

        // 构造函数和析构函数
        Vector();
        Vector( const Vector<Type> &v );
        Vector( int length, const Type &x = Type(0) );
        Vector( int length, const Type *array );
        ~Vector();

        // 赋值号重载
        Vector<Type>& operator=( const Vector<Type> &v );
        Vector<Type>& operator=( const Type &x );

        // 下标符号
        Type& operator[]( int i );
        const Type& operator[]( int i ) const;
        Type& operator()( int i );
        const Type& operator()( int i ) const;

        // 迭代器
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        // 泛型转换
        operator Type*();
        operator const Type*() const;

        // 其他
        int size() const;
        int dim() const;
        Vector<Type>& resize( int length );

        // 赋值运算符重载
        Vector<Type>& operator+=( const Type& );
        Vector<Type>& operator-=( const Type& );
        Vector<Type>& operator*=( const Type& );
        Vector<Type>& operator/=( const Type& );
        Vector<Type>& operator+=( const Vector<Type>& );
        Vector<Type>& operator-=( const Vector<Type>& );
        Vector<Type>& operator*=( const Vector<Type>& );
        Vector<Type>& operator/=( const Vector<Type>& );

    private:

        // 用于0偏移索引的数据指针
        Type *pv0;

        // 用于1偏移索引的数据指针
        Type *pv1;

        // 向量的列
        int	 nRow;

        void init( int length );
        void copyFromArray( const Type *v );
        void setByScalar( const Type &x );
        void destroy();

    };
    // class Vector


    // 输入输出
    template<typename Type>
    ostream& operator<<( ostream&, const Vector<Type>& );
    template<typename Type>
    istream& operator>>( istream&, Vector<Type>& );

    // 算术运算符重载
    template<typename Type>
    Vector<Type> operator-( const Vector<Type>& );
    template<typename Type>
    Vector<Type> operator+( const Vector<Type>&, const Type& );
    template<typename Type>
    Vector<Type> operator+( const Type&, const Vector<Type>& );
    template<typename Type>
    Vector<Type> operator+( const Vector<Type>&, const Vector<Type>& );
    template<typename Type>
    Vector<Type> operator-( const Vector<Type>&, const Type& );
    template<typename Type>
    Vector<Type> operator-( const Type&, const Vector<Type>& );
    template<typename Type>
    Vector<Type> operator-( const Vector<Type>&, const Vector<Type>& );
    template<typename Type>
    Vector<Type> operator*( const Vector<Type>&, const Type& );
    template<typename Type>
    Vector<Type> operator*( const Type&, const Vector<Type>& );
    template<typename Type>
    Vector<Type> operator*( const Vector<Type>&, const Vector<Type>& );
    template<typename Type>
    Vector<Type> operator/( const Vector<Type>&, const Type& );
    template<typename Type>
    Vector<Type> operator/( const Type&, const Vector<Type>& );
    template<typename Type>
    Vector<Type> operator/( const Vector<Type>&, const Vector<Type>& );

    // 点积
    template<typename Type>
    Type dotProd( const Vector<Type>&, const Vector<Type>& );
    template<typename Type> complex<Type>
    dotProd( const Vector<complex<Type> >&, const Vector<complex<Type> >& );

    // 数学运算
    template<typename Type> Type sum( const Vector<Type>& );
    template<typename Type> Type min( const Vector<Type>& );
    template<typename Type> Type max( const Vector<Type>& );
    template<typename Type> Type norm( const Vector<Type>& );
    template<typename Type> Type norm( const Vector<complex<Type> >& );
    template<typename Type> void swap( Vector<Type>&, Vector<Type>& );
    template<typename Type> Vector<Type> linspace( Type, Type, int );
    template<typename Type> Vector<Type> abs( const Vector<complex<Type> >& );
    template<typename Type> Vector<Type> arg( const Vector<complex<Type> >& );
    template<typename Type> Vector<Type> real( const Vector<complex<Type> >& );
    template<typename Type> Vector<Type> imag( const Vector<complex<Type> >& );
    template<typename Type>
    Vector<complex<Type> > complexVector( const Vector<Type>& );
    template<typename Type>
    Vector<complex<Type> > complexVector( const Vector<Type>&,
                                          const Vector<Type>&  );


#include "vector-impl.h"

}
// namespace splab


#endif
// VECTOR_H