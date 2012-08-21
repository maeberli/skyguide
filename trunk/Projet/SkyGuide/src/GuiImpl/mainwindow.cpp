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
            info += "Greek letter: " + stars->at(selections[i])->getGreekLetter() + "\n";
            info += "Constellation: " + stars->at(selections[i])->getConstellation() + "\n";
            info += "Magnitude: " + QString::number(stars->at(selections[i])->getMagnitude()) + "\n";
            info += "-------------------------\n";
        }

        p_log->setText(info);
    }
}

void MainWindow::clearText()
{
    p_log->clear();
    emit resetSelection();
}

MainWindow::~MainWindow()
{
    // Les Widgets sont détruits automatiquement.
}
