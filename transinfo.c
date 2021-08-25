#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "transinfo.h"

void save2txt(ST_transaction_t trans)
{
    FILE *fptr;
    fptr = fopen("transactions.txt","a");
    if(fptr == NULL)
    {
        perror("Error!");
    }

        fprintf(fptr,"%s\t\t",trans.cardHolderData.cardHolderName);
        fprintf(fptr,"%s\t\t",trans.cardHolderData.primaryAccountNumber);
        fprintf(fptr,"%s\t\t",trans.transData.transactionDate);
        fprintf(fptr,"%f\t",trans.transData.transAmount);
        fprintf(fptr,"%d\t\n",trans.transStat );

    fclose(fptr);
}


void view_history()
{
  uint8_t data[150][150];
  uint8_t data_count = 0;

  FILE *fp;
  fp = fopen( "transactions.txt", "r");
  if (fp == NULL){
      perror("\nError while opening the file.\n");
    }

  while(fgets(data[data_count], 150, fp))
  {
      data[data_count][strlen(data[data_count])] = '\0';
    //  printf("%s",data[data_count]);
      data_count++;
  }
  printf("NAME\t\t\tPAN\t\t\tDATE\t\t\tAMOUNT\t\tAPPROVAL\n");
  for(int i = data_count ; i>=0;i--)
  {
      printf("%s",data[i]);
  }
  fclose(fp);
}

int main()
{

    ST_transaction_t t = {{"asdasdasda","1234568946","12345"},{160.5,5000,"19/05/2158"},APPROVED};
    save2txt(t);
    view_history();

    return 0;
}
