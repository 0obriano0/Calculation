#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#define str_length 1000

/* 算法運算區 */ 
char* add(char *num1,char *num2);
/* 字串處理區 */
double string_main(char *str);
int get_string_length(char *str);
bool check_parentheses(char *str);
/* 錯誤回報 */
void error(int code);

/* 主程式 */
int main(){
	char str[str_length+1];
	str[str_length] = '\0';
	do{
		if(str[str_length] != '\0')
			printf("輸入文字的長度以達到上限(%d)請重新輸入\n",str_length);
		printf("請輸入一串算式:" );
		scanf("%[^\n]",str);
	}while(!str[str_length] == '\0');
	string_main(str);
}

/* 算法運算區 */ 

char* add(char *num1,char *num2){
	char num[100];
	sprintf(num,"%lf",atof(num1)+atof(num2));
	return num;
}

/* 字串處理區 */
double string_main(char *str){
	int str_index[2]={0,0};
	char str_num[2][str_length+1];
	int load_num[2];
	
	
	/* + 的判定 */
	str_index[1] = 0;
	load_num[0] = 0;
	load_num[1] = 0;
	char get_code = '\0';
	while(!*(str+str_index[1])=='\0'){
		int get_code_num = get_code == '\0'? 0 : 1;
		if((*(str+str_index[1])-'0' >=0 && *(str+str_index[1]) - '0'<=9)||*(str+str_index[1]) == '.'){
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

bool check_parentheses(char *str){				//檢查()括弧有沒有對稱
	bool have_ = false;
	int num = 0;								//檢查當有 '(' num+1 反之 當有 ')' num-1 判定到 '0' 假如解果為0 表示 () 是對稱的 
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

/* 錯誤回報 */
void error(int code){
	printf("\n錯誤代碼: %d\n錯誤資訊: ",code);
	switch(code){
		case 1:
			printf("括弧不對秤");
			break;
		default:
			printf("未知錯誤，請聯絡程式設計師");
	}
	printf("...");
	getch();
	exit(1);
}
