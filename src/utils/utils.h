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
 * Description: utils module function definition.
 ******************************************************************************/
#ifndef SRC_UTILS_UTILS_H
#define SRC_UTILS_UTILS_H

#include <string.h>
#include <stdlib.h>

#include "local_error.h"
#include "logger.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UTILS_CALLOC(size, err_do)  \
    ({\
        void *__p = malloc(size);\
        if (__p)\
            memset(__p, 0, size);\
        else\
            err_do;\
        __p;\
    })

#define UTILS_FREE(p)\
    do {\
        if (p)\
        {\
            free(p);\
            p = NULL;\
        }\
    } while (0);

#define UNUSED(x)       (void)(x)

#define CONTAINER_ID_SIZE 16
#define MAX_COMMAND_SIZE 64
#define PS_RSS_INDEX 6
#define MAX_PS_READ_SIZE 100

int utils_execute_process(const char *file, char * const params[]);

char **utils_create_str_array(unsigned str_cnt, ...);

void utils_free_arr(char ***arr);

char *utils_generate_random_str(int len);

int utils_exe_cmd_read_out(const char *command, char *out, int size);

int get_cont_id_by_name(const char *endpoint, const char *name, char id[CONTAINER_ID_SIZE]);

int read_memory(const char *id, int *rss);

#ifdef __cplusplus
}
#endif

#endif
