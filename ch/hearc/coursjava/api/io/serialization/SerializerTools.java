
package ch.hearc.coursjava.api.io.serialization;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class SerializerTools
	{

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	public static void saveBin(String fileName, Serializable serializable) throws IOException
		{
		FileOutputStream fos = new FileOutputStream(fileName);
		BufferedOutputStream bos = new BufferedOutputStream(fos);
		ObjectOutputStream oos = new ObjectOutputStream(bos);

		oos.writeObject(serializable);

		oos.close();
		bos.close();
		fos.close();
		}

	public static Serializable loadBin(String fileName) throws IOException, ClassNotFoundException
		{
		FileInputStream fis = new FileInputStream(fileName);
		BufferedInputStream bis = new BufferedInputStream(fis);
		ObjectInputStream ois = new ObjectInputStream(bis);

		Serializable object = (Serializable)ois.readObject();

		ois.close();
		bis.close();
		fis.close();

		return object;
		}

	public static byte[] saveMemory(Serializable object) throws IOException
		{
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		BufferedOutputStream bos = new BufferedOutputStream(baos);
		ObjectOutputStream oos = new ObjectOutputStream(bos);

		oos.writeObject(object);

		oos.close();
		bos.close();
		baos.close();

		return baos.toByteArray();
		}

	public static Serializable loadMemory(byte[] tabByte) throws IOException, ClassNotFoundException
		{
		ByteArrayInputStream bais = new ByteArrayInputStream(tabByte);
		BufferedInputStream bis = new BufferedInputStream(bais);
		ObjectInputStream ois = new ObjectInputStream(bis);

		Serializable object = (Serializable)ois.readObject();

		ois.close();
		bis.close();
		bais.close();

		return object;
		}
	}
