public class Horse
{
	private static int counter=0;
	private int count;
	private String name;
	private double odds;
	private int number;
	private int place;
	private int odds1;
	private int odds2;
	
	public Horse(String s, int o,int o2, int n)
	{
		name=s;
		odds1=o;
		odds2=o2;
		number=n;
		count=counter;
		counter++;
		odds=((odds1+1.0)/odds2);
		
	}
	public void recalcOdds()
	{
		odds=((odds1+1.0)/odds2);
	}
	public void setOdds(double o)
	{
		o=odds;
	}
	public void setOdds1(double o)
	{
		o=odds1;
	}
	public void setOdds2(double o)
	{
		o=odds2;
	}
	public void setName(String s)
	{
		name=s;
	}
	public void setNum(int s)
	{
		number=s;
	}
	public String getName()
	{
		return name;
	}
	public int getNum()
	{
		return number;
	}
	public int getCount()
	{
		return count;
	}
	public double getOdds()
	{
		return odds;
	}
	public int getOdds1()
	{
		return odds1;
	}
	public int getOdds2()
	{
		return odds2;
	}
	public void setPlace(int p)
	{
		place=p;;
	}
		public int getPlace()
	{
		return place;
	}
}
	