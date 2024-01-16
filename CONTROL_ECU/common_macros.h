 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Commonly used Macros
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* TO SET BIT IN ANY REGISTER */
#define		SET_BIT(REG,BIT_NUM)		(REG |= (1<<BIT_NUM))

/*TO CLEAR BIT IN ANY REGESTER */
#define 	CLEAR_BIT(REG,BIT_NUM)		(REG &= (~(1<<BIT_NUM)))

/* TOTOGGLE BIT IN ANY REGESTER */
#define 	TOGGLE_BIT(REG,BIT_NUM)		(REG ^= (1<<BIT_NUM))

/* Rotate right the register value with specific number of rotates */
#define 	ROR_BIT(REG,NUM)		( REG = (REG>>NUM) | (REG<<(8-NUM)) )

/* Rotate LEFT the register value with specific number of rotates */
#define 	ROL_BIT(REG,NUM)		( REG = (REG<<NUM) | (REG>>(8-NUM)) )

/* Check if a specific bit is set in any register and return true if yes */
#define		BIT_IS_SET(REG,BIT_NUM)		( REG & (1<<BIT_NUM) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define		BIT_IS_CLEAR(REG,BIT_NUM)		( !(REG & (1<<BIT_NUM)) )

/* Macro GET_BIT to read certain bit in a register or variable. The Macro
inputs are the register or variable and the bit number */
#define		GET_BIT(REG,BIT_NUM)			( ( REG & (1<<BIT_NUM) ) >> BIT_NUM )


#endif /* COMMON_MACROS_H_ */
