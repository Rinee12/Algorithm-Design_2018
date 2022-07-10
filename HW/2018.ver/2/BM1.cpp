#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>   // 파일읽기
#include <ctime>
using namespace std;

#define num 127
int skip[num];
int index(char);
void InitSkip(char *);
int MisChar(char *, char *);

int main() {
	// 변수들 선언
	int M, N, pos;
	int previous = 0, i = 0, position = 0, number = 0;
	int text_size = 100000;
	int pattern_size = 100;
	char *text = new char[text_size];
	char *pattern = new char[pattern_size];
	double start_time; // 시간 측정을 위한 변수


	printf("알고리즘 설계 HW#2 BM 알고리즘\n12141749 이채원\n\n");


	ifstream file("RFC2616.txt");   // 텍스트 파일열기

	if (file.is_open()) {   // 파일이 열렸을 때
		cout << "텍스트 파일이 열렸습니다." << endl;
		while (!file.eof() && position < text_size) {    // text 배열에 텍스트 파일의 내용 넣기
			file.get(text[position]);
			position++;
		}
		text[position - 1] = '\0';
	}

	// pattern 찾기
	cout << "찾을 단어는? : " << endl;
	cin.getline(pattern, 100); // 엔터 입력할 때 까지 문자열 입력 (현재 100자 제한)
		
	M = strlen(pattern);
	N = strlen(text);
	
	start_time = clock(); // 측정 시작 시간
	while (1) {
		pos = MisChar(pattern, text + i);
		pos += previous;
		i = pos + M;
		if (i <= N) {
			cout << "패턴이 발생한 위치 : " << pos << endl;
			number++;
		}
		else
			break;
		previous = i;
	}

	cout << endl;
	printf("패턴이 발생한 총 개수 : %d\n", number);
	printf("패턴 탐색에 걸린 시간: %1.3f\n", (clock() - start_time) / CLOCKS_PER_SEC);
	printf("스트링 탐색 종료.\n");

	return 0;

}

int index(char c) { // index 반환
	return c;
}

void InitSkip(char *p) { // skip 배열 초기화
	int i, j;
	int M = strlen(p);
	for (i = 0; i < num; i++)  
		skip[i] = M;
	for (i = 0; i < M; i++)  
		skip[index(p[i])] = M - i - 1;
}

int MisChar(char *p, char *t) { 
	int i, j, k;
	int M = strlen(p);
	int N = strlen(t);
	InitSkip(p);
	for (i = M - 1, j = M - 1; j >= 0; i--, j--)
		while (t[i] != p[j]) { // 일치하지 않으면
			k = skip[index(t[i])]; // skip하고 그 다음비교
			i += (M - j > k) ? M - j : k;
			if (i >= N)
				return N;
			j = M - 1;
		}
	return i + 1;
}