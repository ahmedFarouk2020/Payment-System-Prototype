/****************************************************/
/* Author:    Farouk                                 */
/* Date:      24th August 2021                       */
/* Version:   V01                                    */
/* File Name: database.h                            */
/***************************************************/

#ifndef DATABASE_H_
#define DATABASE_H_

typedef unsigned char uint8_t;

typedef struct database
{
    int PAN;        // specific number for each card
    float balance;  // money in the card
}database_t;

/* Function Declaration */

/******
 *  Function Description
 *
 * 
 * 
 */
database_t* create_database (void);
void init_database (database_t* ptr);
// uint8_t Is_PAN_exist(int PAN);
// uint8_t insert_user(int PAN, float balance);

/* Static Functions */
static void bubbleSort(database_t* arr);
static uint8_t Is_sorted (database_t* arr);
static void printArray(database_t* arr);
// static uint8_t binarySearch(database_t* arr, int value);


#endif