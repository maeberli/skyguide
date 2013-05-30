
package ch.hearc.coursjava.gui.controlprincipal;

import javax.swing.JSplitPane;

/**
 *
 * @author Diego
 *
 */

public class JPanelControl extends JSplitPane
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JPanelControl(JPanelDessin dessin,int n)
		{
		super(JSplitPane.VERTICAL_SPLIT);
		panelDessin = dessin;
		this.n = n;
		geometrie();
		controle();
		apparence();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void apparence()
		{
		//Rien
		}

	private void controle()
		{
		//Rien
		}

	private void geometrie()
		{
		panelButtons = new JPanelButtons(panelDessin);
		panelSliderSpinner = new JPanelSliderSpinner(panelDessin, n);

		setTopComponent(panelButtons);
		setBottomComponent(panelSliderSpinner);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	//Inputs
	private int n;
	private JPanelDessin panelDessin;

	//Tools
	private JPanelButtons panelButtons;
	private JPanelSliderSpinner panelSliderSpinner;

	}
