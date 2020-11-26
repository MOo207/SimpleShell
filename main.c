#include <stdio.h>
#include <stdlib.h>
#include<dirent.h>
#include <string.h>

void takeInput(char* command){
reset();
scanf("%s", command);
}

char *inputString(FILE* fp, size_t size){
	char *str;
	int ch;
	size_t len = 0;
	str = realloc(NULL, sizeof(char)*size);
	if(!str)return str;
	while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
		str[len++]=ch;
		if(len==size){
			str = realloc(str, sizeof(char)*(size+=16));
			if(!str)return str;
		}
	}
	str[len++]='\0';
	return realloc(str, sizeof(char)*len);
}

DIR *getCurrentDir(){
    char *currWorkDir, *token;
    char buffer[PATH_MAX + 1];
    char *directory;
    size_t length;

    currWorkDir = getcwd(buffer, PATH_MAX + 1 );
    token = strrchr(currWorkDir, '/');

    if( currWorkDir == NULL ){
        printf("Error"); /* You decide here */
        exit(1);
    }

    if (token == NULL) {
        printf("Error"); /* You decide here */
        exit(1);
    }

    length = strlen(token);
    directory = malloc(length);
    memcpy(directory, token+1, length);

    return directory;
}

void listFiles()
{
    DIR *d; // this means the datatype to which d points is of type directory.
    struct dirent *r; // this's an entery to our directory or can be explined as an access point
    d=opendir( "./" ); // to open current directory of your current main program directory 'parent folder of your program'
    red();
    printf("\n");
    while((r=readdir(d)) != NULL) //if readdir(d) == null, then it means the directory is not vaild
    //If successful not null, opendir() returns a pointer to a DIR object d
    {
        printf("\t %s \n",r->d_name);
    }
}

void red() {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void magenta() {
  printf("\033[0;35m");
}

void green() {
  printf("\033[0;32m");
}

void blue() {
  printf("\033[0;34m");
}

void cyan(){
printf("\033[0;36m");
}

void boldBlue(){
printf("\033[1;34m");
}

void boldMagenta(){
    printf("\033[1;35m");
}

void boldCyan(){
    printf("\033[1;36m");
}

void boldGreen() {
  printf("\033[1;32m");
}

void boldRed() {
  printf("\033[1;31m");
}

void boldYellow(){
printf("\033[01;33m");
}

void reset() {
  printf("\033[0m");
}

int main()
{
    int exit = 0;
    char* command[20];

    while(exit != 1){
        //DIR *dir = getCurrentDir();
        green();
        printf("[Guest ]$ ");
        reset();
        takeInput(command);
        if(strcmp(command, "ls") == 0){
            listFiles();
        } else if(strcmp(command, "exit") == 0){
            return 0;
        } else if(strcmp(command, "help") == 0){
        yellow();
        printf("ls for lising dir and files\nexit to go out\nhelp for more info\n");
        }

    }
}

