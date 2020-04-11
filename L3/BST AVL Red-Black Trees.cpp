#include <iostream>
#include <vector>
#include <algorithm>

#define RED true
#define BLACK false

using namespace std;

template <class T>
void printInorder(T* curr)
{
	if (curr == NULL)
	{
		return;
	}
	else
	{
		printInorder(curr->left);
		cout << curr->val << " ";
		printInorder(curr->right);
	}
}

class RedBlackNode
{
	public :
		int val;
		bool color;
		RedBlackNode* parent;
		RedBlackNode* left;
		RedBlackNode* right;

		RedBlackNode(int toInsert)
		{
			this->val = toInsert;
			this->color = RED;
			this->parent = NULL;
			this->right = NULL;
			this->left = NULL;
		}
};

class RedBlackTree
{
	private:

		int getHeight(RedBlackNode* node)
		{
			if (node ==  NULL)
			{
				return -1;
			}
			else
			{
				return max(getHeight(node->left),getHeight(node->right))+1;
			}
		}

		int getBalanceFactor(RedBlackNode* node)
		{
			return getHeight(node->left)-getHeight(node->right);
		}

		void printIndent(RedBlackNode* node,int indentNo)
		{
			if (node == NULL)
			{
				return;
			}
			else
			{
				for (int i = 0; i < indentNo; ++i)
				{
					cout << "        ";
				}
				cout << node->val << "[" << getBalanceFactor(node) << "]";
				if (node->color == BLACK)
				{
					cout << "[BLACK]";
				}
				else
				{
					cout << "[RED]";
				}
				cout << endl;
				printIndent(node->left,indentNo+1);
				printIndent(node->right,indentNo+1);
			}
		}


		void rotateRight(RedBlackNode* node)
		{
			RedBlackNode* ptr = new RedBlackNode(node->val);
			ptr->right = node->right;
			ptr->color = node->color;

			if (node->left->right != NULL)
			{
				ptr->left = node->left->right;
			}

			node->val = ptr->left->val;
			node->color = ptr->left->color;

			node->right = ptr;

			if (ptr->left != NULL)
			{
				ptr->left->parent = ptr;
			}

			if (ptr->right != NULL)
			{
				ptr->right->parent = ptr;
			}

			ptr->parent = node;

			if (node->left->left != NULL)
			{
				node->left = node->left->left;
			}

			else
			{
				node->left = NULL;
			}

			if (node->left != NULL)
			{
				node->left->parent = node;
			}
		}

		void rotateLeft(RedBlackNode* node)
		{

            RedBlackNode* ptr = new RedBlackNode(node->val);
            ptr->left = node->left;
            ptr->color = node->color;
            if(node->right->left) 
            { 
            	ptr->right = node->right->left; 
            }
            
            node->val = node->right->val;
  
            node->left = ptr;

            if(ptr->left)
            { 
            	ptr->left->parent = ptr;
            }

            if(ptr->right)
            { 
            	ptr->right->parent = ptr;
            }

            ptr->parent = node;
  
            if(node->right->right)
            { 
            	node->right = node->right->right;
            }

            else 
            { 
            	node->right = NULL; 
            }
  
            if(node->right)
            { 
            	node->right->parent = node; 
            }
 
		}

	public:
		int size;
		RedBlackNode* root;

		RedBlackTree()
		{
			this->root = NULL;
			this->size = 0;
		}


		void FixTree(RedBlackNode* ptr)
		{
			while(ptr->parent->color == RED)
			{
				RedBlackNode* grdParent = ptr->parent->parent;
				RedBlackNode* uncle = this->root;

				if (ptr->parent == grdParent->left)
				{
					if (grdParent->right != NULL)
					{
						uncle = grdParent->right;
					}

					if (uncle->color == RED)
					{
						ptr->parent->color = BLACK;
						uncle->color = BLACK;
						grdParent->color = RED;

						if (grdParent != this->root)
						{
							ptr = grdParent;
						}

						else
						{
							break;
						}
					}

					else if (ptr == grdParent->left->right)
					{
						rotateLeft(ptr->parent);
					}

					else
					{
						ptr->parent->color = BLACK;
						grdParent->color = RED;
						rotateRight(grdParent);

						if (grdParent != this->root)
						{
							ptr = grdParent;
						}

						else
						{
							break;
						}
					}
				}

				else
				{
					if (grdParent->left != NULL)
					{
						uncle = grdParent->left;
					}
					
					if (uncle->color == RED)
					{
						ptr->parent->color = BLACK;
						uncle->color = BLACK;
						grdParent->color = RED;

						if (grdParent != this->root)
						{
							ptr = grdParent;
						}

						else
						{
							break;
						}
					}

					else if (ptr == grdParent->right->left)
					{
						rotateRight(ptr->parent);
					}

					else
					{
						ptr->parent->color = BLACK;
						grdParent->color = RED;
						rotateLeft(grdParent);

						if (grdParent != this->root)
						{
							ptr = grdParent;
						}

						else
						{
							break;
						}
					}
				}
			}
			this->root->color = BLACK;
		}

