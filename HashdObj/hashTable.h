/**
 * LBB_Linux
 * HashTable
 */

template<typename HashedObj>
class HushTable
{
public:
	explicit HashTable(int size = 101);

	bool contains(const HashObj & x)const;
	
	void makeEmpty();
	bool insert(const HashObject & x);
	bool insert(HashedObj && x);
	bool remove(const HashedObj & x);

private:
	vector<list<HashedObj>> theLists;  //���������
	int currentSize;

	/**
	 * �Է�������ɢ�б���ɢ��
	 */
	void rehash()
	{
		vector<list<HashedObj>> oldLists = theLists;
		
		//����������Ŀձ�
		theLists.resize(nextPrime(2 * oldLists.size()));
		for (auto & theList : theLists)
			theList.clear();

		//����������
		currentSize = 0;
		for (auto & theList : oldLists)
			for (auto x : theList)
				insert(std::move(x));
	}

	size_t myhash(const HashedObj & x)const
	{
		static hash<HashedObj> hf;
		return hf(x) % theLists.size();
	}

	//��������ģ��
	template<typename Key>
	class hash
	{
	public:
		size_t operator() (const Key & k) const;
	};

	//���磺����string�Ĳ���
	template<>
	class hash<string>
	{
	public:
		size_t operator() (const string & key)
		{
			size_t hashVal = 0;

			for (char ch : key)
				hashVal = 37 * hashVal + ch;

			return hashVal;
		}
	};

	void makeEmpty()
	{
		for (auto & theList : theLists)
			theList.clear();
	}

	bool contains(const HashedObj & x)const
	{
		auto & whichList = theLists[myhash(x)];
		return find(begin(whichList), end(whichList), x) != end(whichList);
	}

	bool remove(const HashedObj & x)
	{
		auto whichList = theLists[myhash(x)];
		auto itr = find(begin(whichList), end(whichList), x);

		if (itr == end(whichList))
			return false;

		whichList.erase(itr);
		--currentSize;
		return false;
	}


	bool insert(const HashedObj & x)
	{
		auto & whichList = theLists[myhash(x)];
		if (find(begin(whichList), end(whichList), x) != end(whichList))
			return false;
		whichList.push_back(x);

		//��ɢ��
		if (++currentSize > theLists.size())
			rehash();

		return true;
	}
};