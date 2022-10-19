// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <qcoreapplication.h>
#include <gtest/gtest.h>
#include <sanitizer/asan_interface.h>
#include <QTimer>
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);

    QTimer::singleShot(0, [&](){
        int ret = RUN_ALL_TESTS();
        app.exit(ret);
    });

#ifdef QT_DEBUG
    __sanitizer_set_report_path("asan_demo.log");
#endif
    return app.exec();
}
