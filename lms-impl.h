/*******************************************************************
 *          基于西安交通大学 M.Zhang 的LMS自适应滤波器程序
 *          北京交通大学 王子龙 wangzilong@bjtu.edu.cn
 *          用于小学期综合训练大作业
 *******************************************************************/


/*******************************************************************
 *                           lms-impl.h
 *
 * 最小均方误差(LMS)自适应滤波器的实现程序
 *
 * 代码来源：Zhang Ming, zmjerry@163.com, 编写与2010年10月
 * 代码修改：王子龙, wangzilong@bjtu.edu.cn, CS1804, SCIT, BJTU
 * 代码修改日期：2020年06月29日
 *******************************************************************/


/**
 * The conventional LMS algorithm, which is sensitive to the scaling of its
 * input "xn". The filter order p = wn.size(), where "wn" is the Weight
 * Vector, and "mu" is the iterative setp size, for stability "mu" should
 * belong to (0, Rr[Rxx]).
 */
template <typename Type>
Type lms( const Type &xk, const Type &dk, Vector<Type> &wn, const Type &mu )
{
    int filterLen = wn.size();
    static Vector<Type> xn(filterLen);

    // update input signal
    for( int i=filterLen; i>1; --i )
        xn(i) = xn(i-1);
    xn(1) = xk;

    // get the output
    Type yk = dotProd( wn, xn );

    // update the Weight Vector
    wn += 2*mu*(dk-yk) * xn;

    return yk;
}


/**
 * The LMS-Newton is a variant of the LMS algorithm which incorporate
 * estimates of the second-order statistics of the environment signals is
 * introduced. The objective of the algorithm is to avoid the slowconvergence
 * of the LMS algorithm when the input signal is highly correlated. The
 * improvement is achieved at the expense of an increased computational
 * complexity.
 */
template <typename Type>
Type lmsNewton( const Type &xk, const Type &dk, Vector<Type> &wn,
                const Type &mu, const Type &alpha, const Type &delta )
{
    assert( 0 < alpha );
    assert( alpha <= Type(0.1) );

    int filterLen = wn.size();
    Type beta = 1-alpha;
    Vector<Type> vP(filterLen);
    Vector<Type> vQ(filterLen);

    static Vector<Type> xn(filterLen);

    // initialize the Correlation Matrix's inverse
    static Matrix<Type> invR = eye( filterLen, Type(1.0/delta) );

    // update input signal
    for( int i=filterLen; i>1; --i )
        xn(i) = xn(i-1);
    xn(1) = xk;

    Type yk = dotProd(wn,xn);

    // update the Correlation Matrix's inverse
    vQ = invR * xn;
    vP = vQ / (beta/alpha+dotProd(vQ,xn));
    invR = (invR - multTr(vQ,vP)) / beta;

    // update the Weight Vector
    wn += 2*mu * (dk-yk) * (invR*xn);

    return yk;
}


/**
 * The conventional LMS is very hard to choose a learning rate "mu" that
 * guarantees stability of the algorithm. The Normalised LMS is a variant
 * of the LMS that solves this problem by normalising with the power of
 * the input. For stability, the parameter "rho" should beong to (0,2),
 * and "gamma" is a small number to prevent <Xn,Xn> == 0.
 */
template <typename Type>
Type lmsNormalize( const Type &xk, const Type &dk, Vector<Type> &wn,
                   const Type &rho, const Type &gamma )
{
    assert( 0 < rho );
    assert( rho < 2 );

    int filterLen = wn.size();
    static Vector<Type> sn(filterLen);

    // update input signal
    for( int i=filterLen; i>1; --i )
        sn(i) = sn(i-1);
    sn(1) = xk;

    // get the output
    Type yk = dotProd( wn, sn );

    // update the Weight Vector
    wn += rho*(dk-yk)/(gamma+dotProd(sn,sn)) * sn;

    return yk;
}

