#include<stdio.h>
#include<windows.h>


void Swap(int *px, int *py){
	int temp = *px;
	*px = *py;
	*py = temp;

}

void AdjustHead(int a[], int num, int i){
	int child = 2 * i + 1;
	while (child < num){
		if (child + 1 < num&&a[child] < a[child + 1]){
			child++;
		}
		int parant = (child - 1) / 2;
		if (a[child] > a[parant]){
			Swap(&a[child], &a[parant]);
			parant = child;
			child = 2 * parant + 1;
		}
		else{
			break;
		}
	}
}

void HeadBuild(int a[],int num){
	for (int i = ((num - 1 - 1) / 2); i >= 0; i--){
		AdjustHead(a, num, i);
	}


}

void HeadSort(int a[],int num){
	for (int i = num - 1; i > 0; i--){
		Swap(&a[0], &a[i]);
		AdjustHead(a, i, 0);
	}
}


int main(){
	int a[] = { 27, 15, 18, 19, 35, 28, 65, 25, 49, 37 };
	int num = sizeof(a) / sizeof(a[0]);
	HeadBuild(a, num);
	HeadSort(a, num);
	system("pause");
	return 0;
}