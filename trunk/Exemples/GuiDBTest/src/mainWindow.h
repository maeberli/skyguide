#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

#include "BrighStars.h"
#include "SkyField.h"
#include "Star.h"
#include "Place.h"

class mainWindow : public QWidget
{
    Q_OBJECT

    public:

    mainWindow(QWidget *parent = 0);

    ~mainWindow();

    signals:

    void beginDraw(Star* starsSky, Place* where);

    public slots:

    void draw();

    private:

    BrighStars *catalogue;

    Star* stars;

    Place* place;

    QPushButton *mainButton;

    QHBoxLayout *layout;

    SkyField *sky;
};

#endif // MAINWINDOW_H
