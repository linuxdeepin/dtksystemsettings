// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <qcoreapplication.h>
#include <gtest/gtest.h>
#include <qresource.h>
#include <qtimer.h>

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    QCoreApplication app(argc, argv);
    QTimer::singleShot(0, [] {
        int ret = RUN_ALL_TESTS();
        qApp->exit(ret);
    });
    return app.exec();
}
