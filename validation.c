#include "types.h"
#include "validation.h"
#include "DB.h"
#include <stdlib.h>
extern uint32_t g_current_pan ;
EN_transStat_t validate_terminal_data(ST_cardData_t* cardData, ST_terminalData_t* terminalData)
{

    uint32_t c_month = 0, c_year=0, t_month=0, t_year=0;
    c_month = ((cardData->cardExpirationData[0])-'0') * 10 + ((cardData->cardExpirationData[1]-'0'));
    c_year = ((cardData->cardExpirationData[3])-'0') * 10 + ((cardData->cardExpirationData[4]-'0'));
    t_month = ((terminalData->transactionDate[3])-'0') * 10 + ((terminalData->transactionDate[4]-'0'));
    t_year = ((terminalData->transactionDate[8]-'0') * 10) + ((terminalData->transactionDate[9]-'0'));

   // printf ("Inside validate terminal data function \n") ;
    printf ("card month = %d \n" , c_month ) ;
    printf ("card year = %d \n" , c_year ) ;
    printf ("terminal month = %d \n" , t_month ) ;
    printf ("terminal year = %d \n" , t_year ) ;
    if((c_month >= t_month) && (c_year >= t_year))
    {
        if((terminalData->transAmount) <= (terminalData->maxTransAmount))
        {
            return APPROVED;
        }
        else
        {
            // exceeded the maximum amount
            return DECLINED;
        }
    }
    else
    {
        //expired card
       return DECLINED;
    }
}
EN_transStat_t validate_server (ST_cardData_t* cardData, ST_terminalData_t* terminalData , database_t* server)
{
    uint32_t account_idx = Is_PAN_exist(g_current_pan);
    if(account_idx != -1)
    {
        if((terminalData->transAmount) <= (server[account_idx].balance))
        {
            return APPROVED;
        }
        else
        {
            return DECLINED;
        }
    }
    else
    {
        return DECLINED;
    }
}
