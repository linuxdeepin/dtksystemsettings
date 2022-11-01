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
