
 /******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: std_types.h
 *
 * Description: types for AVR
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/* boolean data type */
typedef unsigned char 			 boolean;

#ifndef FALSE
#define FALSE  (0u)
#endif

#ifndef TRUE
#define TRUE  (1u)
#endif

#define LOGIC_HIGH  (1u)
#define LOGIC_LOW   (0u)

#define NULL_PTR    ((void*)0)

typedef unsigned char   		 uint8;         /*   from 0  >> to 255 */
typedef signed char      		 sint8;    		/*   from -128  >> to 127 */
typedef unsigned short   		 uint16;		/*	 from 0 >> to 65535 */
typedef signed short 	 		 sint16; 		/*   from -32768 >> to  +32767           */
typedef unsigned long 	 		 uint32;		/*   from       0 >> to  4294967295       */
typedef signed long 			 sint32;		/*   from -2147483648 >> to  +2147483647      */
typedef unsigned long long 		 uint64;		/*   from  0 >> to  18446744073709551615  */
typedef signed long long 		 sint64; 		/*	 from -9223372036854775808 >> to  9223372036854775807 */
typedef float 					 float32;
typedef double					 float64;



#endif /* STD_TYPES_H_ */
