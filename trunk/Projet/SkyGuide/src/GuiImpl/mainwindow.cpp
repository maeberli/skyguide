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
    p_index = 0;

    setWindowTitle(QString("SkyGuide"));
    move(100, 100);

    p_mainLayout = new QHBoxLayout;
    p_sky = new SkyStarField;
    p_rightLayout = new QVBoxLayout;
    p_mainButton = new QPushButton;
    p_logBox = new QGroupBox;
    p_starBox = new QGroupBox;
    p_logLayout = new QVBoxLayout;
    p_log = new QTextEdit;
    p_logClear = new QPushButton;
    p_zoom = new QScrollArea;
    /*****************/
    p_grid = new QGridLayout;
    p_iDeclinaison = new QLabel;
    p_tDeclinaison = new QLabel;
    p_iRightAscension = new QLabel;
    p_tRightAscension = new QLabel;
    p_iAzimuth = new QLabel;
    p_tAzimth = new QLabel;
    p_iHeight = new QLabel;
    p_tHeight = new QLabel;
    p_iGreekLetter = new QLabel;
    p_tGreekLetter = new QLabel;
    p_iConstellation = new QLabel;
    p_tConstellation = new QLabel;
    p_iMagnitude = new QLabel;
    p_tMagnitude = new QLabel;
    p_next = new QPushButton;
    p_previous = new QPushButton;
    /*****************/

    p_mainButton->setText(QString("Start"));
    p_starBox->setTitle(QString("Selected star"));
    p_next->setText(QString(">"));
    p_next->setDisabled(true);
    p_previous->setText(QString("<"));
    p_previous->setDisabled(true);
    p_logBox->setTitle(QString("Log"));
    p_logBox->setLayout(p_logLayout);
    p_logClear->setText(QString("Clear"));

    p_zoom->setWidget(p_sky);

    p_mainLayout->addWidget(p_zoom);
    p_mainLayout->addLayout(p_rightLayout);
    p_rightLayout->addWidget(p_mainButton);

    p_iDeclinaison->setText(QString("Declinaison:"));
    p_tDeclinaison->setText(QString("-"));
    p_iRightAscension->setText(QString("Right ascension:"));
    p_tRightAscension->setText(QString("-"));
    p_iAzimuth->setText(QString("Azimuth:"));
    p_tAzimth->setText(QString("-"));
    p_iHeight->setText(QString("Height:"));
    p_tHeight->setText(QString("-"));
    p_iGreekLetter->setText(QString("Greek letter:"));
    p_tGreekLetter->setText(QString("-"));
    p_iConstellation->setText(QString("Constellation:"));
    p_tConstellation->setText(QString("-"));
    p_iMagnitude->setText(QString("Magnitude:"));
    p_tMagnitude->setText(QString("-"));
    p_grid->addWidget(p_iDeclinaison, 0, 0);
    p_grid->addWidget(p_tDeclinaison, 0, 1);
    p_grid->addWidget(p_iRightAscension, 1, 0);
    p_grid->addWidget(p_tRightAscension, 1, 1);
    p_grid->addWidget(p_iAzimuth, 2, 0);
    p_grid->addWidget(p_tAzimth, 2, 1);
    p_grid->addWidget(p_iHeight, 3, 0);
    p_grid->addWidget(p_tHeight, 3, 1);
    p_grid->addWidget(p_iGreekLetter, 4, 0);
    p_grid->addWidget(p_tGreekLetter, 4, 1);
    p_grid->addWidget(p_iConstellation, 5, 0);
    p_grid->addWidget(p_tConstellation, 5, 1);
    p_grid->addWidget(p_iMagnitude, 6, 0);
    p_grid->addWidget(p_tMagnitude, 6, 1);
    p_grid->addWidget(p_previous, 7, 0);
    p_grid->addWidget(p_next, 7, 1);

    p_starBox->setLayout(p_grid);
    p_rightLayout->addWidget(p_starBox);

    // p_rightLayout->addLayout(p_grid);


    p_rightLayout->addWidget(p_logBox);
    p_logLayout->addWidget(p_log);
    p_logLayout->addWidget(p_logClear);
    setLayout(p_mainLayout);

    QObject::connect(p_sky, SIGNAL(sendInfo(QList<int>,QList<SkyGuiElement*>*)), this, SLOT(updateInfo(QList<int>,QList<SkyGuiElement*>*)));
    QObject::connect(p_logClear, SIGNAL(clicked()), this, SLOT(clearText()));
    QObject::connect(this, SIGNAL(resetSelection()), p_sky, SLOT(clearSelection()));
    QObject::connect(p_sky, SIGNAL(sendAdjust(bool)), this, SLOT(adjustScrollBar(bool)));
    QObject::connect(p_sky, SIGNAL(sendMove(int)), this, SLOT(drag(int)));
    QObject::connect(p_sky, SIGNAL(sendClearText()), this, SLOT(clearText()));
    QObject::connect(p_mainButton, SIGNAL(clicked()), this, SLOT(startStop()));
    QObject::connect(p_previous, SIGNAL(clicked()), this, SLOT(previous()));
    QObject::connect(p_next, SIGNAL(clicked()), this, SLOT(next()));
    QObject::connect(this, SIGNAL(sendInc(int)), p_sky, SLOT(Inc(int)));

    p_zoom->setMinimumSize(702, 702);
}

