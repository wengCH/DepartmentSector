#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    FILE *f;
    f=fopen("import.txt","a");
    srand(time(0));
    for(int i=0;i<20;i++)
    {
        int want;
        want=rand()%15;
        fprintf(f,"%d %d\n",i,want);
    }
    for(int i=0;i<300;i++)
    {
        int g=rand()%500;
        if(g<=200)g+=100;//绩点基本集中2-3 
        double grade=(double)g/100.0;
        fprintf(f,"%d %lf %d %d %d %d %d\n",i,grade,rand()%20,rand()%20,rand()%20,rand()%20,rand()%20);//5个志愿 
    }
    fclose(f);
    return 0;
}
