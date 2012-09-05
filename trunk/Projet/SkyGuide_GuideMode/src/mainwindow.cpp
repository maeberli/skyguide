#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef Q_OS_WIN
    this->ui->comDevice->setText("Com1");
#endif

#ifdef Q_OS_UNIX
    this->ui->comDevice->setText("/dev/ttyUSB0");
#endif

    connect(ui->startStop, SIGNAL(clicked()),
            this, SLOT(onStartStop()));
}

MainWindow::~MainWindow()
{
    closeConn();
    delete ui;
}

void MainWindow::onStartStop()
{
    if(ui->startStop->text() == "start")
    {
        ui->startStop->setText("stop");
        activateForm(false);
        openConn();
    }
    else
    {
        ui->startStop->setText("start");
        activateForm();
        closeConn();
    }
}

void MainWindow::activateForm(bool activate)
{
    ui->altitude->setEnabled(activate);
    ui->azimuth->setEnabled(activate);
    ui->comDevice->setEnabled(activate);
    ui->flashUpdateIntervall->setEnabled(activate);
    ui->verboseConsole->setEnabled(activate     );
}

void MainWindow::openConn(bool connect)
{
    if(connect)
    {
        m_guideModeHandler = new GuideModeHandler(
                    ui->azimuth->value() * (M_PI/180),
                    ui->altitude->value() * (M_PI/180),
                    ui->comDevice->text(),
                    ui->flashUpdateIntervall->value(),
                    ui->verboseConsole->checkState());
        m_guideModeHandler->startupCommunication();
    }
    else
    {
        if(m_guideModeHandler != 0)
            m_guideModeHandler->shutdownCommunication();

        delete m_guideModeHandler;
    }
}

void MainWindow::closeConn()
{
    openConn(false);
}
