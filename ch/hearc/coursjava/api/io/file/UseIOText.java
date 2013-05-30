
package ch.hearc.coursjava.api.io.file;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.StringTokenizer;

public class UseIOText
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
		int n = 5000;
		double[] tabSource = shopData(n);

		String fileName = "./temp/folder/data.txt";
		File file = new File(fileName);
		File dirParent = file.getParentFile();
		dirParent.mkdirs();

		if (!file.exists())
			{

			saveIOText(fileName, tabSource);
			double[] tabClone = loadIOText(fileName, n);

			System.out.println(isEgal(tabClone, tabSource));

			//System.out.println("FileDelete : " + file.delete());
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

	private static void saveIOText(String fileName, double[] tab) throws IOException
		{
		FileWriter fw = new FileWriter(fileName);
		BufferedWriter bw = new BufferedWriter(fw);

		for(double data:tab)
			{
			bw.write(data + SEPARATEUR);
			}

		bw.close();
		fw.close();
		}

	private static double[] loadIOText(String fileName, int n) throws IOException
		{
		FileReader fr = new FileReader(fileName);
		BufferedReader br = new BufferedReader(fr);

		double[] tabLoaded = new double[n];

		String ligne = br.readLine();

		br.close();
		fr.close();

		//Parsing
		StringTokenizer parser = new StringTokenizer(ligne, SEPARATEUR);
		int i = 0;
		while(parser.hasMoreTokens())
			{
			tabLoaded[i] = Double.valueOf(parser.nextToken());
			i++;
			}

		return tabLoaded;
		}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	private final static String SEPARATEUR = " ";

	}
