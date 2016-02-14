#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

#include "tokenizer.h"
#include "sorted-list.h"

/*
*Pass the file name to tokenize and convert the contents to string
*/
void tokenize(char* filename) {		
char *str;						//str- string storing whole file 
int length=0;					//length of the file
int l=0;						//length of the token
char *ptr;						//pointer to hold start of the token
int i=0;
int flag=0;						//flag variable used to ignore succeeding whitespaces
FILE *fp=fopen(filename,"r");	//open file read-only
if(fp==NULL) {
printf("error opening file");
exit(0);
}
fseek(fp,0,SEEK_END);			//go to the end
length=ftell(fp);				//get the length
if(length==0) 					//empty file
return;
fseek(fp,0,SEEK_SET);			//go to the start
str=malloc(length);				//allocate memory for string

if(str) {						//copy contents in string
	fread(str,1,length,fp);
	}
fclose(fp);						//close the file, we're done with it

ptr=str;						
while(str[i]!='\0')				//parse the string
	{
		if(isalnum((int)str[i])) // if alpha numeric character, add the length of token and set flag
			{
				l++;
				flag=1;
				if((int)str[i]>=65 && (int)str[i] <=90)			//convert to small case
					str[i]=(char)((int)str[i]+32);
			}
		else if(isspace((int)str[i]) || str[i]=='\0') 			//if whitespace or end of file, fetch the token
			{
				if(flag==1&&l>0) {								//only if the whitespace is the first one succeeding a token, ignore others
					char *token=malloc(l+1);					//create memory for token (1 more for \0)
					strncpy(token,ptr,l);
					token[l]='\0';								//null terminate
					insertList(token,filename);
					free(token);								//avoid memory leaks
					l=0;										//reset length before fetching next token
					flag=0;										//reset whitespace flag
				}
				ptr=&str[i+1];									//set the pointer to address of first character after a whitespace
			}
		else {
			if(l>0) {											//for last token
					char *token=malloc(l+1);					//create memory for token (1 more for \0)
					strncpy(token,ptr,l);
					token[l]='\0';								//null terminate
					insertList(token,filename);
					free(token);
					l=0;										//reset length before fetching next token
					ptr=&str[i+1];								//move the pointer to next alphanumeric character
			}
			else												//ignore all other characters than alphanumerics
			ptr=&str[i+1];
			}
		i++;													//read each character
     }
 }
