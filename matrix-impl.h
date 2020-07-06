/*
 /*******************************************************************
 *          基于西安交通大学 M.Zhang 的matrix类的实现（-impl）
 *          北京交通大学 王子龙 wangzilong@bjtu.edu.cn
 *          用于小学期综合训练大作业
 *******************************************************************/


/********************************************************************
 *                          matrix-impl.h
 *
 * 矩阵类的实现
 *
 * 代码来源：Zhang Ming, zmjerry@163.com, 编写与2010年012月
 * 代码修改：王子龙, wangzilong@bjtu.edu.cn, CS1804, SCIT, BJTU
 * 代码修改日期：2020年07月06日
 ********************************************************************/


/**
 * 初始化矩阵
 */
template <typename Type>
void Matrix<Type>::init( int rows, int columns )
{
    nRow = rows;
    nColumn = columns;
    nTotal = nRow * nColumn;

    pv0 = new Type[nTotal];
    prow0 = new Type*[nRow];
    prow1 = new Type*[nRow];

    assert( pv0 != NULL );
    assert( prow0 != NULL );
    assert( prow1 != NULL );

    Type *p = pv0;
    pv1 = pv0 - 1;
    for( int i=0; i<nRow; ++i )
    {
        prow0[i] = p;
        prow1[i] = p-1;
        p += nColumn;
    }

    prow1--;
}


/**
 * 从数组向矩阵输入元素
 */
template <typename Type>
inline void Matrix<Type>::copyFromArray( const Type *v )
{
    for( long i=0; i<nTotal; ++i )
        pv0[i] = v[i];
}


/**
 * 使用常量设置矩阵
 */
template <typename Type>
inline void Matrix<Type>::setByScalar( const Type &x )
{
    for( long i=0; i<nTotal; ++i )
        pv0[i] = x;
}


/**
 *删除矩阵
 */
template <typename Type>
void Matrix<Type>::destroy()
{
    if( pv0 == NULL )
        return ;
    else
        delete []pv0;

    if( prow0 != NULL )
        delete []prow0;

    prow1++;
    if( prow1 != NULL )
        delete []prow1;
}


/**
 *各种构造与析构函数
 */
template <typename Type>
Matrix<Type>::Matrix()
        : pv0(0), pv1(0), prow0(0), prow1(0), nRow(0), nColumn(0), nTotal(0)
{
}

template <typename Type>
Matrix<Type>::Matrix( const Matrix<Type> &A )
{
    init( A.nRow, A.nColumn );
    copyFromArray( A.pv0 );
}

template <typename Type>
Matrix<Type>::Matrix( int rows, int columns, const Type &x )
{
    init( rows,columns );
    setByScalar(x);
}

template <typename Type>
Matrix<Type>::Matrix( int rows, int columns, const Type *arrays )
{
    init( rows,columns );
    copyFromArray( arrays );
}

template <typename Type>
Matrix<Type>::~Matrix()
{
    destroy();
}


/**
 * 重载赋值运算符‘=’以方便矩阵间赋值
 */
template <typename Type>
Matrix<Type>& Matrix<Type>::operator=( const Matrix<Type> &A )
{
    if( pv0 == A.pv0 )
        return *this;

    if( nRow == A.nRow && nColumn == A.nColumn )
        copyFromArray( A.pv0 );
    else
    {
        destroy();
        init( A.nRow, A.nColumn );
        copyFromArray( A.pv0 );
    }

    return *this;
}


/**
 * 重载赋值运算符‘=’以方便给矩阵所有元素赋一个常数值
 */
template <typename Type>
inline Matrix<Type>& Matrix<Type>::operator=( const Type &x )
{
    setByScalar( x );

    return *this;
}


/**
* 重载运算符‘[]’以方便拿出矩阵中的行，进行边界检查
 */
template <typename Type>
inline Type* Matrix<Type>::operator[]( int i )
{
#ifdef BOUNDS_CHECK
    assert( 0 <= i );
    assert( i < nRow );
#endif

    return prow0[i];
}

