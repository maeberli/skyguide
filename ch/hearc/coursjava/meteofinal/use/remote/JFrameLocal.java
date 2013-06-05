
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.rmi.RemoteException;

import javax.swing.JFrame;
import javax.swing.JTabbedPane;

import ch.hearc.coursjava.meteofinal.reseau.AfficheurServiceWrapper_I;

public class JFrameLocal extends JFrame
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameLocal()
		{
		geometrie();
		controle();
		apparence();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public void openNewTab()
		{
		tabbedPane.add("Nouvelle station météo", new JPanelStationMeteoLocal(this));
		}

	public void majTitle(JPanelStationMeteoLocal panelStationMeteoLocal, String title)
		{
		int counter = 0;
		for (Component c:tabbedPane.getComponents())
			{
			JPanelStationMeteoLocal panelStationMeteoLocal2 = (JPanelStationMeteoLocal)c;
			if (panelStationMeteoLocal == panelStationMeteoLocal2)
				{
				break;
				}
			counter++;
			}
		tabbedPane.setTitleAt(counter, title);
		}

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
//		tabbedPane.addChangeListener(new ChangeListener()
//			{
//
//				@Override
//				public void stateChanged(ChangeEvent e)
//					{
//					System.out.println("change");
//
//					}
//			});

		add(tabbedPane, BorderLayout.CENTER);

		tabbedPane.add("Station météo", new JPanelStationMeteoLocal(this));
		}

	private void controle()
		{
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		// Enlever les onglets du client sur le serveur.
		addWindowListener(new WindowAdapter()
			{

				@Override
				public void windowClosing(WindowEvent event)
					{
					for(Component c:tabbedPane.getComponents())
						{
						JPanelStationMeteoLocal panelStationMeteoLocal = (JPanelStationMeteoLocal)c;

						AfficheurServiceWrapper_I afficheurService = panelStationMeteoLocal.getAfficheurService();
						if (afficheurService != null)
							{
							try
								{
								afficheurService.removeTab();
								}
							catch (RemoteException e)
								{
								}
							}
						}
					}
			});
		}

	private void apparence()
		{
		setTitle("Stations météo locales");
		setSize(800, 400);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		setLocation((int)((dim.getWidth() - getWidth()) / 2), (int)((dim.getHeight() - getHeight()) / 2));

		setVisible(true);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private JTabbedPane tabbedPane;
	}
