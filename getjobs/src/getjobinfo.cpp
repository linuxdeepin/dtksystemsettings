// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "getjobinfo.h"

#include <cups/cups.h>

int GetJobsInfo(QList<JobsInfo> &jobsInfo, QString name, USER_JOB_E myjobs, WHICH_JOBS_E whichjobs)
{
    cups_job_t *jobs = nullptr;
    int num_jobs = cupsGetJobs(&jobs, name.toStdString().c_str(), myjobs, whichjobs);

    int i = 0;
    cups_job_t *job = nullptr;

    for (i = num_jobs, job = jobs; i > 0; i--, job++) {
        JobsInfo tmpInfo;

        tmpInfo.id = job->id;
        tmpInfo.strDest = job->dest;
        tmpInfo.strTitle = job->title;
        tmpInfo.strUser = job->user;
        tmpInfo.strFormat = job->format;
        tmpInfo.iState = (JOBS_STATE_E)job->state;
        tmpInfo.iSize = job->size;
        tmpInfo.iPriority = job->priority;

        tmpInfo.completedTime = job->completed_time;
        tmpInfo.creationTime = job->creation_time;
        tmpInfo.processingTime =  job->processing_time;

        jobsInfo.append(tmpInfo);
    }

    cupsFreeJobs(num_jobs, jobs); // 需要释放内存

    return 0;
}

