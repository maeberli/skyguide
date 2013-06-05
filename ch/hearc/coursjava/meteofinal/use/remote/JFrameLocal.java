package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.rmi.RemoteException;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.JTabbedPane;

import ch.hearc.coursjava.meteofinal.reseau.AfficheurServiceWrapper_I;

public class JFrameLocal extends JFrame {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameLocal() {
		mapInUseStations = new HashMap<String, Boolean>();
		geometrie();
		controle();
		apparence();
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public void openNewTab() {
		tabbedPane.add("Nouvelle station météo", new JPanelStationMeteoLocal(
				this));
	}

	public void deleteInUsePortsInOtherPanels(JPanelStationMeteoLocal portUser, String portInUse) {
		Component panels[] = tabbedPane.getComponents();
		for (Component otherPanel : panels) {
			if (otherPanel != portUser) {
				JPanelStationMeteoLocal panel = (JPanelStationMeteoLocal)otherPanel;
				panel.getComboBoxModel().removeElement(portInUse);
			}
		}
	}

	public void majTitle(JPanelStationMeteoLocal panelStationMeteoLocal,
			String title) {
		int counter = 0;
		for (Component c : tabbedPane.getComponents()) {
			JPanelStationMeteoLocal panelStationMeteoLocal2 = (JPanelStationMeteoLocal) c;
			if (panelStationMeteoLocal == panelStationMeteoLocal2) {
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

	public Map<String, Boolean> getPortInUseMap() {
		return mapInUseStations;
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void geometrie() {
		setLayout(new BorderLayout());
		tabbedPane = new JTabbedPane();
		setMinimumSize(new Dimension(1100,600));

		add(tabbedPane, BorderLayout.CENTER);

		tabbedPane.add("Station météo", new JPanelStationMeteoLocal(this));
	}

	private void controle() {
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		// Enlever les onglets du client sur le serveur.
		addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent event) {
				for (Component c : tabbedPane.getComponents()) {
					JPanelStationMeteoLocal panelStationMeteoLocal = (JPanelStationMeteoLocal) c;

					AfficheurServiceWrapper_I afficheurService = panelStationMeteoLocal
							.getAfficheurService();
					if (afficheurService != null) {
						try {
							afficheurService.removeTab();
						} catch (RemoteException e) {
						}
					}
				}
			}
		});
	}

	private void apparence() {
		setTitle("Stations météto locales");
		setSize(800, 400);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		setLocation((int) ((dim.getWidth() - getWidth()) / 2),
				(int) ((dim.getHeight() - getHeight()) / 2));

		setVisible(true);
		setIconImage(ImageTools.loadJar("ressources/icon.png", true));
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private JTabbedPane tabbedPane;
	private Map<String, Boolean> mapInUseStations;
}
