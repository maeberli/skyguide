
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.net.InetAddress;
import java.rmi.RemoteException;
import java.util.Map;

import javax.swing.Box;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JSpinner;
import javax.swing.JTextField;

import ch.hearc.coursjava.meteofinal.afficheur.AffichageOptions;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceFactory;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.MeteoService_I;
import ch.hearc.coursjava.meteofinal.meteo.exception.MeteoServiceException;
import ch.hearc.coursjava.meteofinal.meteo.listener.MeteoListener_I;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;
import ch.hearc.coursjava.meteofinal.reseau.AfficheurManager_I;
import ch.hearc.coursjava.meteofinal.reseau.AfficheurServiceWrapper_I;
import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper_I;

import com.bilat.tools.reseau.rmi.IdTools;
import com.bilat.tools.reseau.rmi.RmiTools;
import com.bilat.tools.reseau.rmi.RmiURL;

public class JPanelStationMeteoLocal extends JPanel
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JPanelStationMeteoLocal(JFrameLocal frameLocal)
		{
		meteoService = null;
		afficheurService = null;

		this.frameLocal = frameLocal;

		geometrie();
		controle();
		apparence();

		meteoServiceOptions = new MeteoServiceOptions(1000, 1000, 1000);
		// affichageOptions = new AffichageOptions(100, "Ceci est un client");
		affichageOptions = null;
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

	public Map<String, Boolean> getPortInUseMap()
		{
		return frameLocal.getPortInUseMap();
		}

	public JComboBox<String> getPortsComboBox()
		{
		return portsCom;
		}

	public DefaultComboBoxModel<String> getComboBoxModel()
		{
		return portsComModel;
		}

	public AfficheurServiceWrapper_I getAfficheurService()
		{
		return afficheurService;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void startStopMeteoServive() throws Exception
		{
		if (afficheurService != null)
			{
			System.out.println("TEST1");
			afficheurService.majStartStop(startStop.getText());
			}

		if (startStop.getText() == "Start")
			{
			if (meteoService == null)
				{
				frameLocal.openNewTab();

				meteoService = MeteoServiceFactory.create(portsCom.getItemAt(portsCom.getSelectedIndex()));

				MeteoServiceWrapper_I meteoServiceWrapper = new MeteoServiceWrapper_I()
					{

						@Override
						public void stop() throws RemoteException
							{
							meteoService.stop();

							startStop.setText("Start");
							isConnecting.setForeground(Color.RED);
							isRunning.setForeground(Color.RED);
							}

						@Override
						public void start(MeteoServiceOptions meteoServiceOptions) throws RemoteException
							{
							meteoService.start(meteoServiceOptions);

							startStop.setText("Stop");
							isConnecting.setForeground(Color.GREEN);
							isRunning.setForeground(Color.GREEN);
							}

						@Override
						public boolean isRunning() throws RemoteException
							{
							return meteoService.isRunning();
							}

						@Override
						public boolean isConnect() throws RemoteException
							{
							return meteoService.isConnect();
							}

						@Override
						public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions) throws RemoteException
							{
							JPanelStationMeteoLocal.this.meteoServiceOptions = meteoServiceOptions;

							sliderTemperatureDT.setValue((int)meteoServiceOptions.getTemperatureDT());
							sliderPressionDT.setValue((int)meteoServiceOptions.getPressionDT());
							sliderAltitudeDT.setValue((int)meteoServiceOptions.getAltitudeDT());

							meteoService.stop();
							meteoService.start(meteoServiceOptions);
							}

						@Override
						public void exitClient() throws RemoteException
							{
							System.exit(0);
							}
					};

				String name = IdTools.createID("METEO_SERVICE_");
				RmiURL rmiUrlMeteoService = new RmiURL(name, inetAddressLocal, RmiTools.PORT_RMI_DEFAUT);
				RmiTools.shareObject(meteoServiceWrapper, rmiUrlMeteoService);

				RmiURL rmiUrlAfficheurManager = new RmiURL(RMI_ID_AFFICHEUR_MANAGER, inetAddressServer, RmiTools.PORT_RMI_DEFAUT);

				AfficheurManager_I afficheurManager = (AfficheurManager_I)RmiTools.connectionRemoteObjectBloquant(rmiUrlAfficheurManager);

				affichageOptions = new AffichageOptions((Integer)points.getValue(), inetAddressLocal.getHostAddress() + " - " + title.getText());
				points.setEnabled(false);
				title.setEnabled(false);
				frameLocal.majTitle(this, affichageOptions.getTitre());

				RmiURL rmiUrlAfficheurService = afficheurManager.createRemoteAfficheurService(affichageOptions, new RmiURL(name, inetAddressLocal, RmiTools.PORT_RMI_DEFAUT));

				afficheurService = (AfficheurServiceWrapper_I)RmiTools.connectionRemoteObjectBloquant(new RmiURL(rmiUrlAfficheurService.getIdObjectRMI(), inetAddressServer, RmiTools.PORT_RMI_DEFAUT));
				afficheurService = (AfficheurServiceWrapper_I)RmiTools.connectionRemoteObjectBloquant(new RmiURL(rmiUrlAfficheurService.getIdObjectRMI(), inetAddressServer, RmiTools.PORT_RMI_DEFAUT));

				meteoService.addMeteoListener(new MeteoListener_I()
					{

						@Override
						public void temperaturePerformed(MeteoEvent event)
							{
							panelGrapheTemperature.getGraphe().addToDataset(event.getTime(), event.getValue());
							panelGrapheTemperature.getGraphe().toAffichage();
							panelGrapheTemperature.repaint();

							try
								{
								afficheurService.printTemperature(event);
								}
							catch (RemoteException e)
								{
								// System.exit(-1);
								}
							}

						@Override
						public void pressionPerformed(MeteoEvent event)
							{
							panelGraphePression.getGraphe().addToDataset(event.getTime(), event.getValue());
							panelGraphePression.getGraphe().toAffichage();
							panelGraphePression.repaint();

							try
								{
								afficheurService.printPression(event);
								}
							catch (RemoteException e)
								{
								// System.exit(-1);
								}
							}

						@Override
						public void altitudePerformed(MeteoEvent event)
							{
							panelGrapheAltitude.getGraphe().addToDataset(event.getTime(), event.getValue());
							panelGrapheAltitude.getGraphe().toAffichage();
							panelGrapheAltitude.repaint();

							try
								{
								afficheurService.printAltitude(event);
								}
							catch (RemoteException e)
								{
								// System.exit(-1);
								}
							}
					});

				try
					{
					meteoService.connect();
					}
				catch (MeteoServiceException e)
					{
					System.err.println("MeteoService error !");
					}
				frameLocal.getPortInUseMap().put(portsCom.getItemAt(portsCom.getSelectedIndex()), true);
				frameLocal.deleteInUsePortsInOtherPanels(this, portsCom.getItemAt(portsCom.getSelectedIndex()));
				meteoService.start(meteoServiceOptions);
				startStop.setText("Stop");
				isConnecting.setForeground(Color.GREEN);
				isRunning.setForeground(Color.GREEN);
				}
			else
				{
				meteoService.start(meteoServiceOptions);
				startStop.setText("Stop");
				isConnecting.setForeground(Color.GREEN);
				isRunning.setForeground(Color.GREEN);
				}
			}
		else
			// Stop
			{
			frameLocal.getPortInUseMap().put(portsCom.getItemAt(portsCom.getSelectedIndex()), false);
			meteoService.stop();
			// meteoService.disconnect();
			startStop.setText("Start");
			isConnecting.setForeground(Color.RED);
			isRunning.setForeground(Color.RED);
			}
		}

	private void geometrie()
		{
		setLayout(new BorderLayout());

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new GridLayout(2, 3, 10, 10));

		panelGrapheTemperature = new PanelGraphe("Temperature", "Temps", "Temperature");
		panelGraphePression = new PanelGraphe("Pression", "Temps", "Pression");
		panelGrapheAltitude = new PanelGraphe("Altitude", "Temps", "Altitude");

		JPanel meteoServicePanel = new JPanel();
		meteoServicePanel.setLayout(new BorderLayout());

		meteoServicePanel.add(new JPanelTitle("Meteo service remote"), BorderLayout.NORTH);

		JPanel meteoServiceRemote = new JPanel();
		meteoServiceRemote.setLayout(new GridLayout(5, 1, 10, 10));

		meteoServicePanel.add(meteoServiceRemote, BorderLayout.CENTER);

		ipServer = new JTextField("Ip du serveur");
		ipServer.setText("localhost");
		// portCom = new JTextField("Port COM");
		// portCom.setText("COM1");

		// String[] ports = { "COM1", "COM2", "COM3", "COM4", "COM7", "COM8" };
		portsComModel = new DefaultComboBoxModel<String>();

		portsCom = new JComboBox<String>(portsComModel);

		openPortDetecButton = new JButton("D�tection ports");

		startStop = new JButton("Start");
		startStop.setEnabled(false);
		startStop.setPreferredSize(new Dimension(10, 10));
		isConnecting = new JLabel("Connecting");
		isConnecting.setForeground(Color.RED);
		isRunning = new JLabel("Running");
		isRunning.setForeground(Color.RED);

		Box box = Box.createHorizontalBox();
		box.add(startStop);
		meteoServiceRemote.add(box);

		meteoServiceRemote.add(new JLabel(" "));
		meteoServiceRemote.add(openPortDetecButton);
		meteoServiceRemote.add(portsCom);
		meteoServiceRemote.add(ipServer);
		meteoServiceRemote.add(startStop);
		meteoServiceRemote.add(isConnecting);
		meteoServiceRemote.add(isRunning);

		JPanel meteoServiceOptionsPanel = new JPanel();
		meteoServiceOptionsPanel.setLayout(new BorderLayout());

		meteoServiceOptionsPanel.add(new JPanelTitle("Meteo service options"), BorderLayout.NORTH);

		JPanel sliders = new JPanel();
		sliders.setLayout(new GridLayout(3, 2, 10, 10));

		sliderTemperatureDT = new JSlider(1000, 10000, 1000);
		sliderPressionDT = new JSlider(1000, 10000, 1000);
		sliderAltitudeDT = new JSlider(1000, 10000, 1000);

		sliders.add(new JLabel("Temperature:"));
		sliders.add(sliderTemperatureDT);
		sliders.add(new JLabel("Pression:"));
		sliders.add(sliderPressionDT);
		sliders.add(new JLabel("Altitude:"));
		sliders.add(sliderAltitudeDT);

		meteoServiceOptionsPanel.add(sliders, BorderLayout.CENTER);

		JPanel meteoAffichageOptionsPanel = new JPanel();
		meteoAffichageOptionsPanel.setLayout(new BorderLayout());

		meteoAffichageOptionsPanel.add(new JPanelTitle("Meteo affichage options"), BorderLayout.NORTH);

		Box boite = Box.createVerticalBox();
		meteoAffichageOptionsPanel.add(boite, BorderLayout.CENTER);

		JPanel affichageOptions = new JPanel();
		affichageOptions.setLayout(new GridLayout(3, 2, 10, 10));

		boite.add(affichageOptions);
		title = new JTextField("Station m�t�o");
		points = new JSpinner();
		points.setValue(1000);

		affichageOptions.add(new JLabel("Titre:"));
		affichageOptions.add(title);
		affichageOptions.add(new JLabel("Points:"));
		affichageOptions.add(points);

		JPanel panelIcon = new JPanel();
		panelIcon.setLayout(new FlowLayout());
		JLabel heARCIcon = new JLabel();
		heARCIcon.setIcon(ImageTools.loadIconJar("ressources/logo_arc.png", true));
		panelIcon.add(heARCIcon);
		boite.add(heARCIcon);

		mainPanel.add(panelGrapheTemperature);
		mainPanel.add(panelGraphePression);
		mainPanel.add(panelGrapheAltitude);
		mainPanel.add(meteoServicePanel);
		mainPanel.add(meteoServiceOptionsPanel);
		mainPanel.add(meteoAffichageOptionsPanel);

		add(mainPanel, BorderLayout.CENTER);
		}

	private void controle()
		{
		openPortDetecButton.addActionListener(new ActionListener()
			{

				@Override
				public void actionPerformed(ActionEvent arg0)
					{
					new JFramePortDetection(JPanelStationMeteoLocal.this);
					if (portsCom.getItemCount() != 0)
						{
						startStop.setEnabled(true);
						}
					}
			});
		startStop.addActionListener(new ActionListener()
			{

				@Override
				public void actionPerformed(ActionEvent event)
					{
					try
						{
						// Seulement si initialisation.
						if (meteoService == null)
							{
							inetAddressServer = InetAddress.getByName(ipServer.getText());
							// inetAddressLocal = InetAddress.getLocalHost();

							JDialogNetworkInterface dialogNetworkInterface = new JDialogNetworkInterface();
							inetAddressLocal = dialogNetworkInterface.getInetAddressSelected();
							}
						// Start or stop MeteoService
						JPanelStationMeteoLocal.this.startStopMeteoServive();
						}
					catch (Exception e)
						{
						System.err.println(e);
						System.exit(-1);
						}
					}
			});

		/* Mettre � jour les JSlider sur le serveur. */
		sliderTemperatureDT.addMouseListener(new MouseAdapter()
			{

				@Override
				public void mouseReleased(MouseEvent event)
					{
					meteoServiceOptions.setTemperatureDT(sliderTemperatureDT.getValue());
					try
						{
						afficheurService.setMeteoServiceOptions(meteoServiceOptions);

						meteoService.stop();
						meteoService.start(meteoServiceOptions);
						}
					catch (RemoteException e)
						{
						}
					}
			});

		sliderPressionDT.addMouseListener(new MouseAdapter()
			{

				@Override
				public void mouseReleased(MouseEvent event)
					{
					meteoServiceOptions.setPressionDT(sliderPressionDT.getValue());
					try
						{
						afficheurService.setMeteoServiceOptions(meteoServiceOptions);

						meteoService.stop();
						meteoService.start(meteoServiceOptions);
						}
					catch (RemoteException e)
						{
						}
					}
			});

		sliderAltitudeDT.addMouseListener(new MouseAdapter()
			{

				@Override
				public void mouseReleased(MouseEvent event)
					{
					meteoServiceOptions.setAltitudeDT(sliderAltitudeDT.getValue());
					try
						{
						afficheurService.setMeteoServiceOptions(meteoServiceOptions);

						meteoService.stop();
						meteoService.start(meteoServiceOptions);
						}
					catch (RemoteException e)
						{
						}
					}
			});
		portsCom.addMouseListener(new MouseAdapter()
			{

				@Override
				public void mouseClicked(MouseEvent arg0)
					{
					if (portsCom.getItemCount() == 0)
						{
						new JFramePortDetection(JPanelStationMeteoLocal.this);

						if (portsCom.getItemCount() != 0)
							{
							startStop.setEnabled(true);
							}
						}
					}
			});
		}

	private void apparence()
		{
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private MeteoService_I meteoService;
	private AfficheurServiceWrapper_I afficheurService;

	private JFrameLocal frameLocal;

	private PanelGraphe panelGrapheTemperature;
	private PanelGraphe panelGraphePression;
	private PanelGraphe panelGrapheAltitude;

	private JButton openPortDetecButton;
	private JButton startStop;
	private JTextField ipServer;
	// private JTextField portCom;

	private JComboBox<String> portsCom;
	private DefaultComboBoxModel<String> portsComModel;

	private JLabel isConnecting;
	private JLabel isRunning;

	private JSlider sliderTemperatureDT;
	private JSlider sliderPressionDT;
	private JSlider sliderAltitudeDT;

	private JTextField title;
	private JSpinner points;

	private InetAddress inetAddressServer;
	private InetAddress inetAddressLocal;

	private MeteoServiceOptions meteoServiceOptions;
	private AffichageOptions affichageOptions;

	private static final String RMI_ID_AFFICHEUR_MANAGER = "AFFICHEUR_MANAGER";
	}
