#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "guidemodehandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onStartStop();
    void activateForm(bool activate = true);
    void openConn(bool connect = true);
    void closeConn();

    
private:
    Ui::MainWindow *ui;

    GuideModeHandler* m_guideModeHandler;
};

#endif // MAINWINDOW_H
