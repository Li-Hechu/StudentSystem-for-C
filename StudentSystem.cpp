# include <StudentSystem.h>

int Count; //学生总人数，全局变量

int LoadFile() {

	struct STUDENT* p = student;

	int count = 0;

	FILE* fp;
	if ((fp = fopen("student.txt", "r")) == NULL) {
		printf("Error, cannot open file");
		exit(0);
	}
	
	while (!feof(fp)) {
		if (!fscanf(fp, "%d %s %s %d %s %s %s %f %f %f %f\n", \
			& p->ID, &p->Name, &p->Sex, &p->Age, &p->Origin, &p->College, &p->Phone, \
			& p->Programming, &p->Math, &p->English, &p->Conference)) {
			return 0;
		}
		
		p++;
		count++;

	}
	fclose(fp);  //一定要关闭文件

	return count;
}

void WriteFile(int count) {

	int i;
	struct STUDENT* p = student;

	printf("请按照 <学号> <姓名> <性别> <年龄> <籍贯> <学院> <电话号码> <程序设计> <数学> <英语> <研讨课> 的顺序填写，以空格分隔\n");
	printf("如果暂时没有，请填写为‘0.0’\n");

	FILE* fp;
	if ((fp = fopen("student.txt", "a")) == NULL) {
		printf("Error, cannot open file");
		exit(0);
	}

	for (i = 0; i < count; i++) {

		printf("学生 %d:\n", i);
		if (!scanf("%d %s %s %d %s %s %s %f %f %f %f", \
			& (p + Count)->ID, &(p + Count)->Name, &(p + Count)->Sex, &(p + Count)->Age, &(p + Count)->Origin, &(p + Count)->College, &(p + Count)->Phone, \
			& (p + Count)->Programming, &(p + Count)->Math, &(p + Count)->English, &(p + Count)->Conference)) {
			return;
		}
		fprintf(fp, "%d %s %s %d %s %s %s %.2f %.2f %.2f %.2f\n", \
			(p + Count)->ID, (p + Count)->Name, (p + Count)->Sex, (p + Count)->Age, (p + Count)->Origin, (p + Count)->College, (p + Count)->Phone, \
			(p + Count)->Programming, (p + Count)->Math, (p + Count)->English, (p + Count)->Conference);

		Count += 1;
	}
	fclose(fp);  //这行代码非常重要。一定要关闭文件，否则无法写入。
	printf("学生信息录入完成。\n");
}

void ShowStudentAll(int start, int end) {

	int i;
	struct STUDENT* p = student;

	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+  学号   +  姓名  +性别+年龄+           籍贯        +      学院     +    电话号码     + 程序设计 + 数学 + 英语 + 研讨课 +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	for (i = start; i < end; i++) {
		printf("%-12d%-8s% -5s%-3d  %-25s%-15s  %-15s %-9.2f%-9.2f%-9.2f%-9.2f\n", \
			(p + i)->ID, (p + i)->Name, (p + i)->Sex, (p + i)->Age, (p + i)->Origin, (p + i)->College, (p + i)->Phone, \
			(p + i)->Programming, (p + i)->Math, (p + i)->English, (p + i)->Conference);
	}
}

void ShowStudentInfo(int start, int end) {

	int i;
	struct STUDENT* p = student;

	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+   学号   +  姓名  +性别+年龄+         籍贯        +        学院       +    电话号码    +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	for (i = start; i < end; i++) {
		printf("%-12d%-8s% -5s%-3d   %-25s%-15s   %-15s\n", \
			(p + i)->ID, (p + i)->Name, (p + i)->Sex, (p + i)->Age, (p + i)->Origin, (p + i)->College, (p + i)->Phone);
	}
}

void ShowStudentGrade(int start, int end) {

	int i;
	struct STUDENT* p = student;

	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+  学号   +  姓名  + 程序设计 + 数学 + 英语 + 研讨课 +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	for (i = start; i < end; i++) {
		printf("%-12d%-8s%-9.2f%-9.2f%-9.2f%-9.2f\n", \
			(p + i)->ID, (p + i)->Name, (p + i)->Programming, (p + i)->Math, (p + i)->English, (p + i)->Conference);
	}
}

