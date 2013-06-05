
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.Dimension;
import java.awt.Toolkit;

import javax.swing.JDialog;

public class JFramePortDetection extends JDialog
	{

	public JFramePortDetection(JPanelStationMeteoLocal panelStation)
		{
		setModal(true);
		setContentPane(new JPanelPortDetection(panelStation));
		setSize(500, 300);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		setLocation((int)((dim.getWidth() - getWidth()) / 2), (int)((dim.getHeight() - getHeight()) / 2));
		setVisible(true);
		}
	}
