/*
 * input.c
 *
 *  Created on: Aug 25, 2021
 *      Author: Mohamed AbdelAzeem
 */
#include "input.h"

int isNumber(uint8_t * s);
uint8_t get_size(uint8_t* s);
//check format for Expiry date
uint8_t check_format_ED(uint8_t* s);
//check format for transaction date
uint8_t check_format_TD(uint8_t* s);
void take_Card_Holder_Name(ST_cardData_t* cardData_ptr);
void take_Account_Number(ST_cardData_t* cardData_ptr);
void take_Expiry_Date(ST_cardData_t* cardData_ptr);
void take_Transaction_Date(ST_terminalData_t* terminalData_t_ptr);
void take_Transaction_Amount(ST_terminalData_t* terminalData_t_ptr);
void take_Maxtransaction_Amount(ST_terminalData_t* terminalData_t_ptr);

ST_cardData_t* get_card_data(void)
{
	setbuf(stdout, NULL); //Disable Buffer problems , comment when debugging

	ST_cardData_t* cardData_ptr = (ST_cardData_t*)malloc(sizeof(ST_cardData_t));


	/********************* Card data input  ******************************/
	 take_Card_Holder_Name(cardData_ptr);

	/********************* Pin Number input ******************************/
	 take_Account_Number(cardData_ptr);

	 /******************************************************/
	 take_Expiry_Date( cardData_ptr);

	 return cardData_ptr;
}

ST_terminalData_t* get_terminal_data (void)
{
	ST_terminalData_t* terminalData_t_ptr = (ST_terminalData_t*)malloc(sizeof(ST_terminalData_t));

	take_Transaction_Date(terminalData_t_ptr);

	take_Maxtransaction_Amount(terminalData_t_ptr);

	take_Transaction_Amount(terminalData_t_ptr);

	return terminalData_t_ptr;
}


int isNumber(uint8_t * s)
{
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (!isdigit(s[i]))
              return 0;
    }
    return 1;
}
uint8_t get_size(uint8_t* s)
{
	uint8_t size = 0;
	 for (int i = 0; s[i]!= '\0'; i++)
	    {
	       size++;
	    }
	 return size ;
}

