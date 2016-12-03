/*Middle Earth
 *Chris Puglia
 *1/16/2013
 */
 
import java.util.Scanner;
public class MiddleEarth
{
	public static void main(String [] args)
	{
		final int PAY=800; //amount the customer pays in grumbles
		
		
		Scanner sc = new Scanner(System.in);
		System.out.println ("Enter Cost in trungirs and grumbles");
		System.out.print ("Trungirs?");
		int t = Integer.parseInt(sc.nextLine());
		System.out.print ("Grumbles?");
		int g = Integer.parseInt(sc.nextLine());
		
		int total=(100*t)+g;
		int ch = PAY-total;
		String change = "Change is ";
	
		int i=0;
		
		if(ch-400>=0)
		{
			ch=ch-400;
			change+="a "+4+"-trungir bill, ";
		}
			
	
		if(ch-200>=0)
		{
			ch=ch-200;
			change+="a "+2+"-trungir bill, ";
		}
			
		
		if(ch-100>=0)
		{
			ch=ch-100;
			change+="a "+1+"-trungir bill, ";
		}
		//throans
		 i=0;
		 if(ch%11!=0)
		 {
			for (i = 0; ch-47>=0; i++)
				{
					ch=ch-47;
				}
			if(i==1)
				{
					change+="a throan, ";
				}
			 else if(i>0)
				{
					change+=i+" throans, ";
				}
		}

		//whevs
		 i=0;
		for (i = 0; ch-22>=0; i++)
		{
			ch=ch-22;
		}
		if(i==1)
		{
			change+="a whev, ";
		}
		else if(i>0)
		{
			change+=i+" whevs, ";
		}

		//moans
		i=0;
		for (i = 0; ch-11>=0; i++)
		{
			ch=ch-11;
		}
		if(i==1)
		{
			change+="a moan, ";
		}
		else if(i>0)
		{
			change+=i+" moans, ";
		}
		//groans
		i=0;
		for (i = 0; ch-3>=0; i++)
		{
			ch=ch-3;
		}
		if(i==1)
		{
			change+="a groan, ";
		}
		else if(i>0)
		{
			change+=i+" groans, ";
		}
		//grunts
		if(ch==1)
		{
			change+="a grunt,";
		}
		else if(ch>0)
		{
			change+=ch+" grunts,";
		}
		//Now removing additional comma at the end
		for ( i = change.length(); i>0; i--)
			{
				if(change.substring(i-1,i).equals(","))
				{
					String p1=change.substring(0,i-1);
					String p2=change.substring(i,change.length());
					change=p1+p2;
					break;
				}
			}
			//now adding the and at the last comma
		for ( i = change.length(); i>0; i--)
			{
				if(change.substring(i-1,i).equals(","))
				{
					String p1=change.substring(0,i-1);
					String p3=change.substring(i,change.length());
					String p2=", and";
					change=p1+p2+p3;
					break;
				}
			}
		System.out.println (change);
	}
}