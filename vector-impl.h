/*******************************************************************
 *          基于西安交通大学 M.Zhang 的vector类
 *          北京交通大学 王子龙 wangzilong@bjtu.edu.cn
 *          用于小学期综合训练大作业
 *******************************************************************/


/*******************************************************************
 *                        vector-impl.h
 *
 * vector类的实现
 *
 * 代码来源：Zhang Ming, zmjerry@163.com, 编写与2010年01月
 * 代码修改：王子龙, wangzilong@bjtu.edu.cn, CS1804, SCIT, BJTU
 * 代码修改日期：2020年07月01日
 *******************************************************************/


/**
 * 初始化
 */
template <typename Type>
void Vector<Type>::init( int length )
{
    assert( pv0 == NULL );
    pv0 = new Type[length];

    assert( pv0 != NULL );
    pv1 = pv0 - 1;
    nRow = length;
}


/**
 * 从普通数组赋值给vector
 */
template <typename Type>
inline void Vector<Type>::copyFromArray( const Type *v )
{
    for( int i=0; i<nRow; ++i )
        pv0[i] = v[i];
}


/**
 * 通过标量设置向量
 */
template <typename Type>
inline void Vector<Type>::setByScalar( const Type &x )
{
    for( int i=0; i<nRow; ++i )
        pv0[i] = x;
}


/**
 * 删除向量
 */
template <typename Type>
void Vector<Type>::destroy()
{
    if( pv0 == NULL )
        return;

    delete []pv0;

    pv0 = NULL;
    pv1 = NULL;
}


/**
 * 构造函数和析构函数
 */
template <typename Type>
Vector<Type>::Vector()
        : pv0(0), pv1(0), nRow(0)
{
}

template <typename Type>
Vector<Type>::Vector( const Vector<Type> &v )
        : pv0(0), pv1(0), nRow(0)
{
    init( v.nRow );
    copyFromArray( v.pv0 );
}

template <typename Type>
Vector<Type>::Vector( int length, const Type &x )
        :  pv0(0), pv1(0), nRow(0)
{
    init( length );
    setByScalar( x );
}

template <typename Type>
Vector<Type>::Vector( int length, const Type *array )
        :  pv0(0), pv1(0), nRow(0)
{
    init( length );
    copyFromArray( array );
}

template <typename Type>
Vector<Type>::~Vector()
{
    destroy();
}


/**
 * 重载赋值号（vector to vector）
 */
template <typename Type>
Vector<Type>& Vector<Type>::operator=( const Vector<Type> &v )
{
    if( pv0 == v.pv0 )
        return *this;

    if( nRow == v.nRow )
        copyFromArray( v.pv0 );
    else
    {
        destroy();
        init( v.nRow );
        copyFromArray( v.pv0 );
    }

    return *this;
}


/**
 * 重载赋值号（scalar to vector）
 */
template <typename Type>
inline Vector<Type>& Vector<Type>::operator=( const Type &x )
{
    setByScalar( x );

    return *this;
}


/**
 * 用于0偏移量访问的重载运算符[]
 */
template <typename Type>
inline Type& Vector<Type>::operator[]( int i )
{
#ifdef BOUNDS_CHECK
    assert( 0 <= i );
	assert( i < nRow );
#endif

    return pv0[i];
}

template <typename Type>
inline const Type& Vector<Type>::operator[]( int i ) const
{
#ifdef BOUNDS_CHECK
    assert( 0 <= i );
	assert( i < nRow );
#endif

    return pv0[i];
}


/**
 * 用于1偏移量访问的重载运算符()
 */
template <typename Type>
inline Type& Vector<Type>::operator()( int i )
{
#ifdef BOUNDS_CHECK
    assert( 1 <= i );
	assert( i <= nRow );
#endif

    return pv1[i];
}

template <typename Type>
inline const Type& Vector<Type>::operator()( int i ) const
{
#ifdef BOUNDS_CHECK
    assert( 1 <= i );
	assert( i <= nRow );
#endif

    return pv1[i];
}


/**
 * 迭代器
 */
template <typename Type>
inline typename Vector<Type>::iterator Vector<Type>::begin()
{
    return pv0;
}

template <typename Type>
inline typename Vector<Type>::const_iterator Vector<Type>::begin() const
{
    return pv0;
}

