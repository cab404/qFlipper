#include "storagestatoperation.h"

#include "flipperzero/protobuf/storageprotobufmessage.h"

using namespace Flipper;
using namespace Zero;

StorageStatOperation::StorageStatOperation(QSerialPort *serialPort, const QByteArray &fileName, QObject *parent):
    AbstractProtobufOperation(serialPort, parent),
    m_fileName(fileName),
    m_isPresent(false),
    m_size(0),
    m_type(Type::Invalid)
{}

const QString StorageStatOperation::description() const
{
    return QStringLiteral("Storage stat @%1").arg(QString(m_fileName));
}

const QByteArray &StorageStatOperation::fileName() const
{
    return m_fileName;
}

bool StorageStatOperation::isPresent() const
{
    return m_isPresent;
}

quint64 StorageStatOperation::size() const
{
    return m_size;
}

StorageStatOperation::Type StorageStatOperation::type() const
{
    return m_type;
}

void StorageStatOperation::onSerialPortReadyRead()
{
    StorageStatResponse response(serialPort());

    if(!response.receive()) {
        return;

    } else if(!response.isOk()) {
        const auto status = response.commandStatus();
        // TODO: more flexible error handling
        if(status == PB_CommandStatus_ERROR_STORAGE_NOT_EXIST) {
            finish();
        } else{
            finishWithError(BackendError::ProtocolError, QStringLiteral("Device replied with error: %1").arg(response.commandStatusString()));
        }

    } else if(!response.isValidType()) {
        finishWithError(BackendError::ProtocolError, QStringLiteral("Expected StorageStat response, got something else"));

    } else {
        m_isPresent = response.isPresent();
        m_type = (response.file().type == PB_Storage_File_FileType_FILE) ? Type::RegularFile : Type::Directory;
        m_size = response.file().size;

        finish();
    }
}

bool StorageStatOperation::begin()
{
    StorageStatRequest request(serialPort(), m_fileName);
    return request.send();
}
