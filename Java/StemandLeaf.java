class StemandLeaf
{
	public static void main(String [] args)
	{
		int [] x = new int[]{5,18,23,24,66,89,99,104};
		printit(x);
	}
	public static void printit(int [] sample)
	{
		for (int i = 0; i<=10; i++)
		{
			if(i==10)
				System.out.print (i+"  | ");
			else
				System.out.print (i+"   | ");
			for (int j = 0; j<sample.length; j++)
			{
				if(sample[j]/10==i)
					System.out.print (sample[j]%10+" ");
					
			}
			System.out.println ();
		}
	}
}