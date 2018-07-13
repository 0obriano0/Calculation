#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#define str_length 1000

/* ��k�B��� */ 
char* add(char *num1,char *num2);
/* �r��B�z�� */
void string_main(char *str);
void check_add(char *str);
int get_string_length(char *str);
void Remake(char *str);
bool check_parentheses(char *str);
/* ���~�^�� */
void error(int code);

/* �D�{�� */
int main(){
	while(1){
		char str[str_length+1];
		str[str_length] = '\0';
		str[0] = '\0';
		do{
			fflush(stdin);
			if(str[str_length] != '\0')
				printf("��J��r�����ץH�F��W��(%d)�Э��s��J\n",str_length);
			printf("�п�J�@��⦡:" );
			scanf("%[^\n]",str);
		}while(!str[str_length] == '\0' || str[0] == '\0');
		fflush(stdin);
		Remake(str);
		string_main(str);
		printf("%s\n",str);
		system("pause");
	}
}

/* ��k�B��� */ 

char* add(char *num1,char *num2){
	char num[100];
	sprintf(num,"%lf",atof(num1)+atof(num2));
	return num;
}

/* �r��B�z�� */
void string_main(char *str){ 				//�ˬd���D�禡
	
	check_add(str);
}

void check_add(char *str){					// + ���P�w
	int str_index[2]={0,0};
	char str_num[2][str_length+1];
	int load_num[2];
	str_index[1] = 0;
	load_num[0] = 0;
	load_num[1] = 0;
	char get_code = '\0';
	while(!*(str+str_index[1])=='\0'){
		int get_code_num = get_code == '\0'? 0 : 1;
		if((*(str+str_index[1])-'0' >=0 && *(str+str_index[1]) - '0'<=9)||*(str+str_index[1]) == '.' || *(str+str_index[1]) == '-'){
			str_num[get_code_num][load_num[get_code_num]] = *(str+str_index[1]);
			load_num[get_code_num]++;
			str_num[get_code_num][load_num[get_code_num]] = '\0';
		}else{
			if(get_code == '\0'){
				get_code = *(str+str_index[1]);
			}else if(get_code == '+'){
				char str_buffer[str_length];
				str_buffer[0] = '\0';
				strcat(str_buffer, add(str_num[0],str_num[1]));
				strcat(str_buffer, str+str_index[1]);
				*str = '\0';
				strcat(str, str_buffer);
				str_index[1] = 0;
				load_num[0] = 0;
				load_num[1] = 0;
				str_num[0][0] = '\0';
				str_num[1][0] = '\0';
				get_code = '\0';
				continue;
			}else{
				
			}
		}
		str_index[1]++;
	}
} 

int get_string_length(char *str){
	int loopnum;
	for(loopnum = 0;*(str+loopnum)!='\0';loopnum++);
	return loopnum;
}

void Remake(char *str){
	char str_get[100];
	int loopnum1 = 0;
	int loopnum2 = 0;
	while(!*(str+loopnum1)=='\0'){
		if(*(str+loopnum1)!=' '){
			str_get[loopnum2] = *(str+loopnum1);
			loopnum2++;
		}
		loopnum1++; 
	}
	str_get[loopnum2] = ' ';
	str_get[loopnum2+1] = '\0';
	*str = '\0';
	strcat(str, str_get);
	check_parentheses(str);
}

bool check_parentheses(char *str){				//�ˬd()�A�����S�����,�κ⦡�����S���A�� 
	bool have_ = false;
	int num = 0;								//�ˬd�� '(' num+1 �Ϥ� �� ')' num-1 �P�w�� '0' ���p�ѪG��0 ��� () �O��٪� 
	for(int loopnum1 = 0;!*(str+loopnum1)=='\0';loopnum1++){
		if(*(str+loopnum1) == '('){
			num++;
			have_ = true;
		}else if(*(str+loopnum1) == ')')
			num--;
		if(num <= -1)
			error(1);
	}
	if(num >= 1)
		error(1);
	return have_;
}

/* ���~�^�� */
void error(int code){
	printf("\n���~�N�X: %d\n���~��T: ",code);
	switch(code){
		case 1:
			printf("�A�����ﯯ");
			break;
		default:
			printf("�������~�A���p���{���]�p�v");
	}
	printf("...");
	getch();
	exit(1);
}
