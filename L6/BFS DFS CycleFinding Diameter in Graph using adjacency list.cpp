#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class chars
{
public:
	char v1,v2;
	chars(char v1, char v2)
	{
		this->v1 = v1;
		this->v2 = v2;
	}
};

template <class T>
class Node
{
public:
	T val;
	Node<T>* fd;
	Node()
	{
		this->fd = nullptr;
	}
	Node(T val)
	{
		this->val = val;
		this->fd = nullptr;
	}
	~Node()
	{
		if (this->fd != nullptr)
		{
			delete this->fd;
		}
	}
};

template <class T>
class List
{
public:
	Node<T>* head;
	Node<T>* tail;
	int size;
	List()
	{
		this->size = 0;
		this->head = new Node<T>();
		this->tail = head;
	}
	~List()
	{
		delete this->head;
	}

	void insert(T val)
	{
		Node<T>* it = this->head;
		while(it->fd != nullptr && it->fd->val < val)
		{
			it = it->fd;
		}
		Node<T>* item = new Node<T>(val);
		item->fd = it->fd;
		it->fd = item;
		if (it == tail)
		{
			tail = tail->fd;
		}
		this->size++;
	}

	T top()
	{
		return head->fd->val;
	}

	void push_back(T val)
	{
		Node<T>* item = new Node<T>(val);
		tail->fd = item;
		tail = tail->fd;
		this->size++;
	}

	void push_front(T val)
	{
		Node<T>* item = new Node<T>(val);
		item->fd = head->fd;
		head->fd = item;
		this->size++;
	}

	void pop_front()
	{
		if (head->fd != nullptr)
		{
			T val = head->fd->val;
			Node<T>* temp = head->fd;
			head->fd = temp->fd;
			temp->fd = nullptr;
			delete temp;
		}
		this->size--;
	}

	
	
};

