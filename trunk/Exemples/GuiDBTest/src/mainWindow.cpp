#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QStringList>
#include <QHBoxLayout>
#include <QSize>
#include <QDebug>
#include <cmath>

#include "mainWindow.h"
#include "BrighStars.h"
#include "SkyField.h"
#include "Star.h"
#include "Place.h"

mainWindow::mainWindow(QWidget *parent) : QWidget(parent)
{
    // to apply the geometry of application
    this->setGeometry(100, 100, 800, 600);
    // to load the catalogue of stars
    this->catalogue = new BrighStars("stars.db");

    this->catalogue->toSelect();

    int count = catalogue->getCount();

    this->stars = new Star[count];

    for (int i = 0; i < count; ++i)
    {
        this->stars[i].setRightAscension(this->catalogue->getRightAscension(i));
        this->stars[i].setDeclinaison(this->catalogue->getDeclinaison(i));
        this->stars[i].setMagnitude(this->catalogue->getMagnitude(i));
    }

    this->place = new Place(46.992181, 6.915894);

    // to allocate the widgets of application
    this->mainButton = new QPushButton();

    this->mainButton->setText("Display");

    this->connect(mainButton, SIGNAL(clicked()), this, SLOT(draw()));

    this->sky = new SkyField;

    this->connect(this, SIGNAL(beginDraw(Star*, Place*)), sky, SLOT(drawSky(Star*, Place*)));

    // to create the layout of application
    this->layout = new QHBoxLayout;

    this->layout->addWidget(mainButton);

    this->layout->addWidget(sky);

    this->setLayout(layout);
}

void mainWindow::draw()
{
    emit beginDraw(stars, place);
}

mainWindow::~mainWindow()
{
    delete catalogue;
    delete[] stars;
    delete place;
}
