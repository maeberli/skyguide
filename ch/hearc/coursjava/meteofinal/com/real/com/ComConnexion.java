package ch.hearc.coursjava.meteofinal.com.real.com;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

import javax.swing.ScrollPaneLayout;

import ch.hearc.coursjava.meteofinal.com.logique.MeteoServiceCallback_I;
import ch.hearc.coursjava.meteofinal.com.real.com.trame.TrameDecoder;
import ch.hearc.coursjava.meteofinal.com.real.com.trame.TrameEncoder;
import ch.hearc.coursjava.meteofinal.meteo.exception.MeteoServiceException;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEventType_E;



import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;

public class ComConnexion implements ComConnexions_I {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public ComConnexion(MeteoServiceCallback_I meteoServiceCallback,
			String portName, ComOption comOption) {
		this.comOption = comOption;
		this.portName = portName;
		this.meteoServiceCallback = meteoServiceCallback;
	}

	/*
	 * Must call setMSC(MeteoServiceCallback_I ) right after this constructor is
	 * called!
	 */
	public ComConnexion(String portName, ComOption comOption) {

		this.comOption = comOption;
		this.meteoServiceCallback = null;
		this.portName = portName;
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public void start() throws Exception {
		serialPort.notifyOnDataAvailable(true);
		serialPort.disableReceiveTimeout();
		serialPort.enableReceiveThreshold(1);
		
		serialPort.addEventListener(new SerialPortEventListener() {

			@Override
			public void serialEvent(SerialPortEvent event) {
				switch (event.getEventType()) {
				case SerialPortEvent.DATA_AVAILABLE:
					try {
						
						String trame = ComConnexion.this.reader.readLine();
						float value = TrameDecoder.valeur(trame);
						MeteoEventType_E type = TrameDecoder.dataType(trame);

						switch (type) {
						case ALTITUDE:
							meteoServiceCallback.altitudePerformed(value);
							break;
						case PRESSION:
							meteoServiceCallback.pressionPerformed(value);
							break;
						case TEMPERATURE:
							meteoServiceCallback.temperaturePerformed(value);
							break;
						}
					
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		});
	}

	@Override
	public void stop() throws Exception {
		serialPort.notifyOnDataAvailable(false);
		serialPort.removeEventListener();
	}

	@Override
	public void connect() throws Exception {
		CommPortIdentifier portId = CommPortIdentifier
				.getPortIdentifier(portName);

		try {
			serialPort = (SerialPort) portId.open("MS" + portName, 1000);
		} catch (PortInUseException e) {
			throw new MeteoServiceException("Port d�j� utilis�!");
		}

		comOption.applyTo(serialPort);

		os = serialPort.getOutputStream();
		reader = new BufferedReader(new InputStreamReader(
				serialPort.getInputStream()));

		start();
	}

	@Override
	public void disconnect() throws Exception {
		serialPort.close();
	}

	@Override
	public void askAltitudeAsync() throws Exception {
		byte[] tabByte = TrameEncoder.coder(ASK_ALTITUDE);
		os.write(tabByte);
	}

	@Override
	public void askPressionAsync() throws Exception {
		byte[] tabByte = TrameEncoder.coder(ASK_PRESSION);
		os.write(tabByte);
	}

	@Override
	public void askTemperatureAsync() throws Exception {
		byte[] tabByte = TrameEncoder.coder(ASK_TEMPERATURE);
		os.write(tabByte);
	}

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	@Override
	public String getNamePort() {
		return portName;
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	public void setMSC(MeteoServiceCallback_I meteoServiceCallback) {
		this.meteoServiceCallback = meteoServiceCallback;
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private ComOption comOption;
	private String portName;
	private MeteoServiceCallback_I meteoServiceCallback;

	// Tools
	private SerialPort serialPort;
	private OutputStream os;
	private BufferedReader reader;

	private static final String ASK_ALTITUDE = "010200";
	private static final String ASK_PRESSION = "010000";
	private static final String ASK_TEMPERATURE = "010100";

}
