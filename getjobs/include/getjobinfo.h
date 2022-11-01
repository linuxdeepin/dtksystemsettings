#ifndef GETJOBINFO_H
#define GETJOBINFO_H

#include <QString>
#include <QList>

typedef enum jobs_users_e
{
    ALLUSER_JOBS,
    USERSMIME_JOBS
} USER_JOB_E;

typedef enum which_jobs_e
{
    WHICHJOBS_ALL = -1,
    WHICHJOBS_ACTIVE = 0,
    WHICHJOBS_COMPLETED
} WHICH_JOBS_E;

typedef enum jobs_state_e
{
    JOBS_STATE_PENDING = 3,		/* Job is waiting to be printed */
    JOBS_STATE_HELD,			/* Job is held for printing */
    JOBS_STATE_PROCESSING,		/* Job is currently printing */
    JOBS_STATE_STOPPED,			/* Job has been stopped */
    JOBS_STATE_CANCELED,		/* Job has been canceled */
    JOBS_STATE_ABORTED,			/* Job has aborted due to error */
    JOBS_STATE_COMPLETED		/* Job has completed successfully */
} JOBS_STATE_E;

typedef struct jobs_info_s
{
  int id;                  // The job ID
  QString strDest;         // Printer or class name
  QString strTitle;        // Title/job name
  QString strUser;         // User that submitted the job
  QString strFormat;       // Document format
  JOBS_STATE_E iState;     // Job state
  int iSize;               // Size in kilobytes
  int iPriority;           // Priority (1-100)
  time_t completedTime;     // Time the job was completed
  time_t creationTime;      // Time the job was created
  time_t processingTime;    // Time the job was processed
} JobsInfo;

/*
* 参数1: 获取任务列表信息
* 参数2: 打印机信息; nullptr: 所有打印机任务； 非空: 指定打印机名
* 参数3: ALLUSER_JOBS: 所有用户, USERSMIME_JOBS: 当前用户
* 参数4: WHICHJOBS_ALL: 全部任务
*       WHICHJOBS_ACTIVE: 活跃任务(pending, held, processing);
*       WHICHJOBS_COMPLETED: 已完成任务
*
* 默认获取所有用户，所有打印机的活跃任务信息
*/
extern int GetJobsInfo(QList<JobsInfo> &jobsInfo, QString name = nullptr, USER_JOB_E myjobs = ALLUSER_JOBS, WHICH_JOBS_E whichjobs = WHICHJOBS_ACTIVE);

#endif
