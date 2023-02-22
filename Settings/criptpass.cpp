#include "criptpass.h"
#include "GlobalSettings/globalsettings.h"
#include "Settings/qaesencryption.h"

#include <QCryptographicHash>


CriptPass::CriptPass()
{
    key = GlobalSettings::KEY_SOLT;
    iv = GlobalSettings::VEKTOR_KEY;
    hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
}

QString CriptPass::criptPass(QString password)
{
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QByteArray encodeText = encryption.encode(password.toLocal8Bit(), hashKey, hashIV);
    auto result = QString(encodeText.toBase64());
    return result;
}

QString CriptPass::decriptPass(QString password)
{
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QByteArray encodeText = QByteArray::fromBase64(password.toUtf8());
    QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);
    auto result = QString(encryption.removePadding(decodeText));
    return result;
}


