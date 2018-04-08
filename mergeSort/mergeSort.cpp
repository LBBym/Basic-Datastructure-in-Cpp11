/**
 * �鲢�����㷨����������
 */
template <typename Comparable>
void mergeSort(vector<Comparable> & a)
{
	vector(Comparable) tmpArray(a.size());

	mergeSort(a, tmpArray, 0, a.size() - 1);
}

/**
 * ���еݹ���õ��ڲ�����
 * aΪComparable�������
 * tmpArrayΪ���ù鲢���������
 * leftΪ����������Ԫ�ص��±�
 * rightΪ����������Ԫ�ص��±�
 */
template<typename Comparable>
void mergeSort(vector<Comparable> & a,
	vector<Comparable> & tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center);
		mergeSort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}

/**
 * �ϲ����������������벿�ֵ��ڲ�����
 * aΪComparable�������
 * tmpArrayΪ���ù鲢���������
 * leftPosΪ����������Ԫ�ص��±�
 * rightPosΪ��벿�������±�
 * rightEndΪ����������Ԫ�ص��±�
 */
template<typename Comparable>
void merge(vector<Comparable> & a, vector<Comparable> & tmpArray,
	int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	//��ѭ��
	while (leftPos <= leftEnd && rightPos <= rightEnd)
		if (a[leftPos] <= a[rightPos])
			tmpArray[tmpPos++] = std::move(a[leftPos++]);
		else
			tmpArray[tmpPos++] = std::move(a[rightPos++]);

	while (leftPos <= leftEnd) //����ǰ�벿�ֵ�ʣ��Ԫ��
		tmpArray[tmpPos++] = std::move(a[leftPos++]);

	while (rightPos <= rightEnd)  //���ƺ�벿�ֵ�ʣ��Ԫ��
		tmpArray[tmpPos++] = std::move(a[rightPos++]);

	//��tmpArray���ƻ�a
	for (int i = 0; i < numElements; ++i, --rightEnd)
		a[rightEnd] = std::move(tmpArray[rightEnd]);
}