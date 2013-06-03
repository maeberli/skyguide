
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.rmi.RemoteException;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper_I;

public class JFrameCentrale extends JFrame
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameCentrale()
		{
		control();
		apparence();
		geometrie();
		}

	private void control()
		{
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		graphList = new LinkedList<PanelStationMeteo>();

		addWindowListener(new WindowAdapter()
			{

				@Override
				public void windowClosing(WindowEvent event)
					{
					// Parcourir toutes les stations météo.
					// Puis les fermer via le MeteoServiceWrapper.
					for(Component c:tabbedPane.getComponents())
						{
						if (c instanceof PanelStationMeteo)
							{
							PanelStationMeteo stationMeteo = (PanelStationMeteo)c;

							// Appel d'une méthode qui de MeteoServiceWrapper qui la ferme la fenêtre cliente.
							try
								{
								stationMeteo.getMeteoServiceWrapper().exitClient();
								}
							catch (RemoteException e)
								{
								System.out.println("[JFrameCentrale] Fermeture du client.");
								}
							}
						}
					}
			});
		}

	private void geometrie()
		{
		this.setLayout(new BorderLayout());

		tabbedPane = new JTabbedPane();

		add(tabbedPane, BorderLayout.CENTER);

		tabbedPane.add("Bienvenu sur la central météo", new JLabel("En attente de station météo ..."));
		}


	public PanelStationMeteo openNewTab(MeteoServiceWrapper_I meteoServiceRemote)
		{
		if (tabbedPane.getComponentAt(0) instanceof JLabel)
			{
			tabbedPane.remove(0);
			}

		PanelStationMeteo stationMeteo = new PanelStationMeteo(meteoServiceRemote);
		tabbedPane.add("Station Météo", stationMeteo);

		graphList.add(stationMeteo);

		return stationMeteo;
		}

	public void removeStationMeteo(JPanel stationMeteo)
		{
		tabbedPane.remove(stationMeteo);
		}

	private void apparence()
		{
		setSize(800, 600);
		setTitle("JFramePCCentrale");
		setLocation(30, 30);
		setResizable(true);

		setVisible(true);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/
	public void draw()
		{
		for(PanelStationMeteo graph: graphList)
			{
			graph.repaint();
			}
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

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// private PanelGraphe panel;
	private JTabbedPane tabbedPane;
	// private PanelGraphe newTab;
	private List<PanelStationMeteo> graphList;

	}
