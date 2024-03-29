
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.rmi.RemoteException;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import ch.hearc.coursjava.meteofinal.afficheur.AffichageOptions;
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
					// Parcourir toutes les stations m�t�o.
					// Puis les fermer via le MeteoServiceWrapper.
					for(Component c:tabbedPane.getComponents())
						{
						if (c instanceof PanelStationMeteo)
							{
							PanelStationMeteo stationMeteo = (PanelStationMeteo)c;

							// Appel d'une m�thode qui de MeteoServiceWrapper qui la ferme la fen�tre cliente.
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

		tabbedPane.add("Bienvenu sur la central m�t�o", new JLabel("En attente de station m�t�o ..."));
		}


	public PanelStationMeteo openNewTab(MeteoServiceWrapper_I meteoServiceRemote, AffichageOptions affichageOptions)
		{
		if (tabbedPane.getComponentAt(0) instanceof JLabel)
			{
			tabbedPane.remove(0);
			}

		PanelStationMeteo stationMeteo = new PanelStationMeteo(meteoServiceRemote);
		tabbedPane.add(affichageOptions.getTitre(), stationMeteo);

		graphList.add(stationMeteo);

		return stationMeteo;
		}

	public void removeStationMeteo(JPanel stationMeteo)
		{
		tabbedPane.remove(stationMeteo);

		if (tabbedPane.getComponents().length == 0)
			{
			tabbedPane.add("Bienvenu sur la central m�t�o", new JLabel("En attente de station m�t�o ..."));
			}
		}

	private void apparence()
		{
		setTitle("Station m�t�o centrale");
		setSize(800, 600);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		setLocation((int)((dim.getWidth() - getWidth()) / 2), (int)((dim.getHeight() - getHeight()) / 2));
		setResizable(true);

		setVisible(true);

		setIconImage(ImageTools.loadJar("ressources/icon.png", true));
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
