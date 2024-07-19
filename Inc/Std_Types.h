/**
 ******************************************************************************
 * @file           : Std_Types.h
 * @author         : Mostafa Asaad (https://github.com/M0stafa077)
 * @brief          : Project Standard Types Declaration.
 ******************************************************************************
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#define STD_HIGH		0x01
#define STD_LOW			0x00

typedef unsigned char 	uint8_t;
typedef unsigned short 	uint16_t;
typedef unsigned long 	uint32_t;


typedef uint8_t 		Std_ReturnType_t;

#define E_OK			(Std_ReturnType_t)(0x00)
#define E_NOT_OK		(Std_ReturnType_t)(0x01)




#endif /* STD_TYPES_H_ */
