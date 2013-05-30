
package ch.hearc.coursjava.gui.controlprincipal;

import java.awt.BorderLayout;

import javax.swing.JFrame;

/**
 *
 * @author Diego
 *
 */
public class JFrameCP extends JFrame
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameCP(int n)
		{
		this.n = n;
		geometrie();
		control();
		apparence();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void control()
		{
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		}

	private void geometrie()
		{
		this.setLayout(new BorderLayout());

		panelDessin = new JPanelDessin(n);
		panelControl = new JPanelControl(panelDessin,n);

		add(panelDessin,BorderLayout.CENTER);
		add(panelControl,BorderLayout.SOUTH);
		}

	private void apparence()
		{
		setSize(800, 600);
		setTitle("Contrôle Principale");
		setLocation(30, 30);
		setResizable(true);
		this.setVisible(true);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	//Tools
	private JPanelDessin panelDessin;
	private JPanelControl panelControl;
	private int n;
	}
