
package ch.hearc.coursjava.api.io.persistance.properties;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

import javax.swing.JFrame;

public class JFrameProperties extends JFrame
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameProperties()
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

	private void saveProperties() throws IOException
		{
		FileOutputStream fos = new FileOutputStream(FILE_PROPERTIES);
		BufferedOutputStream bos = new BufferedOutputStream(fos);
		Properties propertie = new Properties();
		propertie.setProperty(POSITION_X, "" + (int)this.getLocation().getX());
		propertie.setProperty(POSITION_Y, "" + (int)this.getLocation().getY());
		propertie.store(bos, JFrameProperties.class.getSimpleName());

		bos.close();
		fos.close();
		}

	private void loadProperties() throws IOException
		{
		FileInputStream fis = new FileInputStream(FILE_PROPERTIES);
		BufferedInputStream bis = new BufferedInputStream(fis);
		Properties propertie = new Properties();
		propertie.load(bis);
		int positionX =  Integer.valueOf(propertie.getProperty(POSITION_X));
		int positionY = Integer.valueOf(propertie.getProperty(POSITION_Y));
		this.setLocation(positionX, positionY);

		bis.close();
		fis.close();
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
					try
						{
						saveProperties();
						}
					catch (IOException e)
						{
						System.err.println("Options non sauvées");
						}
					System.exit(0); // 0 normal, -1 anormal
					}

			});
		}

	private void apparence()
		{

		try
			{
			loadProperties();
			}
		catch (IOException e)
			{
			System.err.println("Option non Lues");
			setLocation(0, 0);
			}

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

	//private static final Preferences PREFERENCES = Preferences.userNodeForPackage(JFrameProperties.class);
	//private static final Preferences PREFERENCES = Preferences.systemNodeForPackage(JFramePersistance.class);
	private static final String POSITION_X = "X";
	private static final String POSITION_Y = "Y";
	private static final String FILE_PROPERTIES = "Options.txt";

	}
