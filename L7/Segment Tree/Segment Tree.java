import java.util.Scanner;
import java.lang.Math;
import java.lang.Integer;

class Node
{
	int low;
	int high;
	int min;
	int max;
	int sum;
	Node left;
	Node right;
	Node(int low, int high)
	{
		this.low = low;
		this.high = high;
		this.left = null;
		this.right = null;
	}
}

class SegmentTree
{
	Node root;
	int nodes;

	SegmentTree(int[] arr)
	{
		this.root = new Node(0,arr.length -1);
		makeUtil(arr,root);
		this.nodes = arr.length;
	}

	int min(int low,int high)
	{
		if (low < 0 || high >= nodes)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			return getMin(root,high,low);
		}
	}

	int max(int low, int high)
	{
		if (low < 0 || high >= nodes)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			return getMax(root,high,low);
		}
	}

	int sum(int low, int high)
	{
		if (low < 0 || high >= nodes)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			return getSum(root,high,low);
		}	
	}

	void add4()
	{
		add4Util(root);	
	}

	private void makeUtil(int[] arr, Node node)
	{
		if (node.low == node.high)
		{
			node.min = node.max = node.sum = arr[node.low];
		}
		else
		{
			node.left = new Node(node.low,(node.low+node.high)/2);
			node.right = new Node(((node.low+node.high)/2) + 1,node.high);
			makeUtil(arr,node.left);
			makeUtil(arr,node.right);
			node.sum = node.left.sum + node.right.sum;
			node.min = Math.min(node.left.min,node.right.min);
			node.max = Math.max(node.left.max,node.right.max);
		}
	}

	private int getMin(Node node, int high, int low)
	{
		if (node.low >= low && node.high <= high)
		{
			return node.min;
		}
		else if (node.high < low || node.low > high)
		{
			return Integer.MAX_VALUE;
		}
		else
		{
			return Math.min(getMin(node.left,high,low),getMin(node.right,high,low));
		}
	}

	private int getMax(Node node, int high, int low)
	{
		if (node.low >= low && node.high <= high)
		{
			return node.max;
		}
		else if (node.high < low || node.low > high)
		{
			return Integer.MIN_VALUE;
		}
		else
		{
			return Math.max(getMax(node.left,high,low),getMax(node.right,high,low));
		}
	}

	private int getSum(Node node, int high, int low)
	{
		if (node.low >= low && node.high <= high)
		{
			return node.sum;
		}
		else if (node.high < low || node.low > high)
		{
			return 0;
		}
		else
		{
			return getSum(node.left,high,low) + getSum(node.right,high,low);
		}
	}

	private void add4Util(Node node)
	{
		if (node != null)
		{
			node.min += 4;
			node.max += 4;
			node.sum += 4*(node.high-node.low + 1);
			add4Util(node.left);
			add4Util(node.right);
		}
	}
}


public class q2
{
	public static void main(String[] args)
	{
		Scanner in = new Scanner(System.in);
		System.out.println("Enter the number of elements in the array:");
		int n = in.nextInt();
		int[] arr = new int[n];
		System.out.println("Enter the numbers now:");
		for (int i = 0; i < n; i++)
		{
			arr[i] = in.nextInt();
		}
		SegmentTree mytree = new SegmentTree(arr);

		while(true)
		{
			menu();
			int option = in.nextInt();
			if (option < 0 || option > 5) 
			{
				System.out.println("Enter a valid option");
				break;
			}
			int low,high,val;			
			switch(option)
			{
				case 1:
					System.out.println("Enter the low and high indices");
					low = in.nextInt();
					high = in.nextInt();
					val = mytree.min(low,high);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 2:
					System.out.println("Enter the low and high indices");
					low = in.nextInt();
					high = in.nextInt();
					val = mytree.max(low,high);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 3:
					System.out.println("Enter the low and high indices");
					low = in.nextInt();
					high = in.nextInt();
					val = mytree.sum(low,high);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 4:
					mytree.add4();
					break;

				case 5:
					System.exit(0);
			}
		}
		
	}
	public static void menu()
	{
		System.out.println("Enter One of These Options to get some results:");
		System.out.println("\t1.Find Minimum value in a range");
		System.out.println("\t2.Find Maximum value in a range");
		System.out.println("\t3.Find The Sum of a given range");
		System.out.println("\t4.Add 4 with each element");
		System.out.println("\t5.Exit");
	}
}