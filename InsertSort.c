
//升序
void InsertSort(int* a, int n){

	for (int i = 0; i<n - 1; i++){//到n-1，key是从end+1开始
		int end = i;
		//我们需要保存要插入的值，完后移的时候会改变原来的值
		int key = a[end + 1];
		//找插入位置
		while (end >= 0){
			//和前面值进行比较
			if (a[end] > key){
				a[end + 1] = a[end];
				end--;
			}
			else{
				//找到
				break;
			}
		}
		//插入
		a[end + 1] = key;
	}


}