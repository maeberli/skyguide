
package ch.hearc.coursjava.poo.thread.pooldethread;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import ch.hearc.coursjava.poo.intro.chrono.Chrono;

public class UsePerformance
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args)
		{
		main();
		}

	public static void main()
		{
		int n = 1000000;
		withExecutorService(n);
		withSimpleThread(n);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void withSimpleThread(int n)
		{
		Chrono chrono = new Chrono();
		Thread[] threads = new Thread[n];
		for(int i = 0; i < n; ++i)
			{
			threads[i] = new Thread(new Runnable()
				{

					@Override
					public void run()
						{
						Long result = System.currentTimeMillis();
						//System.out.println(Thread.currentThread().getName() + " " + result);
						}
				});
			threads[i].start();
			}
		try
			{
			for(int i = 0; i < n; ++i)
				{
				threads[i].join();
				}
			chrono.stop();
			System.out.println("Simple " + chrono);
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}
		}

	private static void withExecutorService(int n)
		{
		Chrono chrono = new Chrono();

		Future<Void>[] futures = new Future[n];
		for(int i = 0; i < n; ++i)
			{
			futures[i] = executorService.submit(new Callable<Void>()
				{

					@Override
					public Void call() throws Exception
						{
						Long result = System.currentTimeMillis();
						//System.out.println(Thread.currentThread().getName() + " " + result);
						return null;
						}
				});
			}
		try
			{
			for(int i = 0; i < n; ++i)
				{
				futures[i].get();
				}
			chrono.stop();
			System.out.println("Pool : " + chrono);
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}

		}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	public static final ExecutorService executorService = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());

	}
