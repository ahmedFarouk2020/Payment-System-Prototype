/*
 * main.c
 *      Author: Mahmoud Ayoub
 */
#include "stdio.h"
#include "stdint.h"
#include "types.h"     // for structures' definitions
#include "input.h"
#include "DB.h"
#include "transinfo.h"
#include "validation.h"

/*
 * NOTES : must include new header files which includes the each function prototype
 *
 */
ST_cardData_t card ;
ST_terminalData_t terminal ;


ST_cardData_t* p_card = NULL ;

ST_terminalData_t* p_terminal = NULL ;

extern database_t *db;
uint32_t g_current_pan ;

ST_transaction_t trans_data ;
ST_transaction_t* p_trans_data = &trans_data ;

//ST_cardData_t* get_card_data (void) ;      /* Access to the global pointer p_card */
//ST_terminalData_t* get_terminal_data (void) ;	 /* Access to the global pointer p_terminal */

//EN_transStat_t validate_terminal_data(ST_cardData_t* cardData, ST_terminalData_t* terminalData);  /* (check expiration + amount) returns (0 >> failed) or (1 >> success)  */
//EN_transStat_t validate_server (ST_cardData_t* cardData, ST_terminalData_t* terminalData , database_t* server) ;  	/* returns an enum status  */
//void save_transaction (ST_transaction_t* p_trans) ; 			/* save transaction in server */

void app (void) ;
//void view_history (void) ;
void approved (void) ;
void rejected (void) ;

int main () {
	int choice ;
	create_database();
	init_database(db);
	while (1) {
		printf ("1 : new operation \n") ;
		printf ("2 : view history \n") ;
		fflush (stdin);		fflush(stdout) ;
		scanf ("%d" , &choice) ;
		printf ("choice = %d \n" , choice) ;
		switch (choice) {
		case 1 :
			app () ;
			break ;
		case 2 :
			view_history() ;
			break ;
		}
	}
	return 0 ;
}

void app (void) {

	ST_cardData_t*  card_Data_ptr = get_card_data() ;  // get Card Data   (sure it is valid)
	p_card = card_Data_ptr;
	ST_terminalData_t* terminal_Data_ptr =  get_terminal_data() ;   // get Terminal Data  (sure it is valid)
	p_terminal =  terminal_Data_ptr;

	printf ("Card and Terminal data are collected \n") ;
	printf ("name = %s \n" , p_card->cardHolderName) ;
	printf ("expiry data = %s \n" , p_card->cardExpirationData) ;
	printf ("account number = %s \n" , p_card->primaryAccountNumber) ;

	if (validate_terminal_data(p_card , p_terminal) == DECLINED) {   // invalid Terminal Data (expired OR too much amount)
		printf ("rejected in terminal data validation \n") ;
		rejected() ;
	}
	else {                               // valid Terminal Data (Card Not expired + Not too much amount)
		if (validate_server(p_card , p_terminal , db) == DECLINED) {  // data doesn't match with server data
			printf ("rejected in server validation \n") ;
			rejected() ;
		}
		else if (validate_server(p_card , p_terminal , db) == APPROVED) {   // data matches with server data
			printf ("inside else if in main \n") ;
			approved() ;
			trans_data.cardHolderData = card ;
			save_transaction(p_card , p_terminal) ;
			update_datebase(p_card,p_terminal,db);
		}
	}
}

void approved (void) {
	printf ("Transaction is Approved \n") ;
}
void rejected (void) {
	printf ("Transaction is Declined \n") ;
}
