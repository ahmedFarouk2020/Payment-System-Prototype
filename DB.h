/****************************************************/
/* Author:    Farouk                                 */
/* Date:      24th August 2021                       */
/* Version:   V01                                    */
/* File Name: database.h                            */
/***************************************************/

#ifndef DATABASE_H_
#define DATABASE_H_
#include "stdint.h"

typedef unsigned char uint8_t;

typedef struct database
{
    int PAN;        // specific number for each card
    float balance;  // money in the card
}database_t;

/* Function Declaration */

/******
 *  Function Description:
 *      Create DB (dynamicly allocated array) once (we just need one array).
 *  Parameters: none
 *  return:
 *      pointer to the first location of DB
 */
database_t* create_database (void);

/******
 *  Function Description:
 *      assign initial values to DB.
 *  Parameters:
 *      pointer to the first location of DB
 *  return: none
 */
void init_database (database_t* ptr);

/******
 *  Function Description:
 *      search on a PAN in the database.
 *  Parameters:
 *      PAN (integer of 9 digits)
 *  return:
 *      the index of PAN (if exist) or 255 (if PAN not exist)
 */
int8_t Is_PAN_exist(int PAN);


/******
 *  Function Description:
 *      Insert user at the end of database.
 *  Parameters:
 *      PAN (integer of 9 digits),
 *      balance (total charge in card)
 *  return:
 *      0 -> inserted successfully
 *      1 -> not inserted (already exist)
 */
uint8_t insert_user(int PAN, float balance);

/* Static Functions */
static void bubbleSort(database_t* arr);
static uint8_t Is_sorted (database_t* arr);
void printArray(database_t* arr);
static int8_t binarySearch(database_t* arr, int value);


#endif
