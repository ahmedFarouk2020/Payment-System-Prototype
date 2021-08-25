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


ST_cardData_t* get_card_data (void) ;    /* return pointer to used structure to be passed to validation function */
ST_terminalData_t* get_terminal_data (void) ;    /* return pointer to used structure to be passed to validation function */
int validate_terminal_data (ST_terminalData_t *) ;  /* returns (0 >> failed) or (1 >> success)  */

EN_transStat_t check_expired (ST_cardData_t * , ST_terminalData_t *) ;
EN_transStat_t check_amount (ST_cardData_t * , ST_terminalData_t *) ;
EN_transStat_t validate_server (ST_cardData_t * , ST_terminalData_t *) ; /* returns an enum status  */
void save_transaction (ST_cardData_t * , ST_terminalData_t *) ; /* save transaction in server */

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
	p_card = get_card_data() ;  // get Card Data
	p_terminal = get_terminal_data() ;   // get Terminal Data
	if (validate_terminal_data(p_terminal) == 0) {   // invalid Terminal Data
		printf ("Invalid Terminal Data \n") ;
	}
	else {                               // valid Terminal Data
		if (check_expired(p_card , p_terminal) == DECLINED) {    // expired card
			rejected() ;
		}
		else if (check_expired(p_card , p_terminal) == APPROVED) {    // not expired card
			if (check_amount(p_card , p_terminal) == DECLINED) {      // too much amount
				rejected() ;
			}
			else if (check_amount(p_card , p_terminal) == APPROVED) {   // not too much amount
				if (validate_server(p_card , p_terminal) == DECLINED) {  // data doesn't match with server data
					rejected() ;
				}
				else if (validate_server(p_card , p_terminal) == APPROVED) {   // data matches with server data
					approved() ;
					save_transaction(p_card , p_terminal) ;
				}
			}
		}
	}
}

void approved (void) {
	printf ("Transaction is Approved \n") ;
}
void rejected (void) {
	printf ("Transaction is Declined \n") ;
}

