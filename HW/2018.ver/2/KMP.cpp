#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>   // 파일읽기
#include <ctime>
using namespace std;

int n[50]; // 재시작 위치 나타내는 배열

void InitNext(char *p);
int KMP(char *p, char *t);

int main() {
	int position = 0;
	int num = 0;
	int text_size = 100000;
	int pattern_size = 100;
	int M, N, pos;
	int previous = 0;
	int i = 0;
	char *text = new char[text_size];
	char *pattern = new char[pattern_size];
	double start_time; // 시간 측정을 위한 변수

	printf("알고리즘 설계 HW#2 KMP 알고리즘\n12141749 이채원\n\n");


	ifstream file("RFC2616.txt");   // 텍스트 파일열기

	if (file.is_open()) {   // 파일 열렸을 때
		cout << "텍스트 파일이 열렸습니다." << endl;
		while (!file.eof() && position < text_size) {   // text 배열에 텍스트 파일의 내용 넣기
			file.get(text[position]);
			position++;
		}
		text[position - 1] = '\0';
	}



	// pattern 입력
	cout << "찾을 단어는? : " << endl;
	cin.getline(pattern, 100); // 엔터 입력할 때 까지 문자열 입력 (현재 100자 제한)


	M = strlen(pattern);
	N = strlen(text);

	start_time = clock(); // 측정 시작 시간
	while (1) {
		pos = KMP(pattern, text + i);
		pos += previous;
		i = pos + M;
		if (i <= N) {
			printf("패턴이 발생한 위치 : %d\n", pos);
			num++;
		}
		else break;
		previous = i;
	}
	printf("패턴이 발생한 총 개수 : %d\n", num);
	printf("패턴 탐색에 걸린 시간: %1.3f\n", (clock() - start_time) / CLOCKS_PER_SEC);
	printf("스트링 탐색 종료.\n");

	return 0;
}

void InitNext(char *p) { // 재시작 위치 알려줌
	int i, j;
	int M = strlen(p); // 탐색할 string의 길이
	n[0] = -1; // 첫번째 자리는 언제나 -1로
	for (i = 0, j = -1; i < M; i++, j++) { // i 인덱스 j 재시작 위치, 1씩 증가시켜 가며 비교. 0 vs 1, 1 vs 2
										   // 불일치 나오면 그 j일때의 재시작 위치로 가 비교 
		n[i] = (p[i] == p[j]) ? n[j] : j; // 일치하면 그냥 일치 다음 문자 비교; 일치 안하면 n에 재시작 위치 넣기
		while ((j >= 0) && (p[i] != p[j])) j = n[j]; // 일치하지 않을 때 j는 j번째의 재시작 위치
	}
}

int KMP(char *p, char *t) {
	int i, j;
	int M = strlen(p);
	int N = strlen(t);
	InitNext(p); // 전처리
	for (i = 0, j = 0; j < M&&i < N; i++, j++) {
		while ((j >= 0) && (t[i] != p[j]))j = n[j];
	}
	if (j == M)return i - M;
	else return i;
}