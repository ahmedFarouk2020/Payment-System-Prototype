#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED
/*
* Function Description
*  first it checks the expiry date of the card if it's not expired then it checks for the amount required whether it's smaller
*  than the maximum amount or not
*/
EN_transStat_t validate_terminal_data(ST_cardData_t* cardData, ST_terminalData_t* terminalData);
/*
* Function Description
*  first it checks it checks if the PAN is exist in the database or not then it checks if the amount required is available in
*  the account or not
*/
EN_transStat_t validate_server (ST_cardData_t* cardData, ST_terminalData_t* terminalData , database_t* server);


#endif // VALIDATION_H_INCLUDED
