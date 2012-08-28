#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QDesktopWidget>
#include <QApplication>
#include <QScrollArea>
#include <QScrollBar>
#include <QRect>

#include "mainwindow.h"
#include "GuiImpl/skystarfield.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(QString("SkyGuide - Projet He-Arc"));
    move(100, 100);

    p_mainLayout = new QHBoxLayout;
    p_sky = new SkyStarField;
    p_rightLayout = new QVBoxLayout;
    p_mainButton = new QPushButton;
    p_logBox = new QGroupBox;
    p_logLayout = new QVBoxLayout;
    p_log = new QTextEdit;
    p_logClear = new QPushButton;
    p_note = new QLabel;
    p_zoom = new QScrollArea;

    p_mainButton->setText(QString("Start"));
    p_logBox->setTitle(QString("Log"));
    p_logBox->setLayout(p_logLayout);
    p_logClear->setText(QString("Clear"));
    p_note->setText(QString("Projet P1 - He-Arc, 2011 - 2012"));

    p_zoom->setWidget(p_sky);

    p_mainLayout->addWidget(p_zoom);
    p_mainLayout->addLayout(p_rightLayout);
    p_rightLayout->addWidget(p_mainButton);
    p_rightLayout->addWidget(p_logBox);
    p_logLayout->addWidget(p_log);
    p_logLayout->addWidget(p_logClear);
    p_rightLayout->addWidget(p_note);

    setLayout(p_mainLayout);

    QObject::connect(p_sky, SIGNAL(sendInfo(QList<int>,QList<SkyGuiElement*>*)), this, SLOT(updateInfo(QList<int>,QList<SkyGuiElement*>*)));
    QObject::connect(p_logClear, SIGNAL(clicked()), this, SLOT(clearText()));
    QObject::connect(this, SIGNAL(resetSelection()), p_sky, SLOT(clearSelection()));
    QObject::connect(p_sky, SIGNAL(sendAdjust(bool)), this, SLOT(adjustScrollBar(bool)));
    QObject::connect(p_sky, SIGNAL(sendMove(int)), this, SLOT(drag(int)));
    QObject::connect(p_sky, SIGNAL(sendClearText()), this, SLOT(clearText()));
    QObject::connect(p_mainButton, SIGNAL(clicked()), this, SLOT(startStop()));

    p_zoom->setMinimumSize(702, 702);
}

void MainWindow::appendLogMessage(QString message)
{
   p_log->setText(p_log->toPlainText()+"\n"+message);
}

void MainWindow::repaintSky(QList<SkyGuiElement *> *stars)
{
    p_sky->setStars(stars);
    p_sky->update();
}

void MainWindow::updateInfo(QList<int> selections, QList<SkyGuiElement *> *stars)
{
    QString info;

    int count = selections.count();
    if (count)
    {
        info += "Etoile[s] sélectionnée[s]\n";
        info += "-------------------------\n";
        for (int i = 0; i < count; ++i)
        {
            info += "Declinaison: " + QString::number(stars->at(selections[i])->getDeclinasion()) + "\n";
            info += "Right ascension: " + QString::number(stars->at(selections[i])->getRightAscension()) + "\n";
            info += "Azimuth: " + QString::number(stars->at(selections[i])->getAzimuth()) + "\n";
            info += "Height: " + QString::number(stars->at(selections[i])->getHeight()) + "\n";
            info += "Greek letter: " + stars->at(selections[i])->getGreekLetter() + "\n";
            info += "Constellation: " + stars->at(selections[i])->getConstellation() + "\n";
            info += "Magnitude: " + QString::number(stars->at(selections[i])->getMagnitude()) + "\n";
            info += "-------------------------\n";
        }

        p_log->setText(info);
    }
}

void MainWindow::drag(int direction)
{
    int valueH = p_zoom->horizontalScrollBar()->value();
    int valueV = p_zoom->verticalScrollBar()->value();
    switch (direction)
    {
        case 1:
            p_zoom->horizontalScrollBar()->setValue(valueH + 10);
            break;
        case 2:
            p_zoom->horizontalScrollBar()->setValue(valueH - 10);
            break;
        case 3:
            p_zoom->verticalScrollBar()->setValue(valueV + 10);
            break;
        case 4:
            p_zoom->verticalScrollBar()->setValue(valueV - 10);
            break;
    }
}

void MainWindow::adjustScrollBar(bool in)
{
    if (in)
    {
        p_zoom->horizontalScrollBar()->setValue(int(1.25 * p_zoom->horizontalScrollBar()->value()
                                + ((1.25 - 1) * p_zoom->verticalScrollBar()->pageStep()/2)));
        p_zoom->verticalScrollBar()->setValue(int(1.25 * p_zoom->verticalScrollBar()->value()
                                                              + ((1.25 - 1) * p_zoom->verticalScrollBar()->pageStep()/2)));
    }
    else
    {
        p_zoom->horizontalScrollBar()->setValue(int(0.8 * p_zoom->horizontalScrollBar()->value()
                                + ((0.8 - 1) * p_zoom->horizontalScrollBar()->pageStep()/2)));
        p_zoom->verticalScrollBar()->setValue(int(0.8 * p_zoom->verticalScrollBar()->value()
                                + ((0.8 - 1) * p_zoom->verticalScrollBar()->pageStep()/2)));
    }
}

void MainWindow::clearText()
{
    p_log->clear();
    emit resetSelection();
}

void MainWindow::startStop()
{
    if (p_mainButton->text() == QString("Start"))
    {
        p_mainButton->setText(QString("Stop"));
        emit sendStartAffichage();
    }
    else
    {
        emit sendStopAffichage();
        p_mainButton->setText(QString("Start"));
    }
}

MainWindow::~MainWindow()
{
    // Les Widgets sont détruits automatiquement.
}
