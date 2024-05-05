/**
 ******************************************************************************
 ******************************************************************************
 * @file           : bit_math.h
 * @author         : Rezk Ahmed
 * @Layer           : Library
 ******************************************************************************
 ******************************************************************************
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(REG,BIT)               (REG|=(1<<BIT))                     // set a bit in the register
#define CLR_BIT(REG,BIT)               (REG&=(~(1<<BIT)))                  // clear a bit in the register
#define TOG_BIT(REG,BIT)               (REG^=(1<<BIT))                     // toggle a bit in the register
#define GET_BIT(REG,BIT)               ((REG>>BIT)&1)                      // Output is 0 or 1


#endif /* BIT_MATH_H_ */
