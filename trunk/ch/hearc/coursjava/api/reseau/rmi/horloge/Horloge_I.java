
package ch.hearc.coursjava.api.reseau.rmi.horloge;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Date;



public interface Horloge_I extends Remote
	{
	public Date getTime() throws RemoteException; // Exception pour RMI obligatoire
	}

