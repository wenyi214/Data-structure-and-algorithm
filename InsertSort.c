
//����
void InsertSort(int* a, int n){

	for (int i = 0; i<n - 1; i++){//��n-1��key�Ǵ�end+1��ʼ
		int end = i;
		//������Ҫ����Ҫ�����ֵ������Ƶ�ʱ���ı�ԭ����ֵ
		int key = a[end + 1];
		//�Ҳ���λ��
		while (end >= 0){
			//��ǰ��ֵ���бȽ�
			if (a[end] > key){
				a[end + 1] = a[end];
				end--;
			}
			else{
				//�ҵ�
				break;
			}
		}
		//����
		a[end + 1] = key;
	}


}