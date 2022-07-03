# include<stdio.h>
# include<stdlib.h>
# include<string.h>


/*
* 定义学生信息
*/
struct STUDENT
{
	int ID;				//学号
	char Name[7];       //姓名
	char Sex[2];        //性别
	int Age;			//年龄
	char Origin[31];	//籍贯
	char College[15];   //学院
	char Phone[13];		//电话
	float Programming;  //程序设计
	float Math;		    //数学
	float English;		//英语
	float Conference;	//研讨课
}student[1000];
// 我们需要注意到，汉字在数组中占用两个字节，即两个位置，所以分配空间尽可能大。
// 这同时也是易错点
