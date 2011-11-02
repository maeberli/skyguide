#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "abstractserial.h"
#include "serialdeviceenumerator.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    AbstractSerial *serialPort;
    SerialDeviceEnumerator *serialEnumerator;

    void initializeConfigurations(AbstractSerial::BaudRate defBaudrate = AbstractSerial::BaudRate1200,
                                  AbstractSerial::Flow defFlowControl = AbstractSerial::FlowControlHardware,
                                  AbstractSerial::Parity defParity = AbstractSerial::ParityNone,
                                  AbstractSerial::DataBits defDatabits = AbstractSerial::DataBits8);
    void setConfigurationEnabled(bool enabled = true);

private slots:
    void signalStatusChanged(const QString &status, QDateTime current);
    void openPort(bool forceDisconnect = false);
    void readIncommingData();
    void emitText();

};

#endif // MAINWINDOW_H
