
package ch.hearc.coursjava.api.io.file.tailleinconnue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class UseTailleInconnue
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args)
		{
		try
			{
			main();
			}
		catch (IOException e)
			{
			System.err.println("File not found !");
			}
		}

	public static void main() throws IOException
		{
		FileReader fr = new FileReader("matrice.txt");
		BufferedReader br = new BufferedReader(fr);

		work(br);

		br.close();
		fr.close();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void work(BufferedReader br)
		{
		List<String[]> listeExterne = new LinkedList<String[]>();

		peupler(listeExterne, br);

		int[][] tab2D = toTableau2D(listeExterne);

		afficher(tab2D);
		}

	private static int[][] toTableau2D(List<String[]> listeExterne)
		{
		int n = listeExterne.size();
		int i = 0;
		int[][] tab2d = new int[n][];

		for(String[] ligne:listeExterne)
			{
			int mi = ligne.length;
			tab2d[i] = new int[mi];
			for(int j = 0; j < mi; j++)
				{
				tab2d[i][j] = Integer.valueOf(ligne[j]);
				}
			i++;
			}

		return tab2d;
		}

	private static void afficher(int[][] tab2d)
		{
		for(int[] ligne:tab2d)
			{
			for(int element:ligne)
				{
				System.out.print(element + " ");
				}
			System.out.println();
			}
		}

	private static void peupler(List<String[]> listeExterne, BufferedReader br)
		{
		try
			{
			while(true)
				{
				String ligne = br.readLine();
				String[] tabLigne = ligne.split(" ");
				listeExterne.add(tabLigne);
				}
			}
		catch (Exception e)
			{
			//break;
			}
		}
	}