		void insertNode(int data)
		{
			if (this->root == NULL)
			{
				root = new RedBlackNode(data);
				root->color = BLACK;
			}
			else
			{
				RedBlackNode* node = new RedBlackNode(data);
				RedBlackNode* it = this->root;
				while(it != NULL)
				{
					if (data > it->val)
					{
						if (it->right == NULL)
						{
							it->right = node;
							it->right->color = RED;
							it->right->parent = it;
							break;
						}
						else
						{
							it = it->right;
						}
					}
					else
					{
						if (it->left == NULL)
						{
							it->left = node;
							it->left->color = RED;
							it->left->parent = it;
							break;
						}
						else
						{
							it = it->left;
						}
					}
				}
				this->size++;
				FixTree(node);
			}
		}
		void printIndentWise()
		{
			this->printIndent(this->root,0);
		}


		void printInorderTraversal()
		{
			printInorder(this->root);
			cout << endl;
		}
};

class Node
{
	public:
		int val;
		Node* right;
		Node* left; 

		Node(int toInsert)
		{
			this->val = toInsert;
			this->right = NULL;
			this->left = NULL;
		}
};



class BinarySearchTree
{
	private:

		Node* leftRotate(Node* ptr)
		{
			Node* temp1 = ptr->right;
			Node* temp2 = temp1->left;

			temp1->left = ptr;
			ptr->right = temp2;
			return temp1;
		}

		Node* rightRotate(Node* ptr)
		{
			Node* temp1 = ptr->left;
			Node* temp2 = temp1->right;

			temp1->right = ptr;
			ptr->left = temp2;
			return temp1;
		}

		int getHeight(Node* node)
		{
			if (node ==  NULL)
			{
				return 0;
			}
			else
			{
				return max(getHeight(node->left),getHeight(node->right))+1;
			}
		}

		int getBalanceFactor(Node* node)
		{
			return getHeight(node->left)-getHeight(node->right);
		}

		void printIndent(Node* node,int indentNo)
		{
			if (node == NULL)
			{
				return;
			}
			else
			{
				for (int i = 0; i < indentNo; ++i)
				{
					cout << "    ";
				}
				cout << node->val << "[" << getBalanceFactor(node) << "]" << endl;
				printIndent(node->left,indentNo+1);
				printIndent(node->right,indentNo+1);
			}
		}

		void deleteNode(Node* node)
		{
			if (node == NULL)
			{
				return;
			}
			else
			{
				deleteNode(node->left);
				deleteNode(node->right);
				delete node;
			}
		}
	public:
		int size;
		Node* root;

		BinarySearchTree()
		{
			this->size=0;
			this->root = NULL;
		}

		~BinarySearchTree()
		{
			this->deleteNode(this->root);
		}

		Node* insertNodeAVL(Node* node, int data)
		{
			if (node == NULL)
			{
				return (new Node(data));
			}
			if (data < node->val)
			{
				node->left = insertNodeAVL(node->left,data);
			}
			else if (data > node->val)
			{
				node->right = insertNodeAVL(node->right,data);
			}
			else
			{
				return node;
			}

			int bal = getBalanceFactor(node);

			if (bal > 1 && data < node->left->val)
			{
				return rightRotate(node);
			} 
		           
		    if (bal < -1 && data > node->right->val)
		    {
		    	return leftRotate(node);
		    }  
		            
		    if (bal > 1 && data > node->left->val)  
		    {  
		        node->left = leftRotate(node->left);  
		        return rightRotate(node);  
		    }  
		  
		    if (bal < -1 && data < node->right->val)  
		    {  
		        node->right = rightRotate(node->right);  
		        return leftRotate(node);  
		    }  
			return node;

		}

		void insertNode(int data)
		{
			if (this->root == NULL)
			{
				this->root = new Node(data);
			}
			else
			{
				Node* curr = this->root;
				Node* parent = this->root;
				while(curr != NULL)
				{
					parent=curr;
					if (data > curr->val)
					{
						curr = curr->right;
					}
					else
					{
						curr = curr->left;
					}
				}
				if (data > parent->val)
				{
					parent->right = new Node(data);
				}
				else
				{
					parent->left = new Node(data);
				}
			}
			this->size++;
		}



		void printIndentWise()
		{
			this->printIndent(this->root,0);
		}


