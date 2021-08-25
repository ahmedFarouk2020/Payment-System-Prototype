/*
 * input.h
 *
 *  Created on: Aug 25, 2021
 *      Author: MohamedAbdelAzeem
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "types.h"
#include <stdio.h>
#include "input.h"
#include <stdlib.h>
#include <ctype.h>

ST_cardData_t* get_card_data (void) ;    /* return pointer to used structure to be passed to validation function */
ST_terminalData_t* get_terminal_data (void) ;    /* return pointer to used structure to be passed to validation function */

#endif /* INPUT_H_ */
