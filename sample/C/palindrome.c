#include <stdio.h>
#include <stdlib.h>

int revcompare(char *temp);

int main()
{
 char string[100],temp[50];
 int i , j , count =0, length =0;
 gets(string);

for( i=0; string[i] != '\0' ;i++){
  length++;
}
string[length] = '\0';

 for(i =0;  string[i] != '\0' ; i++){
   j = i;
   count =0;
   for( j=i; string[j] != ' ' && string[j] != '\0' ; j++){
      temp[count] = string[j];
      count++; 
    
    }
    temp[count] ='\0';
    
    if(revcompare(temp) == 1){
      printf("%s", temp);
      printf("\n");
    }
    
   if(string[j] == '\0')
     break;
    else  
      i = j;
 }
  return 0;
}

int revcompare(char *temp)
{
  int num1[50],num2[50];
  int count =0,count2 =0,count3 =0;

  for(int i =0; temp[i] != '\0' ; i++){
    num1[i] = (int)temp[i];
    count2++;
  }
 
  for(int i =count2 -1; i >= 0 ; i--){
    num2[count3] = (int)temp[i];
    count3++;
  }
 
  for(int i =0; temp[i] != '\0'; i++){
    if(num1[i] == num2[i]){
      count++;
    }
  }
  if(count == count2)
    return 1;
  else 
    return 0;
}
