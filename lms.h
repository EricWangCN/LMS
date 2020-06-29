/*******************************************************************
 *          基于西安交通大学 M.Zhang 的LMS自适应滤波器程序
 *          北京交通大学 王子龙 wangzilong@bjtu.edu.cn
 *          用于小学期综合训练大作业
 *******************************************************************/

/*******************************************************************
 *                              lms.h
 *
 * 最小均方误差（LMS）算法是一类自适应滤波器，用于通过查找与产生误差信号的最小均方
 * （期望信号与实际信号之间的差）有关的滤波器系数来模拟期望滤波器。 这是一种随
 * 机梯度下降方法，因为仅根据当前时间的误差对滤波器进行调整。
 *
 * 该文件包含了三种LMS算法：传统的LMS算法，LMS-Newton算法和归一化LMS算法。
 *
 * 代码来源：Zhang Ming, zmjerry@163.com, 编写与2010年10月
 * 代码修改：王子龙, wangzilong@bjtu.edu.cn, CS1804, SCIT, BJTU
 * 代码修改日期：2020年06月29日 *
 *******************************************************************/

#ifndef LMS_H
#define LMS_H


#include "vector.h"
#include "matrix.h"


namespace splab
{

    template<typename Type>
    Type lms( const Type&, const Type&, Vector<Type>&, const Type& );

    template<typename Type>
    Type lmsNewton( const Type&, const Type&, Vector<Type>&,
                    const Type&, const Type&, const Type& );

    template<typename Type>
    Type lmsNormalize( const Type&, const Type&, Vector<Type>&,
                       const Type&, const Type& );


#include "lms-impl.h"

}
// namespace splab


#endif