/*
* 这里的条件格式为：<字段> <比较符> <条件>
* 并且以空格分隔，否则条件无效
* 比如查找数学成绩在85分以上的同学，可以输入:
* >>> 数学 > 85
* 同时，籍贯支持关键字查找，只要输入关键字，即可查询包含该关键字的信息，比如
* 查询籍贯为四川的所有学生，只需要输入:
* >>> 籍贯 = 四川
* 即可查询得到。
* 目前只支持大于、小于和等于三种运算符，部分条件只有等于运算符，请遵循提示。
*/
void SelectByCondition(int count) {

	//count为条件数，查询结果符合所有条件

	struct CONDITION {
		char Left[10];
		char Op[2];
		char Right[20];
	}condition[6];

	struct CONDITION* q = condition;
	struct STUDENT* p = student;

	int i, j, k, all = Count;

	for (i = 0; i < count; i++) {
		// 输入条件
		printf("请输入条件%d：\n", i+1);
		if (!scanf("%s %s %s", &(q + i)->Left, &(q + i)->Op, &(q + i)->Right)) {
			return;
		}

		// 判断学号
		if (strcmp((q + i)->Left, "学号")==0) {
			if (strcmp((q + i)->Op, ">")==0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->ID <= atoi((q + i)->Right)) {
						// 删除结构体数组后面的内容，这段代码可以复制粘贴，非常有用
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<")==0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->ID >= atoi((q + i)->Right)) {
						for (k = j; k < all - 1; k++) { 
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=")==0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->ID == atoi((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//判断姓名
		else if (strcmp((q + i)->Left, "姓名")==0) {
			if (strcmp((q + i)->Op, "=")!=0) {
				printf("该条件无效\n");
			}
			else {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->Name, (q + i)->Right) != 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
		}
		//判断性别
		else if (strcmp((q + i)->Left, "性别")==0) {
			if (strcmp((q+i)->Op,"=")!=0) {
				printf("该条件无效\n");
			}
			else {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->Sex, (q + i)->Right) != 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
		}
		//判断年龄
		else if (strcmp((q + i)->Left, "年龄") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if (atoi((q + i)->Right) >= (p + j)->Age) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if (atoi((q + i)->Right) == (p + j)->Age) {
						continue;
					}
					else {
					for (k = j; k < all - 1; k++) {
						*(p + k) = *(p + k + 1);
					}
					all -= 1;
					j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
			for (j = 0; j < all; j++) {
				if ((p + j)->Age >= atoi((q + i)->Right)) {
					for (k = j; k < all - 1; k++) {
						*(p + k) = *(p + k + 1);
					}
					all -= 1;
					j -= 1;
				}
				else {
					continue;
				}
			}
			}
			else {
			printf("该条件无效\n");
			}
		}
		//判断籍贯
		else if (strcmp((q + i)->Left, "籍贯") == 0) {
			int t,l;
			char* con = (q + i)->Right;
			int con_len = strlen(con);
			for (j = 0; j < all; j++) {
				char* info = (p + j)->Origin;
				int info_len = strlen(info);
				int pt = 0;
				bool IS = false;
				//判断籍贯中的关键字，代码可以复制粘贴，非常有用。
				for (t = 0; t < info_len; t++) {
					if (*con==*(info + t)) {
						for (l = t; l < t + con_len; l++) {
							if (*(con + l - t) == *( info + l)) {
								pt += 1;
							}
							else {
								break;
							}
						}
						if (pt == con_len) {
							IS = true;
							break;
						}
						else {
							t += pt - 1;
						}
					}
					else continue;
				}
				// 清除结构体数组中不符合要求的内容
				if (!IS) {
					for (k = j; k < all - 1; k++) {
						*(p + k) = *(p + k + 1);
					}
					all -= 1;
					j -= 1;
				}
				else continue;
			}
		}
		//判断学院
		else if (strcmp((q + i)->Left, "学院") == 0) {
			if (strcmp((q + i)->Op, "=") != 0) {
				printf("该条件无效\n");
			}
			else {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->College, (q + i)->Right) != 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
		}
		//判断电话
		else if (strcmp((q + i)->Left, "电话") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->Phone, (q + i)->Right) <= 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if (strcmp((q + i)->Right, (p + j)->Phone) == 0) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->Phone, (q + i)->Right) >= 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//判断程序设计成绩
		else if (strcmp((q + i)->Left, "程序设计") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming <= atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming == atof((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming >= atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//数学
		else if (strcmp((q + i)->Left, "数学") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Math <= atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Math == atof((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Math >= atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//英语
		else if (strcmp((q + i)->Left, "英语") == 0){
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->English <= atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->English == atof((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->English >= atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//研讨课
		else if (strcmp((q + i)->Left, "研讨课") == 0){
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming <= atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming == atof((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming >= atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//最后一种情况
		else {
			printf("该条件无效");
		}
	}

	ShowStudentAll(0, all);

	printf("共 %d 条\n\n", all);

	//重新初始化
	Count = LoadFile();
}

void OrderStudent(char *orderby, char *order) {

	int i, j;
	struct STUDENT* p = student;
	struct STUDENT s;  //结构体交换中间变量

	if (strcmp(orderby, "程序设计") == 0) {
		if (strcmp(order, "降序") == 0) {
			for (i = 0; i < Count - 1; i++) {
				for (j = i; j < Count; j++) {
					if ((p + j)->Programming > (p + i)->Programming) {
						s = *(p + i);
						*(p + i) = *(p + j);
						*(p + j) = s;
					}
				}
			}
		}
		else if (strcmp(order,"升序") == 0) {
			for (i = 0; i < Count - 1; i++) {
				for (j = i; j < Count; j++) {
					if ((p + j)->Programming < (p + i)->Programming) {
						s = *(p + i);
						*(p + i) = *(p + j);
						*(p + j) = s;
					}
				}
			}
		}
		else {
			printf("排序方式有误，只有‘升序’和‘降序’");
			return;
		}
	}
	else if (strcmp(orderby, "数学") == 0) {
		if (strcmp(order, "降序") == 0) {
			for (i = 0; i < Count - 1; i++) {
				for (j = i; j < Count; j++) {
					if ((p + j)->Math > (p + i)->Math) {
						s = *(p + i);
						*(p + i) = *(p + j);
						*(p + i) = s;
					}
				}
			}
		}
		else if (strcmp(order,"升序") == 0) {
			for (i = 0; i < Count - 1; i++) {
				for (j = i; j < Count; j++) {
					if ((p + j)->Math < (p + i)->Math) {
						s = *(p + i);
						*(p + i) = *(p + j);
						*(p + j) = s;
					}
				}
			}
		}
		else {
			printf("排序方式有误，只有‘升序’和‘降序’");
			return;
		}
	}
	else if (strcmp(orderby, "英语") == 0) {
		if (strcmp(order, "降序") == 0) {
			for (i = 0; i < Count - 1; i++) {
				for (j = i; j < Count; j++) {
					if ((p + j)->English > (p + i)->English) {
						s = *(p + i);
						*(p + i) = *(p + j);
						*(p + j) = s;
					}
				}
			}
		}
		else if (strcmp(order,"升序") == 0) {
			for (i = 0; i < Count - 1; i++) {
				for (j = i; j < Count; j++) {
					if ((p + j)->English < (p + i)->English) {
						s = *(p + i);
						*(p + i) = *(p + j);
						*(p + j) = s;
					}
				}
			}
		}
		else {
			printf("排序方式有误，只有‘升序’和‘降序’");
			return;
		}
	}
	else if (strcmp(orderby, "研讨课") == 0) {
		if (strcmp(order, "降序") == 0) {
			for (i = 0; i < Count - 1; i++) {
				for (j = i; j < Count; j++) {
					if ((p + j)->Conference > (p + i)->Conference) {
						s = *(p + i);
						*(p + i) = *(p + j);
						*(p + j) = s;
					}
				}
			}
		}
		else if (strcmp(order,"升序") == 0) {
			for (i = 0; i < Count - 1; i++) {
				for (j = i; j < Count; j++) {
					if ((p + j)->Conference < (p + i)->Conference) {
						s = *(p + i);
						*(p + i) = *(p + j);
						*(p + j) = s;
					}
				}
			}
		}
		else {
			printf("排序方式有误，只有‘升序’和‘降序’");
			return;
		}
	}
	else {
		printf("不支持的排序依据。\n");
		return;
	}

	ShowStudentAll(0, Count);

	//回复原位
	Count = LoadFile();
}

void DeleteByCondition(int count) {

	//count为条件数，查询结果符合所有条件

	struct DELCONDITION {
		char Left[10];
		char Op[2];
		char Right[20];
	}delcondition[6];

	struct DELCONDITION* q = delcondition;
	struct STUDENT* p = student;

	int i, j, k, all = Count;

	for (i = 0; i < count; i++) {
		// 输入条件
		printf("请输入条件%d：\n", i+1);
		if (!scanf("%s %s %s", &(q + i)->Left, &(q + i)->Op, &(q + i)->Right)) {
			return;
		}

		// 判断学号
		if (strcmp((q + i)->Left, "学号") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->ID > atoi((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->ID < atoi((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->ID != atoi((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//判断姓名
		else if (strcmp((q + i)->Left, "姓名") == 0) {
			if (strcmp((q + i)->Op, "=") != 0) {
				printf("该条件无效\n");
			}
			else {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->Name, (q + i)->Right) == 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
		}
		//判断性别
		else if (strcmp((q + i)->Left, "性别") == 0) {
			if (strcmp((q + i)->Op, "=") != 0) {
				printf("该条件无效\n");
			}
			else {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->Sex, (q + i)->Right) == 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
		}
		//判断年龄
		else if (strcmp((q + i)->Left, "年龄") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Age > atoi((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if (atoi((q + i)->Right) != (p + j)->Age) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Age < atoi((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//判断籍贯
		else if (strcmp((q + i)->Left, "籍贯") == 0) {
			int t, l;
			char* con = (q + i)->Right;
			int con_len = strlen(con);
			for (j = 0; j < all; j++) {
				char* info = (p + j)->Origin;
				int info_len = strlen(info);
				int pt = 0;
				bool IS = false;
				//判断籍贯中的关键字，代码可以复制粘贴，非常有用。
				for (t = 0; t < info_len; t++) {
					if (*con == *(info + t)) {
						for (l = t; l < t + con_len; l++) {
							if (*(con + l - t) == *(info + l)) {
								pt += 1;
							}
							else {
								break;
							}
						}
						if (pt == con_len) {
							IS = true;
							break;
						}
						else {
							t += pt - 1;
						}
					}
					else continue;
				}
				if (IS) {
					for (k = j; k < all - 1; k++) {
						*(p + k) = *(p + k + 1);
					}
					all -= 1;
					j -= 1;
				}
				else continue;
			}
		}
		//判断学院
		else if (strcmp((q + i)->Left, "学院") == 0) {
			if (strcmp((q + i)->Op, "=") != 0) {
				printf("该条件无效\n");
			}
			else {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->College, (q + i)->Right) == 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
		}
		//判断电话
		else if (strcmp((q + i)->Left, "电话") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->Phone, (q + i)->Right) > 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if (strcmp((q + i)->Right, (p + j)->Phone) == 0) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if (strcmp((p + j)->Phone, (q + i)->Right) < 0) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//判断程序设计成绩
		else if (strcmp((q + i)->Left, "程序设计") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming > atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming != atof((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming < atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//数学
		else if (strcmp((q + i)->Left, "数学") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Math > atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Math != atof((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Math < atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//英语
		else if (strcmp((q + i)->Left, "英语") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->English > atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->English != atof((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->English < atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//研讨课
		else if (strcmp((q + i)->Left, "研讨课") == 0) {
			if (strcmp((q + i)->Op, ">") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming > atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else if (strcmp((q + i)->Op, "=") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming != atof((q + i)->Right)) {
						continue;
					}
					else {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
				}
			}
			else if (strcmp((q + i)->Op, "<") == 0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->Programming < atof((q + i)->Right)) {
						for (k = j; k < all - 1; k++) {
							*(p + k) = *(p + k + 1);
						}
						all -= 1;
						j -= 1;
					}
					else {
						continue;
					}
				}
			}
			else {
				printf("该条件无效\n");
			}
		}
		//最后一种情况
		else {
			printf("该条件无效");
		}
	}

	ShowStudentAll(0, all);

	printf("共 %d 条\n\n", all);

	FILE* fp;
	if ((fp = fopen("student.txt", "w")) == NULL) {
		return;
	}
	int a;
	for (a = 0; a < all; a++) {
		fprintf(fp, "%d %s %s %d %s %s %s %.2f %.2f %.2f %.2f\n",\
			(p + a)->ID, (p + a)->Name, (p + a)->Sex, (p + a)->Age, (p + a)->Origin, (p + a)->College, (p + a)->Phone, \
			(p + a)->Programming, (p + a)->Math, (p + a)->English, (p + a)->Conference);
	}
	fclose(fp);
	printf("数据删除完成\n");

	Count = all;
}

void main(void) {

	int num;
	int x, y;

	printf("正在初始化，请稍后......\n");
	Count = LoadFile();
	printf("初始化完成，欢迎使用学生成绩管理系统\n\n");
	printf("++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+           本系统功能入口如下           +\n");
	printf("+  1  查看全部人数                       +\n");
	printf("+  2  查看学生全部信息                   +\n");
	printf("+  3  查看学生基本信息                   +\n");
	printf("+  4  查看学生成绩                       +\n");
	printf("+  5  录入学生信息                       +\n");
	printf("+  6  条件查询                           +\n");
	printf("+  7  查看排名                           +\n");
	printf("+  8  条件删除                           +\n");
	printf("+  0  退出程序                           +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++\n");

	
	while (1) {

		printf(">>请输入功能:");
		if (!scanf("%d", &num)) {
			return;  //这里有一个容易错的地方，就是scanf函数末尾不能有空格、制表、回车、换页和换行符，否则要多输入一个数字
		}
		
		if (num == 0) {
			exit(0);
		}
		else if (num == 1) {
			printf("全部人数为：%d\n", Count);
		}
		else if (num == 2) {
			printf(">>请输入起止序号：");
			if (!scanf("%d %d", &x, &y)) {
				return;
			}
			while (x > Count || y > Count || x > y) {
				printf("您输入的起止点超过总人数 %d，请重新输入。\n",Count);
				printf(">>请输入起止序号:");
				if (!scanf("%d %d", &x, &y)) {
					return;
				}
			}

			ShowStudentAll (x, y);
		}
		else if (num == 3) {
			printf(">>请输入起止序号：");
			if (!scanf("%d %d", &x, &y)) {
				return;
			}
			while (x > Count || y > Count || x > y) {
				printf("您输入的起止点超过总人数 %d，请重新输入。\n", Count);
				printf(">>请输入起止序号：");
				if (!scanf("%d %d", &x, &y)) {
					return;
				}
			}

			ShowStudentInfo(x, y);
		}
		else if (num == 4) {
			printf("请输入起止序号：");
			if (!scanf("%d %d", &x, &y)) {
				return;
			}
			while (x > Count || y > Count || x > y) {
				printf("您输入的起止点超过总人数 %d，请重新输入。\n", Count);
				printf(">>请输入起止序号：");
				if (!scanf("%d %d", &x, &y)) {
					return;
				}
			}

			ShowStudentGrade(x,y);
		}
		else if (num == 5) {
			int in;
			printf(">>请输入要写入的学生人数：");
			if (!scanf("%d", &in)) {
				return;
			}

			WriteFile(in);
		}
		else if (num == 6) {
			int count;
			printf(">>请输入条件数：");
			if (!scanf("%d", &count)) {
				return;
			}
			if (count < 0 || count > 5) {
				if (count < 0) {
					printf("条件数不能小于0");
				}
				else {
					printf("条件数过多，请输入小于5的条件数。");
				}
			}
			else {
				SelectByCondition(count);
			}
		}
		else if (num == 7) {
			char orderby[10];
			char order[3];
			printf("请输入排名依据以及方式:");
			if (!scanf("%s %s", &orderby, &order)) {
				return;
			}
			
			OrderStudent(orderby,order);
		}
		else if (num == 8) {
			int delcount;
			printf(">>请输入条件数：");
			if (!scanf("%d", &delcount)) {
				return;
			}
			if (delcount < 0 || delcount > 5) {
				if (delcount < 0) {
					printf("条件数不能小于0");
				}
				else {
					printf("条件数过多，请输入小于5的条件数。");
				}
			}
			else {
				DeleteByCondition(delcount);
			}
		}
		else {
			printf("无此功能，请重新输入");
		}
	}
	
	system("pause");
}