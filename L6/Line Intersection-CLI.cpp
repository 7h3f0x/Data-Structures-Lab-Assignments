#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

class Vertex
{
public:
	float x,y;
	bool isLeft;
	void* segment;
	Vertex(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->segment = nullptr;
	}
};




class Segment
{
public:
	Vertex* left;
	Vertex* right;
	float m,c;
	Segment(float x1, float y1, float x2, float y2)
	{
		left = new Vertex(x1,y1);
		left->isLeft = true;

		right = new Vertex(x2,y2);
		right->isLeft = false;

		left->segment = this;
		right->segment = this;

		m = (y2-y1)/(x2-x1);
		c = y1 - m*x1;
	}

	bool check(float x, float y)
	{
		float x1 = left->x;
		float y1 = left->y;
		float x2 = right->x;
		float y2 = right->y;
		if (x >= min(x1,x2) && x <= max(x1,x2))
		{
			if (y >= min(y1,y2) && y <= max(y1,y2))
			{
				return true;
			}
		}
		return false;
	}

};

class CompareQueue
{
public:
	int operator() (const Vertex& v1, const Vertex& v2)
	{
		if(v1.x != v2.x)
			return v1.x > v2.x;
		else
			return v1.y > v2.y;
	}
};

class CompareSet
{
public:
	int operator() (const Vertex& v1, const Vertex& v2)
	{
		if(v1.x != v2.x)
			return v1.x < v2.x;
		else
			return v1.y < v2.y;
	}
};


bool intersect(Segment* seg1, Segment* seg2, float* x, float *y)
{
	if (seg1->m == seg2->m)
	{
		return false;
	}
	else
	{
		float m1,m2,c1,c2;
		m1 = seg1->m;
		c1 = seg1->c;
		m2 = seg2->m;
		c2 = seg2->c;
		*x = (c2-c1)/(m1-m2);
		*y = m1*(*x) + c1;
		if (seg1->check(*x,*y) && seg2->check(*x,*y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


void linearFit(float* x,float* y,int n, float* a, float* b)
{
	float sumx = 0,sumy = 0;
	for (int i = 0; i < n; ++i)
	{
		sumx += x[i];
		sumy += y[i];
	}


	float ybar = sumy/n;
	float xbar = sumx/n;

	float m = 0;
	float temp = 0;
	for (int i = 0; i < n; ++i)
	{
		m += (x[i] - xbar)*(y[i]-ybar);
		temp += (x[i] - xbar) * (x[i] - xbar);
	}

	*a = m/temp;
	*b = ybar - (*a) * xbar;
}



int main(void)
{
	int n;
	cout << "Enter the number of lines : ";
	cin >> n;
	Segment** segments = new Segment*[n];

	priority_queue <Vertex, vector<Vertex> , CompareQueue> que;
	cout << "Enter the coordinates space separated" << endl;
	for (int i = 0; i < n; ++i)
	{
		float x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		segments[i] = new Segment(x1,y1,x2,y2);
		que.push(*(segments[i]->left));
		que.push(*(segments[i]->right));
	}

	set<Vertex,CompareSet> output;
	set<Segment*> active;

	while(que.empty() == false)
	{
		Vertex v = que.top();
		if (v.isLeft == true)
		{
			Segment* curr = (Segment*)v.segment;
			for (auto it = active.begin() ; it != active.end() ; ++it)
			{
				Segment* temp = *it;
				float x,y;
				bool intersection = intersect(curr, temp,&x,&y);
				if (intersection)
				{
					Vertex ins(x,y);
					output.insert(ins);
				}	
			}
			active.insert((Segment*)v.segment);
		}
		else
		{
			active.erase((Segment*)v.segment);
		}
		que.pop();
	}

	cout << "No. of intersection points: "<< output.size() << endl;
	for (auto it = output.begin(); it != output.end(); it++)
	{
		cout << "(" << it->x << "," << it->y << ")" << endl;
	}

	n = output.size();
	float* x = new float[n];
	float* y = new float[n];
	int i = 0;
	for (auto it = output.begin(); it != output.end(); it++)
	{
		x[i] = it->x;
		y[i] = it->y;
		i++;
	}

	float a;
	float b;

	linearFit(x,y,n,&a,&b);

	cout << "Linear Fit : " << a << "x + " << b << endl;

	return 0;
}