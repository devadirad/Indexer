#include <stdio.h>
#include <string.h>
#include "sorted-list.h"
#include <stdlib.h>

/*
* The List consists of nodes. Each node has a unique token associated to it. A list of files are associated with each token and the frequency of *token occuring in each file
*/

Node *start=NULL;													//Global start node

void insertList(char *token, char *name) {							//Insert token in the list
	
	Node *node=NULL,*temp=NULL,*prev=NULL;							//Use to create new nodes and traverse
	FileNode *fnode =NULL,*ftemp=NULL,*fprev=NULL;					//temp nodes to store previous, allocate new nodes, traverse through the list
	FileNode *i=NULL,*j=NULL;										//use to sort by frequency
	int flag=0;														//Flag to denote if token exists already (1) or not (0)
	
	if(start==NULL)													//empty list
	{
	node=malloc(sizeof(Node));										//insert 1st token
	
	node->tkn=malloc(sizeof(token));								//copy token into the node
	strcpy(node->tkn,token);							
	
	node->file=malloc(sizeof(FileNode));							//list of files
	
	node->file->filename=malloc(sizeof(name));						//copy file name
	strcpy(node->file->filename,name);
	
	node->file->freq=1;												//set frequency =1 
	node->file->next=NULL;
	
	node->succ=NULL;
	start=node;														//set start to the first node

	}
																	//Non-empty list
	else {															// traverse through the list to insert the token
			node=start;
			while(node!=NULL) {
					if(strcmp(node->tkn,token)==0){	 				//If token exists already, set flag and exit this loop traversing tokens
						flag=1;
						break;
					 }
					 else if(strcmp(node->tkn,token)>0)	{			//different token, smaller than the first node (meaning smallest)
					 		temp=malloc(sizeof(Node));				//create a node
					 		temp->tkn=malloc(sizeof(token));
					 		strcpy(temp->tkn,token);
					 		temp->file=malloc(sizeof(FileNode));
					 		temp->succ=NULL;
					 		temp->file->filename=malloc(sizeof(name));
					 		strcpy(temp->file->filename,name);
					 		temp->file->freq=1;
					 		temp->file->next=NULL;
					 		
					 		//insert node at start since its name has a smaller value
					 		if(prev==NULL) {
								temp->succ=node;
								start=temp;
								break;
					 		}
					 		//or in between
					 		else {
					 			temp->succ=node;
					 			prev->succ=temp; 			
					 			break;
					 		}

					 }
					 //else if token is bigger and we already reached the end, then insert at end
					else if ((strcmp(node->tkn,token)<0)&&(node->succ==NULL)) {
					 		temp=malloc(sizeof(Node));				//create a node
					 		temp->tkn=malloc(sizeof(token));
					 		strcpy(temp->tkn,token);
					 		temp->file=malloc(sizeof(FileNode));
					 		temp->succ=NULL;
					 		temp->file->filename=malloc(sizeof(name));
					 		strcpy(temp->file->filename,name);
					 		temp->file->freq=1;
					 		temp->file->next=NULL;	
					 		node->succ=temp;
					 		break;				
					}
					prev=node;											//safekeep previous node
					node=node->succ; 									//go ahead to traverse

				}
				
		if(flag==1)  {													// token exists, now deal with the files
			fnode=node->file;
			while(fnode!=NULL) {										//traverse through the files associated with the token

					if(strcmp(fnode->filename,name)==0)	{				//if file exists, increase frequency
						fnode->freq++;
						break;
						}
						
					else if(strcmp(fnode->filename,name)>0) {			//if file doesnt exist, and is smaller alphabetically
						ftemp=malloc(sizeof(FileNode));   				//create entry for the file
						ftemp->filename=malloc(sizeof(name));
						strcpy(ftemp->filename,name);
						ftemp->freq=1;
						ftemp->next=NULL;
						if(fprev==NULL) {								//if there is only one node prior to current insertion,..
								fnode->next=ftemp->next;				//..don't link  previous of old node since it's null 
								ftemp->next=fnode;
								node->file=ftemp;						//set the head of that token to the smallest file name
								break;
					 		}
					 		//or in between
					 		else {
					 			ftemp->next=fnode;
					 			fprev->next=ftemp;
					 			break;
					 		}
					}
					else if ((strcmp(fnode->filename,name)<0)&&(fnode->next==NULL)) {	//if the name is bigger than all and we have reached the end
					 		ftemp=malloc(sizeof(FileNode));								//create a file node
					 		ftemp->filename=malloc(sizeof(name));
					 		strcpy(ftemp->filename,name);
					 		ftemp->next=NULL;
					 		ftemp->freq=1;
					 		fnode->next=ftemp;	
					 		break;
					 	}
					fprev=fnode;														//safekeep previous File node
					fnode=fnode->next;													//traverse ahead
				}
			
			/*Sorting*/ 
				
			int f=0; char *swap=NULL;
			i=node->file;j=i->next;
			while(i!=NULL){
				j=i->next;
				f=0;swap=NULL;
				while(j!=NULL)
				{
					if(j->freq>i->freq) {			//Sorting is based on frequency
						f=j->freq;
						j->freq=i->freq;
						i->freq=f;
						swap=j->filename;
						j->filename=i->filename;
						i->filename=swap;
						
					}
					j=j->next;
				}
				i=i->next;
			}
			
		}
    }
}

void displayList(char *index) {
	FILE *display;
	display=fopen(index,"w+");
	Node *temp=start;
	FileNode *ftemp;
	//prints first line for list
	fprintf(display,"{\"list\" : [\n");
	while(temp!=NULL) {
		ftemp=temp->file;
		fprintf(display,"    {\"%s\" : [\n",temp->tkn);

		while(ftemp!=NULL) {
			if(ftemp->next!=NULL)
			fprintf(display,"          { \"%s\" : %d },\n",ftemp->filename,ftemp->freq);
			else
			fprintf(display,"          { \"%s\" : %d }\n",ftemp->filename,ftemp->freq);
			ftemp=ftemp->next;
		}
		if(temp->succ!=NULL)
		fprintf(display,"]},\n\n");
		else
		fprintf(display,"]}\n\n");
		temp=temp->succ;
	}
	fprintf(display,"]}\n\n");
}		



