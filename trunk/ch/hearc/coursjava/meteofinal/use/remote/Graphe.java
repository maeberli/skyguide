
package ch.hearc.coursjava.meteofinal.use.remote;

import java.util.List;

import org.jfree.data.xy.XYDataItem;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

public class Graphe
	{

	public Graphe()
		{
		// Create a simple XY chart
		series = new XYSeries("XYGraph");
		seriesMemoire = new XYSeries("XYGraph");

		firstValue = 0;

		// Add the series to your data set
		dataset = new XYSeriesCollection();
		dataset.addSeries(series);
		}

	public void addToDataset(long x, float y)
		{
		if (old == 0)
			{
			seriesMemoire.add(0, y);
			old = x;
			}
		else
			{
			temp = x - old + temp;
			seriesMemoire.add(temp, y);
			old = x;
			}
		}

	@SuppressWarnings("unchecked")
	public void toAffichage()
		{
		series.clear();
		listeSeries = seriesMemoire.getItems();
		for(Object item:listeSeries)
			{
			XYDataItem oldValue;
			oldValue = (XYDataItem)item;
			if (oldValue.getX().intValue() > firstValue)
				{
				series.add(oldValue);
				}
			}

		}


	public XYSeries getSeriesMemoire()
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

	public XYSeriesCollection getDataSet()
		{
		return dataset;
		}

	//attributes
	private XYSeriesCollection dataset;
	private XYSeries series;
	private XYSeries seriesMemoire;
	private long old = 0;
	private long temp = 0;
	private long firstValue;

	private List<Object> listeSeries;
	}
