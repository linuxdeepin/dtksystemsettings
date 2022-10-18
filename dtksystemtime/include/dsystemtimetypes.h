// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DSYSTEMTIMETYPES_H
#define DSYSTEMTIMETYPES_H

#include <qobject.h>
#include "dtksystemtime_global.h"

DSYSTEMTIME_BEGIN_NAMESPACE

struct Address
{
    qint32 type;
    QByteArray ip;
};

struct Message
{
    quint32 ntp_field_leap; /*!< @~english warning code Indicates the next leap to be inserted in the NTP time scale. A value of
                               "11" indicates an alarm state and the clock cannot be synchronized.*/
    quint32 ntp_field_version; /*!< @~english Version number of NTP*/
    quint32
        ntp_field_mode;       /*!< @~english The operating modes of NTP. The meanings of the different values are as follows: 0:
                                 reserved,    reserved. 1: symmetric active, active peer mode. 2: symmetric passive, passive peer mode.
                                 3:    client, client mode. 4: server, server mode. 5: broadcast, broadcast mode. 6: reserved for NTP
                                 control messages, NTP control messages. 7: reserved for private use, NTP control messages. 8:
                                 reserved for private use, NTP control messages. 9: reserved for private use, NTP control messages.
                                 reserved for NTP control messages. 7: reserved for private use, reserved for internal use.*/
    quint32 ntp_msg_stratum;  /*!< @~english The number of layers of the clock defines the accuracy of the clock. The clock with
                                 layer number   1 has the highest accuracy, decreasing from 1 to 15.*/
    qint32 ntp_msg_precision; /*!< @~english Accuracy of the clock*/
    quint64 ntp_ts_short_to_usec_delay;      /*!< @~english Total round-trip delay time to the master reference clock*/
    quint64 ntp_ts_short_to_usec_dispersion; /*< The maximum error of the local clock with respect to the main reference clock.*/
    QByteArray ntp_msg_refid;   /*< The NTP REFID specifies a string of 4 ASCII characters that defines the reference identifier
                                   used by the driver.   The REFID string overrides the default identifier ordinarily assigned by
                                   the driver itself.*/
    quint64 origin_time;        /*!< @~english The local time when the NTP message leaves the source. */
    quint64 ntp_msg_recv_time;  /*!< @~english Local time of arrival of NTP messages at the destination*/
    quint64 ntp_msg_trans_time; /*!< @~english The local time when the answer message leaves the server side at the destination*/
    quint64 dest_time;          /*!< @~english The time to reply to the NTP server after the NTP message is received locally*/
    bool spike;
    quint64 packet_count;
    quint64 samples_jitter;
};

DSYSTEMTIME_END_NAMESPACE

#endif

// TODO: 文档需要用的内容，完成文档后删除
//  // r = sd_bus_message_append(reply, "uuuuitt",
//  //                           NTP_FIELD_LEAP(m->ntpmsg.field),
//  //                           NTP_FIELD_VERSION(m->ntpmsg.field),
//  //                           NTP_FIELD_MODE(m->ntpmsg.field),
//  //                           m->ntpmsg.stratum,
//  //                           m->ntpmsg.precision,
//  //                           ntp_ts_short_to_usec(&m->ntpmsg.root_delay),
//  //                           ntp_ts_short_to_usec(&m->ntpmsg.root_dispersion));
//  // if (r < 0)
//  //         return r;

// // r = sd_bus_message_append_array(reply, 'y', m->ntpmsg.refid, 4);
// // if (r < 0)
// //         return r;

// // r = sd_bus_message_append(reply, "ttttbtt",
// //                           timespec_load(&m->origin_time),
// //                           ntp_ts_to_usec(&m->ntpmsg.recv_time),
// //                           ntp_ts_to_usec(&m->ntpmsg.trans_time),
// //                           timespec_load(&m->dest_time),
// //                           m->spike,
// //                           m->packet_count,
// //                           (usec_t) (m->samples_jitter * USEC_PER_SEC));

// /*

// NTP 客户端发送带有本地时间的数据包 orig_time , NTP 服务器在服务器时间接收 recv_time .然后服务器在服务器时间回复
// tx_time客户端在本地时间收到回复 dest_time .

// 往返delay计算为 recv_time - orig_time + dest_time - tx_time ，并且时钟之间的偏移量是 offset = (recv_time - orig_time + tx_time
// - dest_time) / 2 .

// 假设两个NTP数据包采用一致的路径，正确的调整时间就是dest_time + offset ，相当于 tx_time + delay/2 .
// */