/**
 * ���������㷨����������
 */
template<typename Comparable>
void quicksort(vector<Comparable> & a)
{
	quicksort(a, 0, a.size() - 1);
}

/**
 * ִ��������ֵ�ָ�
 * ����left�� center�� right�������ֵ
 * ����������������ŦԪ
 */
template<typename Comparable>
const Comparable & meidan3(vector<Comparable> & a, int left, int right)
{
	int center = (left + right) / 2;

	if (a[center] < a[left])
		std::swap(a[left], a[center]);
	if (a[right] < a[left])
		std::swap(a[left], a[right]);
	if (a[right] < a[center])
		std::swap(a[center], a[right]);

	//����ŦԪ����right-1��
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}

/**
 * ���еݹ���õ��ڲ��������򷽷�
 * ʹ��������ֵ�ָ���Լ���ֹ��Χ��10�Ľ�������
 * a��Comparable�������
 * leftΪ����������Ԫ�ص��±�
 * rightΪ����������Ԫ�ص��±�
 */
template<typename Comparable>
void quicksort(vector<Comparable> & a, int left, int right)
{
	if (left + 10 <= right)
	{
		const Comparable & pivot = median3(a, left, right);

		//��ʼ�ָ�
		int i = left, j = right - 1;
		for (;;)
		{
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j)
				std::swap(a[i], a[j]);
			else
				break;
		}

		std::swap(a[i], a[right - 1]); //�ָ���ŦԪ

		quicksort(a, left, i - 1); //��С�ڵ�����ŦԪ��Ԫ������
		quicksort(a, i + 1, right); //�����ڵ�����ŦԪ��Ԫ������
	}
	else //����������в�������
		insertionSort(a, left, right);
}