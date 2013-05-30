
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.rmi.RemoteException;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;

import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper_I;

public class PanelStationMeteo extends JPanel
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public PanelStationMeteo(MeteoServiceWrapper_I meteoServiceRemote)
		{
		this.meteoServiceRemote = meteoServiceRemote;

		geometrie();
		controle();
		apparence();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public void geometrie()
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
		meteoServiceRemote.setLayout(new GridLayout(3, 1, 10, 10));

		meteoServicePanel.add(meteoServiceRemote, BorderLayout.CENTER);

		startStop = new JButton("Stop");
		isConnecting = new JLabel("Connecting");
		isConnecting.setForeground(Color.GREEN);
		isRunning = new JLabel("Running");
		isRunning.setForeground(Color.GREEN);

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

		JPanel affichageOptions = new JPanel();
		affichageOptions.setLayout(new GridLayout(1, 1));

		meteoAffichageOptionsPanel.add(affichageOptions);

		mainPanel.add(panelGrapheTemperature);
		mainPanel.add(panelGraphePression);
		mainPanel.add(panelGrapheAltitude);
		mainPanel.add(meteoServicePanel);
		mainPanel.add(meteoServiceOptionsPanel);
		mainPanel.add(meteoAffichageOptionsPanel);

		add(mainPanel, BorderLayout.CENTER);
		}

	public void controle()
		{
		startStop.addActionListener(new ActionListener()
			{

				@Override
				public void actionPerformed(ActionEvent event)
					{
					if (startStop.getText() == "Start")
						{
						startStop.setText("Stop");
						isConnecting.setForeground(Color.GREEN);
						isRunning.setForeground(Color.GREEN);
						MeteoServiceOptions meteoServiceOptions = new MeteoServiceOptions(1000, 1000, 1000, 1000);
						try
							{
							PanelStationMeteo.this.meteoServiceRemote.start(meteoServiceOptions);
							}
						catch (RemoteException e)
							{
							}
						}
					else
						{
						startStop.setText("Start");
						try
							{
							PanelStationMeteo.this.meteoServiceRemote.stop();
							isConnecting.setForeground(Color.RED);
							isRunning.setForeground(Color.RED);
							}
						catch (RemoteException e)
							{
							}
						}
					}
			});

		sliderTemperatureDT.addMouseListener(new MouseAdapter()
			{

				@Override
				public void mouseReleased(MouseEvent event)
					{
					int temperatureDT = sliderTemperatureDT.getValue();
					int pressionDT = sliderPressionDT.getValue();
					int altitudeDT = sliderAltitudeDT.getValue();

					MeteoServiceOptions meteoServiceOptions = new MeteoServiceOptions(altitudeDT, pressionDT, temperatureDT);

					try
						{
						PanelStationMeteo.this.meteoServiceRemote.setMeteoServiceOptions(meteoServiceOptions);
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
					int temperatureDT = sliderTemperatureDT.getValue();
					int pressionDT = sliderPressionDT.getValue();
					int altitudeDT = sliderAltitudeDT.getValue();

					MeteoServiceOptions meteoServiceOptions = new MeteoServiceOptions(altitudeDT, pressionDT, temperatureDT);

					try
						{
						PanelStationMeteo.this.meteoServiceRemote.setMeteoServiceOptions(meteoServiceOptions);
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
					int temperatureDT = sliderTemperatureDT.getValue();
					int pressionDT = sliderPressionDT.getValue();
					int altitudeDT = sliderAltitudeDT.getValue();

					MeteoServiceOptions meteoServiceOptions = new MeteoServiceOptions(altitudeDT, pressionDT, temperatureDT);

					try
						{
						PanelStationMeteo.this.meteoServiceRemote.setMeteoServiceOptions(meteoServiceOptions);
						}
					catch (RemoteException e)
						{
						}
					}
			});
		}

	public void apparence()
		{

		}

	public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions)
		{
		sliderTemperatureDT.setValue((int)meteoServiceOptions.getTemperatureDT());
		sliderPressionDT.setValue((int)meteoServiceOptions.getPressionDT());
		sliderAltitudeDT.setValue((int)meteoServiceOptions.getAltitudeDT());
		}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	public PanelGraphe getPanelGrapheTemperature()
		{
		return panelGrapheTemperature;
		}

	public PanelGraphe getPanelGraphePression()
		{
		return panelGraphePression;
		}

	public PanelGraphe getPanelGrapheAltitude()
		{
		return panelGrapheAltitude;
		}

	public MeteoServiceWrapper_I getMeteoServiceWrapper()
		{
		return meteoServiceRemote;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private MeteoServiceWrapper_I meteoServiceRemote;

	private PanelGraphe panelGrapheTemperature;
	private PanelGraphe panelGraphePression;
	private PanelGraphe panelGrapheAltitude;

	private JButton startStop;
	private JLabel isConnecting;
	private JLabel isRunning;

	private JSlider sliderTemperatureDT;
	private JSlider sliderPressionDT;
	private JSlider sliderAltitudeDT;
	}
