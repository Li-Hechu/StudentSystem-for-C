# include<stdio.h>
# include<stdlib.h>
# include<string.h>


/*
* ����ѧ����Ϣ
*/
struct STUDENT
{
	int ID;				//ѧ��
	char Name[7];       //����
	char Sex[2];        //�Ա�
	int Age;			//����
	char Origin[31];	//����
	char College[15];   //ѧԺ
	char Phone[13];		//�绰
	float Programming;  //�������
	float Math;		    //��ѧ
	float English;		//Ӣ��
	float Conference;	//���ֿ�
}student[1000];
// ������Ҫע�⵽��������������ռ�������ֽڣ�������λ�ã����Է���ռ価���ܴ�
// ��ͬʱҲ���״��
