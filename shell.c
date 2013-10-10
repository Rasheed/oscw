#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

int main(){
	//Read PROFILE FILE
	profileReader();
	// prompt for input
	// handle input.
}

void profileReader(){
   char ch;
   char file_name[8] = "PROFILE";
   FILE *pf;
 
   pf = fopen(file_name,"r"); // read mode
 
   if( pf == NULL )
   {
      exit(EXIT_FAILURE);
   }
  
   while( ( ch = fgetc(pf) ) != EOF )
      printf("%c",ch);
 	
   fclose(pf);
}