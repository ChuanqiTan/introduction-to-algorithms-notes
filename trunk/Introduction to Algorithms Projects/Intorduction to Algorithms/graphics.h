#pragma once
/// ͼ�ı�ʾ��
/// 
/// ͼ�����ֱ�ʾ��������1���ڽӱ�������2���ڽӾ���
/// 


#include <vector>
#include <utility>
using namespace std;

namespace chapter22
{
	/// ͼ�����ͣ�����ͼ��������ͼ
	enum GraphicsType : short
	{
		Digraph,			///< ����ͼ
		Undigraph			///< ����ͼ
	};

	/// ʹ���ڽӱ�����ʾһ��ͼ
	template<typename T>
	class GraphicsViaAdjacencyList
	{
	public:
		/// �ڽӱ��ϵ�һ�����
		struct AdjacencyListNode
		{
			size_t			AimNodeIndex;	///< Ŀ�궥��ı��
			double			Weight;			///< �������ӱߵ�Ȩֵ
			AdjacencyListNode	*Next;			///< ָ����һ�����
		};

	public:
		/// ͨ���������ʼ��һ��ͼ
		GraphicsViaAdjacencyList(vector<T> const &v, GraphicsType type) : _v(v), _e(v.size(), nullptr), _type(type)
		{

		}

		~GraphicsViaAdjacencyList()
		{
			for_each(_e.begin(), _e.end(), [](AdjacencyListNode *e){
				while (e)
				{
					AdjacencyListNode *temp = e;
					e = e->Next;
					delete temp;
				}
			});
		}


		/// ��ʶͼ���������֮����һ����
		void Link2Vertex(size_t index1, size_t index2, double weight = 1)
		{
			AdjacencyListNode *node = new AdjacencyListNode();
			node->AimNodeIndex = index2;
			node->Next = _e[index1];
			node->Weight = weight;
			_e[index1] = node;

			if (_type == Undigraph)
			{
				//����ͼ
				node = new AdjacencyListNode();
				node->AimNodeIndex = index1;
				node->Next = _e[index2];
				node->Weight = weight;
				_e[index2] = node;
			}
		}

		/// ��ѯ���������Ƿ�����
		/// 
		/// �������������Ƿ�������ͬʱ�����ظ����ߵ�Ȩֵ��������������ͷ���<false, 0>�������Ȩֵ������
		pair<bool, AdjacencyListNode *> IsLinked(size_t index1, size_t index2) const
		{
			AdjacencyListNode *l = _e[index1];
			while(l)
			{
				if (l->AimNodeIndex == index2)
				{
					return make_pair(true, l);
				}
				l = l->Next;
			}
			return make_pair(false, nullptr);
		}

		inline vector<T> & GetVertex()				{return _v;}
		inline vector<AdjacencyListNode *> & GetEdges()	{return _e;}

		vector<pair<size_t, size_t>> GetAllEdges()
		{
			vector<pair<size_t, size_t>> edges;
			for (size_t i = 0; i < _e.size(); ++i)
			{
				AdjacencyListNode *l = _e[i];
				while(l)
				{
					edges.push_back(make_pair(i, l->AimNodeIndex));
					l = l->Next;
				}
			}
			return edges;
		}

	
	private:
		//GraphicsViaAdjacencyList(GraphicsViaAdjacencyList<T> const &);
		//GraphicsViaAdjacencyList<T> & operator=(GraphicsViaAdjacencyList<T> &);

		vector<T>				_v;		///< ͼ�Ķ���ļ���
		vector<AdjacencyListNode *>	_e;		///< ͼ�ıߣ����ڽӱ�
		GraphicsType			_type;	///< ͼ������
	};


	/// ʹ���ڽӾ�������ʾһ��ͼ
	template<typename VT, typename ET>
	class GrpahicsViaAdjacencyMatrix
	{
	public:
		GrpahicsViaAdjacencyMatrix(vector<VT> const &v, GraphicsType type = Digraph) : _v(v), _e(v.size(), vector<ET>(v.size())), _type(type)
		{

		}

		void Link2Vertex(size_t index1, size_t index2, ET weight)
		{
			_e[index1][index2] = weight;
			if (_type == Undigraph)
			{
				_e[index2][index1] = weight;
			}
		}

		/// ��ѯ���������Ƿ�����
		bool IsLinked(size_t index1, size_t index2) const
		{
			return _e[index1][index2] != ET();
		}

		inline vector<VT> & GetVertex()			{return _v;}
		inline vector<vector<ET>> & GetEdge()	{return _e;}


	
	private:
		vector<VT>				_v;		///< ͼ�Ķ���ļ���
		vector<vector<ET>>		_e;		///< ͼ�ıߣ����ڽӾ���
		GraphicsType			_type;	///< ͼ������
	};

}