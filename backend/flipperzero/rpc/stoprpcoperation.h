#pragma once

#include "abstractprotobufoperation.h"

namespace Flipper {
namespace Zero {

class StopRPCOperation : public AbstractProtobufOperation
{
    Q_OBJECT

public:
    StopRPCOperation(QSerialPort *serialPort, QObject *parent = nullptr);
    const QString description() const override;

private slots:
    void onSerialPortReadyRead() override;

private:
    bool begin() override;

    QByteArray m_receivedData;
};

}
}

