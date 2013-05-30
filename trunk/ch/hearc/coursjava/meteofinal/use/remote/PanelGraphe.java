
package ch.hearc.coursjava.meteofinal.use.remote;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.Rectangle2D;

import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.StandardChartTheme;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.category.StandardBarPainter;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.ui.RectangleInsets;

public class PanelGraphe extends JPanel
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public PanelGraphe(String label, String xLabel, String yLabel)
		{
		this.label = label;
		this.xLabel = xLabel;
		this.yLabel = yLabel;

		this.setLayout(new BorderLayout());

		graphe = new Graphe();

		this.addMouseMotionListener(new MouseMotionListener()
			{

				@Override
				public void mouseDragged(MouseEvent e)
					{
					if (e.getX() < oldX - 50)
						{
						graphe.setFirstValue(graphe.getFirstValue() + 10000);
						oldX -= 50;
						}
					else if (e.getX() > oldX + 50)
						{
						graphe.setFirstValue(graphe.getFirstValue() - 10000);
						oldX += 50;
						}

					graphe.toAffichage();
					repaint();

					}

				@Override
				public void mouseMoved(MouseEvent e)
					{
					oldX = e.getX();
					}
			});

		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	protected void paintComponent(Graphics g)
		{
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D)g;
		AffineTransform transformOld = g2d.getTransform();
		dessiner(g2d);
		g2d.setTransform(transformOld);
		}

	private void dessiner(Graphics2D g2d)
		{
		// Generate the graph
		chart = ChartFactory.createXYLineChart(this.label, // Title
				this.xLabel, // x-axis Label
				this.yLabel, // y-axis Label
				graphe.getDataSet(), // Dataset
				PlotOrientation.VERTICAL, // Plot Orientation
				true, // Show Legend
				true, // Use tooltips
				false // Configure chart to generate URLs?
				);

		StandardChartTheme theme = (StandardChartTheme)org.jfree.chart.StandardChartTheme.createJFreeTheme();

		theme.setTitlePaint(Color.decode("#4572a7"));
		theme.setRangeGridlinePaint(Color.decode("#C0C0C0"));
		theme.setPlotBackgroundPaint(Color.white);
		theme.setChartBackgroundPaint(Color.white);
		theme.setAxisOffset(new RectangleInsets(0, 0, 0, 0));
		theme.setBarPainter(new StandardBarPainter());
		theme.setAxisLabelPaint(Color.decode("#666666"));
		theme.apply(chart);

		XYPlot plot = (XYPlot)chart.getPlot();
		plot.setDomainCrosshairVisible(true);
		plot.setRangeCrosshairVisible(true);

		XYItemRenderer r = plot.getRenderer();
		if (r instanceof XYLineAndShapeRenderer)
			{
			XYLineAndShapeRenderer renderer = (XYLineAndShapeRenderer)r;

			renderer.setSeriesPaint(0, Color.BLUE);
			}

		chart.draw(g2d, new Rectangle2D.Double(0, 0, this.getWidth(), this.getHeight()));
		}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	public Graphe getGraphe()
		{
		return graphe;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private String label;
	private String xLabel;
	private String yLabel;

	private Graphe graphe;
	private JFreeChart chart;
	private int oldX;
	}
