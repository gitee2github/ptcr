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
 * Description: provide config class definition.
 ******************************************************************************/
#ifndef SRC_LOGIC_CONFIG_H
#define SRC_LOGIC_CONFIG_H

#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"
#include "logger.h"

typedef enum {
    MEASURE_SERIALLY     = 0,
    MEASURE_PARALLERL,

    ATTACK_TYPE_NR,
} MEASURE_TYPE_E;

typedef struct {
    MEASURE_TYPE_E  measureType;
    unsigned        measureCnt;
} Measure_Way_T;

typedef struct {
    std::string configPath;
    std::string outputFile;
    std::string logLever;
    std::string seriallyCount;
    std::string parallyCount;
} OptArgs_T;

class MeasureConfigCls {
public:
    MeasureConfigCls(std::string &configPath);
    ~MeasureConfigCls() {};

    int Init();
    void Deinit();
    int ConfigOptArgs(OptArgs_T *optArgs);

    LOG_LERVER_E                m_logLever;
    /* The path of config file */
    std::string                 m_cfgPath;
    /* measure result save to */
    std::string                 m_outputFile;
    /* each command time out */
    unsigned                    m_timeOut;
    /* used to start container */
    std::string                 m_imageName;
    /* mixed command or not */
    bool                        m_isCmdMixed;

    std::vector <std::string>   m_runtimeName;
    std::vector <std::string>   m_runtimeEndpoint;
    std::vector <std::string>   m_runContCmd;
    std::vector <Measure_Way_T *> m_measureWayVect;

private:
    YAML::Node                  m_node;

    std::string GetNodeKeyValue(std::string key, std::string deflt);
    int         GetNodeKeyValue(std::string key, int deflt);
    std::string GetNodeKeyValue(std::string section, std::string key, std::string deflt);
    int         GetNodeKeyValue(std::string section, std::string key, int deflt);
    int         GetStringVector(std::string key, std::vector<std::string> &strVect);

    int         GetMeasureWay();
};

#endif
