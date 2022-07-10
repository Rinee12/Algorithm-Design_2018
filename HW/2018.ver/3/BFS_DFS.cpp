/* BST, DST Algorithm
12141749 이채원
*/

#include <iostream>
#include <queue>
#include <stack>
using namespace std;


int n; // 입력될 정수의 갯수
int graph[100][100]; // 인접 행렬과 큐
bool visit[100]; // 방문 배열

struct node {
	int f, b;
};

void BFS(int s) { // s: 시작 정점
	int i, j, k;
	int num = 0;
	node nd;
	queue<node> Q; // queue 선언

				  // visit 행렬 초기화(모든 정점이 방문 안된것으로)
	for (i = 0; i < n; i++) {
		visit[i] = false;
	}

	// 시작 정점 s를 방문했다고 표시
	visit[s] = true;

	nd.f = s;
	nd.b = s;
	Q.push(nd); // 큐에 s enqueue

	node save; // 저장용
	while (!Q.empty()) {
		save = Q.front(); // 큐에서 s dequeue
		Q.pop();
		j = save.f;
		k = save.b;
		num++;
		cout << num << ". 정점: " << j << endl;
		cout << "  간선: (" << k << ") - (" << j << ")" << endl;
		for (i = 0; i < n; i++) { // 시작 정점 s를 다른 정점 i와 비교(i를 1씩 증가시켜가며)
								  // 정점 s와 i가 만나고, 정점 i를 방문하지 않은 상태일 때
			if (graph[j][i] == 1 && !visit[i]) {
				visit[i] = true; // 정점 i를 방문했다고 표시하고 
				save.f = i;
				save.b = j;
				Q.push(save); // 큐에 i를 삽입 
			}
		}
	}
}

void DFS(int v) {
	int i, j, k;
	int num = 0;
	node nd;
	stack<node> S;// 간선 저장용 stack

	 // visit 행렬 초기화(모든 정점이 방문 안된것으로)
	for (int i = 0; i < n; i++) {
		visit[i] = false;
	}
	
	nd.b = v;
	nd.f = v;
	S.push(nd);

	node save; // 저장용
	while (!S.empty()) {
		save = S.top();
		S.pop();
		j = save.f;
		k = save.b;
		if (visit[j] == false) {
			visit[j] = true;
			num++;
			cout << num << ". 정점: " << j << endl;
			cout << "  간선: (" << k << ") - (" << j << ")" << endl;
			for (i = 0; i < n; i++) {
				// 정점 v와 정점 i가 연결되었고, 정점 i를 방문하지 않았다면
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
	int start; // 시작 정점
	int v1, v2; // 그래프 간선 저장 위한 변수

	cout << "12141749 이채원" << endl << "알고리즘 설계 HW#3 " << endl << "BFS & DFS" << endl << endl;


	cout << "정점의 개수 입력: " << endl;
	cin >> n;

	cout << "그래프의 간선 정보 입력(-1 입력하면 종료): " << endl;
	while (1) {
		cin >> v1;
		if (v1 == -1) break;
		cin >> v2;
		graph[v1][v2] = graph[v2][v1] = 1; // 입력한 간선을 graph 배열에 저장
	}

	cout << "시작 정점 입력:" << endl;
	cin >> start;


	cout << endl << endl << "=============BFS=============" << endl;
	BFS(start); // BFS 시작
	cout << "=============================" << endl << endl;


	cout << endl << endl << "=============DFS=============" << endl;
	DFS(start); // BFS 시작
	cout << "=============================" << endl;

	system("pause");
	return 0;
}