uint8_t check_format_ED(uint8_t* s)
{
	uint8_t month = 0;
	uint8_t year = 0 ;
	uint8_t side = 0 ;
	for (int i = 0; s[i]!= '\0'; i++)
	{
		if(s[i] != '/')
		{
			if(side == 0)
			{
				month++;
			}
			else
			{
				year++;
			}
		}
		else
		{
			side = 1;
		}
	}
	if(month == 2 && year == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t check_format_TD(uint8_t* s)
{
	uint8_t month = 0;
	uint8_t day = 0 ;
	uint8_t year = 0 ;
	uint8_t side = 0 ;
	for (int i = 0; s[i]!= '\0'; i++)
	{
		if(s[i] != '/')
		{
			if(side == 0)
			{
				day++;
			}
			else if(side == 1)
			{
				month++;
			}
			else if(side == 2)
			{
				year++;
			}
		}
		else
		{
			side += 1;
		}
	}
	if(month == 2 && day == 2 && year == 4 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void take_Card_Holder_Name(ST_cardData_t* cardData_ptr)
{

	printf("Please Enter Card Data: \n");
	uint8_t tempName[25];
	uint8_t accepted0 = 1;
	do{
		printf("Please Enter the Card Holder Name: \n");
		fflush(stdout);//Clears the stdout buffer
		scanf(" %s", tempName );

		uint8_t nameSize= get_size(tempName);

		printf("%d\n", nameSize);
		if(nameSize > 25 )
		{
			//assumption : Pin is 9 digits
			printf("Invalid Pin Number. \n");
			accepted0 = 0;
		}
		else
		{
			accepted0 = 1;
		}

		if(isNumber(tempName))
		{
			accepted0 = 0;
		}
		else
		{
			accepted0 &= 1;
		}
		printf("%s\n", tempName);
		uint8_t lastIndex = 23;
		for(int i =0 ; tempName[i] != '\0';i++)
		{
			cardData_ptr->cardHolderName[i] = tempName[i];
			printf("%c",cardData_ptr->cardHolderName[i]);
			lastIndex= i ;
		}
		cardData_ptr->cardHolderName[lastIndex+1] = '\0';
		printf("\n");

	}while(accepted0 == 0);
}


void take_Account_Number(ST_cardData_t* cardData_ptr)
{
	uint8_t tempPin[20];
	uint8_t accepted = 1;
	do{
		printf("Please Enter the Primary Account Number: \n");
		fflush(stdout);//Clears the stdout buffer
		scanf("%s", tempPin );

		uint8_t pinSize= get_size(tempPin);

		if(pinSize != 9 )
		{
			//assumption : Pin is 9 digits
			printf("Invalid Pin Number. \n");
			accepted = 0;
		}
		else
		{
			accepted= 1;
		}

		if(!isNumber(tempPin))
		{
			accepted = 0;
		}
		else
		{
			accepted &= 1;
		}

		printf("%s\n", tempPin);
		for(int i =0 ; tempPin[i] != '\0';i++)
		{
			cardData_ptr->primaryAccountNumber[i] = tempPin[i];
			printf("%c",cardData_ptr->primaryAccountNumber[i]);
		}
		cardData_ptr->primaryAccountNumber[9] = '\0';
		printf("\n");

	}while(accepted == 0);
}

void take_Expiry_Date(ST_cardData_t* cardData_ptr)
{
	uint8_t accepted2 = 1;
	uint8_t tempDate[6];
	do{

		printf("Please card Expiry Date: \n");
		fflush(stdout);//Clears the stdout buffer
		scanf("%s", tempDate );

		uint8_t DateSize= get_size(tempDate);

		if(DateSize != 5) //example : 12/19
		{
			printf("Invalid Expiry Date!. \n");
			accepted2 = 0;
		}
		else
		{
			accepted2= 1;
		}

		if(!check_format_ED(tempDate))
		{
			printf("Invalid Expiry Date!.\n");
			accepted2 = 0;
		}
		else
		{
			accepted2 &= 1;
		}

		printf("%s\n", tempDate);
		for(int i =0 ; tempDate[i] != '\0';i++)
		{
			cardData_ptr->cardExpirationData[i] = tempDate[i];
			printf("%c",cardData_ptr->cardExpirationData[i]);
		}
		printf("\n");

		cardData_ptr->cardExpirationData[5] = '\0';
	}while(accepted2 == 0);
}


void take_Transaction_Date(ST_terminalData_t* terminalData_t_ptr)
{

	uint8_t accepted = 1;
	uint8_t tempDate[11];
	do{

		printf("Please card Expiry Date: \n");
		fflush(stdout);//Clears the stdout buffer
		scanf("%s", tempDate );

		uint8_t DateSize= get_size(tempDate);

		if(DateSize != 10) //example : 12/19
		{
			printf("Invalid Transaction Date!. \n");
			accepted = 0;
		}
		else
		{
			accepted= 1;
		}

		if(!check_format_TD(tempDate))
		{
			printf("Invalid Transaction Date!.\n");
			accepted = 0;
		}
		else
		{
			accepted &= 1;
		}

		printf("%s\n", tempDate);
		for(int i =0 ; tempDate[i] != '\0';i++)
		{
			terminalData_t_ptr->transactionDate[i] = tempDate[i];
			printf("%c",terminalData_t_ptr->transactionDate[i]);
		}
		printf("\n");

		terminalData_t_ptr->transactionDate[10] = '\0';  //0 - 9 + '\0'
	}while(accepted == 0);

}



void take_Transaction_Amount(ST_terminalData_t* terminalData_t_ptr)
{
	 float  tempAmount;
	uint8_t accepted = 1;
	do{
		printf("Please Enter the transaction Amount: \n");
		fflush(stdout);//Clears the stdout buffer
		scanf("%f", &tempAmount );

		if(tempAmount > terminalData_t_ptr->maxTransAmount)
		{
			accepted = 0 ;
			printf("Transaction amount exceded maximum transaction amount ");
		}
		else
		{
			accepted = 1;
		}

		printf("%f\n", tempAmount);
		terminalData_t_ptr->transAmount =tempAmount ;

	}while(accepted == 0);
}

void take_Maxtransaction_Amount(ST_terminalData_t* terminalData_t_ptr)
{
	 float  tempAmount;
	uint8_t accepted = 1;
	do{
		printf("Please Enter Maximum transaction Amount: \n");
		fflush(stdout);//Clears the stdout buffer
		scanf("%f", &tempAmount );


		printf("%f\n", tempAmount);
		terminalData_t_ptr->maxTransAmount =tempAmount ;

	}while(accepted == 0);
}
