
package ch.hearc.coursjava.gui.controlprincipal;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.net.URL;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import javax.swing.ImageIcon;
import javax.swing.JPanel;

/**
 *
 * @author Diego
 *
 */
public class JPanelDessin extends JPanel
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JPanelDessin(int n)
		{
		dim = 0;
		t = 0;
		isRunning = false;
		isImage1Front = true;
		current_time = 0;
		last_time = 0;

		changeDT(n);
		loadLogo();

		geometrie();
		controle();
		apparence();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public void changeDT(int n)
		{
		dt = 2 * Math.PI / (n);
		}

	public synchronized void startAnimation()
		{
		if (!isRunning)
			{
			isRunning = true;

			Thread t = new Thread(new Runnable()
				{

					@Override
					public void run()
						{
						while(isRunning)
							{
							stepAnimation();
							}

						}
				});
			t.start();
			}
		}

	public void stopAnimation()
		{
		isRunning = false;
		}

	@Override
	protected void paintComponent(Graphics g)
		{
		super.paintComponent(g);

		Graphics2D g2d = (Graphics2D)g;

		AffineTransform oldG2d = g2d.getTransform();
		dessiner(g2d);
		g2d.setTransform(oldG2d);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void loadLogo()
		{
		URL url = ClassLoader.getSystemResource(PATHLOGO);
		logo = new ImageIcon(url).getImage();
		}

	private synchronized void stepAnimation()
		{
		t += dt;

		last_time = current_time;

		creer();

		try
			{
			Thread.sleep(DELAY_MS);
			}
		catch (InterruptedException e)
			{
			e.printStackTrace();
			}
		repaint();

		current_time = System.currentTimeMillis();
		System.out.println(1000.0 / (current_time - last_time) + " fps");
		}

	private void dessiner(Graphics2D g2d)
		{
		if (isImage1Front)
			{
			g2d.drawImage(image1, 0, 0, null);
			}
		else
			{
			g2d.drawImage(image2, 0, 0, null);
			}
		g2d.drawImage(logo, 0, 0, null);
		}

	private void creer()
		{
		EXECUTOR_SERVICE_SINGLE.submit(callableCreer());
		}

	private void calcImage(int startI, int startJ, int endI, int endJ, BufferedImage bf)
		{
		for(int i = startI; i < endI; ++i)
			{
			for(int j = startJ; j < endJ; ++j)
				{
				float rvbValue = (float)(rvb(i, j) / 255.0);
				float aValue = (float)(a(i, j) / 255.0);
				Color col = new Color(rvbValue, rvbValue, rvbValue, aValue);
				int colValue = col.getRGB();

				bf.setRGB(i, j, colValue);
				}
			}
		}

	private Callable<Void> callableCreer()
		{
		return new Callable<Void>()
			{

				@Override
				public Void call() throws Exception
					{
					creerImageBack();
					return null;
					}
			};
		}

	private void creerImageBack()
		{
		BufferedImage bf = new BufferedImage(dim, dim, BufferedImage.TYPE_INT_ARGB);

		Future<Void>[] futures = new Future[NB_CORE];
		for(int i = 0; i < NB_CORE; ++i)
			{
			futures[i] = EXECUTOR_SERVICE.submit(callable(i, dim / NB_CORE, bf));
			}
		try
			{
			for(int i = 0; i < NB_CORE; ++i)
				{
				futures[i].get();
				}
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}

		if (isImage1Front)
			{
			image2 = (new ImageIcon(bf)).getImage();
			}
		else
			{
			image1 = (new ImageIcon(bf)).getImage();
			}
		isImage1Front = !isImage1Front;
		}

	private Callable<Void> callable(final int i, final int dimension, final BufferedImage bf)
		{
		return new Callable<Void>()
			{

				@Override
				public Void call() throws Exception
					{
					int startI = i * dimension;
					int endI = startI + dimension;
					int startJ = 0;
					int endJ = dim;

					calcImage(startI, startJ, endI, endJ, bf);
					return null;
					}
			};
		}

	private void apparence()
		{
		// rien
		}

	private void controle()
		{
		addComponentListener(new ComponentAdapter()
			{

				@Override
				public void componentResized(ComponentEvent arg0)
					{
					int w = JPanelDessin.this.getWidth();
					int h = JPanelDessin.this.getHeight();
					dim = (w > h) ? w : h;
					creer();
					}
			});
		}

	private void geometrie()
		{
		this.setLayout(new FlowLayout(FlowLayout.CENTER));
		}

	private double color(int x, int y)
		{
		return (128.0 + 127.0 * Math.cos(d(x, y) - t / 7.0) / (d(x, y) + 1));
		}

	private double niveauGris(int x, int y)
		{
		return color(x, y);
		}

	private double d(int x, int y)
		{
		return Math.sqrt(fx(x) * fx(x) + fy(y) * fy(y)) / 10.0;
		}

	private double fx(int x)
		{
		return (x - dim / 2);
		}

	private double fy(int y)
		{
		return (y - dim / 2);
		}

	private float rvb(int x, int y)
		{
		return (float)niveauGris(x, y);
		}

	private float a(int x, int y)
		{
		return 255;
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	//tools
	private Image image1;
	private Image image2;
	private Image logo;
	private int dim;
	private double t;
	private double dt;
	private boolean isImage1Front;
	private boolean isRunning;
	private double current_time;
	private double last_time;

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	private final static ExecutorService EXECUTOR_SERVICE_SINGLE = Executors.newSingleThreadExecutor();
	private final static ExecutorService EXECUTOR_SERVICE = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
	private final static int NB_CORE = Runtime.getRuntime().availableProcessors();
	private final static String PATHLOGO = "ressources/PCours/images/coffee_logo.png";
	private final static long DELAY_MS = 100;
	}
