#include "hasher.h"
#include <QCryptographicHash>
#include <QDebug>

Hasher::Hasher(QObject *parent) : QObject(parent)
{

}

void Hasher::md5(QString text)
{
    QString res = QCryptographicHash::hash(text.toLatin1(), QCryptographicHash::Md5).toHex();
    qDebug() << "MD5 Got: " << res;

    emit notifyResult("md5", res);
}

void Hasher::sha256(QString text)
{
    QString res = QCryptographicHash::hash(text.toLatin1(), QCryptographicHash::Sha256).toHex();
    qDebug() << "SHA2 Got: " << res;
    emit notifyResult("sha2", res);
}

void Hasher::sha3(QString text)
{
    QString res = QCryptographicHash::hash(text.toLatin1(), QCryptographicHash::Sha3_512).toHex();
    qDebug() << "SHA3 Got: " << res;
    emit notifyResult("sha3", res);
}
