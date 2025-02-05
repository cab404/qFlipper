#pragma once

#include "abstractprotobufoperation.h"

namespace Flipper {
namespace Zero {

class StorageInfoOperation : public AbstractProtobufOperation
{
    Q_OBJECT

public:
    StorageInfoOperation(QSerialPort *serialPort, const QByteArray &path, QObject *parent = nullptr);
    const QString description() const override;

    bool isPresent() const;
    quint64 sizeFree() const;
    quint64 sizeTotal() const;

private slots:
    void onSerialPortReadyRead() override;

private:
    bool begin() override;

    QByteArray m_path;
    bool m_isPresent;
    quint64 m_sizeFree;
    quint64 m_sizeTotal;
};

}
}

