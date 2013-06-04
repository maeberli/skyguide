package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.Dialog;
import java.awt.Dialog.ModalExclusionType;

import javax.swing.JDialog;
import javax.swing.JFrame;

public class JFramePortDetection extends JDialog {

	public JFramePortDetection(JPanelStationMeteoLocal panelStation) {
		setModal(true);
		setContentPane(new JPanelPortDetection(panelStation));
		setSize(500, 300);
		setVisible(true);
	}
}
