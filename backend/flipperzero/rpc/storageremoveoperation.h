#pragma once

#include "abstractprotobufoperation.h"

namespace Flipper {
namespace Zero {

class StorageRemoveOperation : public AbstractProtobufOperation
{
    Q_OBJECT

public:
    StorageRemoveOperation(QSerialPort *serialPort, const QByteArray &path, QObject *parent = nullptr);
    const QString description() const override;

private slots:
    void onSerialPortReadyRead() override;

private:
    bool begin() override;

    QByteArray m_path;
};

}
}

