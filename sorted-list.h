#include <stdio.h>
#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#endif

/*
* THE MAIN DESIGN OF THE PROGRAM INCLUDES A TWO DIMENSIONAL SORTED LIST STRUCTURE (DYANAMICALLY ALLOCATED TABLE) 
* THE NODE STRUCTURES REPRESENT EACH UNIQUE TOKEN AND GROW DOWNWARDS. 
* THE FILENODE STRUCTURES REPRESENT EACH UNIQUE FILE ASSOCIATED WITH A TOKEN AND GROWS SIDEWARDS
*/

struct FileNode {					//List of files associated with a token
	char *filename;					//file associated
	int freq;						//frequency of the token in that file
	struct FileNode *next;			//link the  list of files associated with the token
	};
	
typedef struct FileNode FileNode;
	
struct Node  {						//We will implement a sorted list of nodes.
	char *tkn;						//A node will be made for each token
	struct FileNode *file;			//Corresponding to one token, there can be multiple files associated and the resp. frequencies
	struct Node *succ;				//link the  list of tokens associated with the indexer
};

typedef struct Node Node;

									//Function delcaration
									
void insertList(char *token, char *name);

void displayList(char* );

void sortbyFreq(Node *);
