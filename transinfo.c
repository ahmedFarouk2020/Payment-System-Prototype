#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "transinfo.h"

struct  Node* head = NULL;

struct Node
{
    uint8_t PAN[10];
    uint8_t name[30];
    f32_t balance;
    struct Node* next;
};

struct Node* add(uint8_t* pan,uint8_t* name,f32_t balance)

{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    strcpy(new_node->name,name);
    strcpy(new_node->PAN,pan);
    new_node->balance = balance;
    new_node->next = head;
    head = new_node;
    return head;

}

void saveList()
{
  //  sorting(head,choice);

    FILE *fptr;
    fptr = fopen("SavedList.txt","w");
    if(fptr == NULL)
    {
        perror("Error!");
    }
    struct Node *current_node = head;
    while ( current_node != NULL)
    {
        fprintf(fptr,"\%s-",current_node->PAN);
        fprintf(fptr,"%s+",current_node->name);
        fprintf(fptr,"%f)\n",current_node->balance);
        current_node = current_node->next;
    }
    fclose(fptr);
}

float str2float(uint8_t *str)
{
  return strtof(str,NULL);
}
void vParseData(uint8_t* name , uint8_t* pan ,f32_t* balance,uint8_t* data)
{
  uint8_t name_count = 0;
  uint8_t balance_str[9];
  uint8_t s =0;

      for( name_count=0; name_count<9; name_count++)
      {
        pan[name_count] = data[name_count];
      }
      name_count+=1;
      while (data[name_count] != '+')
      {
        name[s] = data[name_count];
        s++;
        name_count++;
      }
      s=0;
      name_count++;
      while (data[name_count] != ')')
      {
        balance_str[s] = data[name_count];
        s++;
        name_count++;
      }
      *balance = str2float(balance_str);
}
void view_history()
{
  uint8_t data[100][100];
  uint8_t pan[10];
  uint8_t name[30];
  f32_t balance;
  uint8_t data_count = 0;

  FILE *fp;
  fp = fopen( "transactions.txt", "r");
  if (fp == NULL){
      perror("\nError while opening the file.\n");
    }

  while(fgets(data[data_count], 100, fp))
  {
      data[data_count][strlen(data[data_count])] = '\0';
      data_count++;
  }
  fclose(fp);

  printf("NAME\t\t\t\tPAN\t\t\tBALANCE\n");
  for (int i = 0 ; i <data_count ; i++)
  {
    vParseData(name,pan,&balance,data[i]);
    printf("%s\t\t%s\t\t%f\n",name,pan,balance);
    add(pan,name,balance);
  }

}

int main()
{
view_history();
saveList();
    return 0;
}
