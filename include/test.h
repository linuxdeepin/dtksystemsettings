#pragma once
#include <QObject>

namespace Test {
class Test : public QObject
{
    Q_OBJECT
public:
    Test(QObject *parent =nullptr) : QObject(parent) {}
    virtual ~Test() {}
    int add(const int a, const int b);
};
}
