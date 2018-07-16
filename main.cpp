#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#define str_length 1000								//�]�����Ӽ��x�ʺA�O����A�ҥH�N�ϥεۿ�J���r�]�W�� 

/* ��k�B��� */ 
char* add(char *num1,char *num2);					// �[���B�� 
char* multiply(char *num1,char *num2);				// �����B�� 
char* divide(char *num1,char *num2);				// �����B�� 
/* �r��B�z�� */
void string_main(char *str);						//�B�z�r�ꪺ�D�禡 
void check_negative(char *str);						//�B�z '-' �Ÿ� 
void check_multiply_and_divide(char *str);			//�B�z * & / 
void check_add(char *str);							//�B�z + 
int get_string_length(char *str);					//Ū���r����� 
void Remake(char *str);								//�ˬd�ϥΪ̿�J���r��A�ñN�L��z���{���һݪ��榡 
void take_out_space(char* str);						//�N�Ҧ����ťծ��� 
void get_parentheses(char *str);					//���o�A�������Ȩð��B�� 
bool check_parentheses(char *str);					//�B�z ( ) 
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
char* multiply(char *num1,char *num2){
	char num[100];
	sprintf(num,"%lf",atof(num1)*atof(num2));
	return num;
}

char* divide(char *num1,char *num2){
	char num[100];
	if(atof(num2) == 0)
		error(10);
	sprintf(num,"%lf",atof(num1)/atof(num2));
	return num;
}


/* �r��B�z�� */
void string_main(char *str){				//�ˬd���D�禡
	get_parentheses(str);
	check_negative(str);
	check_multiply_and_divide(str);
	check_add(str);
	take_out_space(str);
}

void check_negative(char *str){				// - ���P�w 
	int str_index[2]={0,0};
	while(!*(str+str_index[1])=='\0'){
		char str_buffer[str_length];
		str_buffer[0] = '\0';
		if(str_index[1]!=0 && *(str+str_index[1]) == '-'){
			if(*(str+str_index[1]-1)>='0' && *(str+str_index[1]-1)<='9'){
				strcat(str_buffer, "+");
				strcat(str_buffer, str+str_index[1]);
				*(str+str_index[1]) = '\0';
				strcat(str, str_buffer);
			}else if(*(str+str_index[1]-1) == '-'){
				strcat(str_buffer, "+");
				strcat(str_buffer, str+str_index[1]+1);
				*(str+str_index[1]-1) = '\0';
				strcat(str, str_buffer);
			}else{
				if(*(str+str_index[1]-1)!='+')
					error(-1);
			}
		}
		str_index[1]++;
	}
}

void check_multiply_and_divide(char *str){
	int str_index[2]={0,0};
	char str_num[2][str_length+1];
	str_num[0][0] = '\0';
	str_num[1][0] = '\0';
	int load_num[2];
	str_index[1] = 0;
	load_num[0] = 0;
	load_num[1] = 0;
	int mode = 0;
	char get_code = '\0';
	while(!*(str+str_index[1]) == '\0'){
		if(get_code == '\0' && mode == 0 && (*(str+str_index[1]) == '*' || *(str+str_index[1]) == '/')){
			get_code = *(str+str_index[1]);
			mode = 1;
			str_index[0] = str_index[1]-1;
		}else if(mode == 1){
			if((*(str+str_index[1])-'0' >=0 && *(str+str_index[1]) - '0'<=9)||*(str+str_index[1]) == '.' || *(str+str_index[1]) == '-'){
				str_num[1][load_num[1]] = *(str+str_index[1]);
				load_num[1]++;
				str_num[1][load_num[1]] = '\0';
			}else{
				mode = 2;
				str_index[1]--;
			}
		}else if(mode == 2){
			while(str_index[0] >= -1 && mode == 2){
				if(str_index[0] >= 0 && ((*(str+str_index[0])-'0' >=0 && *(str+str_index[0]) - '0'<=9)||*(str+str_index[0]) == '.' || *(str+str_index[0]) == '-')){
					str_num[0][load_num[0]+1] = '\0';
					if(load_num[0] != 0){
						for(int loopnum1 = load_num[0]; loopnum1 > 0; loopnum1--){
							str_num[0][loopnum1] = str_num[0][loopnum1-1];
						}
					}
					str_num[0][0] = *(str+str_index[0]);
					load_num[0]++;
				}else{
					if (str_index[0] < -1){
						error(11);
					}
					
					char str_buffer[str_length];
					str_buffer[0] = '\0';
					
					if(get_code == '*'){
						strcat(str_buffer,multiply(str_num[0],str_num[1]));
					}else if(get_code == '/'){
						strcat(str_buffer,divide(str_num[0],str_num[1]));
					}else{
						error(12);
					}
					strcat(str_buffer, str+str_index[1]);
					*(str+str_index[0]+1) = '\0';
					strcat(str, str_buffer);
					str_index[1] = 0;
					str_index[0] = 0;
					load_num[0] = 0;
					load_num[1] = 0;
					str_num[0][0] = '\0';
					str_num[1][0] = '\0';
					get_code = '\0';
					mode = 0;
					continue;
				}
				str_index[0]--;
			}
		}
		str_index[1]++;
	}
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
				error(3);
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

void take_out_space(char* str){
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
	str_get[loopnum2] = '\0';
	*str = '\0';
	strcat(str, str_get);
}

void get_parentheses(char *str){
	char str_buffer[str_length];
	int str_buffer_index = 0;
	int parentheses = 0;
	int str_index[2]={0,0};
	while(!*(str+str_index[1])=='\0'){
		if(*(str+str_index[1])=='('){
			if(parentheses == 0){
				str_index[0] = str_index[1];
				if(str_index[1]!=0)
					if(*(str+str_index[1]-1) >= '0'&& *(str+str_index[1]-1) <= '9' || *(str+str_index[1]-1) == '.')
						error(2);
			}
			parentheses++;
		}else if(*(str+str_index[1])==')'){
			parentheses--;
			if(parentheses == 0){
				Remake(str_buffer);
				string_main(str_buffer);
				strcat(str_buffer, str+str_index[1]+1);
				*(str+str_index[0]) = '\0';
				strcat(str, str_buffer);
				parentheses = 0;
				str_index[1] = str_index[0];
				str_buffer_index = 0;
			}
		}else if(parentheses != 0){
			str_buffer[str_buffer_index] = *(str+str_index[1]);
			str_buffer_index++;
			str_buffer[str_buffer_index] = '\0';
		}
		str_index[1]++;
	}
}

bool check_parentheses(char *str){				//�ˬd()�A�����S�����,�κ⦡�����S���A�� 
	bool have_ = false;
	int num = 0;								//�ˬd���� '(' num+1 �Ϥ� ���� ')' num-1 �P�w�� '0' ���p�ѪG��0 ���� () �O��٪� 
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
		case 2:
			printf("�A���e�����O�Ÿ�");
			break;
		case 3:
			printf("+���B�̥X�{���D");
			break;
		case 10:
			printf("�]���B�⤤�X�{���P 0 �ҥH�{���j������");
			break;
		default:
			printf("�������~�A���p���{���]�p�v");
	}
	printf("...");
	getch();
	exit(1);
}