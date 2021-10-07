//计数排序
void CountSort(int* a, int n)
{
	int min = a[0];//记录数组中的最小值
	int max = a[0];//记录数组中的最大值
	for (int i = 0; i < n; i++)
	{
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}
	int range = max - min + 1;//min和max之间的自然数个数（包括min和max本身）
	int* count = (int*)calloc(range, sizeof(int));//开辟可储存range个整型的内存空间，并将内存空间置0
	if (count == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	//统计相同元素出现次数（相对映射）
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;
	}
	int i = 0;
	//根据统计结果将序列回收到原来的序列中
	for (int j = 0; j < range; j++)
	{
		while (count[j]--)
		{
			a[i++] = j + min;
		}
	}
	free(count);//释放空间
}