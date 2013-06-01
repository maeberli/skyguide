package ch.hearc.coursjava.meteofinal.use.remote;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import java.util.LinkedList;
import java.util.List;

public class ListOfInterfaces {

	public static List<NetworkInterface> getAllNetworkInterfaces() throws SocketException {
		List<NetworkInterface> allNetworkInterfaces = new LinkedList<NetworkInterface>();

		Enumeration<NetworkInterface> networkInterfaces = NetworkInterface.getNetworkInterfaces();

		while (networkInterfaces.hasMoreElements()) {
			NetworkInterface currentNetworkInterface = networkInterfaces.nextElement();

			allNetworkInterfaces.add(currentNetworkInterface);
		}

		return allNetworkInterfaces;
	}

	public static List<InetAddress> getAllAdresses(NetworkInterface networkInterface) {
		List<InetAddress> allAddresses = new LinkedList<InetAddress>();

		Enumeration<InetAddress> addresses = networkInterface.getInetAddresses();

		if (addresses.hasMoreElements()) {
			while (addresses.hasMoreElements()) {
				InetAddress currentAddress = addresses.nextElement();

				allAddresses.add(currentAddress);
			}

			return allAddresses;
		} else {
			return null;
		}

	}

}
