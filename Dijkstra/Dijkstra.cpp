/**
 * LBB_Linux
 * Dijkstra
 */

/**
 * Vertex�ṹ������
 * ��ʵ�ʵ�c++��ʾ��·��ͨ��ΪVertex*��
 * �������������������
 * ����Ҫ�����������*������ʹ��
 * ->��������������.������
 */
struct Vertex
{
	List adj;  //�ڽ�list(��)
	bool known;
	DistType dist;	//DistType�ܿ�����int
	Vertex path;	//�ܿ�����vertex*
		//�������ݺͳ�Ա�������������
};

/**
 * ���赽v�����·������
 * ������dijkstra�㷨֮���ӡ�����·��
 */
void Graph::printPath(Vertex v)
{
	if (v.path != NOT_A_VERTEX)
	{
		printPath(v.path);
		cout << "to";
	}
	cout << v;
}

/**
 * �㷨����
 */
void Graph::dijkstra(Vertex s)
{
	for each Vertex v
	{
		v.dist = INFINITY;
		v.known = false;
	}

	s.dist = 0;

	while (there is an unknown distance Vertex)
	{
		Vertex v = smallest unknown distance Vertex;
		
		v.known = true;

		for each Vertex w adjacent to v
			if (!w.known)
			{
				DistType cvm = cost of edge from v to w;

				if (v.dist + cvm < w.dist)
				{
					//����w
					decrease(w.dist to v.dist + cvm);
					w.path = v;
				}
			}
	}
}