#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define TRUE    1
#define FALSE   0
int  arr[50][3], id, PIN,count=0,check(),entering[100],number[100],N;
clock_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12;
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
    lock(i);
    printf("\nProcess %d is Entering Critical Section\n",i);
    t1 = clock();
    if ((count < 50)){
    printf(" *******Open_Acouont  (%d)***********\n",i);
    printf(" Enter your acount\n");
    scanf("%d", &id);
    for(int j=0;j<count;j++){
       if(id==arr[j][0]) {
           printf("you have acount from befor\n");
           printf("Process %d is leaving Critical Section\n",i);
           unlock(i);
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
        printf("Process %d is leaving Critical Section\n",i);
        unlock(i);
    return 0;}
     else
        printf("Bank is full ");
    printf("Process %d is leaving Critical Section\n",i);
    unlock(i);
     return 0;
}
//-------------------------------------
void* Close_acount(void *integer)
{
    int i = (intptr_t) integer;
    lock(i);
    printf("\nProcess %d is Entering Critical Section\n",i);
    if (count > 0){
    t3=clock();
    printf(" *******Close_Acouont***********\n");
    int CH=check();
    if(CH!=-1){
        printf("Ethe Acount hase closed for big%d and your balance%d\n",arr[CH][0],arr[CH][2]);
    for (int i=CH;i<count;i++){
        arr[CH][0]=arr[CH+1][0];
        arr[CH][1]=arr[CH+1][1];
        arr[CH][2]=arr[CH+1][2];
    }
    count--;
    t4=clock();
    printf("\n TIME IS %f: ",(double)(t4-t3 )/ CLOCKS_PER_SEC);
        printf("Process %d is leaving Critical Section\n",i);
        unlock(i);
    return 0;}
    else
        t4=clock();
    printf("\n TIME IS %f: ",(double)(t4-t3 )/ CLOCKS_PER_SEC);
        printf("Process %d is leaving Critical Section\n",i);
        unlock(i);
    return 0;
    }
    else{
    printf("Bank IS EMPTY");
    printf("Process %d is leaving Critical Section\n",i);
    unlock(i);
    return 0;}
}
//------------------------------------------
void* Withdraw(void *integer)
{
    int i = (intptr_t) integer;
    lock(i);
    printf("\nProcess %d is Entering Critical Section\n",i);
    t5=clock();
    int my = 0;
    int CH = check();
    if (CH != -1)
    printf("\n Enter Withdraw Amunt: ");
    printf("\n Should be integer number: ");
    scanf("%d", &my);
    if(my<=arr[CH][2]){
        arr[CH][2] = arr[CH][2] - my;
        t6 =clock();
        printf("\n TIME IS %f: ",(double)(t6-t5 )/ CLOCKS_PER_SEC);
        printf("Process %d is leaving Critical Section\n",i);
        unlock(i);
    return 0;}
    else
        printf("\n you can't becouse your Withdraw greten than your balance: ");
    t6 =clock();
    printf("\n TIME IS %f: ",(double)(t6-t5 )/ CLOCKS_PER_SEC);
    printf("Process %d is leaving Critical Section\n",i);
    unlock(i);
    return 0;
}
//---------------------------------------
void* Depooseit(void *integer)
{
    int i = (intptr_t) integer;
    lock(i);
    printf("\nProcess %d is Entering Critical Section\n",i);
    t7 =clock();
    int my = 0;
    int CH = check();
    if (CH != -1){
        printf(" Enter Deposit Amunt: ");
        scanf("%d", &my);
        arr[CH][2] +=  my;

        t8 =clock();
        printf("\n TIME IS %f: ",(double)(t8-t7 )/ CLOCKS_PER_SEC); }

    printf("Process %d is leaving Critical Section\n",i);
    unlock(i);
    return 0;

}
//-----------------------------------------------------
void* inquire(void *integer)
{
    int i = (intptr_t) integer;
    lock(i);
    printf("\nProcess %d is Entering Critical Section\n",i);
    t9 =clock();
    int CH = check();
    if (CH!=-1){
        printf("\n your balence is %d: ",arr[CH][2]);
        t10 =clock();
        printf("\n TIME IS %f: ",(double)(t10-t9 )/ CLOCKS_PER_SEC); }
    printf("Process %d is leaving Critical Section\n",i);
    unlock(i);
         return 0;
}
void* servi()
{
    t11=clock();
    //sleep(1);
    printf("1.Open_Acouont\n");
    //sleep(1);
    printf("2.Close-acount\n");
    //sleep(1);
    printf("3.Depooseit\n");
    //sleep(1);
    printf("4.Withdraw\n");
    //sleep(1);
    printf("5.inquire\n");
    //sleep(1);
    printf("6.exit\n");

    t12 =clock();
    printf("\n TIME IS %f: ",(double)(t12-t11 )/ CLOCKS_PER_SEC);return 0;
}
//----------------------------------------------------
int main() {

    printf("Enter Number of Process\n");
    scanf("%d",&N);
    int n;
    pthread_t g1[N];
    pthread_t g2[N];
    pthread_t g3[N];
    pthread_t g4[N];
    pthread_t g5[N];
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
                        pthread_create(&g2[i],NULL,Close_acount,(void *)(intptr_t)i);
                pthread_join(g2[i],NULL);}
                break;

            case 3:
                for(int i=0;i<N;i++){
                    pthread_create(&g3[i],NULL,Depooseit, (void *)(intptr_t)i);
                pthread_join(g3[i],NULL);}
                break;
            case 4:
                for(int i=0;i<N;i++){
                    pthread_create(&g4[i],NULL,Withdraw, (void *)(intptr_t)i);
                pthread_join(g4[i],NULL);}
                break;
            case 5:
                for(int i=0;i<N;i++){
                    pthread_create(&g5[i],NULL,inquire, (void *)(intptr_t)i);
                pthread_join(g5[i],NULL);}
                break;
            case 6:
                printf("thank you for use our banking\n");

               return 0;


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
