#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "transinfo.h"

/*
#include "DB.h"

void update_datebase(ST_transaction_t trans,database_t* ptr)
{
  int index = Is_PAN_exist(atoi(trans.cardHolderData.primaryAccountNumber));
  ptr[index].balance -= trans.transData.transAmount;
}
*/



/*
Function to swap two integers
Inputs: (pointer to uint32_t integer 1, pointer to uint32_t integer 2)
no return
*/
void vSwapInt(uint32_t*x , uint32_t*y)
{
  uint32_t temp = *x;
  *x = *y;
  *y = temp;
}
/*
Function to swap two strings
Inputs: (pointer to uint8_t string 1 , pointer to uint8_t string 2)
no return
*/
void vSwapStr (uint8_t* x , uint8_t* y)
{

uint8_t temp[150];
strcpy(temp,x);
strcpy(x,y);
strcpy(y,temp);

}
/*
  Function to sort 2-D array that contains all data
  based on Int array that contains integer PANs

  Parameters: (uint32_t* PAN array,uint8_t 2-D array[][MAXLINE],number of lines)
  no return

*/
void vSort(uint32_t* arr ,uint8_t (* arr2)[150], uint8_t arr_size)       //selection sort
{
  static uint32_t min = 0;
  static uint32_t count = 0;

  min = count;

  for(int i = count+1 ;i < arr_size ; i++){     //detect minimum in unsorted
    if (arr[i] < arr[min]){
      min = i;
    }
  }
  vSwapInt(&arr[min],&arr[count]);              //swap real minimum with first unsorted
  vSwapStr(arr2[min],arr2[count]);
  if(count<arr_size)
  {
    count++;                              //repeat for unsorted only
    vSort(arr,arr2,arr_size);
  }
}

/*
  Function to save new transaction to the text file
  Parameters -> ST_transaction_t that contains transaction info
  return -> none
*/
void save_transaction(ST_transaction_t trans)
{
    FILE *fptr;
    fptr = fopen("transactions.txt","a");               //'a' -> append to file
    if(fptr == NULL)
    {
        perror("Error!");
    }

        fprintf(fptr,"%-30s\t",trans.cardHolderData.cardHolderName);
        fprintf(fptr,"%s\t\t",trans.cardHolderData.primaryAccountNumber);
        fprintf(fptr,"%s\t\t",trans.transData.transactionDate);
        fprintf(fptr,"%-9f\t",trans.transData.transAmount);
        fprintf(fptr,"%d\t\n",trans.transStat );

    fclose(fptr);
    //update_datebase(trans,database_t* ptr);
}
/*
  Funtion to parse PAN number from the text file
  inputs: (2D array , uint32_t PANs array ,uint8_t number of lines)
  it modifies the second parameter as a return integer array.
  Return value -> none
*/
void vParsePAN(uint8_t (* data)[150],uint32_t* pan_int,uint8_t data_count)
{
  uint8_t pan[data_count][10];

  for(int i = 0 ; i<data_count;i++)
  {
    for (int j = 0;j<strlen(data[i]);j++){
        if(data[i][j] == '\t'){
            for (int k = 0 ; k<9;k++) {                   //PAN is 9 digit number
              pan[i][k] = data[i][j+1+k];               // two tabs before PAN
            }
            pan[i][9] = '\0';                         //terminate the string
            break;
        }
    }
  }
  for (int i = 0; i < data_count ; i++)
  {
    pan_int[i] = atoi(pan[i]);          //convert string to integer
  }
}
/*
    Function to print the matrix of data
    inputs (2-D array , number of lines)
    no return.
*/

void vPrintData(uint8_t (* data)[150],uint8_t data_count)
{
  printf("NAME\t\t\t\tPAN\t\t\tDATE\t\t\tAMOUNT\t\tAPPROVAL\n\n");
  for(int i = 0 ; i<data_count;i++){
      printf("%s",data[i]);
      printf("----------------------------------------------------------------------------------------------\n");
  }
}
/*
  Function to open the transactions text file and get data from it
  Inputs ->uint8_t 2D array
  it modifies the array as a return value.
  Return-> uint8_t that contains number of lines of the text file
*/

uint8_t u8GetDataFromFile(uint8_t (* data)[150])
{
  uint8_t data_count = 0;
  FILE *fp;
  fp = fopen( "transactions.txt", "r");           // 'r' -> Read mode
  if (fp == NULL){
      perror("\nError while opening the file.\n");
    }
  while(fgets(data[data_count], 150, fp)) {
      data[data_count][strlen(data[data_count])] = '\0';
      data_count++;
  }
  fclose(fp);
  return data_count;
}

/*
  Function to print the sorted transaction from the text file
  inputs -> none
  no return.
*/
void view_history()
{
  uint8_t data[150][150];
  uint8_t data_count = u8GetDataFromFile(data);
  uint32_t pan_int[data_count];

  vParsePAN(data,pan_int,data_count);
  vSort(pan_int,data,data_count);
  vPrintData(data,data_count);
}

/* Testing main function */

/*
int main()
{
  ST_transaction_t tr = {"Ahmed Farouk","125789635","15/5",255.5,5000,"11/20/2020",DECLINED};
  ST_transaction_t tr1 = {"Mahmoud Ayoub","953672058","10/5",918.5,5000,"05/10/2021",APPROVED};
  ST_transaction_t tr2 = {"Omar Tarek","731289607","15/5",695.5,5000,"15/20/2020",APPROVED};
  ST_transaction_t tr3 = {"Mohamed Abdelazem","862015689","13/5",1000,5000,"18/20/2020",APPROVED};
  ST_transaction_t tr4 = {"Eslam Anwar Emara","425638974","28/5",2657,5000,"19/5/2020",APPROVED};
  vSaveText(tr);
  vSaveText(tr1);
  vSaveText(tr2);
  vSaveText(tr3);
  vSaveText(tr4);
  vViewHistory();
}
*/
