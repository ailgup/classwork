class test
{
	public static void main(String [] args)
	{
		//System.out.println (c(new Double(9)));
	Integer x = new Integer (3);
	Integer xx = new Integer (1);
	Integer temp = new Integer (x.intValue());
	x=xx;
	xx=temp;
	System.out.println (x);
	System.out.println (xx);
	
	
	}
	public static Double c(Double d)
	{
		double x=d.doubleValue();
		x=Math.sqrt(x);
		return new Double(x);
		
	}
}