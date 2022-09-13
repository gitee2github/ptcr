#ifndef SRC_LOGIC_MEMORY_H
#define SRC_LOGIC_MEMORY_H

#include "config.h"
#include <map>

using namespace std;

class MeasureMemImpl {
public:
    MeasureMemImpl() {}
    MeasureMemImpl(vector<string> runtimeName, vector<string> daemonName, MeasureConfigCls *config)
    {
        m_config = config;

        m_cnt = config->m_cntMemory;

        for (auto it : runtimeName) {
            m_shim[it] = 0;
        }
        for (auto it : daemonName) {
            m_daemon[it] = 0;
        }
    }
    ~MeasureMemImpl() {}

    int PsDaemonOutsideFunc();
    int PsShimOutsideFunc();

    unsigned int m_cnt;
    MeasureConfigCls *m_config;
    map<string, long int> m_daemon;
    map<string, long int> m_shim;
};

#endif