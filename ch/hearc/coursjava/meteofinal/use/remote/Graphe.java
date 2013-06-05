
package ch.hearc.coursjava.meteofinal.use.remote;

import java.util.Date;
import java.util.List;
import java.util.SimpleTimeZone;

import org.jfree.data.time.Millisecond;
import org.jfree.data.time.RegularTimePeriod;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;

public class Graphe
	{

	public Graphe()
		{
		// Create a simple XY chart
		series = new TimeSeries("XYGraph");
		seriesMemoire = new TimeSeries("XYGraph");

		firstValue = 0;

		// Add the series to your data set
		dataset = new TimeSeriesCollection();
		dataset.addSeries(series);
		}

	public void addToDataset(long x, float y)
		{
		SimpleTimeZone timeZone = new SimpleTimeZone(60*60*1000*2, "CEST");
		//		if (old == 0)
//			{
//			seriesMemoire.add(0, y);
//			old = x;
//			}
//		else
//			{
//			temp = x - old + temp;
//			seriesMemoire.add(temp, y);
//			old = x;
//			Date date = new Date(x);
//			System.out.println(date);
//			}
		seriesMemoire.addOrUpdate(RegularTimePeriod.createInstance(Millisecond.class, new Date(x), timeZone ), y);
		series.addOrUpdate(RegularTimePeriod.createInstance(Millisecond.class, new Date(x), timeZone ), y);
		}

	@SuppressWarnings("unchecked")
	public void toAffichage()
		{
//		series.clear();
//		listeSeries = seriesMemoire.getItems();
//		for(Object item:listeSeries)
//			{
//			TimeSeriesDataItem oldValue;
//			oldValue = (TimeSeriesDataItem)item;
//			if (oldValue.getValue() > (number)firstValue)
//				{
//				series.add(oldValue);
//				}
//			}

		}


	public TimeSeries getSeriesMemoire()
		{
		return this.seriesMemoire;
		}

	public void setFirstValue(long firstValue)
		{
		this.firstValue = firstValue;
		System.out.println("set " + firstValue);
		}

	public long getFirstValue()
		{
		return firstValue;
		}

	public TimeSeriesCollection getDataSet()
		{
		return dataset;
		}

	//attributes
	private TimeSeriesCollection dataset;
	private TimeSeries series;
	private TimeSeries seriesMemoire;
	private long old = 0;
	private long temp = 0;
	private long firstValue;

	private List<Object> listeSeries;
	}
