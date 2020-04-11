import java.util.Scanner;

public class q2_brute
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
					val = min(arr,low,high);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 2:
					System.out.println("Enter the low and high indices");
					low = in.nextInt();
					high = in.nextInt();
					val = max(arr,low,high);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 3:
					System.out.println("Enter the low and high indices");
					low = in.nextInt();
					high = in.nextInt();
					val = sum(arr,low,high);
					if (val != -1)
					{
						System.out.println(val);
					}
					break;

				case 4:
					System.out.println("Enter the low and high indices");
					low = in.nextInt();
					high = in.nextInt();
					add4(arr,low,high);
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

	public static int min(int[] arr, int low, int high)
	{
		if (low < 0 || high >= arr.length)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			int result = arr[low];
			for (int i = low+1; i <= high; i++)
			{
				if (arr[i] < result)
				{
					result = arr[i];
				}
			}
			return result;
		}
	}

	public static int max(int[] arr, int low, int high)
	{
		if (low < 0 || high >= arr.length)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			int result = arr[low];
			for (int i = low+1; i <= high; i++)
			{
				if (arr[i] > result)
				{
					result = arr[i];
				}
			}
			return result;
		}
	}

	public static int sum(int[] arr, int low, int high)
	{
		if (low < 0 || high >= arr.length)
		{
			System.out.println("Please Enter valid indices");
			return -1;
		}
		else
		{
			int sum = 0;
			for (int i = low; i <= high; i++)
			{
				sum += arr[i];
			}
			return sum;
		}
	}

	public static void add4(int[] arr, int low, int high)
	{
		if (low < 0 || high >= arr.length)
		{
			System.out.println("Please Enter valid indices");
		}
		else
		{
			for (int i = low; i <= high; i++)
			{
				arr[i] += 4;
			}	
		}
	}
}