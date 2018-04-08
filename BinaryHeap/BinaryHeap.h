template<typename Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100);
	explicit Binaryeap(const vector<Comparable> & items);

	bool isempty() const;
	const Comparable & findMin() const;

	void insert(const Comparable & x);
	void insert(Comparable && x);
	void deleteMin();
	void deleteMin(Comparable & minItem);
	void makeEmpty();

private:
	int currentSize; //����Ԫ�صĸ���
	vector<Comparable> arrayp; //�ѵ�����

	void buildHeap();
	void perolateDown(int hole);
};

template<typename Comparable>
inline BinaryHeap<Comparable>::Binaryeap(const vector<Comparable>& items)
	: array(items.size()+10), currentSize{items.size()}
{
	for (int i = 0; i < items.size(); ++i)
		array[i + 1] = items[i];
	buildHeap();
}

/**
 * ����x���룬��������ظ�Ԫ
 */
template<typename Comparable>
inline void BinaryHeap<Comparable>::insert(const Comparable & x)
{
	if (currentSize == array.size() - 1)
		array.resize(array.size() * 2);

	//����
	int hole = ++currentSize;
	Comparable copy = x;

	array[0] = std::move(copy);
	for (; x < array[hole / 2]; hole /= 2)
		array[hole] = std::move(array[hole / 2]);
	array[hole] = std::move(array[0]);
}

/**
 * ɾ����С��
 * ���Ϊ�����׳�UnderflowException�쳣
 */
template<typename Comparable>
inline void BinaryHeap<Comparable>::deleteMin()
{
	if (isempty())
		throw UnderflowException{};

	array[1] = std::move(array[currentSize--]);
	perolateDown(1);
}

/**
 * ɾ����С��������minItem��
 * ���Ϊ�����׳�UnderflowException�쳣
 */
template<typename Comparable>
inline void BinaryHeap<Comparable>::deleteMin(Comparable & minItem)
{
	if (isempty())
		throw UnderflowException{};
	
	minItem = std::move(array[1]);
	array[1] = std::move(array[currentSize--]);
	perolateDown(1);
}

/**
 * �������һ���н������������
 * ������ʱ������
 */
template<typename Comparable>
inline void BinaryHeap<Comparable>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; --i)
		perolateDown(i);
}

/**
 * �ڶ��н������˵��ڲ�����
 * ��Ѩ�����˿�ʼ�����±�
 */
template<typename Comparable>
inline void BinaryHeap<Comparable>::perolateDown(int hole)
{
	int child;
	Comparable tmp = std::move(array[hole]);

	for (; hole * 2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if (child != currentSize&&array[child + 1] < array[child])
			++child;
		if (array[child] < tmp)
			array[hole] = std::move(array[child]);
		else
			break;
	}
	array[hole] = std::move(tmp);
}