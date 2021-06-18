#include<stdio.h>
#include<Windows.h>
#pragma warning(disable:4996)
//方法一  时间复杂度O(n^3)
//int Maxsubsum(int a[],int num){
//	int max = 0;
//	for (int i = 0; i < num; i++){
//		for (int j = i; j < num; j++){
//			int sum = 0;
//			for (int k = i; k <= j; k++){//计算i到j之间的和，注意k<=j
//				sum += a[k];
//			}
//			if (max < sum){
//				max = sum;
//			}
//		}
//	}
//	return max;
//
//}
//方法二  时间复杂度O(n^2)
//int Maxsubsum(int a[], int num){
//	int max = 0;
//	for (int i = 0; i < num; i++){
//		int sum = 0;
//		for (int j = i; j < num; j++){//不许要k循环，在j基础上往后加一位
//			sum += a[j];
//
//			if (max < sum){
//				max = sum;
//			}
//		}
//	}
//	return max;
//
//}
//方法三 分而治之
int Max(int a,int b,int c){
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int Maxsubsum(int a[], int left, int right){
	int fleftmax = 0;
	int frightmax = 0;
	int leftsum = 0;
	int leftmax = 0;
	int rightsum = 0;
	int rightmax = 0;

	if (left == right){
		if (a[left]>0){
			return a[left];
		}
		else{
			return 0;
		}
	}
	int mid = (left + right) / 2;
	fleftmax = Maxsubsum(a, left, mid);//左边最大子列和
	frightmax = Maxsubsum(a, mid + 1, right);//右边最大子列和
	for (int i = mid; i >=left; i--){//跨域左边中间最大子列和
		leftsum += a[i];
		if (leftsum>leftmax){
			leftmax = leftsum;
		}
	}
	for (int i = mid + 1; i <= right; i++){//跨域右边中间最大子列和
		rightsum += a[i];
		if (rightsum > rightmax){
			rightmax = rightsum;
		}
	}
	return Max(fleftmax, frightmax, leftmax + rightmax);//求出最大值
}


//方法四  在线 时间复杂度 O(n)
//int Maxsubsum(int a[], int num){
//	int max = 0;
//	int sum = 0;
//	for (int i = 0; i < num; i++){
//		sum+= a[i];
//		if (sum>max){
//			max = sum;
//		}
//		if (sum <= 0)
//			sum = 0;
//	}
//	return max;
//
//}
int main(){
	int a[] = { 4, 5, -6, 7, -8, -3, 7, 9, 10 };
	int num = sizeof(a) / sizeof(a[0]);
	int max = Maxsubsum(a, 0, num - 1);
	printf("%d\n", max);
	system("pause");
	return 0;
}