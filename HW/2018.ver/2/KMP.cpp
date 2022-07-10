#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>   // �����б�
#include <ctime>
using namespace std;

int n[50]; // ����� ��ġ ��Ÿ���� �迭

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
	double start_time; // �ð� ������ ���� ����

	printf("�˰��� ���� HW#2 KMP �˰���\n12141749 ��ä��\n\n");


	ifstream file("RFC2616.txt");   // �ؽ�Ʈ ���Ͽ���

	if (file.is_open()) {   // ���� ������ ��
		cout << "�ؽ�Ʈ ������ ���Ƚ��ϴ�." << endl;
		while (!file.eof() && position < text_size) {   // text �迭�� �ؽ�Ʈ ������ ���� �ֱ�
			file.get(text[position]);
			position++;
		}
		text[position - 1] = '\0';
	}



	// pattern �Է�
	cout << "ã�� �ܾ��? : " << endl;
	cin.getline(pattern, 100); // ���� �Է��� �� ���� ���ڿ� �Է� (���� 100�� ����)


	M = strlen(pattern);
	N = strlen(text);

	start_time = clock(); // ���� ���� �ð�
	while (1) {
		pos = KMP(pattern, text + i);
		pos += previous;
		i = pos + M;
		if (i <= N) {
			printf("������ �߻��� ��ġ : %d\n", pos);
			num++;
		}
		else break;
		previous = i;
	}
	printf("������ �߻��� �� ���� : %d\n", num);
	printf("���� Ž���� �ɸ� �ð�: %1.3f\n", (clock() - start_time) / CLOCKS_PER_SEC);
	printf("��Ʈ�� Ž�� ����.\n");

	return 0;
}

void InitNext(char *p) { // ����� ��ġ �˷���
	int i, j;
	int M = strlen(p); // Ž���� string�� ����
	n[0] = -1; // ù��° �ڸ��� ������ -1��
	for (i = 0, j = -1; i < M; i++, j++) { // i �ε��� j ����� ��ġ, 1�� �������� ���� ��. 0 vs 1, 1 vs 2
										   // ����ġ ������ �� j�϶��� ����� ��ġ�� �� �� 
		n[i] = (p[i] == p[j]) ? n[j] : j; // ��ġ�ϸ� �׳� ��ġ ���� ���� ��; ��ġ ���ϸ� n�� ����� ��ġ �ֱ�
		while ((j >= 0) && (p[i] != p[j])) j = n[j]; // ��ġ���� ���� �� j�� j��°�� ����� ��ġ
	}
}

int KMP(char *p, char *t) {
	int i, j;
	int M = strlen(p);
	int N = strlen(t);
	InitNext(p); // ��ó��
	for (i = 0, j = 0; j < M&&i < N; i++, j++) {
		while ((j >= 0) && (t[i] != p[j]))j = n[j];
	}
	if (j == M)return i - M;
	else return i;
}