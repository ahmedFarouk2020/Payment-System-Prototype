/*
 * main.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
#include "stdint.h"
#include "types.h"     // for structures' definitions
/*
 * NOTES : must include new header files which includes the each function prototype
 *
 */

ST_cardData_t card = {"name" , "account_number" , "expiry_date"} ;
ST_cardData_t* p_card = &card ;

ST_terminalData_t terminal = {2000.00 , 5000.00 , "trans date"} ;
ST_terminalData_t* p_terminal = &terminal ;

ST_transaction_t trans_data = {card , terminal , DECLINED} ;
ST_transaction_t* p_trans_data = &trans_data ;

void get_card_data (void) ;      /* Access to the global pointer p_card */
void get_terminal_data (void) ;	 /* Access to the global pointer p_terminal */

int validate_terminal_data (ST_terminalData_t * p_t) ;  /* (check expiration + amount) returns (0 >> failed) or (1 >> success)  */
EN_transStat_t validate_server (ST_transaction_t* p_trans) ; 	/* returns an enum status  */
void save_transaction (ST_transaction_t* p_trans) ; 			/* save transaction in server */

void app (void) ;
void view_history (void) ;
void approved (void) ;
void rejected (void) ;

int main () {
	int choice ;
	while (1) {
		printf ("1 : new operation \n") ;
		printf ("2 : view history \n") ;
		fflush (stdin);		fflush(stdout) ;
		scanf ("%d" , &choice) ;
		printf ("choice = %d \n" , choice) ;
		switch (choice) {
		case 1 :
			//app () ;
			break ;
		case 2 :
			//view_history() ;
			break ;
		}
	}
	return 0 ;
}

void app (void) {
	get_card_data() ;  // get Card Data   (sure it is valid)
	get_terminal_data() ;   // get Terminal Data  (sure it is valid)
	if (validate_terminal_data(p_terminal) == 0) {   // invalid Terminal Data (expired OR too much amount)
		rejected() ;
	}
	else {                               // valid Terminal Data (Card Not expired + Not too much amount)
		if (validate_server(p_trans_data) == DECLINED) {  // data doesn't match with server data
			rejected() ;
		}
		else if (validate_server(p_trans_data) == APPROVED) {   // data matches with server data
			approved() ;
			save_transaction(p_trans_data) ;
		}
	}
}

void approved (void) {
	printf ("Transaction is Approved \n") ;
}
void rejected (void) {
	printf ("Transaction is Declined \n") ;
}
