package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JRadioButton;

public class JDialogNetworkInterface extends JDialog {
	public JDialogNetworkInterface()
	{
		try {
			networkInterfaces = ListOfInterfaces.getAllNetworkInterfaces();
		} catch (SocketException e) {
		}

		labelNetworkInterfaces = new LinkedList<JRadioButton>();
		addressesByNetworkInterfaces = new LinkedList<JComboBox<InetAddress>>();

		inetAddressSelected = null;

		setGeometry();
		setControl();
		setStyle();
	}

	private void setGeometry() {
		int counter = 0;

		ButtonGroup buttonGroup = new ButtonGroup();

		for (NetworkInterface networkInterface : networkInterfaces) {
			if (networkInterface.getInetAddresses().hasMoreElements()) {
				counter++;
				JRadioButton labelNetworkInterface = new JRadioButton(networkInterface.getDisplayName());
				buttonGroup.add(labelNetworkInterface);
				labelNetworkInterfaces.add(labelNetworkInterface);

				JComboBox<InetAddress> addressesByNetworkInterface = new JComboBox<InetAddress>();
				addressesByNetworkInterfaces.add(addressesByNetworkInterface);

				List<InetAddress> addresses = ListOfInterfaces.getAllAdresses(networkInterface);
				if (addresses != null) {
					for (InetAddress inetAddress : addresses) {
						addressesByNetworkInterface.addItem(inetAddress);
					}
				}
			}
		}

		setLayout(new GridLayout(counter * 2 + 3, 1, 10, 10));

		ListIterator<JRadioButton> it1 = labelNetworkInterfaces.listIterator();
		ListIterator<JComboBox<InetAddress>> it2 = addressesByNetworkInterfaces.listIterator();

		while (it1.hasNext()) {
			add(it1.next());
			add(it2.next());
		}

		labelNetworkInterfaces.get(0).setSelected(true);

		information = new JLabel(NOT_OK);
		information.setForeground(Color.RED);
		add(information);

		select = new JButton("Séléctionner");
		add(select);

		ok = new JButton("Ok");
		add(ok);
	}

	private void setControl() {
		setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);

		select.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				int counter = 0;
				for (JRadioButton radioButton : labelNetworkInterfaces) {
					if (radioButton.isSelected()) {
						inetAddressSelected = (InetAddress)addressesByNetworkInterfaces.get(counter).getSelectedItem();

						information.setText(OK + inetAddressSelected.getHostAddress());
						information.setForeground(Color.GREEN);

						break;
					}

					counter++;
				}
			}
		});

		ok.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				if (inetAddressSelected == null) {
					information.setText(ERROR);
				}
				else {
					setVisible(false);
				}
			}
		});

		addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent event) {
				if (inetAddressSelected == null) {
					information.setText(ERROR);
				}
				else {
					setVisible(false);
				}
			}
		});
	}

	private void setStyle() {
		setTitle("Sélétionner la bonne interface réseau");
		setLocation(100, 10);
		setSize(350, 450);
		setModal(true);

		setVisible(true);
	}

	public InetAddress getInetAddressSelected() {
		return inetAddressSelected;
	}

	private List<NetworkInterface> networkInterfaces;
	private List<JRadioButton> labelNetworkInterfaces;
	private List<JComboBox<InetAddress>> addressesByNetworkInterfaces;

	private JLabel information;
	private JButton select;
	private JButton ok;

	private InetAddress inetAddressSelected;

	private static final String NOT_OK = "Séléctionner une adresse IP !";
	private static final String ERROR = "Séléctiooner une adresse IP avant de quitter !";
	private static final String OK = "Votre séléction: ";
}
