/*
 *	Twe:
 *
 *	The Worst Text Editor
 *
 *	This is a really basic text Editor made to
 *	make the programmer's life bad as the earthworm's one.
 *	
 *	Press ESC to enter the COMMAND.
 *	
 *	USAGE:
 *	
 *	twe [...file to open]
 *
 *	:ln		Prints The line Number Once Called
 *	:gt<ln>		Sets the cursor to the requested line
 *	:!!<fl>		Saves to a file 
 *	:?		Exits the program
 */
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100000
#define MAX_LINE_LENGHT 100000
int lindex = 0;
FILE* f_opened;
int maxline = 0;


void gt(){
	printf("GOTO\n");
}


void of(){
	printf("OPEN\n");
}


int mtc(char fs[],char tm[]){


	int mch = 0;
	char *ptr1 = fs;
	char *ptr2 = tm;
	int lt = strlen(tm);
    int fl = strlen(fs);


	for (int j = 0; j < lt; j++){
		if(*ptr1 == *ptr2){

            ++mch;
			ptr1++;
			ptr2++;
		}else{
			ptr2++;
		}

		if (mch==fl){
            return(1);
		}

	}
	return(0);

}

char line[MAX_LINE_LENGHT];
char file[MAX_LINES][MAX_LINE_LENGHT];

void ln(char all){
	if (all !=  '!'){
		printf("%d\n",maxline+1);
	}else{
		for (int i = 0; i < maxline; i++){
			printf("%d %s",i+1,file[i]);
		}
	}
}
void wl(){

	if (f_opened != NULL){
		//IT works SIUUM
		int len = 0;
		for (int j = 0;j < maxline; j++){
			int x = strlen(file[j]);
			len += x;
			for (int i = 0; i < x; i++){
				char c = file[j][i];
				fwrite(&c,sizeof(c),1,f_opened);
				c = '\0';
			}
		}
		printf("%d\n",len);
		fclose(f_opened);

	}else{
		//something wrong
		printf("?\n");
		
	}
}
void pl(char all){
	if (all == '!'){
		for(int i = 0;i<maxline;i++){
			printf("%s",file[i]);
		}
	}else{
		printf("%s",file[maxline-1]);
	}
}
FILE* sf(char file_name[]){
	FILE* file;
	file = fopen(file_name,"w");
	
	f_opened = file;
	if (file != NULL){
		wl();
		return file;
	}
}
FILE* ff(char file_name[]){
	FILE* file;
	file = fopen(file_name,"w+");
	
	f_opened = file;
	if (file != NULL){
		fclose(f_opened);
		printf("0\n");
		return file;
	}
}
int commands(char fc[],char ag[]){



	if (mtc(fc,"&:")!= 0){
		gt();
	}
	else if(mtc(fc,"?")!= 0){
		ln("");
	}
	else if(mtc(fc,"??")!= 0){
		ln('!');
	}
	else if(mtc(fc,"!:")!= 0){
		f_opened = sf(ag);
	}
	else if(mtc(fc,"@")!= 0){
		exit(0);
	}
	else if(mtc(fc,";:")!= 0){
		ff(ag);
	}
	else if(mtc(fc,"p")!= 0){
		pl("");
	}
	else if(mtc(fc,"p!")!= 0){
		pl('!');
	}

	else {
		printf("#\n");
		return(-1);
	}

}

int main(int argc, const char *argv[]){

	if (argc == 2){
		
	}

	int lcount = 0;

	char cm[6];
	char ag[100];
	bool fc = true;
	char c;
	int i = 0;
	int j = 0;
	bool broken = false;

	memset(file,'\0',MAX_LINES-1);

	while (true){
		
		memset(cm,'\0',strlen(cm));
		memset(ag,'\0',strlen(ag));

		c = getchar();
		//if there is an input  <:> do the command check
		
		if (c == ':'){
			if(fc==true){
				broken = false;
				c = getchar();
				i = 0;
				//get the enter command and get the params
				while(c!=':'){
					if (c=='\n'){
						break;
					}
					cm[i] = c;
					i++;
					c = getchar();
				}
				if (c != '\n'){
					c = getchar();
				}
				while(c != '\n'){
					ag[j] = c;
					j++;
					c = getchar();
				}
				
				//check for command existance
				if (broken == false){
					//printf("Command Supplied: %s, Args: %s\n",cm,ag);
					int status = commands(cm,ag);
					//resetting all needed vars
					fc = true;
					j = 0;
					i = 0;
				}
			}	
		}else{
			fc = false;
			//nomal input save
			line[lcount] = c;
			lcount++;
			if (c == '\n'){
				//c = getchar();
				fc = true;
				int j = 0;
				int x = strlen(line);
			
				for (int k = 0;k<x;k++){
                	file[lindex][k] = line[k];
					j = k;
            	}   
				file[lindex][j+1] = '\0';
				lindex++;
				maxline++;
				lcount = 0;
				
				memset(line,'\0',MAX_LINE_LENGHT);
			}
		}
		
	}
	 
}
