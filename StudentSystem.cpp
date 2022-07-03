# include <StudentSystem.h>

int Count; //ѧ����������ȫ�ֱ���

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
	fclose(fp);  //һ��Ҫ�ر��ļ�

	return count;
}

void WriteFile(int count) {

	int i;
	struct STUDENT* p = student;

	printf("�밴�� <ѧ��> <����> <�Ա�> <����> <����> <ѧԺ> <�绰����> <�������> <��ѧ> <Ӣ��> <���ֿ�> ��˳����д���Կո�ָ�\n");
	printf("�����ʱû�У�����дΪ��0.0��\n");

	FILE* fp;
	if ((fp = fopen("student.txt", "a")) == NULL) {
		printf("Error, cannot open file");
		exit(0);
	}

	for (i = 0; i < count; i++) {

		printf("ѧ�� %d:\n", i);
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
	fclose(fp);  //���д���ǳ���Ҫ��һ��Ҫ�ر��ļ��������޷�д�롣
	printf("ѧ����Ϣ¼����ɡ�\n");
}

void ShowStudentAll(int start, int end) {

	int i;
	struct STUDENT* p = student;

	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+  ѧ��   +  ����  +�Ա�+����+           ����        +      ѧԺ     +    �绰����     + ������� + ��ѧ + Ӣ�� + ���ֿ� +\n");
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
	printf("+   ѧ��   +  ����  +�Ա�+����+         ����        +        ѧԺ       +    �绰����    +\n");
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
	printf("+  ѧ��   +  ����  + ������� + ��ѧ + Ӣ�� + ���ֿ� +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	for (i = start; i < end; i++) {
		printf("%-12d%-8s%-9.2f%-9.2f%-9.2f%-9.2f\n", \
			(p + i)->ID, (p + i)->Name, (p + i)->Programming, (p + i)->Math, (p + i)->English, (p + i)->Conference);
	}
}

/*
* �����������ʽΪ��<�ֶ�> <�ȽϷ�> <����>
* �����Կո�ָ�������������Ч
* ���������ѧ�ɼ���85�����ϵ�ͬѧ����������:
* >>> ��ѧ > 85
* ͬʱ������֧�ֹؼ��ֲ��ң�ֻҪ����ؼ��֣����ɲ�ѯ�����ùؼ��ֵ���Ϣ������
* ��ѯ����Ϊ�Ĵ�������ѧ����ֻ��Ҫ����:
* >>> ���� = �Ĵ�
* ���ɲ�ѯ�õ���
* Ŀǰֻ֧�ִ��ڡ�С�ں͵����������������������ֻ�е��������������ѭ��ʾ��
*/
void SelectByCondition(int count) {

	//countΪ����������ѯ���������������

	struct CONDITION {
		char Left[10];
		char Op[2];
		char Right[20];
	}condition[6];

	struct CONDITION* q = condition;
	struct STUDENT* p = student;

	int i, j, k, all = Count;

	for (i = 0; i < count; i++) {
		// ��������
		printf("����������%d��\n", i+1);
		if (!scanf("%s %s %s", &(q + i)->Left, &(q + i)->Op, &(q + i)->Right)) {
			return;
		}

		// �ж�ѧ��
		if (strcmp((q + i)->Left, "ѧ��")==0) {
			if (strcmp((q + i)->Op, ">")==0) {
				for (j = 0; j < all; j++) {
					if ((p + j)->ID <= atoi((q + i)->Right)) {
						// ɾ���ṹ�������������ݣ���δ�����Ը���ճ�����ǳ�����
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
				printf("��������Ч\n");
			}
		}
		//�ж�����
		else if (strcmp((q + i)->Left, "����")==0) {
			if (strcmp((q + i)->Op, "=")!=0) {
				printf("��������Ч\n");
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
		//�ж��Ա�
		else if (strcmp((q + i)->Left, "�Ա�")==0) {
			if (strcmp((q+i)->Op,"=")!=0) {
				printf("��������Ч\n");
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
		//�ж�����
		else if (strcmp((q + i)->Left, "����") == 0) {
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
			printf("��������Ч\n");
			}
		}
		//�жϼ���
		else if (strcmp((q + i)->Left, "����") == 0) {
			int t,l;
			char* con = (q + i)->Right;
			int con_len = strlen(con);
			for (j = 0; j < all; j++) {
				char* info = (p + j)->Origin;
				int info_len = strlen(info);
				int pt = 0;
				bool IS = false;
				//�жϼ����еĹؼ��֣�������Ը���ճ�����ǳ����á�
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
				// ����ṹ�������в�����Ҫ�������
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
		//�ж�ѧԺ
		else if (strcmp((q + i)->Left, "ѧԺ") == 0) {
			if (strcmp((q + i)->Op, "=") != 0) {
				printf("��������Ч\n");
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
		//�жϵ绰
		else if (strcmp((q + i)->Left, "�绰") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//�жϳ�����Ƴɼ�
		else if (strcmp((q + i)->Left, "�������") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//��ѧ
		else if (strcmp((q + i)->Left, "��ѧ") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//Ӣ��
		else if (strcmp((q + i)->Left, "Ӣ��") == 0){
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
				printf("��������Ч\n");
			}
		}
		//���ֿ�
		else if (strcmp((q + i)->Left, "���ֿ�") == 0){
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
				printf("��������Ч\n");
			}
		}
		//���һ�����
		else {
			printf("��������Ч");
		}
	}

	ShowStudentAll(0, all);

	printf("�� %d ��\n\n", all);

	//���³�ʼ��
	Count = LoadFile();
}

void OrderStudent(char *orderby, char *order) {

	int i, j;
	struct STUDENT* p = student;
	struct STUDENT s;  //�ṹ�彻���м����

	if (strcmp(orderby, "�������") == 0) {
		if (strcmp(order, "����") == 0) {
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
		else if (strcmp(order,"����") == 0) {
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
			printf("����ʽ����ֻ�С����򡯺͡�����");
			return;
		}
	}
	else if (strcmp(orderby, "��ѧ") == 0) {
		if (strcmp(order, "����") == 0) {
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
		else if (strcmp(order,"����") == 0) {
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
			printf("����ʽ����ֻ�С����򡯺͡�����");
			return;
		}
	}
	else if (strcmp(orderby, "Ӣ��") == 0) {
		if (strcmp(order, "����") == 0) {
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
		else if (strcmp(order,"����") == 0) {
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
			printf("����ʽ����ֻ�С����򡯺͡�����");
			return;
		}
	}
	else if (strcmp(orderby, "���ֿ�") == 0) {
		if (strcmp(order, "����") == 0) {
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
		else if (strcmp(order,"����") == 0) {
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
			printf("����ʽ����ֻ�С����򡯺͡�����");
			return;
		}
	}
	else {
		printf("��֧�ֵ��������ݡ�\n");
		return;
	}

	ShowStudentAll(0, Count);

	//�ظ�ԭλ
	Count = LoadFile();
}

void DeleteByCondition(int count) {

	//countΪ����������ѯ���������������

	struct DELCONDITION {
		char Left[10];
		char Op[2];
		char Right[20];
	}delcondition[6];

	struct DELCONDITION* q = delcondition;
	struct STUDENT* p = student;

	int i, j, k, all = Count;

	for (i = 0; i < count; i++) {
		// ��������
		printf("����������%d��\n", i+1);
		if (!scanf("%s %s %s", &(q + i)->Left, &(q + i)->Op, &(q + i)->Right)) {
			return;
		}

		// �ж�ѧ��
		if (strcmp((q + i)->Left, "ѧ��") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//�ж�����
		else if (strcmp((q + i)->Left, "����") == 0) {
			if (strcmp((q + i)->Op, "=") != 0) {
				printf("��������Ч\n");
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
		//�ж��Ա�
		else if (strcmp((q + i)->Left, "�Ա�") == 0) {
			if (strcmp((q + i)->Op, "=") != 0) {
				printf("��������Ч\n");
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
		//�ж�����
		else if (strcmp((q + i)->Left, "����") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//�жϼ���
		else if (strcmp((q + i)->Left, "����") == 0) {
			int t, l;
			char* con = (q + i)->Right;
			int con_len = strlen(con);
			for (j = 0; j < all; j++) {
				char* info = (p + j)->Origin;
				int info_len = strlen(info);
				int pt = 0;
				bool IS = false;
				//�жϼ����еĹؼ��֣�������Ը���ճ�����ǳ����á�
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
		//�ж�ѧԺ
		else if (strcmp((q + i)->Left, "ѧԺ") == 0) {
			if (strcmp((q + i)->Op, "=") != 0) {
				printf("��������Ч\n");
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
		//�жϵ绰
		else if (strcmp((q + i)->Left, "�绰") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//�жϳ�����Ƴɼ�
		else if (strcmp((q + i)->Left, "�������") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//��ѧ
		else if (strcmp((q + i)->Left, "��ѧ") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//Ӣ��
		else if (strcmp((q + i)->Left, "Ӣ��") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//���ֿ�
		else if (strcmp((q + i)->Left, "���ֿ�") == 0) {
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
				printf("��������Ч\n");
			}
		}
		//���һ�����
		else {
			printf("��������Ч");
		}
	}

	ShowStudentAll(0, all);

	printf("�� %d ��\n\n", all);

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
	printf("����ɾ�����\n");

	Count = all;
}

void main(void) {

	int num;
	int x, y;

	printf("���ڳ�ʼ�������Ժ�......\n");
	Count = LoadFile();
	printf("��ʼ����ɣ���ӭʹ��ѧ���ɼ�����ϵͳ\n\n");
	printf("++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+           ��ϵͳ�����������           +\n");
	printf("+  1  �鿴ȫ������                       +\n");
	printf("+  2  �鿴ѧ��ȫ����Ϣ                   +\n");
	printf("+  3  �鿴ѧ��������Ϣ                   +\n");
	printf("+  4  �鿴ѧ���ɼ�                       +\n");
	printf("+  5  ¼��ѧ����Ϣ                       +\n");
	printf("+  6  ������ѯ                           +\n");
	printf("+  7  �鿴����                           +\n");
	printf("+  8  ����ɾ��                           +\n");
	printf("+  0  �˳�����                           +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++\n");

	
	while (1) {

		printf(">>�����빦��:");
		if (!scanf("%d", &num)) {
			return;  //������һ�����״�ĵط�������scanf����ĩβ�����пո��Ʊ��س�����ҳ�ͻ��з�������Ҫ������һ������
		}
		
		if (num == 0) {
			exit(0);
		}
		else if (num == 1) {
			printf("ȫ������Ϊ��%d\n", Count);
		}
		else if (num == 2) {
			printf(">>��������ֹ��ţ�");
			if (!scanf("%d %d", &x, &y)) {
				return;
			}
			while (x > Count || y > Count || x > y) {
				printf("���������ֹ�㳬�������� %d�����������롣\n",Count);
				printf(">>��������ֹ���:");
				if (!scanf("%d %d", &x, &y)) {
					return;
				}
			}

			ShowStudentAll (x, y);
		}
		else if (num == 3) {
			printf(">>��������ֹ��ţ�");
			if (!scanf("%d %d", &x, &y)) {
				return;
			}
			while (x > Count || y > Count || x > y) {
				printf("���������ֹ�㳬�������� %d�����������롣\n", Count);
				printf(">>��������ֹ��ţ�");
				if (!scanf("%d %d", &x, &y)) {
					return;
				}
			}

			ShowStudentInfo(x, y);
		}
		else if (num == 4) {
			printf("��������ֹ��ţ�");
			if (!scanf("%d %d", &x, &y)) {
				return;
			}
			while (x > Count || y > Count || x > y) {
				printf("���������ֹ�㳬�������� %d�����������롣\n", Count);
				printf(">>��������ֹ��ţ�");
				if (!scanf("%d %d", &x, &y)) {
					return;
				}
			}

			ShowStudentGrade(x,y);
		}
		else if (num == 5) {
			int in;
			printf(">>������Ҫд���ѧ��������");
			if (!scanf("%d", &in)) {
				return;
			}

			WriteFile(in);
		}
		else if (num == 6) {
			int count;
			printf(">>��������������");
			if (!scanf("%d", &count)) {
				return;
			}
			if (count < 0 || count > 5) {
				if (count < 0) {
					printf("����������С��0");
				}
				else {
					printf("���������࣬������С��5����������");
				}
			}
			else {
				SelectByCondition(count);
			}
		}
		else if (num == 7) {
			char orderby[10];
			char order[3];
			printf("���������������Լ���ʽ:");
			if (!scanf("%s %s", &orderby, &order)) {
				return;
			}
			
			OrderStudent(orderby,order);
		}
		else if (num == 8) {
			int delcount;
			printf(">>��������������");
			if (!scanf("%d", &delcount)) {
				return;
			}
			if (delcount < 0 || delcount > 5) {
				if (delcount < 0) {
					printf("����������С��0");
				}
				else {
					printf("���������࣬������С��5����������");
				}
			}
			else {
				DeleteByCondition(delcount);
			}
		}
		else {
			printf("�޴˹��ܣ�����������");
		}
	}
	
	system("pause");
}