/*******************************************************************
 *          基于西安交通大学 M.Zhang 的常量Header File
 *          北京交通大学 王子龙 wangzilong@bjtu.edu.cn
 *          用于小学期综合训练大作业
 *******************************************************************/


/*******************************************************************
 *                          constants.h
 *
 * 一些用于数值计算的常量
 *
 * 代码来源：Zhang Ming, zmjerry@163.com, 编写与2010年01月
 * 代码修改：王子龙, wangzilong@bjtu.edu.cn, CS1804, SCIT, BJTU
 * 代码修改日期：2020年07月01日
 ********************************************************************/


#ifndef	CONSTANTS_H
#define CONSTANTS_H


namespace splab
{

    const double	EPS		    = 2.220446049250313e-016;

    const double	PI		    = 3.141592653589793;
    const double	TWOPI	    = 6.283185307179586;
    const double	HALFPI	    = 1.570796326794897;
    const double	D2R 	    = 0.017453292519943;

    const double	EXP		    = 2.718281828459046;

    const double	RT2		    = 1.414213562373095;
    const double	IRT2	    = 0.707106781186547;

    const int		FORWARD	    = 1;
    const int		INVERSE	    = 0;

    const int		MAXTERM	    = 20;
    const int       INITSIZE    = 20;
    const int       EXTFACTOR   = 2;

}
// namespace splab


#endif
// CONSTANTS_H