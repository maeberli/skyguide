
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JFrame;
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
		}

	private void geometrie()
		{
		this.setLayout(new BorderLayout());

		tabbedPane = new JTabbedPane();

		add(tabbedPane, BorderLayout.CENTER);
		}


	public PanelStationMeteo openNewTab(MeteoServiceWrapper_I meteoServiceRemote)
		{
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

		this.setVisible(true);
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
	private long oldX;
	// private PanelGraphe newTab;
	private List<PanelStationMeteo> graphList;

	}
