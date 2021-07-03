void InsertSort(int* a, int n){
	for (int i = 0; i<n - 1; i++){//µ½n-1
		int end = i;
		int key = a[end + 1];
		while (end >= 0){
			if (a[end] > key){
				a[end + 1] = a[end];
				end--;
			}
			else{
				break;
			}
		}
		a[end + 1] = key;
	}


}