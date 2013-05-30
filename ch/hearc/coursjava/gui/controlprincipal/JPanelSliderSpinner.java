
package ch.hearc.coursjava.gui.controlprincipal;

import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JSpinner;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/**
 *
 * @author Diego
 *
 */

public class JPanelSliderSpinner extends JPanel
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JPanelSliderSpinner(JPanelDessin dessin,int n)
		{
		this.n = n;
		panelDessin = dessin;
		geometrie();
		controle();
		apparence();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void apparence()
		{
		//Rien
		}

	private void controle()
		{
		spinner.addChangeListener(new ChangeListener()
			{

				@Override
				public void stateChanged(ChangeEvent arg0)
					{
					int value = (Integer)spinner.getValue();

					if (value < N_MIN)
						{
						value = N_MIN;
						}
					else if (value > N_MAX)
						{
						value = N_MAX;
						}
					JPanelSliderSpinner.this.panelDessin.changeDT(value);
					JPanelSliderSpinner.this.slider.setValue(value);
					}
			});

		slider.addChangeListener(new ChangeListener()
			{

				@Override
				public void stateChanged(ChangeEvent arg0)
					{
					int value = slider.getValue();

					if (value < N_MIN)
						{
						value = N_MIN;
						}
					else if (value > N_MAX)
						{
						value = N_MAX;
						}
					JPanelSliderSpinner.this.panelDessin.changeDT(value);
					JPanelSliderSpinner.this.spinner.setValue(value);
					}
			});
		}

	private void geometrie()
		{
		this.setLayout(new FlowLayout(FlowLayout.CENTER));

		spinner = new JSpinner();
		spinner.setValue(n);

		Dimension dim = new Dimension(50, 20);
		spinner.setPreferredSize(dim);
		spinner.setMinimumSize(dim);
		spinner.setMaximumSize(dim);

		slider = new JSlider(SwingConstants.HORIZONTAL, N_MIN, N_MAX, n);

		add(spinner);
		add(slider);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	//Inputs
	private JPanelDessin panelDessin;
	//tools
	private final static int N_MIN = 1;
	private final static int N_MAX = 100;
	private JSlider slider;
	private JSpinner spinner;
	private int n;
	}
