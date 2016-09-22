// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2014.4
// Copyright (C) 2014 Xilinx Inc. All rights reserved.
// 
// ==============================================================

#ifndef XFUNC_HLS_CORE_H
#define XFUNC_HLS_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xfunc_hls_core_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_bus_BaseAddress;
} XFunc_hls_core_Config;
#endif

typedef struct {
    u32 Control_bus_BaseAddress;
    u32 IsReady;
} XFunc_hls_core;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFunc_hls_core_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFunc_hls_core_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFunc_hls_core_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFunc_hls_core_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XFunc_hls_core_Initialize(XFunc_hls_core *InstancePtr, u16 DeviceId);
XFunc_hls_core_Config* XFunc_hls_core_LookupConfig(u16 DeviceId);
int XFunc_hls_core_CfgInitialize(XFunc_hls_core *InstancePtr, XFunc_hls_core_Config *ConfigPtr);
#else
int XFunc_hls_core_Initialize(XFunc_hls_core *InstancePtr, const char* InstanceName);
int XFunc_hls_core_Release(XFunc_hls_core *InstancePtr);
#endif

void XFunc_hls_core_Start(XFunc_hls_core *InstancePtr);
u32 XFunc_hls_core_IsDone(XFunc_hls_core *InstancePtr);
u32 XFunc_hls_core_IsIdle(XFunc_hls_core *InstancePtr);
u32 XFunc_hls_core_IsReady(XFunc_hls_core *InstancePtr);
void XFunc_hls_core_EnableAutoRestart(XFunc_hls_core *InstancePtr);
void XFunc_hls_core_DisableAutoRestart(XFunc_hls_core *InstancePtr);


void XFunc_hls_core_InterruptGlobalEnable(XFunc_hls_core *InstancePtr);
void XFunc_hls_core_InterruptGlobalDisable(XFunc_hls_core *InstancePtr);
void XFunc_hls_core_InterruptEnable(XFunc_hls_core *InstancePtr, u32 Mask);
void XFunc_hls_core_InterruptDisable(XFunc_hls_core *InstancePtr, u32 Mask);
void XFunc_hls_core_InterruptClear(XFunc_hls_core *InstancePtr, u32 Mask);
u32 XFunc_hls_core_InterruptGetEnabled(XFunc_hls_core *InstancePtr);
u32 XFunc_hls_core_InterruptGetStatus(XFunc_hls_core *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
