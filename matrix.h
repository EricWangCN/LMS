/*
 /*******************************************************************
 *          基于西安交通大学 M.Zhang 的matrix类
 *          北京交通大学 王子龙 wangzilong@bjtu.edu.cn
 *          用于小学期综合训练大作业
 *******************************************************************/



/*****************************************************************************
 *                                 matrix.h
 *为基础线性代数操作而设计的matrix 模板类，例如：
 *
 *              A + x    x + A    A += x    A1 + A2   A1 += A2
 *              A - x    x - A    A -= x    A1 - A2   A1 -= A2
 *              A * x    x * A    A *= x    A1 * A2
 *              A / x    x / A    A /= x
 *              mum,     min,     max       mean      swap
 *              eye,     diag,    trT       trH       norm
 *              trMult   multTr   elemMult  elemMultEq
 *              elemDivd elemDivdEq
 * 以上操作均可对实数矩阵与复数矩阵进行运算
 *
 *
 * 同时也提供了如下的基本数学操作：
 *              cos    sin    tan    acos   asin   atan
 *              abs    exp    log    log10  sqrt   pow
 * 这需要 include "matrixmath.h"
 *
 * 调试时，在你自己所写的 "#include matrix.h" 上方添加 #define BOUNDS_CHECK 。
 * 调试完成以后，为了更好的运行性能请将 #define BOUNDS_CHECK 注释掉。
 *
 * 代码来源：Zhang Ming, zmjerry@163.com, 编写与2010年012月
 * 代码修改：王子龙, wangzilong@bjtu.edu.cn, CS1804, SCIT, BJTU
 * 代码修改日期：2020年07月06日
 *
 *****************************************************************************/


#ifndef MATRIX_H
#define MATRIX_H


#include "vector.h"


namespace splab
{

    template <typename Type>
    class Matrix
    {

    public:

        // 构造与析构函数
        Matrix();
        Matrix( const Matrix<Type> &A );
        Matrix( int rows, int columns, const Type &x = Type(0) );
        Matrix( int rows, int columns, const Type *v );
        ~Matrix();

        // 矩阵重载赋值符号‘=’
        Matrix<Type>& operator=( const Matrix<Type> &A );
        Matrix<Type>& operator=( const Type &x );

        // 通过重载‘（）’ 与‘【】’取得获取矩阵的内容的手段
        Type* operator[]( int i );
        const Type* operator[]( int i ) const;
        Type& operator()( int row, int column );
        const Type& operator()( int row, int column ) const;

        // 类型转换
        operator Type*();
        operator const Type*() const;
//        operator Type**();
//        operator const Type**() const;

        // 其他的一些功能（矩阵尺寸，行列数，尺寸更改等）
        long size() const;
        int dim( int dimension ) const;
        int rows() const;
        int cols() const;
        Matrix<Type>& resize( int rows, int columns );
        Vector<Type> getRow( int row ) const;
        Vector<Type> getColumn( int column ) const;
        void setRow( const Vector<Type> &v, int row );
        void setColumn( const Vector<Type> &v, int column );

        // 带计算符号的赋值运算符重载，方便矩阵计算
        Matrix<Type>& operator+=( const Type& );
        Matrix<Type>& operator+=( const Matrix<Type>& );
        Matrix<Type>& operator-=( const Type& );
        Matrix<Type>& operator-=( const Matrix<Type>& );
        Matrix<Type>& operator*=( const Type& );
        // 提示：以下运算符运算时按照每个元素逐一进行运算操作
        Matrix<Type>& operator*=( const Matrix<Type>& );
        Matrix<Type>& operator/=( const Type& );
        // 提示：以下运算符运算时按照每个元素逐一进行运算操作
        Matrix<Type>& operator/=( const Matrix<Type>& );

    private:

        // 基为0与1的数据指针
        Type *pv0, *pv1;

        // 基为0与1的指向行指针的指针
        Type **prow0, **prow1;

        // 行数，列数以及元素总数
        int	 nRow;
        int	 nColumn;
        long nTotal;

        void init( int rows, int columns );
        void copyFromArray( const Type *v );
        void setByScalar( const Type &x );
        void destroy();

    };
    // class Matrix

    // 矩阵输入输出的重载
    template<typename Type>
    ostream& operator<<( ostream&, const Matrix<Type>& );
    template<typename Type>
    istream& operator>>( istream&, Matrix<Type>& );

