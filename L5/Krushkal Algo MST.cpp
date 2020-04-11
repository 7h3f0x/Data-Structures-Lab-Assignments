#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Edge
{
public:
	char v1,v2;
	int weight;
	Edge* fd;

	Edge(char v1, char v2, int weight)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->weight = weight;
	}
};

class Graph
{
private:
	int getVertices()
	{
		int count = 0;
		for (int i = 0; i < 26; ++i)
		{
			if (this->vertex[i] > 0)
			{
				count++;
			}
		}
		return count;
	}

	int find(int* parent,int val)
	{
		if (parent[val] == -1)
		{
			return val;
		}
		else
		{
			return find(parent,parent[val]);
		}
	}

	void Union(int* parent,int val1,int val2)
	{
		int set1 = find(parent,val1);
		int set2 = find(parent,val2);
		if (set1 != set2)
		{
			parent[set1] = set2;
		}	
	}

public:
	int vertices, edges;
	Edge* head;
	int vertex[26];

	Graph()
	{
		this->vertices = 0;
		this->edges = 0;
		head = new Edge(0,0,0);
		head->fd = nullptr;
		for (int i = 0; i < 26; ++i)
		{
			vertex[i] = 0;
		}
	}

	Edge* addEdge(char v1, char v2, int weight)
	{
		Edge* edge = new Edge(v1,v2,weight);

		Edge* it = head->fd;
		Edge* prev = head;
		while(it != nullptr && it->weight <= weight)
		{
			prev = it;
			it = it->fd;
		}
		edge->fd = it;
		prev->fd = edge;

		vertex[v1 % 65]++;
		vertex[v2 % 65]++;
		this->vertices = getVertices();
		this->edges++;
		return prev;
	}

	Edge* popEdge()
	{
		Edge* edge = head->fd;
		if (edge != nullptr)
		{
			head->fd = edge->fd;
			edge->fd = nullptr;
			vertex[edge->v1 % 65]--;
			vertex[edge->v2 % 65]--;
			this->edges--;
			this->vertices = getVertices();
			return edge;
		}
		else
		{
			return nullptr;
		}
	}

	void remove(Edge* prev)
	{
		Edge* temp = prev->fd;
		prev->fd = temp->fd;
		edges--;
		vertex[temp->v1 % 65]--;
		vertex[temp->v2 % 65]--;
		vertices = getVertices();
		delete temp;
	}

	void print()
	{
		Edge* it = head->fd;
		while(it != nullptr)
		{
			cout << it->v1 << "," << it->v2 << "," << it->weight << endl;
			it = it->fd;
		}
	}


	bool has_cycle()
	{
		int* parent = new int[26];
		for (int i = 0; i < 26; ++i)
		{
			parent[i] = -1;
		}
		Edge* it = head->fd;
		for (int i = 0; i < edges; ++i)
		{
			int set1 = find(parent,it->v1 % 65);
			int set2 = find(parent,it->v2 % 65);
			if (set1 == set2)
			{
				return true;
			}
			else
			{
				Union(parent,set1,set2);
			}
			it = it->fd;
		}
		return false;
	}

	int getWeight()
	{
		int wt = 0;
		for (Edge* it = head->fd; it != nullptr; it = it->fd)
		{
			wt += it->weight;
		}
		return wt;
	}

	void writeToDot(string fileName)
	{
		ofstream file;
		file.open(fileName);

		if (file.is_open())
		{
			file << "graph MST {" << endl;
			file << "\tgraph [ dpi = 1200 ];" << endl;

			for (Edge* it = head->fd; it != nullptr; it = it->fd)
			{
				file << "\t" << it->v1 << " -- " << it->v2 << " [label=" << it->weight << "];" << endl; 
			}

			file << "}" << endl;

			file.close();
		}
	}

};

int main(void)
{
	ifstream file;
	file.open("2019_CSN_261_L5_P2.csv");

	Graph graph;

	if (file.is_open())
	{
		string temp;
		while(getline(file,temp))
		{
			char v1,v2,comma;
			int weight;
			stringstream s(temp);
			s >> v1;
			s >> comma;
			s >> v2;
			s >> comma;
			s >> weight;
			graph.addEdge(v1,v2,weight);
		}
		file.close();
	}

	Graph mst;
	int V = graph.vertices;

	while(mst.edges <  V-1)
	{
		Edge* edge = graph.popEdge();
		Edge* temp = mst.addEdge(edge->v1,edge->v2,edge->weight);
		if (mst.has_cycle())
		{
			mst.remove(temp);
		}
		delete edge;
	}

	cout << endl;
	mst.print();
	cout << endl;
	cout << "The total edge weight of the MST is : " << mst.getWeight() << endl;

	mst.writeToDot("Krushkal.dot");

	return 0;
}