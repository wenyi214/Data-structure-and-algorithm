// ϣ������
void ShellSort(int* a, int n){
	int gap = n;
	while (gap > 1){//���ﲻ�ܵ���1����Ϊ���������µ�gap������1����ѭ���ˣ�����������ʽ��1����һֱ����1
		gap = (gap / 3) + 1;//��1ʱΪ�������1��������Ϊ0
		//��ͼ��n-1-gapΪ���һ������gap��keyΪend+gapΪ���һ������ȫ������
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