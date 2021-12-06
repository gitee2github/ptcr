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
 * Description: provide ptcr error code define.
 ******************************************************************************/
#ifndef SRC_LOGIC_LOCAL_ERROR_H
#define SRC_LOGIC_LOCAL_ERROR_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_NO_BASE                 (10000)

#define ERR_INVALID_INPUT_PARAM     (ERR_NO_BASE + 1)
#define ERR_NULL_PTR                (ERR_NO_BASE + 2)
#define ERR_OOM                     (ERR_NO_BASE + 3)

#define ERR_FAILURE                 {return -1;}
#define ERR_NULL                    {return NULL;}
#define RET_INVALID_INPUT_PARAM     {return ERR_INVALID_INPUT_PARAM;}
#define RET_OUT_OF_MEMORY           {return ERR_OOM;}

#define NULL_PTR_CHECK(ptr, err_do)\
    do {\
        if (ptr == NULL)\
        {\
            LOG_OUT(L_ERROR, "%s null ptr checked!\n", #ptr);\
            err_do;\
        }\
    } while (0);

#define RET_CHECK(ret, expr, err_do)\
    do {\
        if (ret != expr) {\
            LOG_ERROR("error %d != %d\n", ret, expr);\
            err_do;\
        }\
    } while(0);

static inline const char *get_err_msg(unsigned int errno)
{
    unsigned index = 0;
    const char *err_str =
        "invalid input param\0"
        "null ptr check\0"
        "error out of memory\0"
        ;

    while (*err_str) {
        if (index == errno - ERR_NO_BASE - 1) {
            return err_str;
        }
        err_str += strlen(err_str) + 1;
        index++;
    }

    return NULL;
}

#ifdef __cplusplus
}
#endif

#endif
