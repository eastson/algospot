#include <stdio.h>
#define MAX_TYPE 6
#define MAX_W	1000

int DP[MAX_TYPE][MAX_W];
int W;

/*
TYPE is state of column 
	(0 : empty, 1 : filled)
TYPE0 : 0000 => NEXT Column can be TYPE (0,1,2,3,5)
TYPE1 : 1100 => NEXT Column can be TYPE (0,2)
TYPE2 : 0011 => NEXT Column can be TYPE (0,1)
TYPE3 : 1001 => NEXT Column can be TYPE (0,4)
TYPE4 : 0110 => NEXT Column can be TYPE (3)
TYPE5 : 1111 => NEXT Column can be TYPE (0)
*/
int getWayToFill(int currCol, const int type){
	int tmp_way, nextCol;
	if (W == currCol) //finish
		return 1;
	else if (W == currCol + 1){ // last column
		if (type == 4)
			return 0;
		else
			return 1;
	}

	if (DP[type][(W - 1) - currCol] != -1)
		return DP[type][(W - 1) - currCol];

	nextCol = currCol + 1;
	tmp_way = 0;
	switch (type){
	case 0:
		tmp_way += getWayToFill(nextCol, 0);
		tmp_way += getWayToFill(nextCol, 1);
		tmp_way += getWayToFill(nextCol, 2);
		tmp_way += getWayToFill(nextCol, 3);
		tmp_way += getWayToFill(nextCol, 5);
		break;
	case 1:
		tmp_way += getWayToFill(nextCol, 0);
		tmp_way += getWayToFill(nextCol, 2);
		break;
	case 2:
		tmp_way += getWayToFill(nextCol, 0);
		tmp_way += getWayToFill(nextCol, 1);
		break;
	case 3:
		tmp_way += getWayToFill(nextCol, 0);
		tmp_way += getWayToFill(nextCol, 4);
		break;
	case 4:
		tmp_way += getWayToFill(nextCol, 3);
		break;
	case 5:
		tmp_way += getWayToFill(nextCol, 0);
		break;
	}

	DP[type][(W - 1) - currCol] = tmp_way;
	return tmp_way;
}

int main(void){
	int N;
	int res, cnt;
	int i, j;
	int calced_idx = 0;
	cnt = 0;
	scanf("%d", &N);
	while (N--){
		scanf("%d", &W);

		//init
		if (W > calced_idx){
			for (i = calced_idx; i < W; i++)
			for (j = 0; j < MAX_TYPE; j++)
				DP[j][i] = -1;
		}

		//calc
		res = getWayToFill(0, 0);

		cnt++;
		printf("%d %d\n", cnt, res);
		if (W > calced_idx) calced_idx = W;
	}
	return 0;
}
