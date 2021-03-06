//==================================================================================
// Copyright (c) 2013-2016 , Advanced Micro Devices, Inc.  All rights reserved.
//
/// \author AMD Developer Tools Team
/// \file CPAdapterDataDefs.h
///
//==================================================================================

#ifndef _CPADAPTERDATADEFS_H_
#define _CPADAPTERDATADEFS_H_

// Infra.
#include <AMDTBaseTools/Include/gtString.h>
#include <AMDTBaseTools/Include/gtHashMap.h>
#include <AMDTCommonHeaders/AMDTCommonProfileDataTypes.h>

struct CPAdapterTopology
{
    gtUInt32 coreId;
    gtUInt16 processor;
    gtUInt16 numaNode;

    CPAdapterTopology(gtUInt32 coreId, gtUInt16 proc, gtUInt16 numa) : coreId(coreId), processor(proc), numaNode(numa) {}
};

using CPAdapterTopologyMap = gtVector<CPAdapterTopology>;

struct CPAProcessInfo
{
    gtUInt32 pid;
    gtString name;
    bool is32Bit;

    CPAProcessInfo(gtUInt32 pid, gtString name, bool is32Bit) : pid(pid), name(name), is32Bit(is32Bit) {}
};

using CPAProcessList = gtVector<CPAProcessInfo>;

struct CPAModuleInfo
{
    gtUInt32 m_id;
    gtString m_name;
    gtUInt32 m_size;
    gtUInt32 m_type;
    bool     m_isSysModule;
    bool     m_is32Bit;
    bool     m_foundDebugInfo;

    CPAModuleInfo(gtUInt32 id, gtString name, gtUInt32 size, gtUInt32 type, bool isSysModule, bool is32Bit, bool foundDebugInfo) :
        m_id(id), m_name(name), m_size(size), m_type(type), m_isSysModule(isSysModule), m_is32Bit(is32Bit), m_foundDebugInfo(foundDebugInfo) {}
};

using CPAModuleList = gtVector<CPAModuleInfo>;

struct CPAModuleInstanceInfo
{
    gtUInt32 m_id;
    gtUInt32 m_moduleId;
    gtUInt64 m_pid;
    gtUInt64 m_loadAddr;

    CPAModuleInstanceInfo(gtUInt32 id, gtUInt32 moduleId, gtUInt64 pid, gtUInt64 loadAddr) :
        m_id(id), m_moduleId(moduleId), m_pid(pid), m_loadAddr(loadAddr) {}
};

using CPAModuleInstanceList = gtVector<CPAModuleInstanceInfo>;

struct CPAProcessThreadInfo
{
    gtUInt64 pid;
    gtUInt32 threadId;

    CPAProcessThreadInfo(gtUInt64 pid, gtUInt32 threadId) : pid(pid), threadId(threadId) {}

    bool operator<(const CPAProcessThreadInfo& rhs) const { return (pid < rhs.pid) || ((pid == rhs.pid) && (threadId < rhs.threadId)); }
};

using CPAProcessThreadList = gtVector<CPAProcessThreadInfo>;

struct CPACoreSamplingConfigInfo
{
    gtUInt32 coreId;
    gtUInt32 eventMask;

    CPACoreSamplingConfigInfo(gtUInt32 coreId, gtUInt32 eventMask) : coreId(coreId), eventMask(eventMask) {}

    // bool operator<(const CPACoreSamplingConfigInfo& rhs) const { return (coreId < rhs.coreId) || ((coreId == rhs.coreId) && (eventMask < rhs.eventMask)); }
    bool operator<(const CPACoreSamplingConfigInfo& rhs) const { return (eventMask < rhs.eventMask) || ((eventMask == rhs.eventMask) && (coreId < rhs.coreId)); }
};

using CPACoreSamplingConfigList = gtVector<CPACoreSamplingConfigInfo>;

struct CPASampleInfo
{
    gtUInt64 m_pid = 0;
    gtUInt32 m_threadId = 0;
    gtUInt32 m_moduleInstanceId = 0;
    gtUInt32 m_coreId = 0;
    gtUInt32 m_eventMask = 0;
    gtUInt32 m_functionid = 0;
    // m_offset is w.r.t. module load address
    gtUInt64 m_offset = 0;
    gtUInt64 m_count = 0;

    CPASampleInfo(gtUInt64 pid, gtUInt32 threadId, gtUInt32 moduleInstanceId, gtUInt32 coreId, gtUInt32 eventMask, gtUInt32 functionid, gtUInt64 offset, gtUInt64 count) :
        m_pid(pid), m_threadId(threadId), m_moduleInstanceId(moduleInstanceId), m_coreId(coreId), m_eventMask(eventMask), m_functionid(functionid), m_offset(offset), m_count(count) {}
};

using CPASampeInfoList = gtVector<CPASampleInfo>;

struct CPAFunctionInfo
{
    gtUInt32 m_funcId = 0;
    gtUInt32 m_modId = 0;
    gtString m_funcName;
    // m_funcStartOffset is w.r.t. module base address, so for multiple instances of module,
    // value of m_funcStartOffset is same for the same function
    gtUInt64 m_funcStartOffset = 0;
    gtUInt64 m_funcSize = 0;

    CPAFunctionInfo(gtUInt32 funcId, gtUInt32 modId, gtString& funcName, gtUInt64 funcStartOffset, gtUInt64 funcSize) :
        m_funcId(funcId), m_modId(modId), m_funcName(funcName), m_funcStartOffset(funcStartOffset), m_funcSize(funcSize) {}
};

using CPAFunctionInfoList = gtVector<CPAFunctionInfo>;

#endif //_CPADAPTERDATADEFS_H_
