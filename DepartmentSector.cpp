#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
int counts=300,countd=20;
struct Student
{
	int id;//ѧ��ID 
	double grade;//���� 
	int flag;//��¼ȡ���� 
	int dep[5];//־Ը 
	double qz;//Ȩ�أ�qz=(5-flag)*10+grade
	vector<int> depart;//¼ȡ�Ĳ���
}stu[310];
struct Department
{
	int id;//����ID 
	double need;//���Խ��ܵ�ѧ����
	double left;//��ʣ�µ�����
	vector<int> stu;//���ܵ�ѧ��
}department[25];
bool cmp(Student a,Student b)//ѧ������Ȩ�صĸߵ�������
{
	return a.qz>b.qz;
}
int main()
{
	FILE *f;
	f=fopen("import.txt","r");
	memset(stu,0,sizeof(stu));
	memset(department,0,sizeof(department));
	for(int i=0;i<countd;i++)//��������
	{
		fscanf(f,"%d %lf",&department[i].id,&department[i].need);
		department[i].left=department[i].need;
//		printf("%d %lf\n",department[i].num,department[i].need);
	}
	for(int i=0;i<counts;i++)//ѧ������ 
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
	
	for(int zy=0;zy<5;zy++){//����ѧ��־Ը��־Ը���� 
		for(int i=0;i<300;i++)//����ѧ��Ȩ��
	    {
	        stu[i].qz=(5-stu[i].flag)*10+stu[i].grade;
	    }
	    sort(stu,stu+300,cmp);//ѧ����Ȩ������
	    for(int i=0;i<300;i++)
	    {
	        if(department[stu[i].dep[zy]].left>0){//�п�
	        	int jsyet=0;
	        	for(int js=0;js<stu[i].depart.size();js++){//�Ѿ����շ� 
	        		if(stu[i].dep[zy]==stu[i].depart[js]){
	        			jsyet=1;
	        			break;
					}
				} 
	        	if(jsyet==0){
	        		stu[i].depart.push_back(stu[i].dep[zy]);//���ѧ��¼ȡ�Ĳ��� 
	        		stu[i].flag++;//����¼ȡ�� 
	        		department[stu[i].dep[zy]].stu.push_back(i);//��Ӳ��Ž��յ�ѧ�� 
	        		department[stu[i].dep[zy]].left--;//����ʣ������ 
				} 
			}
    	}
    }
    fprintf(f,"���ÿ�����Ž��յ�ѧ����\n");
    for(int i=0;i<20;i++)//���ÿ�����Ž��յ�ѧ��
    {
        fprintf(f,"����IDΪ��%d ���յ�ѧ��������%d\n",department[i].id,department[i].stu.size());
        fprintf(f,"   �ֱ�Ϊ��");
        for(int j=0;j<department[i].stu.size();j++)
        {
            fprintf(f,"ѧ��%d ",department[i].stu[j]);
        }
        fprintf(f,"\n");
    }
    fprintf(f,"���ÿ��ѧ������Ĳ��� ��\n");
    for(int i=0;i<300;i++)//���ÿ��ѧ������Ĳ��� 
    {
        fprintf(f,"ѧ��IDΪ��%d ���벿�ŵĸ�����%d\n",stu[i].id,stu[i].depart.size());
        fprintf(f,"   �ֱ�Ϊ��");
        for(int j=0;j<stu[i].depart.size();j++)
        {
            fprintf(f,"����%d ",stu[i].depart[j]);
        }
        fprintf(f,"\n");
    }
    
    int q=0;
    fprintf(f,"���δ���벿�ŵ�ѧ����\n");
    for(int i=0;i<30;i++)//���ÿ�����Ž��յ�ѧ��
    {
        if (stu[i].flag==0){
        	fprintf(f,"ѧ��%d\n",stu[i].id);
        	q++;
		}
    }
    fprintf(f,"\n��%d��δ���벿��\n",q);
    q=0;
    
    fprintf(f,"���δ����ѧ���Ĳ��ţ�\n");
    for(int i=0;i<20;i++)//���ÿ�����Ž��յ�ѧ��
    {
        if (department[i].left==department[i].need){
        	fprintf(f,"����%d\n",department[i].id);
        	q++;
		}
    }
    fprintf(f,"\n��%d����δ���ܵ�ѧ��\n",q);
    return 0;
}
