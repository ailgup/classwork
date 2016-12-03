import javax.swing.*;
import java.util.ArrayList;
import java.awt.*;
import java.awt.event.*;

public class RaceRunner extends JFrame implements ActionListener
{
	private Container con = getContentPane();
	private JLabel title = new JLabel("Welcome to Kentucky Derby Betting !!");
	private JButton bet = new JButton("Place A Bet");
	private JButton admin = new JButton("Admin");
	private Race r1 = new Race();
	
	
	public RaceRunner()
	{
		
		super("Kentucky Derby");
	
		setSize(500,500);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		con.setLayout(new BorderLayout());
		title.setFont(new Font("Arial",Font.BOLD,45));
		con.add(title, BorderLayout.NORTH);
		con.add(bet, BorderLayout.CENTER);
		con.add(admin, BorderLayout.SOUTH);
		bet.addActionListener(this);
		admin.addActionListener(this);
		
		
	}
	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();
		if(source==bet)
		{
			r1.placeBet();
		}
		if(source==admin)
		{
			String input=JOptionPane.showInputDialog(null,"Enter Password");
			if(input.equalsIgnoreCase("1117"))
			r1.admin();
			else
			JOptionPane.showMessageDialog(null,"Incorrect Password","Error",JOptionPane.ERROR_MESSAGE);
		}	
	}
	public static void main(String [] args)
	{
	
		RaceRunner panel = new RaceRunner();
		
	}
}
