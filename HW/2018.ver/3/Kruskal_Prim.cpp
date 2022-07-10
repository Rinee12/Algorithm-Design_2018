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

struct set{ // 집합
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
	for (i = 0; i < n; i++)								//	모든 정점을 방문하지 않음으로 표시
		visit[i] = 0;
}

// kruskal을 위한 sort 함수 
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

// 해당 정점이 포함된 집합 찾는 함수 (v: 확인할 정점, N: 정점그룹)
int find(int v, set N[]){
	int i, j;
	for (i = 0; i < n; i++)						//	모든 정점 집합들을 비교	
	{
		for (j = 0; j < N[i].num; j++)			//	집합 안의 정점 수만큼 비교해 정정 v 찾음
		{
			if (v == N[i].vertices[j])
				return i;						//	v가 속한 집합의 번호를 리턴
		}
	}
	return -1;									// 속한 집합이 없으면 -1을 리턴
}

// 합집합, v1, v2 정점이 속한 정접 집합의 번호,  N : 정접 집합
void merge(int v1, int v2, set N[]){	
	int minv, maxv;
	if (v1 < v2){		// 낮은 쪽 합치기 위해 비교
		minv = v1;
		maxv = v2;
	}
	else{
		minv = v2;
		maxv = v1;
	}
	int i = N[minv].num; //	번호가 낮은 집합이 가진 정점의 수
	int j = 0;
	int num = N[v1].num + N[v2].num; //	정점의 수의 합 
	N[minv].num = num; 	//	합쳐진 정점 집합의 정점의 수
	for (i; i < num; i++) { //	이어 붙임
		N[minv].vertices[i] = N[maxv].vertices[j];
		j++;
	}
}

void Kruskal() {	
	int i, j, k = 0, h;
	int v1, v2, p, q;
	set N[20];		//	정점 집합
	queue<struct edge> F;	//	간선들을 저장하기위한 큐
	for (i = 0; i < n; i++)	{
		N[i].vertices[0] = i;	//	정접 집합을 각각 하나의 정점만 가진 집합으로 선언
		for (j = i; j < n; j++)	{
			if (graph[i][j] != 99)	//	연결된 간선인 경우 
			{
				Distance[k].v1 = i;	 //	시작점
				Distance[k].v2 = j;	//	도작점
				Distance[k].weight = graph[i][j]; // 가중치
				k++; //	중복되는 간선을 제외한 간선의 갯수 예를 들어 {2,3}과 {3,2}라면 {2,3}만 생각
			}
		}
	}
	quicksort(Distance, 0, k - 1);	//	간선의 가중치를 정렬

	j = 1;	//	간선의 수
	h = 0;
	while (j<n && h<k-1){	//	간선의 수가 정점보다 하나 작을 때까지
		v1 = Distance[h].v1; //	시작점
		v2 = Distance[h].v2; //	도착점
		p = find(v1, N); // v1 정점이 속한 정접 집합
		q = find(v2, N); //	v2 정점이 속한 정접 집합
		if (p != q) {	// 두 정접이 속한 정점 집합이 다를 경우 집합에 간선 추가, 및 집합 합침
			edge E;
			E = Distance[h];
			F.push(E);	
			merge(p, q, N); 
			j++; 
		}
		h++;
	}
	cout << "=============Kruskal=============" << endl;
	cout << " 시작점  도착점  가중치" << endl;
	while (!F.empty()){
		cout << setw(4) << F.front().v1 << setw(8) << F.front().v2 << setw(8) << F.front().weight << endl;
		F.pop();
	}
}

void Prim(int start) {	
	int i, j, k, min, st;
	queue<edge> F;	//	신장트리의 간선들을 저장하기 위한 
	st = start;	//	시작점

	for (i = 0; i < n; i++){
		visit[i] = 0; // 초기화
		Distance[i].v1 = st; // 간선의 시작점
		Distance[i].v2 = i;	// 간선의 도착점
		Distance[i].weight = graph[st][i]; // 간선의 가중치
	}

	visit[st] = 1; // 첫 시작점을 방문함

	j = 1; // 간선의 수
	while (j < n){	// 간선의 수가 정점보다 하나 작을 때까지
		min = 999;
		for (i = 0; i < n; i++) { // 연결된 간선들 중 가중치가 가장 작은 간선을 찾음
			if (Distance[i].weight <= min){
				min = Distance[i].weight;
				k = i;
			}
		}
		edge E;	// 가중치가 가장 작은 간선을 큐에 저장
		E = Distance[k];
		F.push(E);
		Distance[k].weight = 999; // 큐에 저장한 간선의 가중치를 무한대로 변경

		if (visit[k] == 0)	// 가중치가 적은 간선의 정점을 방문함 설정
			visit[k] = 1;

		for (i = 0; i < n; i++) {	// 새로운 간선들과 이전의 간선들을 비교. 더 작은 값을 Distance 배열에 저장
			if (graph[k][i] < Distance[i].weight && visit[i] == 0){
				Distance[i].v1 = k; // 간선의 정보를 저장
				Distance[i].v2 = i;
				Distance[i].weight = graph[k][i];
			}
		}
		j++; // 간선의 수 추가
	}

	cout << "=============Prim=============" << endl;
	cout << " 시작점  도착점  가중치" << endl;
	while (!F.empty()){
		cout << setw(4) << F.front().v1 << setw(8) << F.front().v2 << setw(8) << F.front().weight << endl;
		F.pop();
	}
}

int main(){
	int start, v1, v2, weight;
	cout << "12141749 이채원" << endl << "알고리즘 설계 HW#3 " << endl << "kruskal & prim" << endl << endl;
	cout << "정점의 개수 입력: " << endl;
	cin >> n;

	// graph 행렬 초기화 ( 가중치 있으므로 99로 )
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			graph[i][j] = 99;
		}
	}
	cout << "그래프의 간선 정보 및 가중치 입력(-1 입력하면 종료): " << endl;
	
	while (1) {
		cin >> v1;
		if (v1 == -1) break;
		cin >> v2;
		cin >> weight;
		graph[v1][v2] = graph[v2][v1] = weight; // 입력한 간선을 map 배열에 저장

	}

	cout << "시작 정점 입력:" << endl;
	cin >> start;

	Kruskal();
	cout << endl;
	
	Prim(start);
	cout << endl;


	system("pause");
	return 0;
}