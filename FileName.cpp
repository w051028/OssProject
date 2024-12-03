#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void)
{
	int s;
	while (1)
	{
		puts("------------------------------");
		puts("1. 체크리스트에 입력하기");
		puts("2. 체크리스트를 출력하기");
		puts("3. 체크리스트에 완료 표시하기");
		puts("4. 체크리스트 삭제하기");
		puts("5. 종료하기");
		puts("------------------------------");
		puts("원하는 옵션의 번호를 입력하세요");
		printf(">>>");
		scanf_s("%d", &s);

		switch (s)
		{
			case 1:
				puts("1");
				//입력프로그램
				break;
			case 2:
				puts("2");
				//출력프로그램
				break;
			case 3:
				puts("3");
				//완료 표시 프로그램
				break;
			case 4:
				puts("4");
				//삭제 프로그램
				break;
			case 5:
				break;
			default:
				puts("입력한 번호를 다시 확인하세요");
				break;
		}

		if (s == 5)
		{
			puts("프로그램을 종료합니다,..");
			break;
		}
	}
}

int main(void)
{
	menu();
	return 0;
}
