/*
  Prob: antbuster
  Author: K.F.Cat
  Date: 03-11-07 18:05
  Description: д���¿�... 
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>

struct node {
	int age, energy, lv, x, y, LastX, LastY, Full;
	bool GotCake;
};

const int Val_Target = 5;
const int Val_Original = 2;
const int Tot_Ants = 6;
const int Step = 5;

int n, m;
int TimeLimit;

int ant_s;//�������� 
node ant[Tot_Ants];//6ֻ���ϵ���Ϣ

int nest_lv, nest_s;//�ж���һֻ���������ϵ�״̬ 
double nest_energy;//��һֻ�������ϵ����� 

int tower_s, tower_d, tower_r, tower[20][2];//������Ϣ 
int Target;//����������� 

int map[21][21];

//ȫ�ֳ�ʼ�� 
void Setup() {
	memset(map, 0, sizeof map);
	for (int i = 0; i < tower_s; i ++)
		map[tower[i][0]][tower[i][1]] = -1;
	Target = -1;
	
	memset(ant, 0, sizeof ant);
	for (int i = 0; i < Tot_Ants; i ++) {
		ant[i].age = -1;
		ant[i].GotCake = false;
	}
	ant_s = 0;
	nest_lv = nest_s = 1;
	nest_energy = 4.4;
}

//���ϳ��� 
void Birth() { 
	int pos = 0;
	for (int i = 0; i < Tot_Ants; i ++) {
		if (ant[i].x == 0 && ant[i].y == 0 && ant[i].age != -1) return;
		if (ant[i].age == -1) pos = i;
	}
	ant[pos].age = 0;
	ant[pos].lv = nest_lv;
	ant[pos].energy = ant[pos].Full = int(nest_energy);
	ant[pos].x = ant[pos].y = 0;
	ant[pos].LastX = ant[pos].LastY = -1;
	ant[pos].GotCake = false;
	ant_s ++;
	
	nest_s ++;
	if (nest_s > Tot_Ants) {
		nest_s = 1;
		nest_lv ++;
		nest_energy *= 1.1;
	}
}

//ˢ��Ϣ�� 
void SetMark() {
	for (int i = 0; i < Tot_Ants; i ++)
		if (ant[i].age >= 0) {
			if (ant[i].GotCake)	map[ant[i].x][ant[i].y] += Val_Target;
			else map[ant[i].x][ant[i].y] += Val_Original;
		}
}

//�ж�ĳ����������û������ 
bool AntPresent(int x, int y) {
	for (int i = 0; i < Tot_Ants; i ++)
		if (ant[i].age >= 0 && ant[i].x == x && ant[i].y == y) return true;
	return false;
}

//�����ƶ�
const int go[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int bignum = 10000;
void Move() {
	for (int i = 0; i < Tot_Ants - 1; i ++)//�Ȱ����ϰ���·�Ĵ������� 
		for (int j = i + 1; j < Tot_Ants; j ++)
			if (ant[i].age < ant[j].age) {
				node tmp = ant[i];
				ant[i] = ant[j];
				ant[j] = tmp;
				if (Target == i || Target == j) Target = i + j - Target;
			}
	
	for (int i = 0; i < Tot_Ants; i ++) {
		if (ant[i].age < 0) continue;

		int dir = -1, MaxVal = -bignum;
		for (int j = 0; j < 4; j ++) {//����2��3��ʵ���Բ����� 
			int x = ant[i].x + go[j][0];
			int y = ant[i].y + go[j][1];
			if (x < 0 || x > n || y < 0 || y > m || map[x][y] == -1 || (x == ant[i].LastX && y == ant[i].LastY) || AntPresent(x, y))
				continue;
			if (map[x][y] > MaxVal) {
				MaxVal = map[x][y];
				dir = j;
			}
		}

		if (dir >= 0 && ant[i].age % Step == Step - 1)//����һ����������ʶ��һ�� 
			for (int j = 0; j < 4; j ++) {
				dir --;
				if (dir < 0) dir = 3;
				int x = ant[i].x + go[dir][0];
				int y = ant[i].y + go[dir][1];
				if (x < 0 || x > n || y < 0 || y > m || map[x][y] == -1 || (x == ant[i].LastX && y == ant[i].LastY) || AntPresent(x, y))
					continue;
				else break;
			}

		ant[i].LastX = ant[i].x;
		ant[i].LastY = ant[i].y;
		if (dir >= 0) {
			ant[i].x += go[dir][0];
			ant[i].y += go[dir][1];
		}
	}
}

//���Ͽ��ϵ��� 
void GetCake() {
	for (int i = 0; i < Tot_Ants; i ++)
		if (ant[i].age >= 0 && ant[i].x == n && ant[i].y == m) {
			Target = i;
			ant[i].GotCake = true;
			ant[i].energy = (ant[i].energy + (ant[i].Full >> 1)) <? ant[i].Full;
			return;
		}
}

//����ĳ������������� 
int Nearest(int x, int y) {
	int ID = -1, distance = bignum;
	for (int i = 0; i < Tot_Ants; i ++)
		if (ant[i].age >= 0 && (distance > (ant[i].x - x) * (ant[i].x - x) + (ant[i].y - y) * (ant[i].y - y) || 
			ant[i].age > ant[ID].age && distance == (ant[i].x - x) * (ant[i].x - x) + (ant[i].y - y) * (ant[i].y - y))) {
			ID = i;
			distance = (ant[i].x - x) * (ant[i].x - x) + (ant[i].y - y) * (ant[i].y - y);
	}
	return ID;
}

//�ж���������Ƿ�����������
bool TargetInRange(int x1, int y1, int x2, int y2) {
	return tower_r * tower_r >= (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

//ɱ��һ�����ϵ�����
void Damage(int x1, int y1, int x2, int y2) {
	for (int i = 0; i < Tot_Ants; i ++) {
		if (ant[i].x < (x1 <? x2) || ant[i].x > (x1 >? x2) || ant[i].y < (y1 <? y2) || ant[i].y > (y1 >? y2))
			continue;
		int tmp = abs(x1 * y2 + x2 * ant[i].y + ant[i].x * y1 - x2 * y1 - ant[i].x * y2 - x1 * ant[i].y);
		tmp *= tmp;
		int len = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
		if ((tmp << 2) <= len) ant[i].energy -= tower_d;
	}
}

//������������ 
void Attack() {
	for (int i = 0; i < tower_s; i ++)
		if (Target >= 0 && TargetInRange(tower[i][0], tower[i][1], ant[Target].x, ant[Target].y))
			Damage(tower[i][0], tower[i][1], ant[Target].x, ant[Target].y);
		else {
			int tmp = Nearest(tower[i][0], tower[i][1]);
			if (TargetInRange(tower[i][0], tower[i][1], ant[tmp].x, ant[tmp].y))
				ant[tmp].energy -= tower_d;
		}
}

//�������������������� 
void RemoveAnts() {
	for (int i = 0; i < Tot_Ants; i ++)
		if (ant[i].energy < 0 && ant[i].age >= 0) {
			ant[i].age = -1;
			ant_s --;
			if (Target == i) Target = -1;
		}
}

//�ж���Ϸ�Ƿ���� 
bool Determine_Gameover() {
	for (int i = 0; i < Tot_Ants; i ++)
		if (ant[i].x == 0 && ant[i].y == 0 && ant[i].age >= 0 && ant[i].GotCake)
			return true;
	return false;
}

//��Ϣ�ض�ʧ 
void LoseMark() {
	for (int i = 0; i <= n; i ++)
		for (int j = 0; j <= m; j ++)
			if (map[i][j] > 0) map[i][j] --;
}

//���ϳ���1�� 
void AddAge() {
	for (int i = 0; i < Tot_Ants; i ++)
		if (ant[i].age >= 0) ant[i].age ++;
}

//��� 
void Output(int Time) {
	if (Time <= TimeLimit) printf("Game over after %d seconds\n", Time);
	else printf("The game is going on\n");
	
	for (int i = 0; i < Tot_Ants - 1; i ++)
		for (int j = i + 1; j < Tot_Ants; j ++)
			if (ant[i].age < ant[j].age) {
				node tmp = ant[i];
				ant[i] = ant[j];
				ant[j] = tmp;
			}
	printf("%d\n", ant_s);
	for (int i = 0; i < Tot_Ants; i ++)
		if (ant[i].age >= 0)
			printf("%d %d %d %d %d\n", ant[i].age, ant[i].lv, ant[i].energy, ant[i].x, ant[i].y);
}

int main() {
	freopen("antbuster.in", "r", stdin);
	freopen("antbuster.out", "w", stdout);

	scanf("%d %d", &n, &m);
	scanf("%d %d %d", &tower_s, &tower_d, &tower_r);
	for (int i = 0; i < tower_s; i ++)
		scanf("%d %d", &tower[i][0], &tower[i][1]);
	scanf("%d", &TimeLimit);

	Setup();

	for (int i = 1; i <= TimeLimit; i ++) {
		if (ant_s < Tot_Ants) Birth();
		SetMark();
		Move();
		if (Target == -1) GetCake();
		Attack();
		RemoveAnts();
		if (Determine_Gameover()) {
			Output(i);
			return 0;
		}
		LoseMark();
		AddAge();
	}
	Output(TimeLimit + 1);

    return 0;
}
