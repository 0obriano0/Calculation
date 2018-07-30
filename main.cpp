#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream> 
#include <math.h>
#define str_length 1000								//因為不太熟悉動態記憶體，所以將使用著輸入的字設上限

/* 算法運算區 */
char* add(char *num1,char *num2);					//加的運算
char* multiply(char *num1,char *num2);				//乘的運算
char* divide(char *num1,char *num2);				//除的運算
char* factorial(char *num1);						//乘階的運算('!')
/* 字串處理區 */
void string_main(char *str);						//處理字串的主函式
void check_factorial(char *str);					//處理 '!' 乘階符號
void check_negative(char *str);						//處理 '-' 符號
void check_multiply_and_divide(char *str);			//處理 * & /
void check_add(char *str);							//處理 +
int get_string_length(char *str);					//讀取字串長度
void Remake(char *str);								//檢查使用者輸入的字串，並將他整理成程式所需的格式
int take_out_space(char* str);						//將所有的空白拿掉
void get_parentheses(char *str);					//取得括弧內的值並做運算
bool check_parentheses(char *str);					//處理 ( )
/* 錯誤回報 */
void error(int code);
void error(int code,char *error_str);
/* UI介面處理 */ 
void mathematical_string_for_error(char *error_str,char *num1,char *code,char *num2,char *num);

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
			printf("請輸入一串算式:");
			scanf("%[^\n]",str);
		}while(!str[str_length] == '\0' || str[0] == '\0');
		fflush(stdin);
		Remake(str);
		string_main(str);
		printf("\n答案為: %s\n\n",str);
		system("pause");
		printf("\n-----------------------------------------------------------------------\n\n");
	}
}

/* 算法運算區 */ 

char* add(char *num1,char *num2){
	char num[1000];
	num[0] = '\0';
	sprintf(num,"%lf",atof(num1)+atof(num2));
	char buffer[1000];
    sprintf(buffer,"%lf",atof(num) - atof(num2));
	if(atof(buffer) != atof(num1)){
		char error_str[str_length+1];
		mathematical_string_for_error(error_str,num1," + ",num2,num);
		error(31,error_str);
	} 
	return num;
}
char* multiply(char *num1,char *num2){
	char num[1000];
	num[0] = '\0';
	sprintf(num,"%lf",atof(num1)*atof(num2));
	char buffer[1000];
    sprintf(buffer,"%lf",atof(num) / atof(num2));
	if(atof(buffer) != atof(num1)){
		char error_str[str_length+1];
		std::cout << atof(num) << " / " << atof(num2) << " = " << atof(num) / atof(num2) << std::endl;
		mathematical_string_for_error(error_str,num1," * ",num2,num);
		error(32,error_str);
	} 
	return num;
}

char* divide(char *num1,char *num2){
	char num[1000];
	num[0] = '\0';
	if(atof(num2) == 0)						//檢查 被除數是不是為零
		error(10);
	sprintf(num,"%lf",atof(num1)/atof(num2));
	return num;
}

char* factorial(char *num1){
	if( atof(num1) == 0)
        return "1";
    else{
    	char num[1000];
    	num[0] = '\0';
    	sprintf(num,"%lf",atof(num1)-1);
    	char function_buffer[1000];
    	function_buffer[0] = '\0';
    	sprintf(function_buffer,"%lf",atof(factorial(num)));
    	sprintf(num,"%lf",atof(num1) * atof(function_buffer));
    	char buffer[1000];
    	sprintf(buffer,"%lf",atof(num) / atof(function_buffer));
    	if(atof(buffer) != atof(num1)){
    		char error_str[str_length+1];
    		mathematical_string_for_error(error_str,num1,"!","",num);
    		error(24,error_str);
    	}	
    	return num;
    }    
}

/* 字串處理區 */
void string_main(char *str){				//檢查的主函式
	get_parentheses(str);
	check_negative(str);
	check_factorial(str);
	check_multiply_and_divide(str);
	check_add(str);
	take_out_space(str);
}

