#include "shell.h"

char PATH[128];
char HOME[128];

int main(){
	profileReader();
	initShell();
	return 0;
}

void profileReader(){
	char fileName[8] = "PROFILE";
	FILE *pf;
	char line[256]; 
	pf = fopen(fileName,"r"); // read mode 
	if(pf == NULL) {
		printf("%s file has not been found\n", fileName);
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
    if(strcmp(HOME, "") == 0 || strcmp(PATH, "") == 0){
 	   if(strcmp(HOME, "") == 0){
    		printf("HOME variable has not been assigned\n");
    	}
    	if(strcmp(PATH, "") == 0){
    		printf("PATH variable has not been assigned\n");
    	}
    	exit(EXIT_FAILURE);
	}
    //remove \n at end of variables
    if(PATH[strlen(PATH)-1] == '\n') {
    	PATH[strlen(PATH)-1] = '\0';
	}
	if(HOME[strlen(HOME)-1] == '\n') {
    	HOME[strlen(HOME)-1] = '\0';
	}
    // printf("%s\n", PATH);
    // printf("%s\n", HOME);
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
		handleInput(line, cwd);
	}

	//puts(line);
}

void handleInput(char * input, char * cwd){
	// Seperate input into array via strtok.
  	char *pstr;
  	char *binName;
  	int index = 0;
  	char *command[8];
  	pstr = strtok (input," \n");
  	while (pstr != NULL)
  	{
  		if(index == 0){
  			binName = pstr; 
  		}
  		command[index] = pstr;
  		pstr = strtok (NULL, " \n");
  		index ++;
  	}
  	command[index] = NULL;
    if(strcmp(binName,"cd")==0){
      if(command[1] == NULL) {
        changeDirectory("HOME");
      }
      else {
        changeDirectory(command[1]);
      }
    }
    else {
  	char *progPath = getProgramPath(binName);
    if(progPath != NULL){
	  printf("%s\n", progPath);
	  pid_t pid=fork();
	  if (pid==0) {
		  execv(progPath,command);
	  }
	  else { 
		  waitpid(pid,0,0); 
	  }
  }
  }
}

char* getProgramPath(char *progName){
	char *pstr;
	char *fullProgName = malloc(1024);
	struct dirent *pDirent;
  DIR *pDir;
  strcpy(fullProgName,PATH);
	pstr = strtok (fullProgName,":\n");
	while (pstr != NULL){
      //printf("%s\n", pstr);
    	pDir = opendir (pstr);
    	if (pDir == NULL) {
    	    printf ("Cannot open directory '%s'\n", pstr);
   	    	return "ERROR";
    	}
    	while ((pDirent = readdir(pDir)) != NULL) {
        	//printf ("%s\n", pDirent);
        	if(strcmp(pDirent->d_name, progName) == 0 ) {
  				strcpy (fullProgName,pstr);
  				strcat (fullProgName, "/");
  				strcat (fullProgName,progName);
          closedir (pDir); 
          return fullProgName;
        	}
    	}
      pstr = strtok (NULL, ":\n");
    	closedir (pDir); 
	} 
  return "";
}

void changeDirectory(const char *path) {
  printf("%s\n", HOME);
 if(strcmp(path,"HOME") == 0){
  chdir(HOME);
  return;
 }
 // if(strcmp(path, "") == 0) {
   // printf("%s\n", path);
  //}
 printf("%d",chdir(path));
}