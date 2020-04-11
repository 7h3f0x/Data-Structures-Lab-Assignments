#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node
{
public:
	int val;
	Node* child;
	Node* next;
	int degree;
	Node(int val)
	{
		this->degree = 0;
		this->val = val;
		this->child = nullptr;
		this->next = nullptr;
	}
};

void printTree(Node* node)
{
	while(node != nullptr)
	{
		cout << node->val << " ";
		printTree(node->child);
		node = node->next;
	}
}

class Heap
{
private:

	void mergeHeap(Node* ptr1, Node* ptr2)
	{
		Node* newroot = new Node(-1);
		Node* it = newroot;
		while(ptr1 != nullptr && ptr2 != nullptr)
		{
			if (ptr1->degree <= ptr2->degree)
			{
				it->next = ptr1;
				ptr1 = ptr1->next;
			}
			else
			{
				it->next = ptr2;
				ptr2 = ptr2->next;
			}
			it = it->next;
		}

		while(ptr1 != nullptr)
		{
			it->next = ptr1;
			ptr1 = ptr1->next;
			it = it->next;
		}

		while(ptr2 != nullptr)
		{
			it->next = ptr2;
			ptr2 = ptr2->next;
			it = it->next;
		}

		this->minroot = newroot->next;
		newroot->next = nullptr;
		delete newroot;
		satisfy(this->minroot);
	}

	void satisfy(Node* node)
	{
		Node* prev = nullptr;
		Node* curr = node;
		Node* curr_next = node->next;
		if (curr_next == nullptr)
		{
			return; // only 1 node in heap
		}

		while(curr != curr_next)
		{
			
			if (curr->degree != curr_next->degree)
			{
				prev = curr;
				curr = curr_next;
				if(curr_next->next != nullptr)
					curr_next = curr_next->next;
			}
			else if (curr_next->next != nullptr && curr_next->next->degree == curr->degree)
			{
				prev = curr;
				curr = curr_next;
				if(curr_next->next != nullptr)
					curr_next = curr_next->next;
			}
			else if (curr->val <= curr_next->val)
			{
				curr->next = curr_next->next;
				link(curr,curr_next);
				curr_next = curr;
				if(curr->next != nullptr)
					curr_next = curr->next;
			}
			else if (curr->val > curr_next->val)
			{
				if (curr == minroot)
				{
					minroot = curr_next;
				}
				else
				{
					prev->next = curr_next;
				}
				link(curr_next,curr);
				curr = curr_next;
				if(curr_next->next != nullptr)
					curr_next = curr_next->next;

			}
		}
	}

	void link(Node* node1, Node* node2)
	{
		node2->next = node1->child;
		node1->child = node2;
		node1->degree++;
	}

	void dot(Node* node, string* s)
	{
		if (node == nullptr)
		{
			return;
		}
		else
		{
			Node* it = node->child;
			while(it != nullptr)
			{
				*s += "\t" + to_string(node->val) + "->" + to_string(it->val) + ";\n";
				dot(it,s);
				it = it->next;
			}
		}
	}

public:
	Node* minroot;

	Heap()
	{
		this->minroot = nullptr;
	}

	void print()
	{
		Node* it = this->minroot;
		while(it != nullptr)
		{
			cout << it->degree << " : " << it->val << " ";
			printTree(it->child);
			cout << endl;
			it = it->next;
		}
	}

	void insert(int val)
	{
		Node* item = new Node(val);

		mergeHeap(this->minroot,item);
	}

	void writeToDot(string fileName)
	{
		ofstream file;
	
		Node* it = minroot;
		string s;
		s = "digraph G" + to_string(it->degree) + "{\n";
		s += "\tgraph [ dpi = 1200 ];\n";

		while(it != nullptr)
		{
			if (it->degree != 0)
			{
				dot(it,&s);	
			}
			else
			{
				s += "\t" + to_string(it->val) + ";\n";
			}
			it = it->next;
		}

		s += "}" ;
		file.open(fileName);
		if (file.is_open())
		{
			file << s << endl;
			file.close();
		}	
	}

};

int main(void)
{
	Heap* heap = new Heap();
	int n;
	cout << "Enter the number of elements" << endl;
	cin >> n;
	cout << "Enter the elements" << endl;
	for (int i = 0; i < n; ++i)
	{
		int val;
		cin >> val;
		heap->insert(val);
	}
	heap->print();

	heap->writeToDot("q2.dot");

	return 0;
}