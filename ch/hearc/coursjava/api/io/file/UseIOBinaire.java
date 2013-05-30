
package ch.hearc.coursjava.api.io.file;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class UseIOBinaire
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args) throws IOException
		{
		main();
		}

	public static void main() throws IOException
		{
		//TODO : tester performances avec/sans buffer avec classe Chrono
		int n = 5000;
		double[] tabSource = shopData(n);

		String fileName = "./temp/folder/data.bin";
		File file = new File(fileName);
		File dirParent = file.getParentFile();
		dirParent.mkdirs();

		if (!file.exists())
			{

			saveIOBin(tabSource, fileName);
			double[] tabClone = loadIOBin(fileName, n);

			System.out.println(isEgal(tabClone, tabSource));

			System.out.println("FileDelete : " + file.delete());
			}
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static boolean isEgal(double[] t1, double[] t2)
		{
		if (t1.length != t2.length)
			{
			return false;
			}
		else
			{
			for(int i = 1; i <= t1.length; i++)
				{
				if (t1[i - 1] != t2[i - 1]) { return false; }
				}
			return true;
			}

		}

	private static double[] shopData(int n)
		{
		double[] tab = new double[n];

		for(int i = 1; i <= n; i++)
			{
			tab[i - 1] = i * Math.PI;
			}

		return tab;
		}

	private static void saveIOBin(double[] tab, String fileName) throws IOException
		{
		FileOutputStream fos = new FileOutputStream(fileName);
		BufferedOutputStream bos = new BufferedOutputStream(fos);
		DataOutputStream dos = new DataOutputStream(bos);

		for(double dataI:tab)
			{
			dos.writeDouble(dataI);
			}

		dos.close();
		bos.close();
		fos.close();
		}

	private static double[] loadIOBin(String fileName, int n) throws IOException
		{
		FileInputStream fis = new FileInputStream(fileName);
		BufferedInputStream bis = new BufferedInputStream(fis);
		DataInputStream dis = new DataInputStream(bis);

		double[] tab = new double[n];

		for(int i = 1; i <= n; i++)
			{
			tab[i - 1] = dis.readDouble();
			}

		dis.close();
		bis.close();
		fis.close();

		return tab;
		}

	}
