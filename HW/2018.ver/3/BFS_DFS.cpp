/* BST, DST Algorithm
12141749 ��ä��
*/

#include <iostream>
#include <queue>
#include <stack>
using namespace std;


int n; // �Էµ� ������ ����
int graph[100][100]; // ���� ��İ� ť
bool visit[100]; // �湮 �迭

struct node {
	int f, b;
};

void BFS(int s) { // s: ���� ����
	int i, j, k;
	int num = 0;
	node nd;
	queue<node> Q; // queue ����

				  // visit ��� �ʱ�ȭ(��� ������ �湮 �ȵȰ�����)
	for (i = 0; i < n; i++) {
		visit[i] = false;
	}

	// ���� ���� s�� �湮�ߴٰ� ǥ��
	visit[s] = true;

	nd.f = s;
	nd.b = s;
	Q.push(nd); // ť�� s enqueue

	node save; // �����
	while (!Q.empty()) {
		save = Q.front(); // ť���� s dequeue
		Q.pop();
		j = save.f;
		k = save.b;
		num++;
		cout << num << ". ����: " << j << endl;
		cout << "  ����: (" << k << ") - (" << j << ")" << endl;
		for (i = 0; i < n; i++) { // ���� ���� s�� �ٸ� ���� i�� ��(i�� 1�� �������Ѱ���)
								  // ���� s�� i�� ������, ���� i�� �湮���� ���� ������ ��
			if (graph[j][i] == 1 && !visit[i]) {
				visit[i] = true; // ���� i�� �湮�ߴٰ� ǥ���ϰ� 
				save.f = i;
				save.b = j;
				Q.push(save); // ť�� i�� ���� 
			}
		}
	}
}

void DFS(int v) {
	int i, j, k;
	int num = 0;
	node nd;
	stack<node> S;// ���� ����� stack

	 // visit ��� �ʱ�ȭ(��� ������ �湮 �ȵȰ�����)
	for (int i = 0; i < n; i++) {
		visit[i] = false;
	}
	
	nd.b = v;
	nd.f = v;
	S.push(nd);

	node save; // �����
	while (!S.empty()) {
		save = S.top();
		S.pop();
		j = save.f;
		k = save.b;
		if (visit[j] == false) {
			visit[j] = true;
			num++;
			cout << num << ". ����: " << j << endl;
			cout << "  ����: (" << k << ") - (" << j << ")" << endl;
			for (i = 0; i < n; i++) {
				// ���� v�� ���� i�� ����Ǿ���, ���� i�� �湮���� �ʾҴٸ�
				if (graph[j][i] == 1 && !visit[i]) {
					save.f = i;
					save.b = j;
					S.push(save);
				}
			}
		}
	}
}

int main() {
	int start; // ���� ����
	int v1, v2; // �׷��� ���� ���� ���� ����

	cout << "12141749 ��ä��" << endl << "�˰��� ���� HW#3 " << endl << "BFS & DFS" << endl << endl;


	cout << "������ ���� �Է�: " << endl;
	cin >> n;

	cout << "�׷����� ���� ���� �Է�(-1 �Է��ϸ� ����): " << endl;
	while (1) {
		cin >> v1;
		if (v1 == -1) break;
		cin >> v2;
		graph[v1][v2] = graph[v2][v1] = 1; // �Է��� ������ graph �迭�� ����
	}

	cout << "���� ���� �Է�:" << endl;
	cin >> start;


	cout << endl << endl << "=============BFS=============" << endl;
	BFS(start); // BFS ����
	cout << "=============================" << endl << endl;


	cout << endl << endl << "=============DFS=============" << endl;
	DFS(start); // BFS ����
	cout << "=============================" << endl;

	system("pause");
	return 0;
}