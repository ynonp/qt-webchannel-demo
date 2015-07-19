#ifndef HASHER_H
#define HASHER_H

#include <QObject>


class Hasher : public QObject
{
    Q_OBJECT
public:
    explicit Hasher(QObject *parent = 0);

signals:
    void notifyResult(QString method, QString hex);

public slots:
    void md5(QString text);
    void sha256(QString text);
    void sha3(QString text);


};

#endif // HASHER_H
