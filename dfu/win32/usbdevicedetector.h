#ifndef WIN32DEVICEDETECTOR_H
#define WIN32DEVICEDETECTOR_H

#include <QObject>

#include "usbdeviceinfo.h"

class USBDeviceDetector : public QObject
{
    Q_OBJECT

    struct USBDeviceDetectorPrivate;

    USBDeviceDetector(QObject *parent = nullptr);
    ~USBDeviceDetector();

public:
    static USBDeviceDetector *instance();

    bool setWantedDevices(const QList <USBDeviceInfo> &wantedList);

public slots:
    void update();

signals:
    void devicePluggedIn(const USBDeviceInfo&);
    void deviceUnplugged(const USBDeviceInfo&);

private:
    bool registerAtom();
    bool createHotplugWindow();

    QList <USBDeviceInfo> availableDevices() const;

    void processDevicesArrived(const QList <USBDeviceInfo> &available);
    void processDevicesLeft(const QList <USBDeviceInfo> &available);

    static USBDeviceInfo parseInstanceID(const char *buf);

    USBDeviceDetectorPrivate *m_p;
    QList <USBDeviceInfo> m_wanted;
    QList <USBDeviceInfo> m_current;
};

#endif // WIN32DEVICEDETECTOR_H
