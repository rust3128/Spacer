#ifndef OBJECTDATA_H
#define OBJECTDATA_H
#include "ObjectWorkplace/workpalce.h"
#include "ObjectWorkplace/objecttitle.h"

#include <QObject>

class ObjectData : public QObject
{
    Q_OBJECT
public:
    explicit ObjectData(int ID, QObject *parent = nullptr);
    ObjectTitle * getObjTitle();
    const QList<Workpalce> &getListWorkplace() const;

signals:
private:
    void ListWorkpace(void);
private:
    int objectID;
    ObjectTitle *titleObj;
    QList<Workpalce> listWorkplace;

};

#endif // OBJECTDATA_H
