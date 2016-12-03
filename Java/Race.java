import javax.swing.*;
import java.io.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Scanner;
import java.util.ArrayList;
 import java.util.Collections;

public class Race implements ActionListener

{ 		 ArrayList <Horse> horses = new ArrayList <Horse>();
		 ArrayList <Bet> bets = new ArrayList <Bet>();
		 int[] winners;
		
	public Race()
	{
	}
	
	public void admin()
	{
		Scanner sc = new Scanner(System.in);
		
		String[] possibleValues = { "Run Race","Add Horses","Edit Horses","Edit Bets"};
		Object selectedValue = JOptionPane.showInputDialog(null,"Choose one", "Admin Menu",JOptionPane.INFORMATION_MESSAGE, null,possibleValues, possibleValues[0]);
		
			if(selectedValue.equals("Add Horses"))
				{	
					while(true)
					{
					
						
						JPanel newHorse = new JPanel();
						JTextField number = new JTextField(2);
						JTextField name = new JTextField(10);
						JTextField odds = new JTextField(2);
						JTextField odds2 = new JTextField(2);
						newHorse.add(new JLabel("Horse Name:"));
						newHorse.add(name);
						newHorse.add(new JLabel("Number:"));
						newHorse.add(number);
						newHorse.add(new JLabel("Odds "));
						newHorse.add(odds);
						newHorse.add(new JLabel(":"));
						newHorse.add(odds2);
						
						
				try{
			     int result = JOptionPane.showConfirmDialog(null, newHorse, "Please Enter Info", JOptionPane.OK_CANCEL_OPTION); 
			     if (result == JOptionPane.OK_OPTION) 
			     {
			     	//double o=Double.parseDouble(odds.getText())/Double.parseDouble(odds2.getText());
						
						Horse h= new Horse(name.getText(),Integer.parseInt(odds.getText()), Integer.parseInt(odds2.getText()),Integer.parseInt(number.getText()));
						horses.add(h);
				}
				else
					break;
	      		}
	      			catch(Exception exc)
					{
					exc.printStackTrace();
					}
					}
				//	saveHorses();
					printHorses();
			}
			if(selectedValue.equals("Edit Horses"))
			{
				String [] names = new String[horses.size()];
				for (int i = 0; i<horses.size(); i++)
				{
					names[i] = "#"+horses.get(i).getNum()+" "+horses.get(i).getName();
				}
					
			Object edit = JOptionPane.showInputDialog(null,"Choose one", "Edit Menu",JOptionPane.INFORMATION_MESSAGE, null,names, names[0]);
				int y=0;
				for (int i = 0; i<names.length; i++)
				{
					if(edit.equals(names[i]))
						y=i;
				}
				Horse x = horses.get(y);
				JPanel newHorse = new JPanel();
						JTextField number = new JTextField(x.getNum()+"");
						JTextField name = new JTextField(x.getName());
						JTextField odds = new JTextField(x.getOdds1()+"");
						JTextField odds2 = new JTextField(x.getOdds2()+"");
						newHorse.add(new JLabel("Horse Name:"));
						newHorse.add(name);
						newHorse.add(new JLabel("Number:"));
						newHorse.add(number);
						newHorse.add(new JLabel("Odds "));
						newHorse.add(odds);
						newHorse.add(new JLabel(":"));
						newHorse.add(odds2);
						
						
						
				try{
			     int result = JOptionPane.showConfirmDialog(null, newHorse, "Please Enter Info", JOptionPane.OK_CANCEL_OPTION); 
			     if (result == JOptionPane.OK_OPTION) 
			     {
			     	//double o=Double.parseDouble(odds.getText())/Double.parseDouble(odds2.getText());
						
						Horse h= new Horse(name.getText(),Integer.parseInt(odds.getText()), Integer.parseInt(odds2.getText()),Integer.parseInt(number.getText()));
						horses.set(y,h);
				}
				
					
	      		}
	      			catch(Exception exc)
					{
					exc.printStackTrace();
					}
				}
			
				/* OLD IDEA DIDN'T ORK
				JPanel editHorse = new JPanel();
				editHorse.setLayout(new GridLayout(0,1));
				for(Horse h:horses)
				{
					JPanel c = new JPanel();
					c.add(new JLabel("Name:"));
					JTextArea name = new JTextArea();
					name.setText(h.getName());
					c.add(name);
					c.add(new JLabel("  Number:"));
					JTextArea number = new JTextArea();
					number.setText(h.getNum()+"");
					c.add(number);
					c.add(new JLabel("  Odds:"));
					JTextField odds1 = new JTextField();
					JTextField odds2 = new JTextField();
					odds1.setText(h.getOdds1()+"");
					odds2.setText(h.getOdds2()+"");
					c.add(odds1);
					c.add(new JLabel(":"));
					c.add(odds2);
					JButton remove = new JButton("Remove");
					c.add(remove);
					remove.addActionListener(this);
					editHorse.add(c);
				}
				try{
		     JOptionPane.showConfirmDialog(null, editHorse, "Please Enter Info", JOptionPane.OK_CANCEL_OPTION); 
			
      				}
      				
      			catch(Exception exc)
				{
				exc.printStackTrace();
				}
      		*/
					
					
				
			
			
	}
	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();
	/*	if(source==runRace)
		{
			
		}
		else if(source==editHorses)
		{
			
		}
		else if(source==addHorses)
		{
			
		}
		else if(source==editBets)
		{
			
		}
	*/}
	public void placeBet()
	{		
	
			JPanel myPanel = new JPanel();
			JTextField name = new JTextField(5);
      		JTextField amount = new JTextField(3);
      		JTextField amountdecimal = new JTextField(2);
      		JComboBox horseList = new JComboBox();
      		JComboBox place = new JComboBox();

      		myPanel.add(new JLabel("Your Name:"));
		      myPanel.add(name);
		      myPanel.add(Box.createHorizontalStrut(15)); // a spacer
		      myPanel.add(new JLabel("Bet Amount $"));
		      myPanel.add(amount);
		      myPanel.add(new JLabel("."));
		      myPanel.add(amountdecimal);
		      for(Horse h:horses)
		      {
		      	horseList.addItem("#"+h.getNum()+" "+h.getName()+" Odds "+h.getOdds1()+":"+h.getOdds2());
		      }
		      myPanel.add(horseList);
		      place.addItem("Win");
		      place.addItem("Place");
		      place.addItem("Show");
		      myPanel.add(place);
		     // horseList.addActionListener();
		     try{
		     int result = JOptionPane.showConfirmDialog(null, myPanel, "Please Enter Info", JOptionPane.OK_CANCEL_OPTION); 
		     if (result == JOptionPane.OK_OPTION) 
		     {
		     	double amountBet=(Double.parseDouble(amountdecimal.getText())/100)+Integer.parseInt(amount.getText());
		     	int horseNum=horses.get(horseList.getSelectedIndex()).getNum();
		     	int placeBet=(place.getSelectedIndex())+1;
	//Add Exception handling
         	 Bet x=new Bet(name.getText(),amountBet,placeBet,horseNum);
			bets.add(x);
			JOptionPane.showMessageDialog(null,"Thanks for placing $"+amountBet+" on Horse number "+horseNum+" to "+ placeBet);
      		}}
      			catch(Exception exc)
				{
				exc.printStackTrace();
				}
      		
			
			//Creates a string of the place
			
			
			
		
	}//end of bet
	
	
	public void createBet(String s, double a, int n, int p)
		{
				Bet x=new Bet(s,a,n,p);
				bets.add(x);
		}
	/*
	public static void openHorses()
	{
		try
		{
			FileInputStream saveFile = new FileInputStream("Horses.horse");
			ObjectInputStream save = new ObjectInputStream(saveFile);
			horses = (ArrayList) save.readObject();
			save.close();
		}
		catch(Exception exc)
		{
				exc.printStackTrace();
			}
	}
	
		
	public static void saveHorses()
	{
	
		try
		{
			FileOutputStream saveFile = new FileOutputStream("Horses.horse");
			ObjectOutputStream save = new ObjectOutputStream(saveFile);
				save.writeObject(horses);
			
		//	save.close();
		}
			catch(Exception exc)
			{
				exc.printStackTrace();
			}
	
	} */
	
	public  void printHorses()
	{
		for(Horse h:horses)
			System.out.println ("#"+h.getNum() +" : "+h.getName());
	}
	public  void printExpandedHorses()
	{
		for(Horse h:horses)
			System.out.println ("ID"+h.getCount()+"#"+h.getNum() +" : "+h.getName()+" Odds: "+ h.getOdds());
	}
	public  void runRace()
	{
		Scanner sc = new Scanner(System.in);
		
		String[] possibleValues = { "Random Race", "Input Winners"};
		Object selectedValue = JOptionPane.showInputDialog(null,
		"Choose one", "Input",
		JOptionPane.INFORMATION_MESSAGE, null,
		possibleValues, possibleValues[0]);
	if(selectedValue.equals("Random Race"))
	{
		
		 winners=generateWinners(horses.size());
		/*for(Horse h:horses)
		{
			if(h.getCount()==winners[0])
				h.setPlace(1);
			else if(h.getCount()==winners[1])
				h.setPlace(2);
			else if(h.getCount()==winners[2])
				h.setPlace(3);
		}
		*/
		horses.get(winners[0]).setPlace(1);
		horses.get(winners[1]).setPlace(2);
		horses.get(winners[2]).setPlace(3);
	/*
		int w=0;
		for (Horse h:horses)
		{
			if(w==h.getNum())
				{h.setPlace(1);
				System.out.println ("Winner is "+h.getName());
			}
		}
	*/
	}
	if(selectedValue.equals("Input Winners"))
	{ 
		printHorses();
		
		System.out.println ("Enter Winner Number");
		int w = Integer.parseInt(sc.nextLine());
		System.out.println ("Enter Placer Number");
		int p = Integer.parseInt(sc.nextLine());
		System.out.println ("Enter Shower Number");
		int s = Integer.parseInt(sc.nextLine());
		
		for(Horse h:horses)
		{
			if(h.getNum()==w)
				h.setPlace(1);
			else if(h.getNum()==p)
				h.setPlace(2);
			else if(h.getNum()==s)
				h.setPlace(3);
		}
		
	}
		//outputs the winners
		System.out.println ("Winner : #"+horses.get(winners[0]).getNum()+" "+horses.get(winners[0]).getName());
		System.out.println ("Placer : #"+horses.get(winners[1]).getNum()+" "+horses.get(winners[1]).getName());
		System.out.println ("Shower : #"+horses.get(winners[2]).getNum()+" "+horses.get(winners[2]).getName());
	
	calcBets();
	
	}
	
	public  void calcBets()
	{
		/*current calc paysout 100% of odds for win
		 *75% for place, and 50% for show
		 */
		 final double WIN_PAYOUT = 1;
		 final double PLACE_PAYOUT = .75;
		 final double SHOW_PAYOUT = .5;
		 
		 for (Bet b:bets)
		 {b.setPayout(0);
		 	if(b.getHorse()==horses.get(winners[0]).getNum())
		 	{
		 		
		 		double calcbet=(b.getAmount()*horses.get(winners[0]).getOdds()+b.getAmount());
		 		if(b.getPlace()==1)
		 			b.setPayout(calcbet*WIN_PAYOUT);
		 		else if(b.getPlace()==2)
		 			b.setPayout(calcbet*PLACE_PAYOUT);
		 		else if(b.getPlace()==3)
		 			b.setPayout(calcbet*SHOW_PAYOUT);
			}
			else if(b.getHorse()==horses.get(winners[1]).getNum())
		 	{
		 		double calcbet=(b.getAmount()*horses.get(winners[1]).getOdds()+b.getAmount());
		 		if(b.getPlace()==1)
		 			b.setPayout(0);
		 		else if(b.getPlace()==2)
		 			b.setPayout(calcbet*PLACE_PAYOUT);
		 		else if(b.getPlace()==3)
		 			b.setPayout(calcbet*SHOW_PAYOUT);
			}
			else if(b.getHorse()==horses.get(winners[2]).getNum())
		 	{
		 		double calcbet=(b.getAmount()*horses.get(winners[2]).getOdds()+b.getAmount());
		 		if(b.getPlace()==1)
		 			b.setPayout(0);
		 		else if(b.getPlace()==2)
		 			b.setPayout(0);
		 		else if(b.getPlace()==3)
		 			b.setPayout(calcbet*SHOW_PAYOUT);
			}
				
			}
			displayPayouts();
		}
		 
	public  void displayPayouts()
	{
		double totalin=0.0;
		double totalout=0.0;
		System.out.println ("::::::::::::::::::::::::::::::::::\nPAYOUTS:");
		for(Bet b:bets)
		{
			totalin+=b.getAmount();
			totalout+=b.getPayout();
			System.out.println (b.getName()+" : $"+b.getPayout()+ " Profit of $"+(b.getPayout()-b.getAmount()));
		}
		System.out.println (":::::::::::::::::::::::::::::::::::\n\n Track Statistics \n Total Bets Recieved = $"+totalin+"\n Total Payouts = $"+totalout+"\n Total Profit = $"+(totalin-totalout));
		
	}
				
	public  int[] generateWinners(int range)
	{
		ArrayList<Integer> numbers = new ArrayList<Integer>();
		int[] winners = new int[3];
     for(int i = 0; i < range; i++)
     {
     numbers.add(i+1);
   	}
 
     Collections.shuffle(numbers);
     //System.out.print("The winners are: ");
     for(int j =0; j < 3; j++)
     {
     //  System.out.print(numbers.get(j) + " ");
       winners[j]=numbers.get(j)-1;
     }
     return winners;
	}
			
     
    

}//end of class