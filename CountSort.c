//��������
void CountSort(int* a, int n)
{
	int min = a[0];//��¼�����е���Сֵ
	int max = a[0];//��¼�����е����ֵ
	for (int i = 0; i < n; i++)
	{
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}
	int range = max - min + 1;//min��max֮�����Ȼ������������min��max����
	int* count = (int*)calloc(range, sizeof(int));//���ٿɴ���range�����͵��ڴ�ռ䣬�����ڴ�ռ���0
	if (count == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	//ͳ����ͬԪ�س��ִ��������ӳ�䣩
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;
	}
	int i = 0;
	//����ͳ�ƽ�������л��յ�ԭ����������
	for (int j = 0; j < range; j++)
	{
		while (count[j]--)
		{
			a[i++] = j + min;
		}
	}
	free(count);//�ͷſռ�
}