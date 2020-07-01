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


/*******************************************************************
 * 常规的LMS算法，对其的输入:"Xn"的缩放十分敏感。滤波器的阶数p=wn.size()，其中
 * wn是权值向量，"mu"是迭代阶数，为了"mu"的稳定，它应该属于(0,Rr[Rxx])。
 *******************************************************************/

template <typename Type>
Type lms( const Type &xk, const Type &dk, Vector<Type> &wn, const Type &mu )
{
    int filterLen = wn.size();
    static Vector<Type> xn(filterLen);

    // 更新输入信号
    for( int i=filterLen; i>1; --i )
        xn(i) = xn(i-1);
    xn(1) = xk;

    // 获取输出
    Type yk = dotProd( wn, xn );

    // 更新权重向量
    wn += 2*mu*(dk-yk) * xn;

    return yk;
}

/*******************************************************************
 * 牛顿LMS算法是LMS算法的一种变体，它引入了环境信号的二阶统计量的估计。该算法的目
 * 的是在输入信号高度相关时避免LMS算法收敛较慢的特性，并通过牺牲计算的复杂度为代价
 * 来实现相关改进。
 *******************************************************************/

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

    // 初始化相关矩阵的逆
    static Matrix<Type> invR = eye( filterLen, Type(1.0/delta) );

    // 更新输入信号
    for( int i=filterLen; i>1; --i )
        xn(i) = xn(i-1);
    xn(1) = xk;

    Type yk = dotProd(wn,xn);

    // 更新相关矩阵的逆
    vQ = invR * xn;
    vP = vQ / (beta/alpha+dotProd(vQ,xn));
    invR = (invR - multTr(vQ,vP)) / beta;

    // 更新权重向量
    wn += 2*mu * (dk-yk) * (invR*xn);

    return yk;
}


/*******************************************************************
 * 传统的LMS很难选择保证算法稳定性的学习速率“ mu”。 归一化LMS是LMS的一种变体，
 * 它通过使用输入功率进行归一化来解决此问题。 为了稳定起见，参数“rho”应等于
 * （0,2），而“ gamma”为小数，以防止<Xn，Xn> == 0。
 *******************************************************************/

/**
 * @func lmsNormalize
 * @param xk
 * @param dk
 * @param wn
 * @param rho
 * @param gamma
 */
template <typename Type>
Type lmsNormalize( const Type &xk, const Type &dk, Vector<Type> &wn,
                   const Type &rho, const Type &gamma )
{
    assert( 0 < rho );
    assert( rho < 2 );

    int filterLen = wn.size();
    static Vector<Type> sn(filterLen);

    // 更新输入信号
    for( int i=filterLen; i>1; --i )
        sn(i) = sn(i-1);
    sn(1) = xk;

    // 获取输出
    Type yk = dotProd( wn, sn );

    // 更新权重向量
    wn += rho*(dk-yk)/(gamma+dotProd(sn,sn)) * sn;

    return yk;
}

