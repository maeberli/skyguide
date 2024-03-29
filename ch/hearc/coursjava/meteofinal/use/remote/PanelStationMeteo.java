
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.math.RoundingMode;
import java.rmi.RemoteException;
import java.text.DecimalFormat;

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

	public void majStartStop(String startStop)
		{
		System.out.println("TEST2" + startStop);

		if (this.startStop.getText() == "Start")
			{
			this.startStop.setText("Stop");
			isConnecting.setForeground(Color.GREEN);
			isRunning.setForeground(Color.GREEN);
			}
		else
			{
			this.startStop.setText("Start");
			isConnecting.setForeground(Color.RED);
			isRunning.setForeground(Color.RED);
			}
		}

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

		meteoAffichageOptionsPanel.add(new JPanelTitle("Statistiques"), BorderLayout.NORTH);

		JPanel affichageOptions = new JPanel();
		affichageOptions.setLayout(new GridLayout(6, 1));


		labelMinT = new JLabel("temperature minimum");
		labelMaxT = new JLabel("temperature maximum");
		labelMinP = new JLabel("Pression minimum");
		labelMaxP = new JLabel("pression maximum");
		labelMinA = new JLabel("altitude minimum");
		labelMaxA = new JLabel("altitude maximum");

		Box tMinBox = Box.createHorizontalBox();
		Box tMaxBox = Box.createHorizontalBox();
		Box pMinBox = Box.createHorizontalBox();
		Box pMaxBox = Box.createHorizontalBox();
		Box aMinBox = Box.createHorizontalBox();
		Box aMaxBox = Box.createHorizontalBox();
		
		tMinBox.add(new JLabel("Temperature minimum: "));
		tMinBox.add(Box.createHorizontalGlue());
		tMinBox.add(labelMinT);
		tMaxBox.add(new JLabel("Temperature maximum: "));
		tMaxBox.add(Box.createHorizontalGlue());
		tMaxBox.add(labelMaxT);
		pMinBox.add(new JLabel("Pression minimum: "));
		pMinBox.add(Box.createHorizontalGlue());
		pMinBox.add(labelMinP);
		pMaxBox.add(new JLabel("Pression maximum: "));
		pMaxBox.add(Box.createHorizontalGlue());
		pMaxBox.add(labelMaxP);
		aMinBox.add(new JLabel("Altitude minimum: "));
		aMinBox.add(Box.createHorizontalGlue());
		aMinBox.add(labelMinA);
		aMaxBox.add(new JLabel("Altitude maximum: "));;
		aMaxBox.add(Box.createHorizontalGlue());
		aMaxBox.add(labelMaxA);
		
		affichageOptions.add(tMinBox);
		affichageOptions.add(tMaxBox);
		affichageOptions.add(pMinBox);
		affichageOptions.add(pMaxBox);
		affichageOptions.add(aMinBox);
		affichageOptions.add(aMaxBox);

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
		df = new DecimalFormat("##.##");
		df.setRoundingMode(RoundingMode.DOWN);
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


		labelMinT.setText(String.valueOf(df.format(minT) + "�C"));
		labelMaxT.setText(String.valueOf(df.format(maxT) + "�C"));
		labelMinP.setText(String.valueOf(df.format(minP) + "mB"));
		labelMaxP.setText(String.valueOf(df.format(maxP) + "mB"));
		labelMinA.setText(String.valueOf(df.format(minA) + "m"));
		labelMaxA.setText(String.valueOf(df.format(maxA) + "m"));
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
	private DecimalFormat df;

	private PanelGraphe panelGrapheTemperature;
	private PanelGraphe panelGraphePression;
	private PanelGraphe panelGrapheAltitude;

	private JButton startStop;
	private JLabel isConnecting;
	private JLabel isRunning;

	private JSlider sliderTemperatureDT;
	private JSlider sliderPressionDT;
	private JSlider sliderAltitudeDT;

	private float minT = 1000;
	private float maxT = 1000;
	private float minP = 1000;
	private float maxP = 1000;
	private float minA = 1000;
	private float maxA = 1000;

	private JLabel labelMinT;
	private JLabel labelMaxT;
	private JLabel labelMinP;
	private JLabel labelMaxP;
	private JLabel labelMinA;
	private JLabel labelMaxA;

	}
