
package ch.hearc.coursjava.meteofinal.afficheur.simulateur.vue;

import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.rmi.RemoteException;

import javax.swing.JFrame;
import javax.swing.JSlider;

import ch.hearc.coursjava.meteofinal.afficheur.simulateur.moo.AfficheurServiceMOO;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;

public class JFrameAfficheurService extends JFrame
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameAfficheurService(AfficheurServiceMOO afficheurServiceMOO, MeteoServiceOptions meteoServiceOptions)
		{
		this.afficheurServiceMOO = afficheurServiceMOO;
		this.meteoServiceOptions = meteoServiceOptions;

		geometry();
		control();
		apparence();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public void refresh()
		{
		panelRoot.update();
		}

	public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions)
		{
		this.meteoServiceOptions = meteoServiceOptions;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void geometry()
		{
		GridLayout gridLayout = new GridLayout(2, 1);
		setLayout(gridLayout);

		sliderTemperatureDT = new JSlider(1000, 10000, 1000);

		panelRoot = new JPanelRoot(afficheurServiceMOO);
		add(panelRoot);
		add(sliderTemperatureDT);
		}

	private void control()
		{
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		// Polling
		Thread thread = new Thread(new Runnable()
			{

				@Override
				public void run()
					{
					while(true)
						{
						System.out.println("Polling!");
						sliderTemperatureDT.setValue((int)meteoServiceOptions.getTemperatureDT());
						try
							{
							Thread.sleep(1000);
							}
						catch (InterruptedException e)
							{
							}
						}
					}
			});
		thread.start();

		sliderTemperatureDT.addMouseListener(new MouseAdapter()
			{

				@Override
				public void mouseReleased(MouseEvent event)
					{
					meteoServiceOptions.setTemperatureDT(sliderTemperatureDT.getValue());
					try
						{
						afficheurServiceMOO.setMeteoServiceOptions(meteoServiceOptions);
						}
					catch (RemoteException e)
						{
						}
					}
			});
		}

	private void apparence()
		{
		setTitle(afficheurServiceMOO.getTitre());
		setSize(500, 550);
		setResizable(false);
		setVisible(true);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Inputs
	private AfficheurServiceMOO afficheurServiceMOO;

	// Tools
	private JPanelRoot panelRoot;
	private JSlider sliderTemperatureDT;

	private MeteoServiceOptions meteoServiceOptions;

	}
