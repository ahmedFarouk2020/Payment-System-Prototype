
#ifndef TRANSINFO_H_
#define TRANSINFO_H_

#include "types.h"
#include "DB.h"


void save_transaction(ST_cardData_t* cardData, ST_terminalData_t* terminalData);
void view_history();
void update_datebase(ST_cardData_t* cardData, ST_terminalData_t* terminalData,database_t* ptr);


#endif
