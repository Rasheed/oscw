#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void profileReader();
void initShell();
void handleInput(char*, char *);
char* getProgramPath(char *);

#define length(x)  (sizeof(x) / sizeof(x[0]))
