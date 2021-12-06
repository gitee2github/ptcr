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
 * Description: provide container manager class definition.
 ******************************************************************************/
#ifndef SRC_LOGIC_CONTAINER_MANAGER_H
#define SRC_LOGIC_CONTAINER_MANAGER_H

#include "wrap.h"
#include <mutex>

typedef struct ST_Cont_Info {
    string *contId;
    CONT_STAT_E stat;
} Cont_Info_T;

typedef struct ST_Wrap_Cont_Info {
    wrapperManager *m_RtWrapper;
    vector<Cont_Info_T *> m_ContInfo;
} Wrap_Cont_Info_T;

class WrapContInfoCls {
public:
    WrapContInfoCls() {}
    ~WrapContInfoCls() {}

    int InsertWrapper(wrapperManager *wrapper);
    int ContBindWrapper(string *contId, CONT_STAT_E state, wrapperManager *wrapper);
    int GetContVectByWrapper(wrapperManager *wrapper, vector<Cont_Info_T *> *ContVect);
    void PrintAllContInfo();
    void CleanAllCont(wrapperManager *wrapper);
    void ResourceRls();

    static WrapContInfoCls *GetInstance()
    {
        static WrapContInfoCls *self = NULL;
        if (self == NULL) {
            self = new WrapContInfoCls;
        }
        return self;
    }

private:
    void StopAndRemoveContainer(wrapperManager *wm, Cont_Info_T *contInfo);
    vector<Wrap_Cont_Info_T *> m_wrapContInfo;
    mutex m_mutex;
};

#endif
