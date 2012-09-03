#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QList>
#include <QLabel>

#include "GuiImpl/skystarfield.h"
#include "skyguielement.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void appendLogMessage(QString message);

public slots:
    void repaintSky(QList<SkyGuiElement *> *stars, double xP, double yP);
    void updateInfo(QList<int> selections, QList<SkyGuiElement *> *stars);
    void clearText();
    void adjustScrollBar(bool in);
    void drag(int direction);
    void startStop();

    void next();
    void previous();

signals:
    void resetSelection();

    void sendStartAffichage();
    void sendStopAffichage();

    void sendInc(int index);
    
private:
    QHBoxLayout *p_mainLayout;
    SkyStarField *p_sky;
    QVBoxLayout *p_rightLayout;
    QPushButton *p_mainButton;
    QGroupBox *p_logBox;
    QGroupBox *p_starBox;
    QVBoxLayout *p_logLayout;
    QTextEdit *p_log;
    QPushButton *p_logClear;
    QScrollArea *p_zoom;
    /************/
    QGridLayout *p_grid;
    QLabel *p_iDeclinaison;
    QLabel *p_tDeclinaison;
    QLabel *p_iRightAscension;
    QLabel *p_tRightAscension;
    QLabel *p_iAzimuth;
    QLabel *p_tAzimth;
    QLabel *p_iHeight;
    QLabel *p_tHeight;
    QLabel *p_iGreekLetter;
    QLabel *p_tGreekLetter;
    QLabel *p_iConstellation;
    QLabel *p_tConstellation;
    QLabel *p_iMagnitude;
    QLabel *p_tMagnitude;
    QPushButton *p_next;
    QPushButton *p_previous;
    /************/
    int p_index;
    QList<int> p_selections;
    QList<SkyGuiElement *> *p_stars;
};

#endif // MAINWINDOW_H