template <typename Type>
inline typename Vector<Type>::iterator Vector<Type>::end()
{
    return pv0 + nRow;
}

template <typename Type>
inline typename Vector<Type>::const_iterator Vector<Type>::end() const
{
    return pv0 + nRow;
}


/**
 * 类型转换
 */
template <typename Type>
inline Vector<Type>::operator Type*()
{
    return pv0;
}

template <typename Type>
inline Vector<Type>::operator const Type*() const
{
    return pv0;
}


/**
 * 返回vector的大小
 */
template <typename Type>
inline int Vector<Type>::size() const
{
    return  nRow;
}


/**
 * 获取vector维度
 */
template <typename Type>
inline int Vector<Type>::dim() const
{
    return  nRow;
}


/**
 * 重新为向量分配大小
 */
template <typename Type>
Vector<Type>& Vector<Type>::resize( int length )
{
    if( nRow == length )
        return *this;

    destroy();
    init( length );

    return *this;
}


/**
 * 赋值运算符+=的重载
 */
template <typename Type>
Vector<Type>& Vector<Type>::operator+=( const Type &x )
{
    iterator itr = (*this).begin();
    while( itr != (*this).end() )
        *itr++ += x;

    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator+=( const Vector<Type> &rhs )
{
    assert( nRow == rhs.dim() );

    iterator itrL = (*this).begin();
    const_iterator itrR = rhs.begin();
    while( itrL != (*this).end() )
        *itrL++ += *itrR++;

    return *this;
}


/**
 * 赋值运算符-=的重载
 */
template <typename Type>
Vector<Type>& Vector<Type>::operator-=( const Type &x )
{
    iterator itr = (*this).begin();
    while( itr != (*this).end() )
        *itr++ -= x;

    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator-=( const Vector<Type> &rhs )
{
    assert( nRow == rhs.dim() );

    iterator itrL = (*this).begin();
    const_iterator itrR = rhs.begin();
    while( itrL != (*this).end() )
        *itrL++ -= *itrR++;

    return *this;
}


/**
 * 赋值运算符*=的重载
 */
template <typename Type>
Vector<Type>& Vector<Type>::operator*=( const Type &x )
{
    iterator itr = (*this).begin();
    while( itr != (*this).end() )
        *itr++ *= x;

    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator*=( const Vector<Type> &rhs )
{
    assert( nRow == rhs.dim() );

    iterator itrL = (*this).begin();
    const_iterator itrR = rhs.begin();
    while( itrL != (*this).end() )
        *itrL++ *= *itrR++;

    return *this;
}


/**
 * 赋值运算符/=的重载
 */
template <typename Type>
Vector<Type>& Vector<Type>::operator/=( const Type &x )
{
    iterator itr = (*this).begin();
    while( itr != (*this).end() )
        *itr++ /= x;

    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator/=( const Vector<Type> &rhs )
{
    assert( nRow == rhs.dim() );

    iterator itrL = (*this).begin();
    const_iterator itrR = rhs.begin();
    while( itrL != (*this).end() )
        *itrL++ /= *itrR++;

    return *this;
}


/**
 * 重载输出流运算符<<
 */
template <typename Type>
ostream& operator<<( ostream &out, const Vector<Type> &v )
{
    int N = v.dim();
    out << "size: " << N << " by 1" << "\n";

    for( int i=0; i<N; ++i )
        out << v[i] << " " << "\n";

    return out;
}


/**
 * 重载输入流运算符>>
 */
template <typename Type>
istream& operator>>( istream &in, Vector<Type> &v )
{
    int N;
    in >> N;

    if( !( N == v.dim() ) )
        v.resize( N );

    for( int i=0; i<N; ++i )
        in >> v[i];

    return in;
}


/**
 * 得到向量的负值
 */
template <typename Type>
Vector<Type> operator-( const Vector<Type> &v )
{
    Vector<Type> tmp( v.dim() );
    typename Vector<Type>::iterator itrL = tmp.begin();
    typename Vector<Type>::const_iterator itrR = v.begin();

    while( itrL != tmp.end() )
        *itrL++ = -(*itrR++);

    return tmp;
}


/**
 * 向量-标量加法
 */
template <typename Type>
inline Vector<Type> operator+( const Vector<Type> &v, const Type &x )
{
    Vector<Type> tmp( v );
    return tmp += x;
}

template <typename Type>
inline Vector<Type> operator+( const Type &x, const Vector<Type> &v )
{
    return v+x;
}


/**
 * 向量-标量减法
 */
template <typename Type>
inline Vector<Type> operator-( const Vector<Type> &v, const Type &x )
{
    Vector<Type> tmp( v );
    return tmp -= x;
}

template <typename Type>
inline Vector<Type> operator-( const Type &x, const Vector<Type> &v )
{
    Vector<Type> tmp( v );
    return -tmp += x;
}


/**
 * 向量-标量乘法
 */
template <typename Type>
inline Vector<Type> operator*( const Vector<Type> &v, const Type &x )
{
    Vector<Type> tmp( v );
    return tmp *= x;
}

template <typename Type>
inline Vector<Type> operator*( const Type &x, const Vector<Type> &v )
{
    return v*x;
}


/**
 * 向量-标量除法
 */
template <typename Type>
inline Vector<Type> operator/( const Vector<Type> &v, const Type &x )
{
    Vector<Type> tmp( v );
    return tmp /= x;
}

template <typename Type>
inline Vector<Type> operator/( const Type &x, const Vector<Type> &v )
{
    int N = v.dim();
    Vector<Type> tmp( N );

    for( int i=0; i<N; ++i )
        tmp[i] = x / v[i];

    return tmp;
}


/**
 * 向量-向量加法
 */
template <typename Type>
inline Vector<Type> operator+( const Vector<Type> &v1, const Vector<Type> &v2 )
{
    Vector<Type> tmp( v1 );
    return tmp += v2;
}


/**
 * 向量-向量减法
 */
template <typename Type>
inline Vector<Type> operator-( const Vector<Type> &v1, const Vector<Type> &v2 )
{
    Vector<Type> tmp( v1 );
    return tmp -= v2;
}


/**
 * 向量-向量乘法
 */
template <typename Type>
inline Vector<Type> operator*( const Vector<Type> &v1, const Vector<Type> &v2 )
{
    Vector<Type> tmp( v1 );
    return tmp *= v2;
}


/**
 * 向量-向量除法
 */
template <typename Type>
inline Vector<Type> operator/( const Vector<Type> &v1, const Vector<Type> &v2 )
{
    Vector<Type> tmp( v1 );
    return tmp /= v2;
}


/**
 * 向量內积
 */
template <typename Type>
Type dotProd( const Vector<Type> &v1, const Vector<Type> &v2 )
{
    assert( v1.dim() == v2.dim() );

    Type sum = 0;
    typename Vector<Type>::const_iterator itr1 = v1.begin();
    typename Vector<Type>::const_iterator itr2 = v2.begin();

    while( itr1 != v1.end() )
        sum += (*itr1++) * (*itr2++);

    return sum;
}


/**
 * 多个向量內积
 */
template <typename Type>
complex<Type> dotProd( const Vector<complex<Type> > &v1,
                       const Vector<complex<Type> > &v2 )
{
    assert( v1.dim() == v2.dim() );

    complex<Type> sum = 0;
    typename Vector<complex<Type> >::const_iterator itr1 = v1.begin();
    typename Vector<complex<Type> >::const_iterator itr2 = v2.begin();

    while( itr1 != v1.end() )
        sum += (*itr1++) * conj(*itr2++);

    return sum;
}


/**
 * 向量元素和
 */
template <typename Type>
Type sum( const Vector<Type> &v )
{
    Type sum = 0;
    typename Vector<Type>::const_iterator itr = v.begin();

    while( itr != v.end() )
        sum += *itr++;

    return sum;
}


/**
 * 向量元素最小值
 */
template <typename Type>
Type min( const Vector<Type> &v )
{
    Type m = v[0];
    for( int i=1; i<v.size(); ++i )
        if( m > v[i] )
            m = v[i];

    return m;
}


/**
 * 向量元素最大值
 */
template <typename Type>
Type max( const Vector<Type> &v )
{
    Type M = v[0];
    for( int i=1; i<v.size(); ++i )
        if( M < v[i] )
            M = v[i];

    return M;
}


/**
 * 欧几里得空间中的向量范数
 */
template <typename Type>
Type norm( const Vector<Type> &v )
{
    Type sum = 0;
    typename Vector<Type>::const_iterator itr = v.begin();

    while( itr != v.end() )
    {
        sum += (*itr) * (*itr);
        itr++;
    }

    return Type(sqrt(1.0*sum));
}


/**
 * 欧几里得空间中的向量范数
 */
template <typename Type>
Type norm( const Vector<complex<Type> > &v )
{
    Type sum = 0;
    typename Vector<complex<Type> >::const_iterator itr = v.begin();

    while( itr != v.end() )
        sum += norm(*itr++);

    return Type(sqrt(1.0*sum));
}


/**
 * 返回向量的逆
 */
template <typename Type>
void swap( Vector<Type> &lhs, Vector<Type> &rhs )
{
    typename Vector<Type>::iterator itrL = lhs.begin(),
            itrR = rhs.begin();

    while( itrL != lhs.end() )
        std::swap( *itrL++, *itrR++ );
}


/**
 * 生成在a和b之间（包括a和b）线性间隔的n个点的向量。
 */
template <typename Type>
Vector<Type> linspace( Type a, Type b, int n )
{
    if( n < 1 )
        return Vector<Type>();
    else if( n == 1 )
        return Vector<Type>( 1, a );
    else
    {
        Type dx = (b-a) / (n-1);

        Vector<Type> tmp(n);
        for( int i=0; i<n; ++i )
            tmp[i] = a + i*dx;

        return tmp;
    }
}


/**
 * 获取复数向量的绝对值
 */
template <typename Type>
Vector<Type> abs( const Vector< complex<Type> > &v )
{
    Vector<Type> tmp( v.dim() );
    typename Vector<Type>::iterator itrL = tmp.begin();
    typename Vector< complex<Type> >::const_iterator itrR = v.begin();

    while( itrL != tmp.end() )
        *itrL++ = abs(*itrR++);

    return tmp;
}


/**
 * 获取复数向量的arg
 */
template <typename Type>
Vector<Type> arg( const Vector< complex<Type> > &v )
{
    Vector<Type> tmp( v.dim() );
    typename Vector<Type>::iterator itrL = tmp.begin();
    typename Vector< complex<Type> >::const_iterator itrR = v.begin();

    while( itrL != tmp.end() )
        *itrL++ = arg(*itrR++);

    return tmp;
}


/**
 * 获取复数向量的实部
 */
template <typename Type>
Vector<Type> real( const Vector< complex<Type> > &v )
{
    Vector<Type> tmp( v.dim() );
    typename Vector<Type>::iterator itrL = tmp.begin();
    typename Vector< complex<Type> >::const_iterator itrR = v.begin();

    while( itrL != tmp.end() )
        *itrL++ = (*itrR++).real();

    return tmp;
}


/**
 * 获取复数向量虚部
 */
template <typename Type>
Vector<Type> imag( const Vector< complex<Type> > &v )
{
    Vector<Type> tmp( v.dim() );
    typename Vector<Type>::iterator itrL = tmp.begin();
    typename Vector< complex<Type> >::const_iterator itrR = v.begin();

    while( itrL != tmp.end() )
        *itrL++ = (*itrR++).imag();

    return tmp;
}


/**
 * 将实向量转为复数向量
 */
template <typename Type>
Vector<complex<Type> > complexVector( const Vector<Type> &rv )
{
    int N = rv.dim();

    Vector<complex<Type> > cv( N );
    typename Vector<complex<Type> >::iterator itrL = cv.begin();
    typename Vector<Type>::const_iterator itrR = rv.begin();

    while( itrR != rv.end() )
        *itrL++ = *itrR++;

    return cv;
}

template <typename Type>
Vector<complex<Type> > complexVector( const Vector<Type> &vR,
                                      const Vector<Type> &vI )
{
    int N = vR.dim();

    assert( N == vI.dim() );

    Vector<complex<Type> > cv( N );
    typename Vector<complex<Type> >::iterator itrC = cv.begin();
    typename Vector<Type>::const_iterator itrR = vR.begin(),
            itrI = vI.begin();

    while( itrC != cv.end() )
        *itrC++ = complex<Type>( *itrR++, *itrI++ );

    return cv;
}