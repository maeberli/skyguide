
package ch.hearc.coursjava.api.reseau.rmi.pc.secret;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.rmi.RemoteException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

import ch.hearc.coursjava.api.reseau.rmi.horloge.Horloge_I;

public class JFrameHorloge extends JFrame
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameHorloge(Horloge_I horloge)
		{
		this.horloge = horloge;

		geometrie();
		controle();
		apparence();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/


	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void controle()
		{
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		buttonDate.addActionListener(new ActionListener()
			{
				@Override
				public void actionPerformed(ActionEvent event)
					{
					String date;

					try
						{
						date = JFrameHorloge.this.horloge.getTime().toString();
						}
					catch (RemoteException e)
						{
						date = "Inconnue.";
						e.printStackTrace();
						}

					JFrameHorloge.this.labelDate.setText(date);
					}
			});
		}

	private void geometrie()
		{
		this.setLayout(new FlowLayout());

		labelDate = new JLabel("Label date");
		buttonDate = new JButton("Date PC distant");

		add(labelDate);
		add(buttonDate);
		}

	private void apparence()
		{
		setSize(400, 100);
		setTitle("JVM PC Secret");
		setLocation(30, 30);
		setResizable(true);
		this.setVisible(true);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private JLabel labelDate;
	private JButton buttonDate;

	// Input
	private Horloge_I horloge;

	}

