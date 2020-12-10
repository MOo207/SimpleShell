#include <pthread.h>
#define TRUE    1
#define FALSE   0
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <string.h>
#include <stddef.h>
#include <regex.h>

int indexPid = 0;
int pids[10];

#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define TRUE    1
#define FALSE   0
int  arr[50][3];
int id, PIN,count=0;
int check();
int entering[100],number[100],N;
int my = 10;
clock_t t1,t2,t3,t4,t5,t6,t7,t8;
int max(int number[100]) {
    int i = 0;
    int maximum = number[0];
    for (i = 0; i < N; i++) {
        if (maximum < number[i])
            maximum = number[i];
    }
    return maximum;
}

void lock(int i) {
    int j = 0;
    entering[i] =TRUE;
    number[i] = 1 + max(number);
    entering[i] = FALSE;
    for (j = 0; j < N; j++) {
        while (entering[j]);
        while (number[j] != 0 && (number[j] < number[i] || (number[i] == number[j]) && j < i)) {}
    }
}


void unlock(int i) {
    number[i] = 0;
}


void* Open(void *integer)
{
    int i = (intptr_t) integer;

    t1 = clock();
    if ((count < 50)){
    printf(" **Open_Acouont  (%d)****\n",i);
    printf(" Enter your acount\n");
    scanf("%d", &id);
    for(int j=0;j<count;j++){
       if(id==arr[j][0]) {
           printf("you have acount from befor\n");


           return 0;

       }
    }
    arr[count][0]=id;
    printf("Enter your PIN\n");
    scanf("%d", &arr[count][1]);
    printf(" Enter your initial Deposit\n");
    scanf("%d", &arr[count][2]);
    count++;
    t2 = clock();
    printf("\n TIME IS %f: \n",(double)(t2-t1 )/ CLOCKS_PER_SEC);
    return 0;}
     else

     return 0;
}
//-------------------------------------

void* Withdraw(void *integer)
{
    int i = (intptr_t) integer;
    lock(i);
    printf("\n\n-----------Process %d---------",i);
    printf("\nProcess %d is Entering Critical Section\n",i);
    t3=clock();
//int CH = check();
    int CH=arr[count][2];

    //if (CH != -1)
  // scanf("%d", &my);
    if(my<=arr[CH][2]){
        arr[CH][2] = arr[CH][2] - my;
         sleep(1);
        printf("\n your  new balence is %d: ",arr[CH][2]);
         int CH=arr[count][2]++;

        t4 =clock();
        printf("\n TIME IS %f: ",(double)(t4-t3 )/ CLOCKS_PER_SEC);
        printf("Process %d is leaving Critical Section\n",i);
        unlock(i);
    return 0;}
    else
        printf("\n you can't becouse your Withdraw greten than your balance: ");
    t4 =clock();
    printf("\n TIME IS %f: ",(double)(t4-t3 )/ CLOCKS_PER_SEC);
    printf("Process %d is leaving Critical Section\n",i);
    unlock(i);
    return 0;
}
//---------------------------------------
void* Depooseit(void *integer)
{
    int i = (intptr_t) integer;

    t5 =clock();
    int my = 0;
    int CH = check();
    if (CH != -1){
        printf(" Enter Deposit Amunt: ");
        scanf("%d", &my);
        arr[CH][2] +=  my;

        t5 =clock();
        printf("\n TIME IS %f: ",(double)(t6-t5 )/ CLOCKS_PER_SEC); }


    return 0;



}
//-----------------------------------------------------

void* servi()
{
    t7=clock();
    //sleep(1);
    printf("1.Open_Acouont\n");
    //sleep(1);
    printf("2.Depooseit\n");
    //sleep(1);
    printf("3.Withdraw\n");
    //sleep(1);
    printf("4.exit\n");

    t8 =clock();
    printf("\n TIME IS %f: ",(double)(t8-t7 )/ CLOCKS_PER_SEC);return 0;
}
//----------------------------------------------------
void bank() {

    printf("Enter Number of Process\n");
    scanf("%d",&N);
    int n;
    pthread_t g1[N];
    pthread_t g2[N];
    pthread_t g3[N];
    pthread_t g6;


    while (1) {
        pthread_create(&g6,NULL,servi,NULL);
        pthread_join(g6,NULL);
        printf("\nENTER YOUR CHOICE\n");
        scanf("%d", &n);
        switch (n) {
            case 1:
               for(int i=0;i<N;i++){
                    pthread_create(&g1[i],NULL,Open,(void *)(intptr_t)i);
                    pthread_join(g1[i],NULL);}

                break;

            case 2:
                for(int i=0;i<N;i++){
                    pthread_create(&g2[i],NULL,Depooseit, (void *)(intptr_t)i);
                pthread_join(g2[i],NULL);}
                break;
            case 3:
                for(int i=0;i<N;i++){
                    pthread_create(&g3[i],NULL,Withdraw, (void *)(intptr_t)i);
                pthread_join(g3[i],NULL);}
                break;

            case 4:
                printf("thank you for use our banking\n");

               exit(0);


        }
    }
}
//------------------------------------------------------------------------
int check(){
    printf(" Enter your acount\n");
    scanf("%d",&id);

    printf(" Enter your PIN\n");
    scanf("%d",&PIN);
    for(int i=0;i<count;i++){
    if (id==arr[i][0]&&PIN==arr[i][1]){
        return i;}}

    printf(" invalid ID or PIN\n");
            return -1;

    }


//-------------------Project1-------------------------

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

void shell()
{
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

int main(){
int choice;
while(1){
system("clear");
    printf("\n\n\t\t\tA start Menu for your Project");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1.First project\n\t\t2.Second project\n\t\t3.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);
if(choice==1){
    shell();
} else if(choice==2){
    bank();
} else if(choice == 3){
    return 0;
} else{
    printf("no correct choice");
}
}
}
