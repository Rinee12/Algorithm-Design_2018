#include<iostream>
#include<queue>
#include<iomanip>
using namespace std;

struct edge{
	int v1;
	int v2;
	int weight;
};

struct vertice{
	int V;
};

struct set{ // ����
	int vertices[20];
	int num = 1;
};

int visit[20];
int n;
int graph[100][100];
edge Distance[100];
vertice V[100];

void initialize(int n){
	int i;
	for (i = 0; i < n; i++)								//	��� ������ �湮���� �������� ǥ��
		visit[i] = 0;
}

// kruskal�� ���� sort �Լ� 
void quicksort(edge *S, int a, int b){
	if (a < b){
		int p = S[b].weight;					
		int l = a;
		int r = b - 1;
		while (l <= r){
			while (l <= r&&S[l].weight <= p)l++;
			while (l <= r && S[r].weight >= p)	r--;
			if (l < r) swap(S[l], S[r]);
		}
		swap(S[l], S[b]);
		quicksort(S, a, (l - 1));
		quicksort(S, (l + 1), b);
	}
}

// �ش� ������ ���Ե� ���� ã�� �Լ� (v: Ȯ���� ����, N: �����׷�)
int find(int v, set N[]){
	int i, j;
	for (i = 0; i < n; i++)						//	��� ���� ���յ��� ��	
	{
		for (j = 0; j < N[i].num; j++)			//	���� ���� ���� ����ŭ ���� ���� v ã��
		{
			if (v == N[i].vertices[j])
				return i;						//	v�� ���� ������ ��ȣ�� ����
		}
	}
	return -1;									// ���� ������ ������ -1�� ����
}

// ������, v1, v2 ������ ���� ���� ������ ��ȣ,  N : ���� ����
void merge(int v1, int v2, set N[]){	
	int minv, maxv;
	if (v1 < v2){		// ���� �� ��ġ�� ���� ��
		minv = v1;
		maxv = v2;
	}
	else{
		minv = v2;
		maxv = v1;
	}
	int i = N[minv].num; //	��ȣ�� ���� ������ ���� ������ ��
	int j = 0;
	int num = N[v1].num + N[v2].num; //	������ ���� �� 
	N[minv].num = num; 	//	������ ���� ������ ������ ��
	for (i; i < num; i++) { //	�̾� ����
		N[minv].vertices[i] = N[maxv].vertices[j];
		j++;
	}
}

void Kruskal() {	
	int i, j, k = 0, h;
	int v1, v2, p, q;
	set N[20];		//	���� ����
	queue<struct edge> F;	//	�������� �����ϱ����� ť
	for (i = 0; i < n; i++)	{
		N[i].vertices[0] = i;	//	���� ������ ���� �ϳ��� ������ ���� �������� ����
		for (j = i; j < n; j++)	{
			if (graph[i][j] != 99)	//	����� ������ ��� 
			{
				Distance[k].v1 = i;	 //	������
				Distance[k].v2 = j;	//	������
				Distance[k].weight = graph[i][j]; // ����ġ
				k++; //	�ߺ��Ǵ� ������ ������ ������ ���� ���� ��� {2,3}�� {3,2}��� {2,3}�� ����
			}
		}
	}
	quicksort(Distance, 0, k - 1);	//	������ ����ġ�� ����

	j = 1;	//	������ ��
	h = 0;
	while (j<n && h<k-1){	//	������ ���� �������� �ϳ� ���� ������
		v1 = Distance[h].v1; //	������
		v2 = Distance[h].v2; //	������
		p = find(v1, N); // v1 ������ ���� ���� ����
		q = find(v2, N); //	v2 ������ ���� ���� ����
		if (p != q) {	// �� ������ ���� ���� ������ �ٸ� ��� ���տ� ���� �߰�, �� ���� ��ħ
			edge E;
			E = Distance[h];
			F.push(E);	
			merge(p, q, N); 
			j++; 
		}
		h++;
	}
	cout << "=============Kruskal=============" << endl;
	cout << " ������  ������  ����ġ" << endl;
	while (!F.empty()){
		cout << setw(4) << F.front().v1 << setw(8) << F.front().v2 << setw(8) << F.front().weight << endl;
		F.pop();
	}
}

void Prim(int start) {	
	int i, j, k, min, st;
	queue<edge> F;	//	����Ʈ���� �������� �����ϱ� ���� 
	st = start;	//	������

	for (i = 0; i < n; i++){
		visit[i] = 0; // �ʱ�ȭ
		Distance[i].v1 = st; // ������ ������
		Distance[i].v2 = i;	// ������ ������
		Distance[i].weight = graph[st][i]; // ������ ����ġ
	}

	visit[st] = 1; // ù �������� �湮��

	j = 1; // ������ ��
	while (j < n){	// ������ ���� �������� �ϳ� ���� ������
		min = 999;
		for (i = 0; i < n; i++) { // ����� ������ �� ����ġ�� ���� ���� ������ ã��
			if (Distance[i].weight <= min){
				min = Distance[i].weight;
				k = i;
			}
		}
		edge E;	// ����ġ�� ���� ���� ������ ť�� ����
		E = Distance[k];
		F.push(E);
		Distance[k].weight = 999; // ť�� ������ ������ ����ġ�� ���Ѵ�� ����

		if (visit[k] == 0)	// ����ġ�� ���� ������ ������ �湮�� ����
			visit[k] = 1;

		for (i = 0; i < n; i++) {	// ���ο� ������� ������ �������� ��. �� ���� ���� Distance �迭�� ����
			if (graph[k][i] < Distance[i].weight && visit[i] == 0){
				Distance[i].v1 = k; // ������ ������ ����
				Distance[i].v2 = i;
				Distance[i].weight = graph[k][i];
			}
		}
		j++; // ������ �� �߰�
	}

	cout << "=============Prim=============" << endl;
	cout << " ������  ������  ����ġ" << endl;
	while (!F.empty()){
		cout << setw(4) << F.front().v1 << setw(8) << F.front().v2 << setw(8) << F.front().weight << endl;
		F.pop();
	}
}

int main(){
	int start, v1, v2, weight;
	cout << "12141749 ��ä��" << endl << "�˰��� ���� HW#3 " << endl << "kruskal & prim" << endl << endl;
	cout << "������ ���� �Է�: " << endl;
	cin >> n;

	// graph ��� �ʱ�ȭ ( ����ġ �����Ƿ� 99�� )
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			graph[i][j] = 99;
		}
	}
	cout << "�׷����� ���� ���� �� ����ġ �Է�(-1 �Է��ϸ� ����): " << endl;
	
	while (1) {
		cin >> v1;
		if (v1 == -1) break;
		cin >> v2;
		cin >> weight;
		graph[v1][v2] = graph[v2][v1] = weight; // �Է��� ������ map �迭�� ����

	}

	cout << "���� ���� �Է�:" << endl;
	cin >> start;

	Kruskal();
	cout << endl;
	
	Prim(start);
	cout << endl;


	system("pause");
	return 0;
}