/*
 * zsummerX License
 * -----------
 *
 * zsummerX is licensed under the terms of the MIT license reproduced below.
 * This means that zsummerX is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 *
 *
 * ===============================================================================
 *
 * Copyright (C) 2010-2016 YaweiZhang <yawei.zhang@foxmail.com>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ===============================================================================
 *
 * (end of COPYRIGHT)
 */

#ifndef BREEZE_SERVICE_H_
#define BREEZE_SERVICE_H_
#include <common.h>


using Slot = std::function < void(const Tracing & trace, zsummer::proto4z::ReadStream &) >;
using ServiceCallback = std::function<void(zsummer::proto4z::ReadStream &)>;

using ProtoID = zsummer::proto4z::ProtoInteger;
const ProtoID InvalidProtoID = -1;

enum ServiceStatus
{
    SS_CREATED,
    SS_INITING,
    SS_WORKING,
    SS_UNINITING,
    SS_DESTROY,
};



class Docker;
class Service : public std::enable_shared_from_this<Service>
{
    friend Docker;
public:
    Service(){}
    virtual ~Service(){};

public:
    inline ui16 getServiceType(){ return _serviceType; }
    inline ServiceID getServiceID(){ return _serviceID; }
    inline DockerID getDockerID() { return _dockerID; }
    inline SessionID getClientID() { return _clientID; }

    inline ui16 getStatus() { return _status; }
    inline bool isShell() { return _shell; }
protected:
    inline void setServiceType(ui16 serviceType) { _serviceType = serviceType; }
    inline void setServiceID(ServiceID serviceID) { _serviceID = serviceID; }
    inline void setDockerID(DockerID dockerID) { _dockerID = dockerID; }
    inline void setClientID(SessionID clientID) { _clientID = clientID; }

    inline void setStatus(ui16 status) { _status = status; };
    inline void setShell(bool shell) { _shell = shell; }

private:
    void beginTimer();
    void onTimer();
protected:
    virtual void onTick() = 0; //���޵���ģʽ���ҷ�shell��service�Ż������� 

    virtual bool onInit() = 0; //service��ʼ����֮��Ҫ����finishInit 
    bool finishInit();
    virtual void onUninit() = 0;//serviceж�غ�֮��Ҫ����finishUninit 
    bool finishUninit();

protected:
    using Slots = std::unordered_map<unsigned short, Slot>;
    template<class Proto>
    inline void slotting(const Slot & msgfun) { _slots[Proto::getProtoID()] = msgfun; _slotsName[Proto::getProtoID()] = Proto::getProtoName(); }
    
    virtual void process(const Tracing & trace, const char * block, unsigned int len);
    virtual void process4bind(const Tracing & trace, const std::string & block);

    void toService(ui16 st, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    void toService(ui16 st, ServiceID svcID, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    template<class Proto>
    void toService(ui16 st, Proto proto, ServiceCallback cb = nullptr);
    template<class Proto>
    void toService(ui16 st, ServiceID svcID, Proto proto, ServiceCallback cb = nullptr);

    void backToService(const Tracing & trace, const char * block, unsigned int len, ServiceCallback cb = nullptr);
    template<class Proto>
    void backToService(const Tracing & trace, Proto proto, ServiceCallback cb = nullptr);

    ui32 makeCallback(const ServiceCallback &cb);
    void cleanCallback();
    ServiceCallback checkoutCallback(ui32 cbid);

private:
    Slots _slots;
    std::map<ProtoID, std::string> _slotsName;

    TimerID _timer = InvalidTimerID;

private:
    ui16 _serviceType = (ui16)ServiceInvalid;
    ServiceID _serviceID = InvalidServiceID;
    DockerID _dockerID = InvalidDockerID; //ʵ�����ڵ�docker
    SessionID _clientID = InvalidSessionID; //������ڹ����Ŀͻ���,���ID������ʵ������docker�е�sessionID. Ŀǰ����UserServiceʹ��
    short _status = 0;
    bool _shell = false;
    

private:
    ui32 _callbackSeq = 0;
    time_t _callbackCleanTS = 0;
    std::map<ui32, std::pair<time_t,ServiceCallback> > _cbs;

};
using ServicePtr = std::shared_ptr<Service>;

template<class Proto>
void Service::toService(ui16 st, Proto proto, ServiceCallback cb)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(st, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toService catch except error. e=" << e.what());
    }
}
template<class Proto>
void Service::toService(ui16 st, ServiceID svcID, Proto proto, ServiceCallback cb)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        toService(st, svcID, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::toService catch except error. e=" << e.what());
    }
}

template<class Proto>
void Service::backToService(const Tracing & trace, Proto proto, ServiceCallback cb)
{
    try
    {
        WriteStream ws(Proto::getProtoID());
        ws << proto;
        backToService(trace, ws.getStream(), ws.getStreamLen(), cb);
    }
    catch (const std::exception & e)
    {
        LOGE("Service::backToService catch except error. e=" << e.what());
    }
}












#endif


