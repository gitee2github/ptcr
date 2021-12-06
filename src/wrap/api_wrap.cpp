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
 * Description: measure by cri interface implement.
 ******************************************************************************/
#include "api_wrap.h"
#include <stdlib.h>
#include "utils.h"

#define CONFIG_DIR      "/etc/ptcr/"
#define POD_CONFIG      CONFIG_DIR "pod_config.json "
#define CONT_CONFIG     CONFIG_DIR "container_config.json "
#define COMMAND_PREFIX  "crictl --runtime-endpoint "
#define ID_LEN          (128)

ApiWrapperCls::ApiWrapperCls(string &cliName) : m_cliName(cliName)
{
    string runpCmd;
    char buf[ID_LEN] = {0};

    runpCmd = COMMAND_PREFIX + m_cliName + " runp " + POD_CONFIG;

    utils_exe_cmd_read_out(runpCmd.c_str(), buf, ID_LEN);
    m_podID = buf;
}

ApiWrapperCls::~ApiWrapperCls()
{
    if (!m_podID.empty()) {
        string stopCmd = COMMAND_PREFIX + m_cliName + " stopp " + m_podID;
        string removeCmd = COMMAND_PREFIX + m_cliName + " rmp " + m_podID;

        utils_exe_cmd_read_out(stopCmd.c_str(), NULL, 0);
        utils_exe_cmd_read_out(removeCmd.c_str(), NULL, 0);
    }
}

int ApiWrapperCls::pullImage(string &imageName)
{
    int ret = 0;
    char *buf = (char *)UTILS_CALLOC(ID_LEN, RET_OUT_OF_MEMORY);

    string cmd = COMMAND_PREFIX + m_cliName + " pull " + imageName;
    ret = utils_exe_cmd_read_out(cmd.c_str(), buf, ID_LEN);
    free(buf);

    return ret;
}

int ApiWrapperCls::removeImage(string &imageName)
{
    int ret = 0;
    char *buf = (char *)UTILS_CALLOC(ID_LEN, RET_OUT_OF_MEMORY);

    string cmd = COMMAND_PREFIX + m_cliName + " rmi " + imageName;
    ret = utils_exe_cmd_read_out(cmd.c_str(), buf, ID_LEN);
    free(buf);

    return ret;
}

static int GenerateRandContName()
{
    int ret;
    char *cmd = NULL;
    char buf[4] = {0};

    char *randID = utils_generate_random_str(4);
    ret = asprintf(&cmd, "sed -i \"s/$(grep name %s | cut -d : -f2)/ \\\"%s\\\"/g\" %s",
                   CONT_CONFIG, randID, CONT_CONFIG);
    if (ret < 0) {
        return ret;
    }

    ret = utils_exe_cmd_read_out(cmd, buf, sizeof(buf));
    free(cmd);
    free(randID);

    return ret;
}

int ApiWrapperCls::createContainer(string &imageName, string *contStr)
{
    int ret;
    string createCmd;
    char *buf = (char *)UTILS_CALLOC(ID_LEN, RET_OUT_OF_MEMORY);

    memset(buf, 0, ID_LEN);
    ret = GenerateRandContName();
    RET_CHECK(ret, 0, goto exit);

    createCmd = COMMAND_PREFIX + m_cliName + " create " + m_podID + " " + CONT_CONFIG + " " + POD_CONFIG;
    ret = utils_exe_cmd_read_out(createCmd.c_str(), buf, ID_LEN);
    if (ret != 0 || strlen(buf) == 0) {
        LOG_ERROR("exe %s failed!\n", createCmd.c_str());
        ret = -1;
        goto exit;
    }

    *contStr = buf;
    ret = 0;

    LOG_DEBUG("Create cont:%s ret:%d\n", buf, ret);
exit:
    if (buf != NULL) {
        free(buf);
    }

    return ret;
}

int ApiWrapperCls::startContainer(string &contStr)
{
    int ret = 0;
    if (m_podID.empty()) {
        LOG_ERROR("Pod not create yet!\n");
        return -1;
    }

    char *buf = (char *)UTILS_CALLOC(ID_LEN, RET_OUT_OF_MEMORY);
    string cmd = COMMAND_PREFIX + m_cliName + " start " + contStr;
    ret = utils_exe_cmd_read_out(cmd.c_str(), buf, ID_LEN);

    LOG_DEBUG("Start cont:%s ret:%d\n", contStr.c_str(), ret);

    return ret;
}

int ApiWrapperCls::runContainer(string &imageName, vector<string> &cmd, string *contStr)
{
    // TODO
    return 0;
}

int ApiWrapperCls::stopContainer(string contId, int timeOut)
{
    int ret = 0;
    if (m_podID.empty()) {
        LOG_ERROR("Pod not create yet!\n");
        return -1;
    }

    char *buf = (char *)UTILS_CALLOC(ID_LEN, RET_OUT_OF_MEMORY);
    string cmd = COMMAND_PREFIX + m_cliName + " stop " + contId;
    ret = utils_exe_cmd_read_out(cmd.c_str(), buf, ID_LEN);

    LOG_DEBUG("Stop cont:%s ret:%d\n", contId.c_str(), ret);

    return ret;
}

int ApiWrapperCls::stopAllContainer()
{
    // TODO
    return 0;
}

int ApiWrapperCls::rmContainer(string ContId)
{
    int ret = 0;
    if (m_podID.empty()) {
        LOG_ERROR("Pod not create yet!\n");
        return -1;
    }

    char *buf = (char *)UTILS_CALLOC(ID_LEN, RET_OUT_OF_MEMORY);
    string cmd = COMMAND_PREFIX + m_cliName + " rm " + ContId;
    ret = utils_exe_cmd_read_out(cmd.c_str(), buf, ID_LEN);

    LOG_DEBUG("Rm cont:%s ret:%d\n", ContId.c_str(), ret);

    return ret;
}
