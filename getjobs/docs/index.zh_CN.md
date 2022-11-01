@~chinese

\mainpage

## 项目介绍

getjobs是对cups的cupsGetJobs接口的封装。用于查询用户打印作业任务信息。

## 接口说明

```extern int GetJobsInfo(QList<JobsInfo> &jobsInfo, QString name = nullptr, USER_JOB_E myjobs = ALLUSER_JOBS, WHICH_JOBS_E whichjobs = WHICHJOBS_ACTIVE);
```
参数1: 获取任务列表信息
参数2: 打印机信息; nullptr: 所有打印机任务； 非空: 指定打印机名
参数3: ALLUSER_JOBS: 所有用户, USERSMIME_JOBS: 当前用户
参数4: WHICHJOBS_ALL: 全部任务
      WHICHJOBS_ACTIVE: 活跃任务(pending, held, processing);
      WHICHJOBS_COMPLETED: 已完成任务

默认获取所有用户，所有打印机的活跃任务信息

## 使用实例

`main.cpp`

```cpp
#include <QCoreApplication>

#include "getjobinfo.h"

#include <QDateTime>
#include <QDebug>

QString ShowFormatTime(time_t time)
{
    if (time == 0) { // 当时间戳返回值为0, 阶段任务未开始处理或者未完成
        return "job has not started processing or completed!";
    }
    QDateTime formatTime = QDateTime::fromSecsSinceEpoch(time);
    return formatTime.toString("yyyy-MM-dd hh:mm:ss");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<JobsInfo> jobsInfo;
    QString name = ""; // name为打印机信息，如果为空，获取所有打印机任务信息
    GetJobsInfo(jobsInfo, name, ALLUSER_JOBS, WHICHJOBS_ALL);

    for (auto it = jobsInfo.begin(); it != jobsInfo.end(); ++it) {
        qInfo() << "任务ID: " << it->id;
        qInfo() << "打印机信息: " << it->strDest;      // 打印机
        qInfo() << "文档信息: " << it->strTitle;       // 文档信息
        qInfo() << "用户信息: " << it->strUser;        // 用户
        qInfo() << "文档格式: " << it->strFormat;      // 文档格式
        qInfo() << "任务状态: " << it->iState;         // 任务状态
        qInfo() << "文档大小: " << it->iSize;          // 文档大小(单位KB)
        qInfo() << "任务优先级: " << it->iPriority;    // 任务优先级

        qInfo() << "任务完成时间: " << ShowFormatTime(it->completedTime);  // 完成时间
        qInfo() << "任务创建时间: " << ShowFormatTime(it->creationTime);   // 创建时间
        qInfo() << "任务处理时间: " << ShowFormatTime(it->processingTime); // 处理时间
    }

    return a.exec();
}
```


