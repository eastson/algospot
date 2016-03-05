#include <stdio.h>
#define MAX_SEQ	100
#define MAX_S 10
#define INF 1000000000
#define MIN(X,Y)	((X)<(Y))?(X):(Y)
int num[MAX_SEQ];
int S;// number of quiatizer
int N;
int dp[MAX_SEQ][MAX_S];

void quicksort(int arr[], int left, int right){
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	/*partition*/
	while (i <= j){
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;

		if (i <= j){
			/*swap*/
			tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
			i++; j--;
		}

		/*recursion*/
		if (left < j)
			quicksort(arr, left, j);
		if (right > i)
			quicksort(arr, i, right);
	}
}

int calc_diff(const int start, const int end){
	int i;
	int avg, ret;

	avg = 0;
	for (i = start; i <= end; i++){
		avg += num[i];
	}
	avg = (int)(((avg * 1.0) / (end - start + 1)) + 0.5);

	ret = 0;
	for (i = start; i <= end; i++){
		ret += (avg - num[i]) * (avg - num[i]);
	}

	return ret;
}

int quant(const int idx, const int S){
	int ret,i;
	if (idx >= N) return 0;
	if (S == 0) return INF;

	if (dp[idx][S] != -1) return dp[idx][S];

	ret = INF;
	for (i = idx; i < N; i++){
		ret = MIN(ret, calc_diff(idx, i) + quant(i+1, S-1));
	}
	dp[idx][S] = ret;
	//printf("idx(%d), S(%d) = min(%d)\n", idx, S, ret);
	return ret;
}


int main(void){
	int C;
	int i, j;
	//printf("int max : %d\n", INF);
	scanf("%d", &C);
	while (C--){
		scanf("%d %d", &N, &S);

		for (i = 0; i < N; i++){
			scanf("%d", &num[i]);
		}
		//init
		for (i = 0; i < MAX_S; i++)
			for (j = 0; j < MAX_SEQ; j++)
				dp[j][i] = -1;

		//sort
		quicksort(num, 0, N - 1);

		/*
		for (i = 0; i < N; i++)
			printf("%d ", num[i]);
		printf("\n");
		*/

		printf("%d\n", quant(0,S));
	}
	return 0;
}
