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

#include "GuiImpl/skystarfield.h"
#include "skyguielement.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void repaintSky(QList<SkyGuiElement *> *stars);
    void updateInfo(QList<int> selections, QList<SkyGuiElement *> *stars);
    void clearText();
    void adjustScrollBar(bool in);
    void drag(int direction);
    void startStop();

signals:
    void resetSelection();

    void sendStartAffichage();
    
private:
    QHBoxLayout *p_mainLayout;
    SkyStarField *p_sky;
    QVBoxLayout *p_rightLayout;
    QPushButton *p_mainButton;
    QGroupBox *p_logBox;
    QVBoxLayout *p_logLayout;
    QTextEdit *p_log;
    QPushButton *p_logClear;
    QLabel *p_note;
    QScrollArea * p_zoom;
};

#endif // MAINWINDOW_H
