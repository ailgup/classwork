public class Bet
{
	private String name;
	private double amount;
	private int place;
	private int horse;
	private double payout;
	
	public Bet(String n, double a, int p, int h)
	{
		name=n;
		amount=a;
		place=p;
		horse=h;
	}
	public String getName()
	{
		return name;
	}
	public int getPlace()
	{
		return place;
	}
	public double getAmount()
	{
		return amount;
	}
	public int getHorse()
	{
		return horse;
	}
	public void setPayout(double pa)
	{
		payout=pa;
	}
	public double getPayout()
	{
		return payout;
	}
	
		
}