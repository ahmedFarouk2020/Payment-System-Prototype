/****************************************************/
/* Author:    Farouk                                 */
/* Date:      24th August 2021                       */
/* Version:   V01                                    */
/* File Name: DB.h                            */
/***************************************************/

#include "DB.h"
#include <stdlib.h>
#include <stdio.h>


database_t *db;  // global pointer to DB
static uint8_t size = 10; // DB occupied size

static uint8_t Is_sorted (database_t* arr)
{
    // iterate over the whole array
    for (int j = 0; j < size-1; j++)
    {
        // left element  >  right element (not sorted)
        if(arr[j].PAN > arr[j+1].PAN) {
            // printf("Not sorted\n");
            return 0;  // not sorted
        }
    }
    // printf("sorted\n");
    return 1;    // sorted
}


static void bubbleSort(database_t* arr)
{
    uint8_t dynamicSize = size; // decremented after each iteration on the array
    /* Bubble sort */
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < dynamicSize-1; j++)
        {

            if(arr[j].PAN > arr[j+1].PAN) {
                // SWAP
                database_t temp = {arr[j].PAN, arr[j].balance};
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        dynamicSize--;
    }
}


static uint8_t binarySearch(database_t* arr, int value)
{
    uint8_t start = 0;                // start position
    uint8_t end = size-1;          // end position
    uint8_t mid = (start + end) / 2;  // middle position
    uint8_t previousMid = 0;      // the previous value of mid to avoid infinite loop
    uint8_t state = 1;
    while (1)
    {
        // infinite loop?
        if (previousMid == mid)
        {
            // value is not found
            return -1;
        }

        // value is found?
        if (arr[mid].PAN == value)
        {
            return mid; // reurn index
        }

        // stuck and didn't find the value?
        if (start == end)
        {
            return -1;  // not found
        }

        // the value is at the right side?
        if (arr[mid].PAN < value)
        {
            // update positions
            start = mid+1;
            previousMid = mid;
            mid = (start + end) / 2;
            continue;
        }

        // the value is at the left side?
        if (arr[mid].PAN > value)
        {
            // update positions
            end = mid-1;
            previousMid = mid;
            mid = (start + end) / 2;
            continue;
        }
    }

}


database_t* create_database (void) {
    static int key = 1;  // exist

    // key exist?  open the door (create database)
    if (key == 1)
    {
        db = (database_t*) calloc(15, sizeof(database_t));
        key = 0; // close door
        return db;
    }
    // key not exist -> NULL
    return NULL;
}

void init_database (database_t* ptr) {

    // first user
    ptr[0].PAN = 123456789;
    ptr[0].balance = 100.00;
    // second user
    ptr[1].PAN = 234567891;
    ptr[1].balance = 6000.00;
    // 3rd user
    ptr[2].PAN = 567891234;
    ptr[2].balance = 3250.25;
    // 4th user
    ptr[3].PAN = 456789123;
    ptr[3].balance = 1500.12;
    // 5th user
    ptr[4].PAN = 258649173;
    ptr[4].balance = 500.00;
    // 6th user
    ptr[5].PAN = 654823719;
    ptr[5].balance = 2100.00;
    // 7th user
    ptr[6].PAN = 971362485;
    ptr[6].balance = 00.00;
    // 8th user
    ptr[7].PAN = 793148625;
    ptr[7].balance = 1.00;
    // 9th user
    ptr[8].PAN = 123123456;
    ptr[8].balance = 10.12;
    // 10th user
    ptr[9].PAN = 456789321;
    ptr[9].balance = 0.55;
}

uint8_t Is_PAN_exist(int PAN) {
    // if not sorted? sort it
    if ( !(Is_sorted(db)) )
    {
        bubbleSort(db);
    }

    return binarySearch(db, PAN);
}

uint8_t insert_user(int PAN, float balance) {
    // check if the user already in database
    if ( Is_PAN_exist(PAN) ) {
        // printf("User already exist\n");
        return 0; // exist (no insertion occurs)
    }
    static uint8_t total_size = 15;
    // array is full?
    if (size >= total_size)
    {
        // enlarge the array
        db = (database_t*)realloc(db, total_size+5);

        // data can't be realocated? (database if freed)
        if (db == NULL)
        {
            // start the process from beginning
            db = create_database();
            init_database(db);
            return 0; // can't add users anymore
        }

        // initialize database again
        init_database(db);

        // update total_size
        total_size += 5;
    }
    // add user
    db[size].balance = balance;
    db[size].PAN = PAN;
    // increment the occupied size
    size++ ;
    // printf("successfully updated\n");
    return 1; // successfully updated
}

static void printArray(database_t* arr)
{
    printf("Array Elements:\n");
    for (int i = 0; i < size; i++)
    {
        printf("(");
        printf("%d", arr[i].PAN);
        printf(",");
        printf("%.2f", arr[i].balance);
        printf("),");
    }
    printf("\n");
    fflush (stdin) ; 	fflush (stdout) ;
}

/* the main function is for debugging purposes */
/*
int main() {
    create_database();
    init_database(db);
    // printf("%d %f", db[5].PAN, db[5].balance);
    Is_sorted(db);
    // printArray(db);
    bubbleSort(db);
    // printArray(db);

    // int user_status = binarySearch(ptr, 123100000);
    // printf("%d\n", Is_PAN_exist(456789123));
    insert_user(234000891, 10000.00);
    insert_user(234000890, 10000.00);
    insert_user(234000895, 10000.00);
    insert_user(234000896, 10000.00);
    insert_user(234000897, 10000.00);
    insert_user(234000898, 10000.00);
    // printArray(db);
    free(db); // segmentation fault
    return 0;
}
*/
