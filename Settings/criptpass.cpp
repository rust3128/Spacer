#include "criptpass.h"

CriptPass::CriptPass()
{

}

QString CriptPass::criptPass(QString str)
{
    QByteArray ba = str.toUtf8();
    return ba.toBase64();
}

QString CriptPass::decriptPass(QString str)
{
    QByteArray ba = str.toUtf8();
    return QByteArray::fromBase64(ba);
}
