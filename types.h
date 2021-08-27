/*
 * types.h
 *      Author: Mahmoud Ayoub
 */

#ifndef TYPES_H_
#define TYPES_H_

/* Defined Structures
 * card data >> ST_cardData_t
 * terminal data >> ST_terminalData_t
 * transaction data >> ST_transaction_t
 *
 */
typedef unsigned char	 uint8_t;
typedef unsigned int	 uint32_t;
typedef signed int		 sint32_t;

typedef struct ST_cardData_t {
	uint8_t cardHolderName[25] ;
	uint8_t primaryAccountNumber[20] ;
	uint8_t cardExpirationData[6] ; //example : 12/19
}ST_cardData_t;

typedef struct ST_terminalData_t {
	float transAmount ;
	float maxTransAmount ;
	uint8_t transactionDate[11] ;
}ST_terminalData_t;

typedef enum EN_transStat_t {
	DECLINED ,
	APPROVED
}EN_transStat_t;

typedef struct ST_transaction_t {
	ST_cardData_t cardHolderData ;
	ST_terminalData_t transData ;
	EN_transStat_t transStat ;
}ST_transaction_t;

#endif /* TYPES_H_ */