		void printInorderTraversal()
		{
			printInorder(this->root);
			cout << endl;
		}
};

BinarySearchTree* bst;
BinarySearchTree* avl;
RedBlackTree* rbt;

void menu()
{
	cout << endl;

	cout << "1.Insert a node in BST and in the Red-Black tree" << endl;
	cout << "2.Create AVL tree from the BST" << endl;
	cout << "3.Print the inorder traversal of the BST/AVL/red-black tree" << endl;
	cout << "4.Display all the paths in the BST/AVL/Red-Black tree" << endl;
	cout << "5.Print the BST/AVL/Red-Black Tree using level-wise indentation" << endl;
	cout << "6.Exit this program" << endl;

	cout << endl;
}

void insert()
{
	cout << "Enter the number to insert" << endl;
	int toInsert = 0;
	cin >> toInsert;
	bst->insertNode(toInsert);
	rbt->insertNode(toInsert);
}

void BSTtraverse(int* arr,int &counter,Node* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		BSTtraverse(arr,counter,node->left);
		arr[counter++] = node->val;
		BSTtraverse(arr,counter,node->right);
	}
}

// void createAVL(int lower, int upper, int* traverse)
// {
// 	if (lower > upper)
// 	{
// 		return;
// 	}
// 	else
// 	{
// 		avl->insertNode(traverse[(lower+upper+1)/2]);
// 		createAVL(lower,(lower+upper+1)/2 -1 ,traverse);
// 		createAVL((lower+upper+1)/2 +1, upper, traverse);
// 	}
// }

void createAVLHandler()
{
	if (avl != NULL)
	{
		delete avl;
		avl = new BinarySearchTree();
	}
	else
	{
		avl = new BinarySearchTree();
	}

	int counter=0;
	int* traversal = new int[bst->size];
	BSTtraverse(traversal,counter,bst->root);
	for (int i = 0; i < bst->size ; ++i)
	{
		avl->root = avl->insertNodeAVL(avl->root, traversal[i]);
	}	

}

void print()
{
	cout << endl;
	cout << "The inorder traversal for the BST is" << endl;
	bst->printInorderTraversal();

	if(avl == NULL)
	{
		cout << "The AVL tree hasn't been created yet" << endl;
	}
	else
	{
		cout << "The inorder traversal for the AVL tree is " << endl;
		avl->printInorderTraversal();
	}

	cout << "The inorder traversal for the Red-Black Tree is" << endl;
	rbt->printInorderTraversal();
	
}

template <class T>
void printAllPaths(T* node,vector<int> vec)
{
	if (node == NULL)
	{
		return;
	}
	vec.push_back(node->val);
	if (node->right == NULL && node->left == NULL)
	{
		for(auto it = vec.begin(); it != vec.end(); it++)
		{
			if (it == vec.begin())
			{
				cout << *it;
			}
			else
			{
				cout << "->" << *it;
			}
		}
		cout << endl;
	}
	else
	{
		printAllPaths(node->left,vec);
		printAllPaths(node->right,vec);
	}
}

template <class T>
void printAllPathsHelper(T* node)
{
	if (node == NULL)
	{
		return;
	}
	vector<int> vec;
	printAllPaths(node,vec);
	printAllPathsHelper(node->left);
	printAllPathsHelper(node->right);
}

void printAllPathsHandler()
{
	cout << "For BST : " << endl;
	printAllPathsHelper(bst->root);

	if (avl == NULL)
	{
		cout << "The AVL tree hasn't been created yet" << endl;
	}
	else
	{
		cout << "For AVL Tree : " << endl;
		printAllPathsHelper(avl->root);
	}
	
	cout << "For Red-Black Tree : " << endl;
	printAllPathsHelper(rbt->root);
}

void printIndentHandler()
{
	cout << "For BST : " << endl;
	bst->printIndentWise();

	if (avl == NULL)
	{
		cout << "The AVL tree hasn't been created yet" << endl;
	}
	else
	{
		cout << "For AVL Tree : " << endl;
		avl->printIndentWise();
	}
	

	cout << "For Red-Black Tree : " << endl;
	rbt->printIndentWise();
	
}


int main(void)
{
	bst = new BinarySearchTree();
	rbt = new RedBlackTree();
	while(true)
	{
		menu();
		int option=0;
		cin >> option;
		switch(option)
		{
			case 1:
				insert();
				break;

			case 2:
				createAVLHandler();
				break;

			case 3:
				print();
				break;

			case 4:
				printAllPathsHandler();
				break;

			case 5:
				printIndentHandler();
				break;

			case 6:
				exit(0);

			default:
				cout << "Enter a correct option" << endl;
				break;
		}
	}

	return 0;
}