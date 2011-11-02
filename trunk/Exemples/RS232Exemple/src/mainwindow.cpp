#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serialPort(new AbstractSerial(this)),
    serialEnumerator(new SerialDeviceEnumerator())
{
    ui->setupUi(this);

    serialEnumerator->setEnabled(true);
    serialPort->enableEmitStatus(true);

    initializeConfigurations();

    connect(this->serialPort, SIGNAL(signalStatus(QString,QDateTime)),
            this, SLOT(signalStatusChanged(QString,QDateTime)));
    connect(this->serialPort, SIGNAL(readyRead()),
            this, SLOT(readIncommingData()));

    connect(this->ui->openCloseConnection, SIGNAL(clicked()),
            this, SLOT(openPort()));
    connect(this->ui->emitButton, SIGNAL(clicked()),
            this, SLOT(emitText()));
    connect(this->ui->clearReceive, SIGNAL(clicked()),
            this->ui->receivedText, SLOT(clear()));
    connect(this->ui->clearStatus, SIGNAL(clicked()),
            this->ui->deviceStatus, SLOT(clear()));

}

MainWindow::~MainWindow()
{
    delete serialEnumerator;
    delete serialPort;
    delete ui;
}

void MainWindow::initializeConfigurations(AbstractSerial::BaudRate defBaudrate,
                                          AbstractSerial::Flow defFlowControl,
                                          AbstractSerial::Parity defParity,
                                          AbstractSerial::DataBits defDatabits)
{
    for(int i = 0; i < this->serialPort->baudRateMap().count(); ++i)
        this->ui->baudrate->addItem(
                this->serialPort->baudRateMap().values()[i],
                this->serialPort->baudRateMap().keys()[i]);

    this->ui->baudrate->setCurrentIndex(
                this->ui->baudrate->findData(defBaudrate));

    for(int i = 0; i < this->serialPort->flowControlMap().count(); ++i)
        this->ui->flowControl->addItem(
                    this->serialPort->flowControlMap().values()[i],
                    this->serialPort->flowControlMap().keys()[i]);

    this->ui->flowControl->setCurrentIndex(
                this->ui->flowControl->findData(defFlowControl));

    for(int i = 0; i < this->serialPort->parityMap().count(); ++i)
        this->ui->parityBit->addItem(
                    this->serialPort->parityMap().values()[i],
                    this->serialPort->parityMap().keys()[i]);

    this->ui->parityBit->setCurrentIndex(
                this->ui->parityBit->findData(defParity));

    for(int i = 0; i < this->serialPort->dataBitsMap().count(); ++i)
        this->ui->dataBits->addItem(
                    this->serialPort->dataBitsMap().values()[i],
                    this->serialPort->dataBitsMap().keys()[i]);

    this->ui->dataBits->setCurrentIndex(
                this->ui->dataBits->findData(defDatabits));


    this->ui->port->addItems(this->serialEnumerator->devicesAvailable());
}

void MainWindow::setConfigurationEnabled(bool enabled)
{
    this->ui->port->setEnabled(enabled);
    this->ui->dataBits->setEnabled(enabled);
    this->ui->parityBit->setEnabled(enabled);
    this->ui->flowControl->setEnabled(enabled);
    this->ui->baudrate->setEnabled(enabled);
    this->ui->emitButton->setEnabled(!enabled);

    if(enabled)
        this->ui->openCloseConnection->setText(tr("Connect"));
    else
        this->ui->openCloseConnection->setText(tr("Disconnect"));

}

void MainWindow::openPort(bool forceDisconnect)
{
    if(this->serialPort->isOpen() || forceDisconnect)
    {
        this->serialPort->close();

        this->setConfigurationEnabled();
    }
    else
    {
        this->serialPort->setDeviceName(this->ui->port->currentText());

        if(this->serialPort->open(QIODevice::ReadWrite))
        {
            this->setConfigurationEnabled(false);

            this->serialPort->setBaudRate(
                        this->ui->baudrate->currentText());
            this->serialPort->setParity(
                        this->ui->parityBit->currentText());
            this->serialPort->setDataBits(
                        this->ui->dataBits->currentText());
            this->serialPort->setFlowControl(
                        this->ui->flowControl->currentText());
        }


    }
}

void MainWindow::signalStatusChanged(const QString &status, QDateTime current)
{
    this->ui->deviceStatus->append(current.toString("dd.MM.yy hh:mm:ss: ")+status);
    this->ui->receivedText->ensureCursorVisible();
}

void MainWindow::readIncommingData()
{
    QByteArray ba = this->serialPort->readAll();

    this->ui->receivedText->insertPlainText(QString::fromUtf8(ba.data()));
    this->ui->receivedText->ensureCursorVisible();

}

void MainWindow::emitText()
{
    if(!this->ui->emitText->toPlainText().isEmpty())
    {
        this->serialPort->write(this->ui->emitText->toPlainText().toUtf8());
    }
}
