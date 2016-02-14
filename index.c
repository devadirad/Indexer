#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include "tokenizer.h"
#include "sorted-list.h"

void traverseDir(char *dirname);			//declaring functions
int isFile(const char* path);

/*Function that checks if the path inputted by the user is a 
* file (1) or a directory(0) or if the path is wrong (-1)
*/
int isFile(const char* path) {
DIR* directory=opendir(path);			
if(directory !=NULL) {						//If opendir returns null, there's some error. Else return 0 to indicate a folder
	closedir(directory);					//close the file descriptor
	return 0;
	}
	
	if(errno == ENOTDIR) 					//is File 
		{
			return 1;
		}
		
	return -1;								// error
	}
	
/*
* A function to recursively parse a directory 
*/
void traverseDir(char* dirname) {
	struct dirent *dp;
	DIR *dir;
	int i=0;
	char path[1024];				//store the path in an array
	
	for(i=0;i<1024;i++)				//initialize to null
		path[i]='\0';
		
	if((dir=opendir(dirname))==NULL)	//error opening dir
		return;
	if((dp=readdir(dir))==NULL)			//error reading dir
		return;
		
	do {
		 	if(dp->d_type == DT_DIR) {		// is directory
	         
                int len = snprintf(path, sizeof(path)-1, "%s/%s", dirname, dp->d_name);		//use snprintf to write the directoryname/filename in path
            path[len] = 0;																	//terminate string
				if( (strcmp(dp->d_name,".")==0) || (strcmp(dp->d_name,"..")==0))			//ignore the . and .. directories
				continue;
			    traverseDir(path);															//recursively traverse
				}
			else {
					char relpath[1024];														//store the complete path of current file
					strcpy(relpath,dirname);
					strcat(relpath,"/");
					strcat(relpath,dp->d_name);
					tokenize(relpath);
				}
			}
		while((dp=readdir(dir))!=NULL);
	closedir(dir);


}
/*
Start the indexer here
*/
int main (int argc, char *argv[])  {		// Indexer file and path as argument variables

FILE *fp;									// File pointer to the indexer file

int file=0;									// Variable to indicate if the path is a single file or a directory

if(argc!=3) {								// check no. of arguments
 printf ("Enter the inverted index file name and the directory/file to be indexed\n");
 exit(0);
 }

fp=fopen(argv[1],"w+");						// open the file with read and write permission, create if doesnt exist, truncate to start if exists.

if(fp==NULL) {								// Error opening/creating the file
	printf("error creating indexer file\n");
	exit(0); 
	}
	
file=isFile(argv[2]);						// Check if entered path is correct

if (file==-1) {	
	printf("Invalid directory path/name %s\n:",argv[2]);
	exit(0);
	}

else if(file==1) {						//Just a file to tokenize
	tokenize(argv[2]);
	}
	
else if(file==0) {						//deal with a directory
	//recursive dir parsing
	DIR* directory=opendir(argv[2]);
	if(directory==NULL){				//error opening dir
			printf("Error opening directory:%s",argv[2]);
			closedir(directory);
			exit(0);
		}
	else {
			closedir(directory);
			traverseDir(argv[2]);			
		}
    }

displayList(argv[1]);					//outputs the inverted indexer into the file
fclose(fp);
return 0;
}
