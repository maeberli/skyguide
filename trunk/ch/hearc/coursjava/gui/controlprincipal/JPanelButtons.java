
package ch.hearc.coursjava.gui.controlprincipal;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;

/**
 *
 * @author Diego
 *
 */

public class JPanelButtons extends JPanel
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JPanelButtons(JPanelDessin dessin)
		{
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
		start.addActionListener(new ActionListener()
			{

				@Override
				public void actionPerformed(ActionEvent arg0)
					{
					panelDessin.startAnimation();
					changeStateButtons();
					}
			});

		stop.addActionListener(new ActionListener()
			{

				@Override
				public void actionPerformed(ActionEvent arg0)
					{
					panelDessin.stopAnimation();
					changeStateButtons();
					}
			});

		}

	private void geometrie()
		{
		this.setLayout(new FlowLayout(FlowLayout.CENTER));

		start = new JButton("Start");
		stop = new JButton("Stop");
		stop.setEnabled(false);

		add(start);
		add(stop);

		}

	private void changeStateButtons()
		{
		start.setEnabled(!start.isEnabled());
		stop.setEnabled(!stop.isEnabled());
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	//Inputs
	private JPanelDessin panelDessin;

	//Tools
	private JButton start;
	private JButton stop;
	}