class Graph
{
private:
	void addEdge(char v1, char v2)
	{
		if (adjacencyList[v1%65] == nullptr)
		{
			adjacencyList[v1%65] = new List<char>();
		}
		if (adjacencyList[v2%65] == nullptr)
		{
			adjacencyList[v2%65] = new List<char>();
		}

		adjacencyList[v1%65]->insert(v2);
		adjacencyList[v2%65]->insert(v1);
		this->edges++;

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

	void DFS(List<char>* stack, bool* isVisited)
	{
		if (stack->size == 0)
		{
			return;
		}
		else
		{
			char temp = stack->top();
			Node<char>* it = adjacencyList[temp%65]->head->fd;
			while(it != nullptr)
			{
				char val = it->val;
				if (isVisited[val%65] == false)
				{
					cout << val << " ";
					isVisited[val%65] = true;
					stack->push_front(val);
					DFS(stack,isVisited);
				}
				it = it->fd;
			}
			stack->pop_front();
		}
	}

	void BFS(List<char>* queue, bool* isVisited)
	{
		if (queue->size == 0)
		{
			return;
		}
		else
		{
			char temp = queue->top();
			Node<char>* it = adjacencyList[temp%65]->head->fd;
			while(it != nullptr)
			{
				char val = it->val;
				if (isVisited[val%65] == false)
				{
					cout << val << " ";
					isVisited[val%65] = true;
					queue->push_back(val);			
				}
				it = it->fd;
			}
			queue->pop_front();
			BFS(queue,isVisited);	
		}
	}

	void readEdges(List<chars*>* edges, string fileName)
	{
		ifstream file;
		file.open(fileName);

		if (file.is_open())
		{
			string temp;
			while(getline(file,temp))
			{
				stringstream s(temp);
				char v1,v2;
				s >> v1;
				s >> v2;
				chars* mypair = new chars(v1,v2);
				edges->push_back(mypair);
			}
			file.close();
		}	
	}


public:
	List<char>* adjacencyList[26];
	int edges;
	Graph()
	{
		this->edges = 0;
		for (int i = 0; i < 26; ++i)
		{
			adjacencyList[i] = nullptr;
		}
	}

	int getVertices()
	{
		int count = 0;
		for (int i = 0; i < 26; ++i)
		{
			if (adjacencyList[i] != nullptr)
			{
				count++;
			}
		}
		return count;
	}


	void readFromFile(string fileName)
	{
		ifstream file;
		file.open(fileName);

		if (file.is_open())
		{
			string temp;
			while(getline(file,temp))
			{
				stringstream s(temp);
				char v1,v2;
				s >> v1;
				s >> v2;
				this->addEdge(v1,v2);
			}
			file.close();
		}	
	}

	void printDFS()
	{
		bool isVisited[26];
		for (int i = 1; i < 26; ++i)
		{
			isVisited[i] = false;
		}
		List<char>* stack = new List<char>();
		stack->push_front('A');
		isVisited[0] = true;
		cout << "A" << " ";
		DFS(stack,&isVisited[0]);
		cout << endl;
		delete stack;
	}

	void printBFS()
	{
		bool isVisited[26];
		for (int i = 1; i < 26; ++i)
		{
			isVisited[i] = false;
		}

		List<char>* queue = new List<char>();
		queue->push_back('A');
		isVisited[0] = true;
		cout << "A" << " ";
		BFS(queue,&isVisited[0]);
		cout << endl;
		delete queue;
	}

	bool has_cycle(string fileName)
	{
		List<chars*>* edges = new List<chars*>();

		readEdges(edges,fileName);


		int* parent = new int[26];
		for (int i = 0; i < 26; ++i)
		{
			parent[i] = -1;
		}

		Node<chars*>* it = edges->head->fd;

		while(it != nullptr)
		{
			int set1 = find(parent,it->val->v1%65);
			int set2 = find(parent,it->val->v2%65);
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


	int getDiameter(string fileName)
	{
		int distance[26][26];
		for (int i = 0; i < 26; ++i)
		{
			for (int j = 0; j < 26; ++j)
			{
				distance[i][j] = -1;
			}
			distance[i][i] = 0;
		}

		ifstream file;
		file.open(fileName);

		if (file.is_open())
		{
			string temp;
			while(getline(file,temp))
			{
				stringstream s(temp);
				char v1,v2;
				s >> v1;
				s >> v2;
				distance[v1%65][v2%65] = 1;
				distance[v2%65][v1%65] = 1;
			}
			file.close();
		}

		for (int k = 0; k < 26; ++k)
		{
			for (int i = 0; i < 26; ++i)
			{
				if (distance[i][k] != -1)
				{
					for (int j = 0; j < 26; ++j)
					{
						if (distance[k][j] != -1 && (distance[i][j]==-1 || distance[i][k]+distance[k][j]<distance[i][j]))
						{
							 distance[i][j]=distance[i][k]+distance[k][j];
						}
					}
				}
			}
		}

		int diameter = -1;

		for (int i = 0; i < 26; ++i)
		{
			for (int j = 0; j < 26; ++j)
			{
				if (diameter<distance[i][j])
				{
                	diameter=distance[i][j];
				}
			}
		}

		return diameter;

	}

};

void menu()
{
	cout << endl;
	cout << "Select an option" << endl;
	cout << "\t1.BFS traversal" << endl;
	cout << "\t2.DFS traversal" << endl;
	cout << "\t3.Cycle finding in graph" << endl;
	cout << "\t4.Diameater of the graph" << endl;
	cout << "\t5.Exit" << endl;
}


int main(int argc, const char* argv[])
{
	if (argc <= 1)
	{
		cout << "Usage ./q1 fileName" << endl;
		exit(0);
	}
	Graph* graph = new Graph();
	graph->readFromFile(argv[1]);
	while(true)
	{
		int option;
		menu();
		cin >> option;
		switch(option)
		{
			case 1:
				graph->printBFS();
				break;
			case 2:
				graph->printDFS();
				break;
			case 3:
				if(graph->has_cycle(argv[1]))
				{
					cout << "Yes" << endl;
				}
				else
				{
					cout << "No" << endl;
				}
				break;
			case 4:
				cout << graph->getDiameter(argv[1]) << endl;
				break;
			case 5:
				exit(0);
			default:
				cout << " Enter a valid option" << endl;
		}
	}
	return 0;
}