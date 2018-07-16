#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#define str_length 1000								//因為不太熟悉動態記憶體，所以將使用著輸入的字設上限 

/* 算法運算區 */ 
char* add(char *num1,char *num2);					// 加的運算 
char* multiply(char *num1,char *num2);				// 乘的運算 
char* divide(char *num1,char *num2);				// 除的運算 
/* 字串處理區 */
void string_main(char *str);						//處理字串的主函式 
void check_negative(char *str);						//處理 '-' 符號 
void check_multiply_and_divide(char *str);			//處理 * & / 
void check_add(char *str);							//處理 + 
int get_string_length(char *str);					//讀取字串長度 
void Remake(char *str);								//檢查使用者輸入的字串，並將他整理成程式所需的格式 
void take_out_space(char* str);						//將所有的空白拿掉 
void get_parentheses(char *str);					//取得括弧內的值並做運算 
bool check_parentheses(char *str);					//處理 ( ) 
/* 錯誤回報 */
void error(int code);

/* 主程式 */
int main(){
	while(1){
		char str[str_length+1];
		str[str_length] = '\0';
		str[0] = '\0';
		do{
			fflush(stdin);
			if(str[str_length] != '\0')
				printf("輸入文字的長度以達到上限(%d)請重新輸入\n",str_length);
			printf("請輸入一串算式:" );
			scanf("%[^\n]",str);
		}while(!str[str_length] == '\0' || str[0] == '\0');
		fflush(stdin);
		Remake(str);
		string_main(str);
		printf("%s\n",str);
		system("pause");
	}
}

/* 算法運算區 */ 

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


/* 字串處理區 */
void string_main(char *str){				//檢查的主函式
	get_parentheses(str);
	check_negative(str);
	check_multiply_and_divide(str);
	check_add(str);
	take_out_space(str);
}

void check_negative(char *str){				// - 的判定 
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

void check_add(char *str){					// + 的判定
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

bool check_parentheses(char *str){				//檢查()括弧有沒有對稱,及算式中有沒有括弧 
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
		case 2:
			printf("括弧前面不是符號");
			break;
		case 3:
			printf("+的處裡出現問題");
			break;
		case 10:
			printf("因為運算中出現除與 0 所以程式強制關閉");
			break;
		default:
			printf("未知錯誤，請聯絡程式設計師");
	}
	printf("...");
	getch();
	exit(1);
}
