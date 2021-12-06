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
 * Description: provide Apiwrapper class definition.
 ******************************************************************************/
#ifndef SRC_WRAP_API_WRAP_H
#define SRC_WRAP_API_WRAP_H

#include "wrap.h"

class ApiWrapperCls : public measureWrapperCls {
public:
    ApiWrapperCls(string &cliName);
    virtual ~ApiWrapperCls();

    virtual int pullImage(string &imageName);
    virtual int removeImage(string &imageName);
    virtual int createContainer(string &imageName, string *contStr);
    virtual int startContainer(string &contStr);
    virtual int runContainer(string &imageName, vector<string> &cmd, string *contStr);
    virtual int stopContainer(string contId, int timeOut);
    virtual int stopAllContainer();
    virtual int rmContainer(string ContId);

private:
    string m_cliName;
    string m_podID;
};

#endif
