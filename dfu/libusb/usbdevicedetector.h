#ifndef LIBUSBDEVICEDETECTOR_H
#define LIBUSBDEVICEDETECTOR_H

#include <QObject>

#include "usbdeviceinfo.h"

class USBDeviceDetector : public QObject
{
    Q_OBJECT

    USBDeviceDetector(QObject *parent = nullptr);
    ~USBDeviceDetector();

public:
    static USBDeviceDetector *instance();
    bool setWantedDevices(const QList <USBDeviceInfo> &wantedList);

signals:
    void devicePluggedIn(const USBDeviceInfo&);
    void deviceUnplugged(const USBDeviceInfo&);

private:
    void timerEvent(QTimerEvent *e) override;
};

#endif // LIBUSBDEVICEDETECTOR_H
