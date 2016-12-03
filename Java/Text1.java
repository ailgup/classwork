

public class Text1 {

    public Text1() {
    }

 public double convert(double a,String c, String d)
 {
 	double z=-9999999;
 	if(c.equals("in"))
 	{
 		if(d.equals("in"))
 		{
 			z=a;
 		}
 		else if(d.equals("ft"))
	 	{
	 		z=a/12;
	 	}
	 	else if(d.equals("mi"))
	 	{
	 		z=a*.0000157828;
	 	}
	 	else if(d.equals("m"))
	 	{
	 		z=a*.0254;
	 	}
	 	else if(d.equals("cm"))
	 	{
	 		z=a*2.54;
	 	}
	 	else if(d.equals("mm"))
	 	{
	 		z=a*25.4;
	 	}
	 	else if(d.equals("km"))
	 	{
	 		z=a*.0000254;
	 	}
 	}
 	else if(c.equals("ft"))
 	{
 		if(d.equals("in"))
 		{
 			z=a*12;
 		}
 		else if(d.equals("ft"))
	 	{
	 		z=a;
	 	}
	 	else if(d.equals("mi"))
	 	{
	 		z=a*.000189394;
	 	}
	 	else if(d.equals("m"))
	 	{
	 		z=a*0.3048;
	 	}
	 	else if(d.equals("cm"))
	 	{
	 		z=a*30.48;
	 	}
	 	else if(d.equals("mm"))
	 	{
	 		z=a*304.8;
	 	}
	 	else if(d.equals("km"))
	 	{
	 		z=a*.0003048;
	 	}
 	}
 	else if(c.equals("mi"))
 	{
 		if(d.equals("in"))
 		{
 			z=a*63360;
 		}
 		else if(d.equals("ft"))
	 	{
	 		z=a*5280;
	 	}
	 	else if(d.equals("mi"))
	 	{
	 		z=a;
	 	}
	 	else if(d.equals("m"))
	 	{
	 		z=a*1609.34;
	 	}
	 	else if(d.equals("cm"))
	 	{
	 		z=a*160934;
	 	}
	 	else if(d.equals("mm"))
	 	{
	 		z=a*1609340;
	 	}
	 	else if(d.equals("km"))
	 	{
	 		z=a*1.60934;
	 	}
 	}
 	else if(c.equals("m"))
 	{
 		if(d.equals("in"))
 		{
 			z=a*39.3701;
 		}
 		else if(d.equals("ft"))
	 	{
	 		z=a*3.28084;
	 	}
	 	else if(d.equals("mi"))
	 	{
	 		z=0.000621371;
	 	}
	 	else if(d.equals("m"))
	 	{
	 		z=a;
	 	}
	 	else if(d.equals("cm"))
	 	{
	 		z=a*100;
	 	}
	 	else if(d.equals("mm"))
	 	{
	 		z=a*1000;
	 	}
	 	else if(d.equals("km"))
	 	{
	 		z=a*.001;
	 	}
 	}
 	else if(c.equals("cm"))
 	{
 		if(d.equals("in"))
 		{
 			z=a*0.393701;
 		}
 		else if(d.equals("ft"))
	 	{
	 		z=a*0.0328084;
	 	}
	 	else if(d.equals("mi"))
	 	{
	 		z=a*.00000621371;
	 	}
	 	else if(d.equals("m"))
	 	{
	 		z=a*.01;
	 	}
	 	else if(d.equals("cm"))
	 	{
	 		z=a;
	 	}
	 	else if(d.equals("mm"))
	 	{
	 		z=a*10;
	 	}
	 	else if(d.equals("km"))
	 	{
	 		z=a*.00001;
	 	}
 	}
 	else if(c.equals("mm"))
 	{
 		if(d.equals("in"))
 		{
 			z=a*0.0393701;
 		}
 		else if(d.equals("ft"))
	 	{
	 		z=a*0.00328084;
	 	}
	 	else if(d.equals("mi"))
	 	{
	 		z=a*.000000621371;
	 	}
	 	else if(d.equals("m"))
	 	{
	 		z=a*.001;
	 	}
	 	else if(d.equals("cm"))
	 	{
	 		z=a*.1;
	 	}
	 	else if(d.equals("mm"))
	 	{
	 		z=a;
	 	}
	 	else if(d.equals("km"))
	 	{
	 		z=a*.000001;
	 	}
 	}
 	else if(c.equals("km"))
 	{
 		if(d.equals("in"))
 		{
 			z=a*39370.1;
 		}
 		else if(d.equals("ft"))
	 	{
	 		z=a*3280.84;
	 	}
	 	else if(d.equals("mi"))
	 	{
	 		z=a*0.621371;
	 	}
	 	else if(d.equals("m"))
	 	{
	 		z=a*1000;
	 	}
	 	else if(d.equals("cm"))
	 	{
	 		z=a*100000;
	 	}
	 	else if(d.equals("mm"))
	 	{
	 		z=a*1000000;
	 	}
	 	else if(d.equals("km"))
	 	{
	 		z=a;
	 	}
 	}
return z;}

}