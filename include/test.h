#pragma once

#include <qobject.h>

namespace Test {
class Test : public QObject {
    Q_OBJECT
  public:
    Test(QObject *parent = nullptr);
    ~Test();
    int add(const int a, const int b);
};
} // namespace Test
