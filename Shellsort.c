// 希尔排序
void ShellSort(int* a, int n){
	int gap = n;
	while (gap > 1){//这里不能等于1，因为不是最后更新的gap，等于1就死循环了，下面这个表达式加1最后会一直等于1
		gap = (gap / 3) + 1;//加1时为了最后退1，不会退为0
		//画图，n-1-gap为最后一个数减gap，key为end+gap为最后一个数，全调整了
		for (int i = 0; i<n - gap; i++){
			int end = i;
			int key = a[end + gap];
			while (end >= 0){
				if (a[end] > key){
					a[end + gap] = a[end];
					end -= gap;
				}
				else{
					break;
				}
			}
			a[end + gap] = key;
		}
	}
}