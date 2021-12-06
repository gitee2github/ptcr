/******************************************************************************
 * Copyright (c) KylinSoft  Co., Ltd. 2021. All rights reserved.
 * ptcr licensed under the Mulan PSL v2.

 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *     http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
 * PURPOSE.
 * See the Mulan PSL v2 for more details.
 * Author: xiapin
 * Create: 2021-11-29
 * Description: provide logger module definition.
 ******************************************************************************/
#ifndef SRC_LOGIC_LOGGER_H
#define SRC_LOGIC_LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    L_DEBUG     = 0,
    L_INFO,
    L_WARN,
    L_ERROR,
    L_FATAL,

    L_NR,
} LOG_LERVER_E;

#define LOG_OUT(lever, fmt, ...)   vlog_in(lever, "%s@[%s]%d:" fmt, #lever, __func__, __LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(fmt ...)   LOG_OUT(L_DEBUG, fmt)
#define LOG_INFO(fmt ...)    LOG_OUT(L_INFO, fmt)
#define LOG_WARN(fmt ...)    LOG_OUT(L_WARN, fmt)
#define LOG_ERROR(fmt ...)   LOG_OUT(L_ERROR, fmt)
#define LOG_FATAL(fmt ...)   LOG_OUT(L_FATAL, fmt)

#define TRACE()  LOG_OUT(L_DEBUG, "---> start...\n")

int vlog_in(LOG_LERVER_E lever, const char *format, ...) __attribute__((format(printf, 2, 3)));

void set_log_lever(LOG_LERVER_E lever);

#ifdef __cplusplus
}
#endif
#endif
