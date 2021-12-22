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
 * Description: ptcr result print and export.
 ******************************************************************************/
#include "format_print.h"
#include <iostream>
#include "utils.h"
#include <stdio.h>
#include <ctime>

int MeasureResultCls::InsertMeasureReulst(Measure_Result_T *measureRes)
{
    NULL_PTR_CHECK(measureRes, RET_INVALID_INPUT_PARAM);

    m_measureResultVect.push_back(measureRes);
    return 0;
}

void MeasureResultCls::PrintAllResult()
{
    cout << "action\t|""count\t\t|""total spent\t\t|""average spent" << endl;
    for (auto item : m_measureResultVect) {
        cout << item->interfaceDesc << "\t|" << item->Cnt << "\t\t|" << item->totalSpent / 1000 <<
             "\t\t\t|" << (item->totalSpent - item->maxSpent - item->minSpent) / (item->Cnt - 2) / 1000 << endl;
    }
}

void MeasureResultCls::GetDescripesForReport(string *descAll)
{
    string descStr;
    if (descAll == NULL) {
        return;
    }

    for (auto item : m_measureResultVect) {
        descStr += item->interfaceDesc + " ";
    }
    *descAll = descStr;
}

int MeasureResultCls::InsertMeasureItem(Measure_Result_T *measureRes, long int currentSpent)
{
    NULL_PTR_CHECK(measureRes, RET_INVALID_INPUT_PARAM);

    m_mutex.lock();
    measureRes->totalSpent += currentSpent;
    if (currentSpent < measureRes->minSpent || measureRes->minSpent == 0) {
        measureRes->minSpent = currentSpent;
    } else if (currentSpent > measureRes->maxSpent || measureRes->maxSpent == 0) {
        measureRes->maxSpent = currentSpent;
    }
    measureRes->Cnt++;
    m_mutex.unlock();

    return 0;
}

int FormatPrintCls::InsertMeasureCls(MeasureResultCls *msCls)
{
    NULL_PTR_CHECK(msCls, RET_INVALID_INPUT_PARAM);

    m_measureResClsVect.push_back(msCls);
    return 0;
}

int FormatPrintCls::InsertDaemonRes(Mem_Daemon_T * res)
{
    NULL_PTR_CHECK(res, RET_INVALID_INPUT_PARAM);

    m_memDaemonVect.push_back(res);
    return 0;
}

int FormatPrintCls::InsertShimRes(Mem_Shim_T * res)
{
    NULL_PTR_CHECK(res, RET_INVALID_INPUT_PARAM);

    m_memShimVect.push_back(res);
    return 0;
}

void FormatPrintCls::GenerateReport(std::string &filePath)
{
    if (m_measureResClsVect.empty()) {
        return;
    }

    FILE *pF = fopen(filePath.c_str(), "w+");
    if (pF == 0) {
        LOG_ERROR("fopen %s failed!\n", filePath.c_str());
        return;
    }

    fprintf(pF, __DATE__ " " __TIME__ " %d times ptcr result\n",
            m_measureResClsVect[0]->m_measureResultVect[0]->Cnt);

    string *keys = new string;
    m_measureResClsVect[0]->GetDescripesForReport(keys);
    fprintf(pF, "%s\n", keys->c_str());
    delete keys;

    for (auto outter : m_measureResClsVect) {
        string context = outter->m_measureDesc + "_" + outter->m_endPoint + " ";
        for (auto inner : outter->m_measureResultVect) {
            context += to_string((inner->totalSpent / inner->Cnt / 1000)) + " ";
        }
        fprintf(pF, "%s\n", context.c_str());
    }

    fclose(pF);
}

void FormatPrintCls::formatPrint()
{
    time_t now = time(0);
    char *date = ctime(&now);

    cout << date << "unit: msec" << endl;
    cout << "------------------------------------------------------------------\n";
    for (auto item : m_measureResClsVect) {
        cout << "TargetName:" + item->m_endPoint + "\tType: " << item->m_measureDesc << endl;
        cout << "------------------------------------------------------------------\n";
        item->PrintAllResult();
        cout << "------------------------------------------------------------------\n";
    }
    cout << "\n------------------------------------------------------------------" << endl;
    for (auto item : m_memDaemonVect) {
        cout << "DaemonName: " + item->daemonName << "\nmem: " << item->daemonMemory << "kb" << endl;
    }
    cout << "------------------------------------------------------------------\n";
    for (auto item : m_memShimVect) {
        cout << "TargetName: " + item->endpoint << endl;
        cout << "count: " << item->cnt << "\nTotal shim mem: " << item->shimTotalMemory << "kb" << endl;
        cout << "------------------------------------------------------------------\n";
    }
}
