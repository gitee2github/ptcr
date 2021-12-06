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
 * Description: provide measure class definition.
 ******************************************************************************/
#ifndef SRC_LOGIC_ATTACKER_H
#define SRC_LOGIC_ATTACKER_H

#include "config.h"
#include "wrap.h"
#include "format_print.h"

class MeasureImpl {
public:
    virtual ~MeasureImpl() {}
    virtual int startWithMixedCmd() = 0;
    virtual int startWithoutMixedCmd() = 0;
    virtual int start()
    {
        if (m_config->m_isCmdMixed) {
            return startWithMixedCmd();
        }

        return startWithoutMixedCmd();
    }

    unsigned int m_cnt;
    wrapperManager *m_wrapperManager;
    MeasureConfigCls *m_config;
    MeasureResultCls *m_measureResCls;
};

class measureCls {
public:
    measureCls() {}
    ~measureCls() {}

    int startMeasure(MeasureConfigCls *config);

private:
    int runWrapperRepeat(MeasureConfigCls *config, wrapperManager *wm);
};

#endif
