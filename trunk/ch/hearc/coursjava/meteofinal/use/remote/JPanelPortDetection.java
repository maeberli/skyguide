package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.Box;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import net.miginfocom.swing.MigLayout;

import ch.hearc.coursjava.meteofinal.com.real.com.MeteoPortDetectionService;
import ch.hearc.coursjava.meteofinal.meteo.MeteoPortDetectionServiceFactory;
import ch.hearc.coursjava.meteofinal.meteo.MeteoPortDetectionService_I;

public class JPanelPortDetection extends JPanel {

	JPanelPortDetection(JPanelStationMeteoLocal panelStation) {
		this.panelStation = panelStation;

		excludedPortsList = new ArrayList<String>();
		portsList = new ArrayList<String>();
		foundStationsList = new ArrayList<String>();

		geometry();
		control();
		appearance();
	}

	private void geometry() {
		setOpaque(false);
		btnAddToExcluded = new JButton("Exclure >>>");
		btnRemFromExcluded = new JButton("<<< Autoriser");
		btnAutoDetect = new JButton("Auto-Detect Stations");
		allPortsListModel = new DefaultListModel<String>();
		excludedPortsListModel = new DefaultListModel<String>();
		foundStationsListModel = new DefaultListModel<String>();

		addAllPortsToJList();

		jListAllPorts
				.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);

		jListExcludedPorts = new JList<String>();
		jListExcludedPorts.setModel(excludedPortsListModel);

		jListFoundStations = new JList<String>();
		jListFoundStations.setModel(foundStationsListModel);
	}

	private void addAllPortsToJList() {
		List<String> ports = detectionService.findPortSerie();
		jListAllPorts = new JList<String>();
		jListAllPorts.setModel(allPortsListModel);
		for (Object object : ports) {
			allPortsListModel.addElement(object.toString());
			portsList.add(object.toString());
		}
	}

	private void control() {
		btnAddToExcluded.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {

				for (Object object : jListAllPorts.getSelectedValuesList()) {
					if (!excludedPortsListModel.contains(object)) {
						allPortsListModel.removeElement(object);
						excludedPortsListModel.addElement(object.toString());
						excludedPortsList.add(object.toString());
					}
					jListAllPorts.setSelectedIndex(allPortsListModel.getSize() - 1);
				}
			}
		});
		btnRemFromExcluded.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {

				for (Object object : jListExcludedPorts.getSelectedValuesList()) {
					if (!allPortsListModel.contains(object)) {
						excludedPortsListModel.removeElement(object);
						allPortsListModel.addElement(object.toString());
						excludedPortsList.remove(object.toString());
					}
					jListExcludedPorts.setSelectedIndex(excludedPortsListModel
							.getSize() - 1);
				}
			}
		});

		btnAutoDetect.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				 List<String> stations =
				 detectionService.findPortNameMeteo(excludedPortsList);
				 
				for (String station : stations) {
					if (!foundStationsListModel.contains(station)) {
						foundStationsList.add(station);
						foundStationsListModel.addElement(station);
						if(panelStation.getComboBoxModel().getIndexOf(station) == -1)
							{
							panelStation.getPortsComboBox().addItem(station);
							}
					}
				}
			}
		});
	}

	private void appearance() {
		setLayout(new MigLayout("flowx, fillx, filly", "[grow,left][grow,fill,][grow,right]", ""));

		/*JPanel panelNorth = new JPanel();
		panelNorth.setOpaque(false);
		panelNorth.setLayout(new MigLayout("flowx, fillx, filly",
				"[center][grow, fill, right]", "[center]"));

		panelNorth.add(btnAutoDetect);*/
		//panelNorth.add(jListFoundStations, "w 100, h 150");
		//add(panelNorth, "north, span");
		add(new JLabel("Ports COM branchés"), "spanx");
		add(jListAllPorts, "w 100, h 300, grow");
		add(btnAutoDetect, "flowy, cell 1 0");
		add(btnAddToExcluded, "flowy, cell 1 1");
		add(btnRemFromExcluded, "cell 1 1");
		add(new JLabel("Ports COM exclus"), "cell 2 0");
		add(jListExcludedPorts, "w 100, h 300,grow,cell 2 1");
	}

	// Inputs
	private JPanelStationMeteoLocal panelStation;

	// Tools

	private MeteoPortDetectionService_I detectionService = MeteoPortDetectionServiceFactory
			.create();

	private List<String> portsList;
	private List<String> excludedPortsList;
	private List<String> foundStationsList;

	// Graphic elements
	private JButton btnAutoDetect;
	private JButton btnAddToExcluded;
	private JButton btnRemFromExcluded;
	// private JButton btnConfirmSelectedStations;

	private DefaultListModel<String> allPortsListModel;
	private DefaultListModel<String> excludedPortsListModel;
	private DefaultListModel<String> foundStationsListModel;
	private JList<String> jListAllPorts;
	private JList<String> jListExcludedPorts;
	private JList<String> jListFoundStations;
}