void check_factorial(char *str){
	int str_index[2] = {0,0};
	char str_num[str_length+1];
	str_num[0] = '\0';
	char get_code = '\0';
	while(!*(str+str_index[1])=='\0'){
		if(get_code == '\0'){
			if(*(str+str_index[1]) == '!'){
				get_code = *(str+str_index[1]);
				str_index[0] = str_index[1];
			}else{
				str_index[1]++;
			}
		}else if(get_code == '!'){
			if(str_index[0] >= 0){
				if((*(str+str_index[0]-1)-'0' >=0 && *(str+str_index[0]-1) - '0'<=9)||*(str+str_index[0]-1) == '.'){
					str_index[0]--;
					char str_buffer[str_length+1];
					str_buffer[0] = *(str+str_index[0]);
					str_buffer[1] = '\0';
					strcat(str_buffer,str_num);
					str_num[0] = '\0';
					strcat(str_num,str_buffer);
				}else{
					if(str_num[0] != '\0'){
						if(str_index[0] >= 1){
							if(*(str+str_index[0]-1) == '-'){
								if(str_index[0] == 1){
									char error_str[str_length+1];
									error_str[0] = '\0';
									strcat(error_str,"-");
									strcat(error_str,str_num);
									strcat(error_str,"!");
									error(22,error_str);
								}else
									if(*(str+str_index[0]-2) != '+')
										error(23);
							}
						}
						char str_buffer[str_length+1];
						str_buffer[0] = '\0';
						*(str+str_index[0]) = '\0';
						strcat(str_buffer,str);
						strcat(str_buffer,factorial(str_num));
						strcat(str_buffer,str+str_index[1]+1);
						*str = '\0';
						strcat(str,str_buffer);
						str_index[1] = str_index[0];
						get_code = '\0';
						str_index[0] = 0;
						str_num[0] = '\0';
					}else
						error(21);
				}
			}else if(str_num[0] == '\0')
				error(21);
		}
	}
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
				if(*(str+str_index[1]-2) == '+'){
					*(str+str_index[1]-2) = '\0';
					str_index[1]--;
				}else
					*(str+str_index[1]-1) = '\0';
				strcat(str, str_buffer);
			}else{
				if(*(str+str_index[1]-1)!='+' && *(str+str_index[1]-1)!='*' && *(str+str_index[1]-1)!='/')
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
	int str_index=0;
	char str_num[2][str_length+1];
	int load_num[2];
	load_num[0] = 0;
	load_num[1] = 0;
	char get_code = '\0';
	while(!*(str+str_index)=='\0'){
		int get_code_num = get_code == '\0'? 0 : 1;
		if((*(str+str_index)-'0' >=0 && *(str+str_index) - '0'<=9)||*(str+str_index) == '.' || *(str+str_index) == '-'){
			str_num[get_code_num][load_num[get_code_num]] = *(str+str_index);
			load_num[get_code_num]++;
			str_num[get_code_num][load_num[get_code_num]] = '\0';
		}else{
			if(get_code == '\0'){
				get_code = *(str+str_index);
			}else if(get_code == '+'){
				char str_buffer[str_length];
				str_buffer[0] = '\0';
				strcat(str_buffer, add(str_num[0],str_num[1]));
				strcat(str_buffer, str+str_index);
				*str = '\0';
				strcat(str, str_buffer);
				str_index = 0;
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
		str_index++;
	}
} 

int get_string_length(char *str){
	int loopnum;
	for(loopnum = 0;*(str+loopnum)!='\0';loopnum++);
	return loopnum;
}

void Remake(char *str){
	int index = take_out_space(str);
	*(str+index) = ' ';
	*(str+index+1) = '\0';
	check_parentheses(str);
}

int take_out_space(char* str){
	char str_get[str_length+1];
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
	return loopnum2;
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
			}else if(parentheses > 0){
				str_buffer[str_buffer_index] = *(str+str_index[1]);
				str_buffer_index++;
				str_buffer[str_buffer_index] = '\0';
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
			}else if(parentheses > 0){
				str_buffer[str_buffer_index] = *(str+str_index[1]);
				str_buffer_index++;
				str_buffer[str_buffer_index] = '\0';
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
		case 21:
			printf("!號前面不是數字 請確認算式");
			break;
		case 22:
			printf("程式不支援 運算 負數的 乘階");
			break;
		case 23:
			printf("在做 ! 的運算時出現錯誤");
			break;
		case 24:
			printf("! 在運算中 出現錯誤");
			break;
		case 31:
			printf("算到 + 時 出現錯誤");
			break;
		case 32:
			printf("算到 * 時 出現錯誤");
			break;
		default:
			printf("未知錯誤，請聯絡程式設計師");
	}
	printf("...");
	getch();
	exit(1);
}

void error(int code,char *error_str){
	printf("\n\n運算式　: %s",error_str);
	error(code);
}

/* UI介面處理 */ 
void mathematical_string_for_error(char *error_str,char *num1,char *code,char *num2,char *num){
	*error_str = '\0';
	strcat(error_str,num1);
	strcat(error_str,code);
	strcat(error_str,num2);
	strcat(error_str," = ");
	strcat(error_str,num);
}
