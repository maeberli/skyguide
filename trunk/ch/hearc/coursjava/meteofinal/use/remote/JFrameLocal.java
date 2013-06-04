
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTabbedPane;

public class JFrameLocal extends JFrame
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameLocal(int test)
		{
		System.out.println(test);

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

	private void geometrie()
		{
		setLayout(new BorderLayout());
		tabbedPane = new JTabbedPane();

		add(tabbedPane, BorderLayout.CENTER);

		tabbedPane.add("Station météo", new JPanelStationMeteoLocal());
		tabbedPane.add(new JLabel("TEST"));
		}

	private void controle()
		{
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		// Enlever l'onglet du client sur le serveur.
		addWindowListener(new WindowAdapter()
			{

				@Override
				public void windowClosing(WindowEvent event)
					{
					/*try
						{
						afficheurService.removeTab();
						}
					catch (RemoteException e)
						{
						}*/
					System.out.println("TEST");
					}
			});
		}

	private void apparence()
		{
		setTitle("Nouvelle station météo");
		setLocation(100, 10);
		setSize(800, 400);

		setVisible(true);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private JTabbedPane tabbedPane;
	}
