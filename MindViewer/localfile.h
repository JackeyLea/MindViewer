#ifndef LOCALFILE_H
#define LOCALFILE_H

#include <QObject>

class LocalFile : public QObject
{
    Q_OBJECT
public:
    explicit LocalFile(QObject *parent = nullptr);

signals:

};

#endif // LOCALFILE_H
