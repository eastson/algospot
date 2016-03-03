#include <stdio.h>
#define INT_MIN		(-65536)

int nums[50];
int memory[50][50];
int calced[50][50];

int getMaxEarn(int left, int right){
	int possibleEarn[4], max, i;
	if (left == right)
		return nums[left];
	else if (right - left == 1)
		return ((nums[left] > nums[right]) ? (nums[left] - nums[right]) : (nums[right] - nums[left]));

	if (calced[left][right] != 0) return memory[left][right];

	possibleEarn[0] = nums[left] - getMaxEarn(left + 1, right);
	possibleEarn[1] = nums[right] - getMaxEarn(left, right - 1);
	possibleEarn[2] = 0 - getMaxEarn(left + 2, right);
	possibleEarn[3] = 0 - getMaxEarn(left, right - 2);

	max = INT_MIN;
	for (i = 0; i < 4; i++){
		if (max < possibleEarn[i]) max = possibleEarn[i];
	}
	memory[left][right] = max;
	calced[left][right] = 1;

	return max;
}

int main(void){
	int C, n, i, j;

	scanf("%d", &C);
	while (C--){
		scanf("%d", &n);

		for (i = 0; i < n; i++){
			scanf("%d", &nums[i]);
		}
		for (i = 0; i < 50; i++)
		for (j = 0; j < 50; j++)
			calced[i][j] = 0;

		printf("%d\n", getMaxEarn(0, n-1));
	}
	return 0;
}
