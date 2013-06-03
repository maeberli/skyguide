
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.rmi.RemoteException;

import javax.swing.Box;
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

		Box box = Box.createHorizontalBox();
		box.setSize(new Dimension(70,50));
		box.add(startStop);
		meteoServiceRemote.add(box);

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
		affichageOptions.setLayout(new GridLayout(6, 2));


		labelMinT = new JLabel("temperature minimum");
		labelMaxT = new JLabel("temperature maximum");
		labelMinP = new JLabel("Pression minimum");
		labelMaxP = new JLabel("pression maximum");
		labelMinA = new JLabel("altitude minimum");
		labelMaxA = new JLabel("altitude maximum");

		affichageOptions.add(new JLabel("temperature minimum"));
		affichageOptions.add(labelMinT);
		affichageOptions.add(new JLabel("temperature maximum"));
		affichageOptions.add(labelMaxT);
		affichageOptions.add(new JLabel("pression minimum"));
		affichageOptions.add(labelMinP);
		affichageOptions.add(new JLabel("pression maximum"));
		affichageOptions.add(labelMaxP);
		affichageOptions.add(new JLabel("altitude minimum"));
		affichageOptions.add(labelMinA);
		affichageOptions.add(new JLabel("altitude maximum"));
		affichageOptions.add(labelMaxA);

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

	public void updateAffichageOptions()
		{
		minT = (float)panelGrapheTemperature.getGraphe().getSeriesMemoire().getMinY();
		maxT = (float)panelGrapheTemperature.getGraphe().getSeriesMemoire().getMaxY();
		minP = (float)panelGraphePression.getGraphe().getSeriesMemoire().getMinY();
		maxP = (float)panelGraphePression.getGraphe().getSeriesMemoire().getMaxY();
		minA = (float)panelGrapheAltitude.getGraphe().getSeriesMemoire().getMinY();
		maxA = (float)panelGrapheAltitude.getGraphe().getSeriesMemoire().getMaxY();

		labelMinT.setText(String.valueOf(minT));
		labelMaxT.setText(String.valueOf(maxT));
		labelMinP.setText(String.valueOf(minP));
		labelMaxP.setText(String.valueOf(maxP));
		labelMinA.setText(String.valueOf(minA));
		labelMaxA.setText(String.valueOf(maxA));
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

	private float minT = 0;
	private float maxT = 0;
	private float minP = 0;
	private float maxP = 0;
	private float minA = 0;
	private float maxA = 0;

	private JLabel labelMinT;
	private JLabel labelMaxT;
	private JLabel labelMinP;
	private JLabel labelMaxP;
	private JLabel labelMinA;
	private JLabel labelMaxA;

	}