template <typename Type>
inline const Type* Matrix<Type>::operator[]( int i ) const
{
#ifdef BOUNDS_CHECK
    assert( 0 <= i );
    assert( i < nRow );
#endif

    return prow0[i];
}


/**
 * 重载运算符‘（）’以方便拿出矩阵中的元素，进行边界检查
 */
template <typename Type>
inline Type& Matrix<Type>::operator()( int row, int column )
{
#ifdef BOUNDS_CHECK
    assert( 1 <= row );
    assert( row <= nRow ) ;
    assert( 1 <= column);
    assert( column <= nColumn );
#endif

    return  prow1[row][column];
}

template <typename Type>
inline const Type& Matrix<Type>::operator()( int row, int column ) const
{
#ifdef BOUNDS_CHECK
    assert( 1 <= row );
    assert( row <= nRow ) ;
    assert( 1 <= column);
    assert( column <= nColumn );
#endif

    return  prow1[row][column];
}


/**
 * 类型转换函数
 */
template <typename Type>
inline Matrix<Type>::operator Type*()
{
    return pv0;
}

template <typename Type>
inline Matrix<Type>::operator const Type*() const
{
    return pv0;
}

//template <typename Type>
//inline Matrix<Type>::operator Type**()
//{
//	return prow0;
//}
//
//template <typename Type>
//inline Matrix<Type>::operator const Type**() const
//{
//	return prow0;
//}


/**
 * 得到矩阵的元素总数
 */
template <typename Type>
inline long Matrix<Type>::size() const
{
    return nTotal;
}


/**
 * 得到矩阵的长宽
 */
template <typename Type>
int Matrix<Type>::dim( int dimension ) const
{
#ifdef BOUNDS_CHECK
    assert( dimension >= 1);
    assert( dimension <= 2);
#endif

    if( dimension == 1 )
        return nRow;
    else if( dimension == 2 )
        return nColumn;
    else
        return 0;
}

template <typename Type>
inline int Matrix<Type>::rows() const
{
    return nRow;
}

template <typename Type>
inline int Matrix<Type>::cols() const
{
    return nColumn;
}


/**
 * 重新分配矩阵的空间，改变其大小
 */
template <typename Type>
Matrix<Type>& Matrix<Type>::resize( int rows, int columns )
{
    if(  rows == nRow && columns == nColumn )
        return *this;

    destroy();
    init( rows, columns );

    return *this;
}


/**
 * 得到矩阵的行向量
 */
template <typename Type>
Vector<Type> Matrix<Type>::getRow( int row ) const
{
#ifdef BOUNDS_CHECK
    assert( row >= 0 );
    assert( row < nRow );
#endif

    Vector<Type> tmp( nColumn );
    for( int j=0; j<nColumn; ++j )
        tmp[j] = prow0[row][j];

    return tmp;
}


/**
 * 得到矩阵的列向量
 */
template <typename Type>
Vector<Type> Matrix<Type>::getColumn( int column ) const
{
#ifdef BOUNDS_CHECK
    assert( column >= 0 );
    assert( column < nColumn );
#endif

    Vector<Type> tmp( nRow );
    for( int i=0; i<nRow; ++i )
        tmp[i] = prow0[i][column];

    return tmp;
}


/**
 * 设置矩阵的行向量
 */
template <typename Type>
void Matrix<Type>::setRow( const Vector<Type> &v, int row )
{
#ifdef BOUNDS_CHECK
    assert( row >= 0 );
    assert( row < nRow );
    assert( v.dim() == nColumn );
#endif

    for( int j=0; j<nColumn; ++j )
        prow0[row][j] = v[j];
}


/**
 * 设置矩阵的列向量
 */
template <typename Type>
void Matrix<Type>::setColumn( const Vector<Type> &v, int column )
{
#ifdef BOUNDS_CHECK
    assert( column >= 0 );
    assert( column < nColumn );
    assert( v.dim() == nRow );
#endif

    for( int i=0; i<nRow; ++i )
        prow0[i][column] = v[i];
}


