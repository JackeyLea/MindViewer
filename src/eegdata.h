#ifndef EEGDATA_H
#define EEGDATA_H

#include <QObject>
#include <QQmlEngine>

class EEGData : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit EEGData(QObject *parent = nullptr);

signals:

private:
};

#endif // EEGDATA_H
