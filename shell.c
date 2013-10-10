#include "shell.h"

char PATH[128];
char HOME[128];

int main(){
	// Read PROFILE FILE
	profileReader();
	initShell();
	
	//execve("/bin/ls",HOME,PATH);
	// prompt for input
	// handle input.
	return 0;
}

void profileReader(){
	char file_name[8] = "PROFILE";
	FILE *pf;
	char line[256]; 
	pf = fopen(file_name,"r"); // read mode 
	if(pf == NULL) {
		printf("%s file has not been found\n", file_name);
		exit(EXIT_FAILURE);
	}
    // get lines
	while (fgets(line, sizeof(line), pf)) {
    	char *pathVar = strstr (line,"PATH=");
    	char *homeVar = strstr (line,"HOME=");
    	if(pathVar != NULL){
    		memmove (pathVar,pathVar+5, strlen(pathVar));
    		strcpy(PATH, pathVar);
    	}
    	else if(homeVar != NULL){
    		memmove (homeVar,homeVar+5, strlen(homeVar));
    		strcpy(HOME, homeVar);
    	}
    }
    if(strcmp(HOME, "") == 0){
    	printf("HOME variable has not been assigned\n");
    }
    if(strcmp(PATH, "") == 0){
    	printf("PATH variable has not been assigned\n");
    }
    //remove \n at end of path;
    //printf("%s\n", PATH);
    //printf("%s\n", HOME);
   	fclose(pf);
}

void initShell(){
	char cwd[1024];
	char line[256];
	char ch = '\n';
	while(ch == '\n'){
		if (getcwd(cwd, sizeof(cwd)) == NULL) {
        	printf("Current working directory not found\n");
        	return;
    	}
		printf("%s>", cwd);
		fgets(line, 256, stdin);
		ch = line[strlen(line)-1];
		if(strcmp(line, "ls\n")==0){
			printf("LIST\n");
		}
	}

	//puts(line);
}