void MainWindow::appendLogMessage(QString message)
{
    p_log->setText(p_log->toPlainText() + message + "\n");
}
void MainWindow::repaintSky(QList<SkyGuiElement *> *stars, double xP, double yP){
    p_sky->setStars(stars);
    p_sky->setXP(xP);
    p_sky->setYP(yP);
    p_sky->update();
}

void MainWindow::updateInfo(QList<int> selections, QList<SkyGuiElement *> *stars)
{
    p_previous->setDisabled(true);
    p_next->setDisabled(true);
    p_index = 0;

    p_selections = selections;
    p_stars = stars;

    if (selections.count())
    {
        p_tDeclinaison->setText(QString::number(stars->at(selections[0])->getDeclinasion() * (180 / 3.14)));
        p_tRightAscension->setText(QString::number(stars->at(selections[0])->getRightAscension() * (180 / 3.14)));
        p_tAzimth->setText(QString::number(stars->at(selections[0])->getAzimuth() * (180 / 3.14)));
        p_tHeight->setText(QString::number(stars->at(selections[0])->getHeight() * (180 / 3.14)));
        p_tGreekLetter->setText(stars->at(selections[0])->getGreekLetter());
        p_tConstellation->setText(stars->at(selections[0])->getConstellation());
        p_tMagnitude->setText(QString::number(stars->at(selections[0])->getMagnitude()));
    }
    if (selections.count() > 1) p_next->setDisabled(false);

    /*
    QString info;
    int count = selections.count();
    if (count)
    {
        info += "Etoile[s] sélectionnée[s]\n";
        info += "----------------------------\n";
        for (int i = 0; i < count; ++i)
        {
            info += "Declinaison: " + QString::number(stars->at(selections[i])->getDeclinasion() * (180 / 3.14)) + "\n";
            info += "Right ascension: " + QString::number(stars->at(selections[i])->getRightAscension() * (180 / 3.14)) + "\n";
            info += "Azimuth: " + QString::number(stars->at(selections[i])->getAzimuth() * (180 / 3.14)) + "\n";
            info += "Height: " + QString::number(stars->at(selections[i])->getHeight() * (180 / 3.14)) + "\n";
            info += "Greek letter: " + stars->at(selections[i])->getGreekLetter() + "\n";
            info += "Constellation: " + stars->at(selections[i])->getConstellation() + "\n";
            info += "Magnitude: " + QString::number(stars->at(selections[i])->getMagnitude()) + "\n";
            info += "----------------------------\n";
        }
        p_log->setText(info);
    }
    */
}

void MainWindow::previous()
{
    p_index--;
    emit sendInc(p_index);
    if (p_index == 0)
    {
        p_previous->setDisabled(true);
        p_next->setDisabled(false);
    }
    else
    {
        p_next->setDisabled(false);
    }
    p_tDeclinaison->setText(QString::number(p_stars->at(p_selections[p_index])->getDeclinasion() * (180 / 3.14)));
    p_tRightAscension->setText(QString::number(p_stars->at(p_selections[p_index])->getRightAscension() * (180 / 3.14)));
    p_tAzimth->setText(QString::number(p_stars->at(p_selections[p_index])->getAzimuth() * (180 / 3.14)));
    p_tHeight->setText(QString::number(p_stars->at(p_selections[p_index])->getHeight() * (180 / 3.14)));
    p_tGreekLetter->setText(p_stars->at(p_selections[p_index])->getGreekLetter());
    p_tConstellation->setText(p_stars->at(p_selections[p_index])->getConstellation());
    p_tMagnitude->setText(QString::number(p_stars->at(p_selections[p_index])->getMagnitude()));
}

void MainWindow::next()
{
    p_index++;
    emit sendInc(p_index);
    if (p_index == p_selections.count() - 1)
    {
        p_next->setDisabled(true);
        p_previous->setDisabled(false);
    }
    else
    {
        p_previous->setDisabled(false);
    }
    p_tDeclinaison->setText(QString::number(p_stars->at(p_selections[p_index])->getDeclinasion() * (180 / 3.14)));
    p_tRightAscension->setText(QString::number(p_stars->at(p_selections[p_index])->getRightAscension() * (180 / 3.14)));
    p_tAzimth->setText(QString::number(p_stars->at(p_selections[p_index])->getAzimuth() * (180 / 3.14)));
    p_tHeight->setText(QString::number(p_stars->at(p_selections[p_index])->getHeight() * (180 / 3.14)));
    p_tGreekLetter->setText(p_stars->at(p_selections[p_index])->getGreekLetter());
    p_tConstellation->setText(p_stars->at(p_selections[p_index])->getConstellation());
    p_tMagnitude->setText(QString::number(p_stars->at(p_selections[p_index])->getMagnitude()));
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
    p_tDeclinaison->setText("-");
    p_tRightAscension->setText("-");
    p_tAzimth->setText("-");
    p_tHeight->setText("-");
    p_tGreekLetter->setText("-");
    p_tConstellation->setText("-");
    p_tMagnitude->setText("-");
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
