#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct {
	char array[MAX_SIZE][61]; // UTF-8에서 한글 한 글자는 3바이트 차지
	int finished[MAX_SIZE]; // 완료 여부
	int size; // 목록 현재 개수
} List;
List l;

void menu(void);
void Add(void);
void ReadFile(void);
void OutFile(void);
int get_display_width(const char* str);
void print_aligned(const char* str, int total_width);
void PrintList(void);

int main(void) 
{
	l.size = 0;
	ReadFile();
	menu();
	OutFile();
	return 0;
}

void menu(void)
{
	int menu;
	while (true)
	{
		puts("------------------------------");
		puts("1. 체크리스트에 입력하기");
		puts("2. 체크리스트를 출력하기");
		puts("3. 체크리스트에 완료 표시하기");
		puts("4. 체크리스트 삭제하기");
		puts("5. 종료하기\n");
		puts("원하는 옵션의 번호를 입력하세요");
		printf(">>> ");
		scanf_s("%d", &menu);
		getchar();  printf("\n");

		switch (menu)
		{
		case 1:
			Add();
			break;
		case 2:
			PrintList();
			break;
		case 3:
			//완료 표시 프로그램
			break;
		case 4:
			//삭제 프로그램
			break;
		case 5:
			puts("프로그램을 종료합니다..."); 
			return;
		default:
			puts("1 ~ 6 사이의 번호를 입력해주세요");
			break;
		}
		puts("------------------------------\n");
	}
}

void Add(void) 
{
	printf("할 일 입력: ");
	scanf_s("%[^\n]s", l.array[l.size], 61);
	if (strcmp(l.array[l.size], "") != 0) {
		printf("[%s] added!\n", l.array[l.size]);
		l.size++;
	}
	else puts("빈 텍스트를 입력하셨습니다!");
}

void ReadFile(void) { // 파일 읽기
	FILE* inFile;
	inFile = fopen("ToDoList.txt", "r");
	if (inFile == NULL) {
		printf("Cannot open \"ToDoList.txt\"");
		return;
	}
	while (fscanf_s(inFile, "%[^,], %d\n", l.array[l.size], 61, &l.finished[l.size]) == 2) {
		l.size++;
	}
	fclose(inFile);
}

void OutFile(void) { // 파일 출력
	int i = 0;
	FILE* outFile = fopen("ToDoList.txt", "w");
	if (outFile == NULL) {
		printf("Cannot open \"ToDoList.txt\"\n");
		return;
	}
	for (i = 0; i < l.size; i++) {
		fprintf(outFile, "%s, %d\n",l.array[i], l.finished[i]);
	}
	fclose(outFile);
}

int get_display_width(const char* str) // 입력받은 문자열이 차지하는 공간 계산: 한글 등 비아스키 글자는 2칸 차지, 아스키 글자는 1칸 차지
{
	int width = 0;
	while (*str) {
		// UTF-8에서 첫 바이트가 0x80 이상인 경우 한글/비ASCII 문자
		if ((unsigned char)*str >= 0x80) {
			width += 2; // 한글은 두 칸 차지
			str += 3;   // UTF-8에서 한글은 3바이트
		}
		else {
			width += 1; // ASCII 문자는 한 칸 차지
			str++;
		}
	}
	return width;
}

void print_aligned(const char* str, int total_width) 
{
	int display_width = get_display_width(str);
	printf("%s", str); // 문자열 출력
	for (int i = 0; i < total_width - display_width; i++) {
		putchar(' '); // 부족한 폭만큼 공백 추가
	}
}

void PrintList(void) // 목록 출력
{
	printf("%3s %-40s %s\n", "번호", "할 일", "완료 여부");
	for (int i = 0; i < l.size; i++) {
		printf("%3d. ", i + 1);
		print_aligned(l.array[i], 40); // 할 일 출력 (40 칸 맞춤)
		printf("%d\n", l.finished[i]); // 완료 여부 출력
	}
}