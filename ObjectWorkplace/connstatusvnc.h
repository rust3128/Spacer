#ifndef CONNSTATUSVNC_H
#define CONNSTATUSVNC_H

#include <QObject>

class ConnStatusVNC : public QObject
{
    Q_OBJECT
public:
    explicit ConnStatusVNC(QString IP, int port, QObject *parent = nullptr);

signals:
    void signalSendStatus(bool);
    void finish();
public slots:
    void getConnStatus();
private:
    QString ipAdress;
    int portVNC;
    bool statusVNC;
};

#endif // CONNSTATUSVNC_H
