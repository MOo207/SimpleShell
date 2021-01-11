#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <string.h>
#include <stddef.h>
#include <regex.h>

int indexPid = 0;
int pids[10];

char* getDir(){
char dir[100];
return getcwd(dir, 100);
}

void execArgs(char** parsed)
{
    pid_t pid = fork();
    pids[indexPid] = pid;
    indexPid++;
    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        int operation = execvp(parsed[0], parsed);
        if (operation < 0) {
            printf("Error: Command could not be executed");
        }
    } else {
        wait(NULL);
        return;
    }
}

char** split (char* string, const char* delim) {
   char* p;
   int i = 0;
   char** array;
   array = malloc(strlen(string) * sizeof (char*));
   p = strtok (string, delim);
   while (p != NULL) {
      array[i] = malloc(sizeof(char) );
      array[i++] = p;
      p = strtok(NULL, delim);
    }
  return array;
}

int login(char* name, char* id){

char studentID[]="372027763", studentName[]="Mohammed";
    int x, y;
         printf("\nEnter Student Name: ");
        scanf("%s",name);
        trim(name);
        printf("\nEnter Student ID: ");
        scanf("%s",id);
        trim(id);

         x=strcmp(id, studentID);
         y=strcmp(name, studentName);

         if(x==0 && y==0){
            bold Cyan();
           printf("\nSucessfully Logged In, Welcome %s!",name);
           return 1;
         }else {
           printf("\nWrong Password, try again");
           return 0;
           }
}

void takeInput(char command[80]){
reset();
scanf("%s",command);
trim(command);
}

void trim(char * str)
{
    int index, i;
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }
    i = 0;
    while(str[i + index] != '\0')
    {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; // Terminate string with NULL
    i = 0;
    index = -1;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }

        i++;
    }
    str[index + 1] = '\0';
}

void promptLable(char *name, char *dir){
green();
printf("\n[%s", name);
boldBlue();
printf(" %s", dir);
green();
printf("]$ ");
reset();
}


void green(){
printf("\033[0;32m");
}

void red(){
printf("\033[0;31m");
}

void boldBlue(){
printf("\033[1;34m");
}

void boldCyan(){
printf("\033[1;36m");
}

void reset(){
printf("\033[0m");
}


int main(){
int exit = 0;
char name[100];
char id[100];
char *dir;
char command[80];
int loggedIn;
regex_t regex;
int isCD;
isCD = regcomp(&regex,"cd",0);

logIn: loggedIn = login(name,id);
if(loggedIn == 1){
while(exit != 1){
system("clear");
dir = getDir();
promptLable(name, dir);
takeInput(command);
isCD = regexec(&regex, command, 0, NULL, 0);
if (strcmp(command, "exit")==0){
printf("\neShell has been exited");
exit++;
} else if(isCD == 0){
pid_t pid = fork();
pids[indexPid] = pid;
indexPid++;
char **parsed = split(command, " ");
chdir(parsed[1]);
}else if(strcmp(command,"showpid")==0){
    red();
    printf("\nparent pid: %d",getppid());
    for(int i = 0; i<indexPid; i++){
        printf("\nchildpid: %d",pids[i]);
    }
    reset();
}else{
char **parsed = split(command, " ");
execArgs(parsed);
}
}
} else{
    goto logIn;
}
}
