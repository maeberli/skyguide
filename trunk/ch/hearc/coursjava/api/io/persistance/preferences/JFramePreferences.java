
package ch.hearc.coursjava.api.io.persistance.preferences;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.prefs.Preferences;

import javax.swing.JFrame;

public class JFramePreferences extends JFrame
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFramePreferences()
		{
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

	private void savePreferences()
		{
		PREFERENCES.putInt(POSITION_X, (int)this.getLocation().getX());
		PREFERENCES.putInt(POSITION_Y, (int)this.getLocation().getY());
		}

	private void loadPreferences()
		{
		int positionX = PREFERENCES.getInt(POSITION_X, 0); //2ème argument : valeur par défaut
		int positionY = PREFERENCES.getInt(POSITION_Y, 0); //2ème argument : valeur par défaut
		this.setLocation(positionX, positionY);
		}

	private void geometrie()
		{
		// rien
		}

	private void controle()
		{
		this.addWindowListener(new WindowAdapter()
			{

				@Override
				public void windowClosing(WindowEvent event)
					{
					savePreferences();
					System.exit(0); // 0 normal, -1 anormal
					}

			});
		}

	private void apparence()
		{
		loadPreferences();
		this.setSize(200, 300);
		this.setTitle("Preferences");
		this.setVisible(true);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	private static final Preferences PREFERENCES = Preferences.userNodeForPackage(JFramePreferences.class);
	//private static final Preferences PREFERENCES = Preferences.systemNodeForPackage(JFramePersistance.class);
	private static final String POSITION_X = "X";
	private static final String POSITION_Y = "Y";

	}
