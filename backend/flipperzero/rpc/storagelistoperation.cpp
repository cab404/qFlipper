#include "storagelistoperation.h"

#include "flipperzero/protobuf/storageprotobufmessage.h"

using namespace Flipper;
using namespace Zero;

StorageListOperation::StorageListOperation(QSerialPort *serialPort, const QByteArray &path, QObject *parent):
    AbstractSerialOperation(serialPort, parent),
    m_path(path)
{}

const QString StorageListOperation::description() const
{
    return QStringLiteral("Storage list @%1").arg(QString(m_path));
}

const FileInfoList &StorageListOperation::files() const
{
    return m_result;
}

void StorageListOperation::onSerialPortReadyRead()
{
    StorageListResponse response(serialPort());

    while(response.receive()) {

        if(!response.isOk()) {
            finishWithError(BackendError::ProtocolError, QStringLiteral("Device replied with error: %1").arg(response.commandStatusString()));
            return;

        } else if(!response.isValidType()) {
            finishWithError(BackendError::ProtocolError, QStringLiteral("Expected StorageList response, got something else"));
            return;
        }

        const auto &files = response.files();
        for(auto &file : files) {

            FileInfo fileInfo {
                QByteArray(file.name),
                m_path + QByteArrayLiteral("/") + QByteArray(file.name),
                file.type == PB_Storage_File_FileType_FILE ? FileType::RegularFile : FileType::Directory,
                file.size
            };

            m_result.append(fileInfo);
        }

        if(!response.hasNext()) {
            finish();
            return;
        }
    }
}

bool StorageListOperation::begin()
{
    StorageListRequest request(serialPort(), m_path);
    return request.send();
}
