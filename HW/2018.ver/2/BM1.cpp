#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>   // �����б�
#include <ctime>
using namespace std;

#define num 127
int skip[num];
int index(char);
void InitSkip(char *);
int MisChar(char *, char *);

int main() {
	// ������ ����
	int M, N, pos;
	int previous = 0, i = 0, position = 0, number = 0;
	int text_size = 100000;
	int pattern_size = 100;
	char *text = new char[text_size];
	char *pattern = new char[pattern_size];
	double start_time; // �ð� ������ ���� ����


	printf("�˰��� ���� HW#2 BM �˰���\n12141749 ��ä��\n\n");


	ifstream file("RFC2616.txt");   // �ؽ�Ʈ ���Ͽ���

	if (file.is_open()) {   // ������ ������ ��
		cout << "�ؽ�Ʈ ������ ���Ƚ��ϴ�." << endl;
		while (!file.eof() && position < text_size) {    // text �迭�� �ؽ�Ʈ ������ ���� �ֱ�
			file.get(text[position]);
			position++;
		}
		text[position - 1] = '\0';
	}

	// pattern ã��
	cout << "ã�� �ܾ��? : " << endl;
	cin.getline(pattern, 100); // ���� �Է��� �� ���� ���ڿ� �Է� (���� 100�� ����)
		
	M = strlen(pattern);
	N = strlen(text);
	
	start_time = clock(); // ���� ���� �ð�
	while (1) {
		pos = MisChar(pattern, text + i);
		pos += previous;
		i = pos + M;
		if (i <= N) {
			cout << "������ �߻��� ��ġ : " << pos << endl;
			number++;
		}
		else
			break;
		previous = i;
	}

	cout << endl;
	printf("������ �߻��� �� ���� : %d\n", number);
	printf("���� Ž���� �ɸ� �ð�: %1.3f\n", (clock() - start_time) / CLOCKS_PER_SEC);
	printf("��Ʈ�� Ž�� ����.\n");

	return 0;

}

int index(char c) { // index ��ȯ
	return c;
}

void InitSkip(char *p) { // skip �迭 �ʱ�ȭ
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
		while (t[i] != p[j]) { // ��ġ���� ������
			k = skip[index(t[i])]; // skip�ϰ� �� ������
			i += (M - j > k) ? M - j : k;
			if (i >= N)
				return N;
			j = M - 1;
		}
	return i + 1;
}