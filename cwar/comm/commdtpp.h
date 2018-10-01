#ifndef COMMDTPP_H
#define COMMDTPP_H

#include <QObject>

class CommDtpp : public QObject
{
    Q_OBJECT
public:
    explicit CommDtpp(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COMMDTPP_H