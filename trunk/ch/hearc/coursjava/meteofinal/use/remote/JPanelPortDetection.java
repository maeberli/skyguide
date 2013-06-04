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

	JPanelPortDetection(JFrameLocal frameLocal) {
		this.frameLocal = frameLocal;

		excludedPortsList = new ArrayList<String>();
		portsList = new ArrayList<String>();
		foundStationsList = new ArrayList<String>();

		geometry();
		control();
		appearance();
	}

	public static void main(String[] args) {
		JFrame testFrame = new JFrame();
		testFrame.setContentPane(new JPanelPortDetection(null));
		testFrame.setSize(300, 500);
		testFrame.setResizable(false);
		testFrame.setVisible(true);
	}

	private void geometry() {
		setLayout(new MigLayout("fillx, filly", "[grow,fill]", ""));
		setOpaque(false);
		btnAddToExcluded = new JButton(">>>>>");
		btnRemFromExcluded = new JButton("<<<<<");
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
				// List<String> stations =
				// detectionService.findPortNameMeteo(excludedPortsList);

				List<String> list = new ArrayList<String>();

				list.add("test1");
				list.add("test2");
				list.add("test3");
				list.add("test4");
				for (String station : list) {
					if (!foundStationsListModel.contains(station)) {
						foundStationsList.add(station);
						foundStationsListModel.addElement(station);
					}
				}
			}
		});
	}

	private void appearance() {
		JPanel panelNorth = new JPanel();
		panelNorth.setOpaque(false);
		panelNorth.setLayout(new MigLayout("flowx, fillx, filly",
				"[center][grow, fill, right]", "[center]"));

		panelNorth.add(btnAutoDetect, "");
		panelNorth.add(jListFoundStations, "w 100, h 150");
		add(panelNorth, "north");
		add(jListAllPorts, "west, w 100, h 150");
		add(btnAddToExcluded);
		add(btnRemFromExcluded);
		add(jListExcludedPorts, "east, w 100, h 150");
	}

	// Inputs
	private JFrameLocal frameLocal;

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
