/*
**LBB_Linux
**Chongqing Univer
**2017/9/20
*/
template<typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree & rhs);
	BinarySearchTree()(BinarySearchTree && rhs);
	~BinarySearchTree();

	const Comparable & findMin() const;
	const Comparable & findMax() const;
	bool contains(const Comparable & x) const;
	bool isEmpty() const;
	void printTree(ostream & out = cout)const;

	void makeEmpty();
	void insert(const Comparable & x);
	void insert(Comparable && x);
	void remove(const Comparable & x);

	BinarySearchTree & operator=(const BinarySearchTree & rhs);
	BinarySearchTree & operator=(BinarySearchTree && rhs);

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
			:element{ theElement }, left{ lt }, right{ rt } {}

		BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
			:element{ std::move(theElement) }, left(lt), right{ rt } {}
	};

	BinaryNode *root;

	void insert(const Comparable & x, BinaryNode * & t);
	void insert(Comparable && x, BinaryNode * & t);
	void remove(const Comparable & x, BinaryNode * & t);
	BinaryNode * findMin(BinaryNode *t)const;
	BinaryNode * findMax(BinaryNode *t)const;
	bool contains(const Comparable & x, BinaryNode * t)const;
	void makeEmpty(BinaryNode * & t);
	void printTree(BinaryNode * t, ostream & out)const;
	BinaryNode * clone(BinaryNode *t)const;
};


/*
**�������캯��
*/
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree & rhs):root{nullptr}
{
	root = clone(rhs.root);
}

/*
**�����������������
*/
template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
	makeEmpty();
}

//����������ҵ�x������true
template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x) const
{
	return contains(x, root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
	return makeEmpty();
}

//��x���뵽���У������ظ�Ԫ
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x)
{
	insert(x, root);
}

//��x������ɾ�������û��x��ʲôҲ����
template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x)
{
	remove(x, root);
}

/*
**����������Ԫ�ص��ڲ�����
**x��Ҫ�������
**tΪ�������ĸ��ڵ�
*���������¸�
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode *& t)
{
	if (t == nullptr)
		t = new BinaryNode{ x,nullptr,nullptr };
	else if (x < t->element)
		insert(x, t->left);
	else if (t->element < x)
		insert(x, t->right);
	else
		;//�ظ�Ԫ:ʲôҲ����
}

/*
**����������Ԫ�ص��ڲ�����
**x��ͨ���ƶ�ʵ�ֲ������
**tΪ�������ĸ�
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable && x, BinaryNode * & t)
{
	if (t == nullptr)
		t = new BinaryNode{ std::move(x),nullptr,nullptr };
	else if (std::move(x) < t->element)
		insert(std::move(x), t->left);
	else if (t->element < std::move(x))
		insert(std::move(x), t->right);
	else
		;//�ظ�Ԫ:ʲôҲ����
}

/*
**��һ������ɾ��һ����ڲ�����
**����x�Ǳ�ɾ������
**����tΪ�������ĸ��ڵ�
**�ø��������¸�
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x, BinaryNode * & t)
{
	if (t == nullptr)
		return;//û�ҵ���ʲôҲ����
	if (x < t->element)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr)//����������
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else 
	{
		BinaryNode *oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

/*
**�ҳ���t�е���С����ڲ�����
**���ذ�����С��Ľڵ�
*/
template<typename Comparable>
BinaryNode * BinarySearchTree<Comparable>::findMin(BinaryNode * t) const
{
	if(t==nullptr)
		return nullptr;
	if (t->left == nullptr)
		return t;
	return findMin(t->left);
}

/*
**�ҳ���t���������ڲ�����
**���ذ��������Ľڵ�
*/
template<typename Comparable>
BinaryNode * BinarySearchTree<Comparable>::findMax(BinaryNode * t) const
{
	if (t != nullptr)
		while (t->right != nullptr)
			t = t->right;
	return t;
}

/*
**����һ���Ƿ��������ϵ��ڲ�����
**x��Ҫ���ҵ���
**t����Ϊ�������ĸ��ڵ�
*/
template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode * t) const
{
	if (t == nullptr)
		return false;
	else if (x < t->element)
		return contains(x, t->left);
	else if (t->element < x)
		return contains(x, t->right);
	else
		return true;
}

/*
**ʹ����Ϊ�յ��ڲ�����
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *& t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}


/**
 * ��¡�������ڲ�����
 */
template<typename Comparable>
BinaryNode * BinarySearchTree<Comparable>::clone(BinaryNode * t) const
{
	if (t == nullptr)
		return nullptr;
	else
		return new BinaryNode{ t->element,clone(t->left),clone(t->right) };
}
