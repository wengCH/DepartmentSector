#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
int counts=300,countd=20;
struct Student
{
	int id;//学生ID 
	double grade;//绩点 
	int flag;//已录取个数 
	int dep[5];//志愿 
	double qz;//权重，qz=(5-flag)*10+grade
	vector<int> depart;//录取的部门
}stu[310];
struct Department
{
	int id;//部门ID 
	double need;//可以接受的学生数
	double left;//还剩下的名额
	vector<int> stu;//接受的学生
}department[25];
bool cmp(Student a,Student b)//学生按照权重的高到低排序
{
	return a.qz>b.qz;
}
int main()
{
	FILE *f;
	f=fopen("import.txt","r");
	memset(stu,0,sizeof(stu));
	memset(department,0,sizeof(department));
	for(int i=0;i<countd;i++)//部门输入
	{
		fscanf(f,"%d %lf",&department[i].id,&department[i].need);
		department[i].left=department[i].need;
//		printf("%d %lf\n",department[i].num,department[i].need);
	}
	for(int i=0;i<counts;i++)//学生输入 
	{
		fscanf(f,"%d %lf",&stu[i].id,&stu[i].grade);
	//	printf("%d %lf\n",stu[i].num,stu[i].grade);
		for(int j=0;j<5;j++)
		{
			fscanf(f,"%d",&stu[i].dep[j]);
		//	printf("%d\n",stu[i].dep[j]);
		}
	}
	fclose(f);
	f=fopen("output_condition.txt","w"); 
	
	for(int zy=0;zy<5;zy++){//按照学生志愿，志愿优先 
		for(int i=0;i<300;i++)//计算学生权重
	    {
	        stu[i].qz=(5-stu[i].flag)*10+stu[i].grade;
	    }
	    sort(stu,stu+300,cmp);//学生按权重排序
	    for(int i=0;i<300;i++)
	    {
	        if(department[stu[i].dep[zy]].left>0){//有空
	        	int jsyet=0;
	        	for(int js=0;js<stu[i].depart.size();js++){//已经接收否 
	        		if(stu[i].dep[zy]==stu[i].depart[js]){
	        			jsyet=1;
	        			break;
					}
				} 
	        	if(jsyet==0){
	        		stu[i].depart.push_back(stu[i].dep[zy]);//添加学生录取的部门 
	        		stu[i].flag++;//更新录取数 
	        		department[stu[i].dep[zy]].stu.push_back(i);//添加部门接收的学生 
	        		department[stu[i].dep[zy]].left--;//减少剩余名额 
				} 
			}
    	}
    }
    fprintf(f,"输出每个部门接收的学生：\n");
    for(int i=0;i<20;i++)//输出每个部门接收的学生
    {
        fprintf(f,"部门ID为：%d 接收到学生个数：%d\n",department[i].id,department[i].stu.size());
        fprintf(f,"   分别为：");
        for(int j=0;j<department[i].stu.size();j++)
        {
            fprintf(f,"学生%d ",department[i].stu[j]);
        }
        fprintf(f,"\n");
    }
    fprintf(f,"输出每个学生加入的部门 ：\n");
    for(int i=0;i<300;i++)//输出每个学生加入的部门 
    {
        fprintf(f,"学生ID为：%d 加入部门的个数：%d\n",stu[i].id,stu[i].depart.size());
        fprintf(f,"   分别为：");
        for(int j=0;j<stu[i].depart.size();j++)
        {
            fprintf(f,"部门%d ",stu[i].depart[j]);
        }
        fprintf(f,"\n");
    }
    
    int q=0;
    fprintf(f,"输出未加入部门的学生：\n");
    for(int i=0;i<30;i++)//输出每个部门接收的学生
    {
        if (stu[i].flag==0){
        	fprintf(f,"学生%d\n",stu[i].id);
        	q++;
		}
    }
    fprintf(f,"\n共%d人未加入部门\n",q);
    q=0;
    
    fprintf(f,"输出未接收学生的部门：\n");
    for(int i=0;i<20;i++)//输出每个部门接收的学生
    {
        if (department[i].left==department[i].need){
        	fprintf(f,"部门%d\n",department[i].id);
        	q++;
		}
    }
    fprintf(f,"\n共%d部门未接受到学生\n",q);
    return 0;
}