/**
 * 重载 “+=”复合赋值符号
 */
template <typename Type>
Matrix<Type>& Matrix<Type>::operator+=( const Type &x )
{
    Type **rowPtr = prow0;
    Type *colPtr = 0;

    for( int i=0; i<nRow; ++i )
    {
        colPtr = *rowPtr++;
        for( int j=0; j<nColumn; ++j )
            *colPtr++ += x;
    }

    return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator+=( const Matrix<Type> &rhs )
{
    assert( nRow == rhs.rows() );
    assert( nColumn == rhs.cols() );

    Type **rowPtrL = prow0;
    Type *colPtrL = 0;
    Type **rowPtrR = rhs.prow0;
    const Type *colPtrR = 0;

    for( int i=0; i<nRow; ++i )
    {
        colPtrL = *rowPtrL++;
        colPtrR = *rowPtrR++;
        for( int j=0; j<nColumn; ++j )
            *colPtrL++ += *colPtrR++;
    }

    return *this;
}


/**
 * 重载 “-=”复合赋值符号
 */
template <typename Type>
Matrix<Type>& Matrix<Type>::operator-=( const Type &x )
{
    Type **rowPtr = prow0;
    Type *colPtr = 0;

    for( int i=0; i<nRow; ++i )
    {
        colPtr = *rowPtr++;
        for( int j=0; j<nColumn; ++j )
            *colPtr++ -= x;
    }

    return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator-=( const Matrix<Type> &rhs )
{
    assert( nRow == rhs.rows() );
    assert( nColumn == rhs.cols() );

    Type **rowPtrL = prow0;
    Type *colPtrL = 0;
    Type **rowPtrR = rhs.prow0;
    const Type *colPtrR = 0;

    for( int i=0; i<nRow; ++i )
    {
        colPtrL = *rowPtrL++;
        colPtrR = *rowPtrR++;
        for( int j=0; j<nColumn; ++j )
            *colPtrL++ -= *colPtrR++;
    }

    return *this;
}


/**
 * 重载 “*=”复合赋值符号
 */
template <typename Type>
Matrix<Type>& Matrix<Type>::operator*=( const Type &x )
{
    Type **rowPtr = prow0;
    Type *colPtr = 0;

    for( int i=0; i<nRow; ++i )
    {
        colPtr = *rowPtr++;
        for( int j=0; j<nColumn; ++j )
            *colPtr++ *= x;
    }

    return *this;
}

// 提示：以下是矩阵元素与元素的逐一乘法
template <typename Type>
Matrix<Type>& Matrix<Type>::operator*=( const Matrix<Type> &rhs )
{
    assert( nRow == rhs.rows() );
    assert( nColumn == rhs.cols() );

    Type **rowPtrL = prow0;
    Type *colPtrL = 0;
    Type **rowPtrR = rhs.prow0;
    const Type *colPtrR = 0;

    for( int i=0; i<nRow; ++i )
    {
        colPtrL = *rowPtrL++;
        colPtrR = *rowPtrR++;
        for( int j=0; j<nColumn; ++j )
            *colPtrL++ *= *colPtrR++;
    }

    return *this;
}


/**
 *重载 “/=”复合赋值符号
 */
template <typename Type>
Matrix<Type>& Matrix<Type>::operator/=( const Type &x )
{
    Type **rowPtr = prow0;
    Type *colPtr = 0;

    for( int i=0; i<nRow; ++i )
    {
        colPtr = *rowPtr++;
        for( int j=0; j<nColumn; ++j )
            *colPtr++ /= x;
    }

    return *this;
}

// 提示：以下是矩阵元素与元素的逐一除法
template <typename Type>
Matrix<Type>& Matrix<Type>::operator/=( const Matrix<Type> &rhs )
{
    assert( nRow == rhs.rows() );
    assert( nColumn == rhs.cols() );

    Type **rowPtrL = prow0;
    Type *colPtrL = 0;
    Type **rowPtrR = rhs.prow0;
    const Type *colPtrR = 0;

    for( int i=0; i<nRow; ++i )
    {
        colPtrL = *rowPtrL++;
        colPtrR = *rowPtrR++;
        for( int j=0; j<nColumn; ++j )
            *colPtrL++ /= *colPtrR++;
    }

    return *this;
}


/**
 * 重载矩阵输出符号 “<<”
 */
template <typename Type>
ostream& operator<<( ostream &out, const Matrix<Type> &A )
{
    int rows = A.rows();
    int columns = A.cols();

    out << "size: " << rows << " by " << columns << "\n";
    for( int i=0; i<rows; ++i )
    {
        for( int j=0; j<columns; ++j )
            out << A[i][j] << "\t";
        out << "\n";
    }

    return out;
}


/**
 * 重载矩阵输入符号 “>>”
 */
template <typename Type>
istream& operator>>( istream &in, Matrix<Type> &A )
{
    int rows, columns;
    in >> rows >> columns;

    if( !( rows == A.rows() && columns == A.cols() ) )
        A.resize( rows, columns );

    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            in >> A[i][j];

    return in;
}


/**
 * 将矩阵每个元素取相反数
 */
template<typename Type>
Matrix<Type> operator-( const Matrix<Type> &A )
{
    int rows = A.rows();
    int columns = A.cols();

    Matrix<Type> tmp( rows, columns );
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            tmp[i][j] = -A[i][j];

    return tmp;
}


/**
 * 矩阵-常数加法
 */
template<typename Type>
inline Matrix<Type> operator+( const Matrix<Type> &A, const Type &x )
{
    Matrix<Type> tmp( A );
    return tmp += x;
}

template<typename Type>
inline Matrix<Type> operator+( const Type &x, const Matrix<Type> &A )
{
    return A + x;
}


/**
 * 矩阵-矩阵加法
 */
template<typename Type>
inline Matrix<Type> operator+( const Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    Matrix<Type> tmp( A1 );
    return tmp += A2;
}


/**
 * 矩阵-常数减法
 */
template<typename Type>
inline Matrix<Type> operator-( const Matrix<Type> &A, const Type &x )
{
    Matrix<Type> tmp( A );
    return tmp -= x;
}

template<typename Type>
inline Matrix<Type> operator-( const Type &x, const Matrix<Type> &A )
{
    Matrix<Type> tmp( A );
    return -tmp += x;
}


/**
 * 矩阵-矩阵减法
 */
template<typename Type>
inline Matrix<Type> operator-( const Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    Matrix<Type> tmp( A1 );
    return tmp -= A2;
}


/**
 *矩阵-常数乘法
 */
template <typename Type>
inline Matrix<Type> operator*( const Matrix<Type> &A, const Type &x )
{
    Matrix<Type> tmp( A );
    return tmp *= x;
}

template <typename Type>
inline Matrix<Type> operator*( const Type &x, const Matrix<Type> &A )
{
    return A * x;
}


/**
 * 矩阵-矩阵乘法
 */
template <typename Type>
Matrix<Type> operator*( const Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    assert( A1.cols() == A2.rows() );

    int rows = A1.rows();
    int columns = A2.cols();
//	int K = A1.cols();

    Matrix<Type> tmp( rows, columns );
//	for( int i=0; i<rows; ++i )
//		for( int j=0; j<columns; ++j )
//		{
//            tmp[i][j] = 0;
//			for( int k=0; k<K; ++k )
//			    tmp[i][j] += A1[i][k] * A2[k][j];
//		}

    mult( A1, A2, tmp );

    return tmp;
}


/**
 * 矩阵-向量乘法
 */
template <typename Type>
Vector<Type> operator*( const Matrix<Type> &A, const Vector<Type> &b )
{
    assert( A.cols() == b.dim() );

    int rows = A.rows();
//	int columns = A.cols();

    Vector<Type> tmp(rows);
//	for( int i=0; i<rows; ++i )
//	{
//		Type sum = 0;
//		for( int j=0; j<columns; ++j )
//			sum += A[i][j] * v[j];
//		tmp[i] = sum;
//	}

    mult( A, b, tmp );

    return tmp;
}


/**
 * 矩阵-常数除法
 */
template <typename Type>
inline Matrix<Type> operator/( const Matrix<Type> &A, const Type &x )
{
    Matrix<Type> tmp( A );
    return tmp /= x;
}

template <typename Type>
Matrix<Type> operator/( const Type &x, const Matrix<Type> &A )
{
    int rows = A.rows();
    int clumns = A.cols();

    Matrix<Type> tmp( rows,clumns );
    for( int i=0; i<rows; ++i )
        for( int j=0; j<clumns; ++j )
            tmp[i][j] = x / A[i][j];

    return tmp;
}


/**
 * 以下为矩阵乘法的优化版本，
 * 目标矩阵已经被分配
 */
template <typename Type>
Matrix<Type>& mult( const Matrix<Type> &A, const Matrix<Type> &B,
                    Matrix<Type> &C )
{
    int M = A.rows();
    int N = B.cols();
    int K = A.cols();

    assert( B.rows() == K );

    C.resize( M, N );//目标矩阵
    Type        sum;
    const Type  *pRow,
            *pCol;

    for( int i=0; i<M; i++ )
        for( int j=0; j<N; ++j )
        {
            pRow  = &A[i][0];
            pCol  = &B[0][j];
            sum = 0;

            for( int k=0; k<K; ++k )
            {
                sum += (*pRow) * (*pCol);
                pRow++;
                pCol += N;
            }
            C[i][j] = sum;
        }
    return C;
}


/**
 * 以下为矩阵-向量乘法的优化版本，
 * 目标向量已经被分配
 */
template <typename Type>
Vector<Type>& mult( const Matrix<Type> &A, const Vector<Type> &b,
                    Vector<Type> &c )
{
    int M = A.rows();
    int N = A.cols();

    assert( b.size() == N );

    c.resize( M );//目标向量
    Type        sum;
    const Type  *pRow,
            *pCol;

    for( int i=0; i<M; i++ )
    {
        pRow  = &A[i][0];
        pCol  = &b[0];
        sum = 0;

        for( int j=0; j<N; ++j )
        {
            sum += (*pRow) * (*pCol);
            pRow++;
            pCol++;
        }
        c[i] = sum;
    }
    return c;
}


/**
 * 矩阵-矩阵 元素逐一乘法
 */
template<typename Type>
inline Matrix<Type> elemMult( const Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    Matrix<Type> tmp( A1 );
    return tmp *= A2;
}

template <typename Type>
inline Matrix<Type>& elemMultEq( Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    return A1 *= A2;
}


/**
 * 矩阵-矩阵 元素逐一除法
 */
template <typename Type>
inline Matrix<Type> elemDivd( const Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    Matrix<Type> tmp( A1 );
    return tmp /= A2;
}

template <typename Type>
inline Matrix<Type>& elemDivdEq( Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    return A1 /= A2;
}


/**
 * 矩阵转置
 */
template <typename Type>
Matrix<Type> trT( const Matrix<Type> &A )
{
    int rows = A.cols();
    int clumns = A.rows();

    Matrix<Type> tmp( rows, clumns );
    for( int i=0; i<rows; ++i )
        for( int j=0; j<clumns; ++j )
            tmp[i][j] = A[j][i];

    return tmp;
}


/**
 * 矩阵共轭转置
 */
template <typename Type>
Matrix<Type> trH( const Matrix<Type> &A )
{
    int rows = A.cols();
    int clumns = A.rows();

    Matrix<Type> tmp( rows, clumns );
    for( int i=0; i<rows; ++i )
        for( int j=0; j<clumns; ++j )
            tmp[i][j] = conj(A[j][i]);

    return tmp;
}


/**
 * 矩阵-矩阵 间 转置-乘法 形如: A^T * B
 */
template <typename Type>
Matrix<Type> trMult( const Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    assert( A1.rows() == A2.rows() );

    int rows = A1.cols();
    int columns = A2.cols();
    int K = A1.rows();

    Matrix<Type> tmp( rows, columns );
//	for( int i=0; i<rows; ++i )
//		for( int j=0; j<columns; ++j )
//		{
//			Type sum = 0;
//			for( int k=0; k<K; ++k )
//			   sum += A1[k][i] * A2[k][j];
//			tmp[i][j] = sum;
//		}
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            for( int k=0; k<K; ++k )
                tmp[i][j] += A1[k][i] * A2[k][j];

    return tmp;
}


/**
 * 矩阵-向量 间 转置-乘法， 形如: A^T * b.
 */
template <typename Type>
Vector<Type> trMult( const Matrix<Type> &A, const Vector<Type> &v )
{
    assert( A.rows() == v.dim() );

    int rows = A.rows();
    int columns = A.cols();

    Vector<Type> tmp( columns );
//	for( int i=0; i<columns; ++i )
//	{
//		Type sum = 0;
//		for( int j=0; j<rows; ++j )
//			sum += A[j][i] * v[j];
//		tmp[i] = sum;
//	}
    for( int i=0; i<columns; ++i )
        for( int j=0; j<rows; ++j )
            tmp[i] += A[j][i] * v[j];

    return tmp;
}


/**
 * 矩阵-矩阵 间 乘法-转置 形如: A * B^T.
 */
template <typename Type>
Matrix<Type> multTr( const Matrix<Type> &A1, const Matrix<Type> &A2 )
{
    assert( A1.cols() == A2.cols() );

    int rows = A1.rows();
    int columns = A2.rows();
    int K = A1.cols();

    Matrix<Type> tmp( rows, columns );
//	for( int i=0; i<rows; ++i )
//		for( int j=0; j<columns; ++j )
//		{
//			Type sum = 0;
//			for( int k=0; k<K; ++k )
//			   sum += A1[i][k] * A2[j][k];
//			tmp[i][j] = sum;
//		}
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            for( int k=0; k<K; ++k )
                tmp[i][j] += A1[i][k] * A2[j][k];

    return tmp;
}


/**
 * 向量-向量 间 乘法-转置， 形如: a * b^T.
 */
template <typename Type>
Matrix<Type> multTr( const Vector<Type> &a, const Vector<Type> &b )
{
    int rows = a.dim();
    int columns = b.dim();

    Matrix<Type> tmp( rows, columns );
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            tmp[i][j] = a[i]*b[j];

    return tmp;
}


/**
 * （复数）矩阵-矩阵 间 转置-乘法 形如: A^H * B.
 */
template <typename Type>
Matrix<complex<Type> > trMult( const Matrix<complex<Type> > &A1,
                               const Matrix<complex<Type> > &A2 )
{
    assert( A1.rows() == A2.rows() );

    int rows = A1.cols();
    int columns = A2.cols();
    int K = A1.rows();

    Matrix<complex<Type> > tmp( rows, columns );
//	for( int i=0; i<rows; ++i )
//		for( int j=0; j<columns; ++j )
//		{
//			Type sum = 0;
//			for( int k=0; k<K; ++k )
//			   sum += A1[k][i] * A2[k][j];
//			tmp[i][j] = sum;
//		}
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            for( int k=0; k<K; ++k )
                tmp[i][j] += conj(A1[k][i]) * A2[k][j];

    return tmp;
}


/**
 * （复数）矩阵-向量 间 转置-乘法 形如: A^H * b.
 */
template <typename Type>
Vector<complex<Type> > trMult( const Matrix<complex<Type> > &A,
                               const Vector<complex<Type> > &v )
{
    assert( A.rows() == v.dim() );

    int rows = A.rows();
    int columns = A.cols();

    Vector<complex<Type> > tmp( columns );
//	for( int i=0; i<columns; ++i )
//	{
//		Type sum = 0;
//		for( int j=0; j<rows; ++j )
//			sum += A[j][i] * v[j];
//		tmp[i] = sum;
//	}
    for( int i=0; i<columns; ++i )
        for( int j=0; j<rows; ++j )
            tmp[i] += conj(A[j][i]) * v[j];

    return tmp;
}


/**
 * （复数）矩阵-矩阵 间 乘法-转置 形如: A * B^H.
 */
template <typename Type>
Matrix<complex<Type> > multTr( const Matrix<complex<Type> > &A1,
                               const Matrix<complex<Type> > &A2 )
{
    assert( A1.cols() == A2.cols() );

    int rows = A1.rows();
    int columns = A2.rows();
    int K = A1.cols();

    Matrix<complex<Type> > tmp( rows, columns );
//	for( int i=0; i<rows; ++i )
//		for( int j=0; j<columns; ++j )
//		{
//			Type sum = 0;
//			for( int k=0; k<K; ++k )
//			   sum += A1[i][k] * A2[j][k];
//			tmp[i][j] = sum;
//		}
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            for( int k=0; k<K; ++k )
                tmp[i][j] += A1[i][k] * conj(A2[j][k]);

    return tmp;
}


/**
 * （复数）向量-向量 间 乘法-转置 形如: a * b^H.
 */
template <typename Type>
Matrix<complex<Type> > multTr( const Vector<complex<Type> > &a,
                               const Vector<complex<Type> > &b )
{
    int rows = a.dim();
    int columns = b.dim();

    Matrix<complex<Type> > tmp( rows, columns );
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            tmp[i][j] = a[i]*conj(b[j]);

    return tmp;
}


/**
 * 生成单位矩阵
 */
template <typename Type>
Matrix<Type> eye( int N, const Type &x )
{
    Matrix<Type> tmp( N, N );
    for( int i=0; i<N; ++i )
        tmp[i][i] = x;

    return tmp;
}


/**
 * 取得矩阵的对角线元素
 */
template <typename Type>
Vector<Type> diag( const Matrix<Type> &A )
{
    int nColumn = A.rows();
    if( nColumn > A.cols() )
        nColumn = A.cols();

    Vector<Type> tmp( nColumn );
    for( int i=0; i<nColumn; ++i )
        tmp[i] = A[i][i];

    return tmp;
}


/**
 * 将已有的对角线元素（数组存储）装入矩阵对角线
 */
template <typename Type>
Matrix<Type> diag( const Vector<Type> &d )
{
    int N = d.size();

    Matrix<Type> tmp( N, N );
    for( int i=0; i<N; ++i )
        tmp[i][i] = d[i];

    return tmp;
}


/**
 * 计算矩阵的Frobenius norm
 */
template <typename Type>
Type norm( const Matrix<Type> &A )
{
    int m = A.rows();
    int n = A.cols();

    Type sum = 0;
    for( int i=1; i<=m; ++i )
        for( int j=1; j<=n; ++j )
            sum += A(i,j) * A(i,j);

    return sqrt(sum);
}

template <typename Type>
Type norm( const Matrix<complex<Type> > &A )
{
    int m = A.rows();
    int n = A.cols();

    Type sum = 0;
    for( int i=1; i<=m; ++i )
        for( int j=1; j<=n; ++j )
            sum += norm(A(i,j));

    return sqrt(sum);
}


/**
 * 交换两个矩阵
 */
template <typename Type> void swap( Matrix<Type> &lhs, Matrix<Type> &rhs )
{
    int m = lhs.rows();
    int n = lhs.cols();

    assert( m == rhs.rows() );
    assert( n == rhs.cols() );

    for( int i=1; i<=m; ++i )
        for( int j=1; j<=n; ++j )
            swap( lhs(i,j), rhs(i,j) );
}


/**
 * 计算矩阵的每个列向量的各元素的和
 */
template <typename Type>
Vector<Type> sum( const Matrix<Type> &A )
{
    int m = A.rows();
    int n = A.cols();
    Vector<Type> sum(n);

    for( int j=1; j<=n; ++j )
        for( int i=1; i<=m; ++i )
            sum(j) += A(i,j);

    return sum;
}


/**
 * 找到矩阵的每个列向量中最小元素
 */
template <typename Type>
Vector<Type> min( const Matrix<Type> &A )
{
    int m = A.rows();
    int n = A.cols();
    Vector<Type> sum(n);

    for( int j=1; j<=n; ++j )
    {
        Type tmp = A(1,j);
        for( int i=2; i<m; ++i )
            if( tmp > A(i,j) )
                tmp = A(i,j);
        sum(j) = tmp;
    }

    return sum;
}


/**
 *找到矩阵的每个列向量中最大元素
 */
template <typename Type>
Vector<Type> max( const Matrix<Type> &A )
{
    int m = A.rows();
    int n = A.cols();
    Vector<Type> sum(n);

    for( int j=1; j<=n; ++j )
    {
        Type tmp = A(1,j);
        for( int i=2; i<m; ++i )
            if( tmp < A(i,j) )
                tmp = A(i,j);
        sum(j) = tmp;
    }

    return sum;
}


/**
 * 矩阵列向量平均值
 */
template <typename Type>
inline Vector<Type> mean( const Matrix<Type> &A )
{
    return sum(A) / Type(A.rows());
}


/**
 * 将实数矩阵转换为复数矩阵
 */
template <typename Type>
Matrix<complex<Type> > complexMatrix( const Matrix<Type> &rA )
{
    int rows = rA.rows();
    int columns = rA.cols();

    Matrix<complex<Type> > cA( rows, columns );
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            cA[i][j] = rA[i][j];

    return cA;
}

template <typename Type>
Matrix<complex<Type> > complexMatrix( const Matrix<Type> &mR,
                                      const Matrix<Type> &mI )
{
    int rows = mR.rows();
    int columns = mR.cols();

    assert( rows == mI.rows() );
    assert( columns == mI.cols() );

    Matrix<complex<Type> > cA( rows, columns );
    for( int i=0; i<rows; ++i )
        for( int j=0; j<columns; ++j )
            cA[i][j] = complex<Type>( mR[i][j], mI[i][j] );

    return cA;
}


/**
 * 得到一个复数矩阵的模
 */
template <typename Type>
Matrix<Type> abs( const Matrix<complex<Type> > &A )
{
    int m = A.rows(),
            n = A.cols();
    Matrix<Type> tmp( m, n );

    for( int i=0; i<m; ++i )
        for( int j=0; j<n; ++j )
            tmp[i][j] = abs( A[i][j] );

    return tmp;
}


/**
 * 得到一个复数矩阵的角
 */
template <typename Type>
Matrix<Type> arg( const Matrix<complex<Type> > &A )
{
    int m = A.rows(),
            n = A.cols();
    Matrix<Type> tmp( m, n );

    for( int i=0; i<m; ++i )
        for( int j=0; j<n; ++j )
            tmp[i][j] = arg( A[i][j] );

    return tmp;
}


/**
 * 得到一个复数矩阵的所有实部
 */
template <typename Type>
Matrix<Type> real( const Matrix<complex<Type> > &A )
{
    int m = A.rows(),
            n = A.cols();
    Matrix<Type> tmp( m, n );

    for( int i=0; i<m; ++i )
        for( int j=0; j<n; ++j )
            tmp[i][j] = A[i][j].real();

    return tmp;
}


/**
 * 得到一个复数矩阵的所有虚部
 */
template <typename Type>
Matrix<Type> imag( const Matrix<complex<Type> > &A )
{
    int m = A.rows(),
            n = A.cols();
    Matrix<Type> tmp( m, n );

    for( int i=0; i<m; ++i )
        for( int j=0; j<n; ++j )
            tmp[i][j] = A[i][j].imag();

    return tmp;
}
