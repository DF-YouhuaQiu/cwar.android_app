#ifndef COMMCONTROLLER_H
#define COMMCONTROLLER_H

#include <QObject>

class CommController : public QObject
{
    Q_OBJECT
public:
    explicit CommController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COMMCONTROLLER_H