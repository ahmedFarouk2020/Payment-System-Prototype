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

void app (void) ;
void approved (void) ;
void rejected (void) ;

int main () {
	// declaration
	int choice ;
	int PAN = 0; float balance; int status;
	create_database();
	init_database(db);
	while (1) {
		printf ("1 : new operation \n") ;
		printf ("2 : view history \n") ;
		printf ("3 : Add User \n") ;
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
		case 3 :
			printf ("Insert PAN = ") ;
			fflush (stdin);		fflush(stdout) ;
			scanf("%d", &PAN);
			printf("\n");
			printf ("Insert balance = ") ;
			fflush (stdin);		fflush(stdout) ;
			scanf("%f", &balance);
			printf("\n");
			status = insert_user(PAN,balance) ;
			if (status)
			{
				printf("Updated Successfully...\n");
				break;
			}
			printf("Not Updated, try again...\n");
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
			approved() ;
			trans_data.cardHolderData = card ;
			save_transaction(p_card , p_terminal,db) ;
		}
	}
	//printArray(db) ;
	free(card_Data_ptr);
	free(terminal_Data_ptr);
}

void approved (void) {
	printf ("Transaction is Approved \n") ;
}
void rejected (void) {
	printf ("Transaction is Declined \n") ;
}

/*
 * Test Case 1 :
 * name = mahmoud magdy
 * PAN = 123456789
 * expiry date = 12/21
 * transaction date = 10/10/2019
 * max amount = 5000
 * transaction amount = 200
 * >> APPROVED
 */

/*
 * Test Case 2 :
 * name = eslam emara
 * PAN = 234567891
 * expiry date = 12/18
 * transaction date = 10/10/2019
 * max amount = 5000
 * transaction amount = 200
 * >> DECLINED >> card expired
 */

/*
* Test Case 3 :
* name = mohamed
* PAN = 567891234
* expiry date = 12/21
* transaction date = 10/10/2019
* max amount = 5000
* transaction amount = 4000
* >> DECLINED >> amount greater than balance in DB
*
* Test Case 4 :
* name = omar
* PAN = 741852963
* expiry date = 12/21
* transaction date = 10/10/2019
* max amount = 5000
* transaction amount = 20
* >> DECLINED >> PAN NOT exist
*
* Test Case 5 :
* name = ali
* PAN = 654823719
* expiry date = 12/21
* transaction date = 10/10/2019
* max amount = 5000
* transaction amount = 7000
* >> DECLINED >> transaction greater than max amount
*
*
*/
