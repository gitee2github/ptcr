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
#ifdef CRI_CLIENT // default open

#include "wrap.h"
#include <grpcpp/grpcpp.h>
#include "api.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace runtime::v1alpha2;

class RuntimeClient final {
public:
    RuntimeClient(std::shared_ptr<Channel> channel)
      : stub_(RuntimeService::NewStub(channel)) {}
    ~RuntimeClient() {};

    std::string GetVersion(const string &version);
    int RunPodSandBox(string *podID);
    int StopPodSandBox(string &podID);
    int RemovePodSandBox(string &podID);

    int CreateContainer(string &podID, string &imageName, string *contID, bool bRun, vector<string> &cmd);
    int StartContainer(string &contID);
    int StopContainer(string &contID, int timeOut);
    int RemoveContainer(string &contID);
    int RunContainer(string &imageName, vector<string> &cmd, string *contStr);

private:
    std::unique_ptr<RuntimeService::Stub> stub_;
};

class ImageClient final {
public:
    ImageClient(std::shared_ptr<Channel> channel)
        : stub_(ImageService::NewStub(channel)) {}
    ~ImageClient() {};

    int PullImage(string &imageName);
    int RemoveImage(string &imageName);
private:
    std::unique_ptr<ImageService::Stub> stub_;
};

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
    RuntimeClient *m_criClient;
    ImageClient *m_imageClient;
};

#endif
#endif
