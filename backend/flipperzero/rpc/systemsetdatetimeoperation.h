#pragma once

#include "abstractprotobufoperation.h"

#include <QDateTime>

namespace Flipper {
namespace Zero {

class SystemSetDateTimeOperation : public AbstractProtobufOperation
{
    Q_OBJECT

public:
    SystemSetDateTimeOperation(QSerialPort *serialPort, const QDateTime &dateTime, QObject *parent = nullptr);
    const QString description() const override;

private slots:
    void onSerialPortReadyRead() override;

private:
    bool begin() override;
    QDateTime m_dateTime;
};

}
}