    // 矩阵各种运算符的重载
    template<typename Type>
    Matrix<Type> operator-( const Matrix<Type>& );
    template<typename Type>
    Matrix<Type> operator+( const Matrix<Type>&, const Type& );
    template<typename Type>
    Matrix<Type> operator+( const Type&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type> operator+( const Matrix<Type>&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type> operator-( const Matrix<Type>&, const Type& );
    template<typename Type>
    Matrix<Type> operator-( const Type&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type> operator-( const Matrix<Type>&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type> operator*( const Matrix<Type>&, const Type& );
    template<typename Type>
    Matrix<Type> operator*( const Type&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type> operator*( const Matrix<Type>&, const Matrix<Type>& );
    template<typename Type>
    Vector<Type> operator*( const Matrix<Type>&, const Vector<Type>& );
    template<typename Type>
    Matrix<Type> operator/( const Matrix<Type>&, const Type& );
    template<typename Type>
    Matrix<Type> operator/( const Type&, const Matrix<Type>& );

    // 优化的乘法
    template<typename Type>
    Matrix<Type>& optMult( const Matrix<Type>&, const Matrix<Type>&,
                           Matrix<Type>& );
    template<typename Type>
    Vector<Type>& optMult( const Matrix<Type>&, const Vector<Type>&,
                           Vector<Type>& );

    // 每个元素逐一进行运算操作的乘除法
    template<typename Type>
    Matrix<Type> elemMult( const Matrix<Type>&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type> elemDivd( const Matrix<Type>&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type>& elemMultEq( Matrix<Type>&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type>& elemDivdEq( Matrix<Type>&, const Matrix<Type>& );

    // 转置与共轭转置
    template<typename Type> Matrix<Type> trT( const Matrix<Type>& );
    template<typename Type> Matrix<Type> trH( const Matrix<Type>& );

    // 转置 乘法
    template<typename Type>
    Matrix<Type> trMult( const Matrix<Type>&, const Matrix<Type>& );
    template<typename Type>
    Vector<Type> trMult( const Matrix<Type>&, const Vector<Type>& );
    template<typename Type>
    Matrix<Type> multTr( const Matrix<Type>&, const Matrix<Type>& );
    template<typename Type>
    Matrix<Type> multTr( const Vector<Type>&, const Vector<Type>& );
    template<typename Type>
    Matrix<complex<Type> > trMult( const Matrix<complex<Type> >&,
                                   const Matrix<complex<Type> >& );
    template<typename Type>
    Vector<complex<Type> > trMult( const Matrix<complex<Type> >&,
                                   const Vector<complex<Type> >& );
    template<typename Type>
    Matrix<complex<Type> > multTr( const Matrix<complex<Type> >&,
                                   const Matrix<complex<Type> >& );
    template<typename Type>
    Matrix<complex<Type> > multTr( const Vector<complex<Type> >&,
                                   const Vector<complex<Type> >& );

    // 单位矩阵与对角矩阵
    template<typename Type> Matrix<Type> eye( int, const Type& );
    template<typename Type> Vector<Type> diag( const Matrix<Type>& );
    template<typename Type> Matrix<Type> diag( const Vector<Type>& );

    // 其他功能
    template<typename Type> Type norm( const Matrix<Type>& );
    template<typename Type> Type norm( const Matrix<complex<Type> >& );
    template<typename Type> void swap( Matrix<Type>&, Matrix<Type>& );
    template<typename Type> Vector<Type> sum( const Matrix<Type>& );
    template<typename Type> Vector<Type> min( const Matrix<Type>& );
    template<typename Type> Vector<Type> max( const Matrix<Type>& );
    template<typename Type> Vector<Type> mean( const Matrix<Type>& );
    template<typename Type> Matrix<Type> abs( const Matrix<complex<Type> >& );
    template<typename Type> Matrix<Type> arg( const Matrix<complex<Type> >& );
    template<typename Type> Matrix<Type> real( const Matrix<complex<Type> >& );
    template<typename Type> Matrix<Type> imag( const Matrix<complex<Type> >& );
    template<typename Type>
    Matrix<complex<Type> > complexMatrix( const Matrix<Type>& );
    template<typename Type>
    Matrix<complex<Type> > complexMatrix( const Matrix<Type>&,
                                          const Matrix<Type>& );


#include "matrix-impl.h"

}
// namespace splab


#endif
// MATRIX_H
