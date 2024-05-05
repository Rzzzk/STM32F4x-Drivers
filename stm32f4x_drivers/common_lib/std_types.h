/**
 ******************************************************************************
 ******************************************************************************
 * @file           : std_types.h
 * @author         : Rezk Ahmed
 * @Layer           : Library
 ******************************************************************************
 ******************************************************************************
 */



#ifndef STD_TYPES_H_
#define STD_TYPES_H_


typedef unsigned char          u8;
typedef signed char            s8;

typedef unsigned short int     u16;
typedef signed short int       s16;

typedef unsigned long int      u32;
typedef signed long int        s32;

#ifndef __vo
#define __vo  volatile
#endif

#ifndef __weak
#define __weak __attribute__ ((weak))
#endif

#ifndef NULL
#define NULL  (void *)0
#endif

#ifndef SET
#define SET         1
#endif

#ifndef RESET
#define RESET       0
#endif

#ifndef ENABLE
#define ENABLE      SET
#endif

#ifndef DISABLE
#define DISABLE		RESET
#endif


#endif /* STD_TYPES_H_ */
