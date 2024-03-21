
#ifndef RUNTIME_SERVICES_H
#define RUNTIME_SERVICES_H

#include "typedefs.h"

// EFI_TPL Levels (Task priority levels)
#define TPL_APPLICATION 4   // 0b00000100
#define TPL_CALLBACK    8   // 0b00001000
#define TPL_NOTIFY      16  // 0b00010000
#define TPL_HIGH_LEVEL  31  // 0b00011111

// EFI_EVENT types 
// These types can be "ORed" together as needed - for example,
// EVT_TIMER might be "ORed" with EVT_NOTIFY_WAIT or EVT_NOTIFY_SIGNAL.
#define EVT_TIMER                         0x80000000
#define EVT_RUNTIME                       0x40000000
#define EVT_NOTIFY_WAIT                   0x00000100
#define EVT_NOTIFY_SIGNAL                 0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES     0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

typedef enum EFI_RESET_TYPE
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef struct EFI_CAPSULE_HEADER
{
    EFI_GUID                      CapsuleGuid;
    uint32_t                      HeaderSize;
    uint32_t                      Flags;
    uint32_t                      CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef struct EFI_TIME_CAPABILITIES
{
	uint32_t      Resolution;
	uint32_t      Accuracy;
	uint8_t       SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef EFI_STATUS (*EFI_GET_TIME)(EFI_TIME *Time, EFI_TIME_CAPABILITIES *Capabilities);
typedef EFI_STATUS (*EFI_SET_TIME)(EFI_TIME *Time);
typedef EFI_STATUS (*EFI_GET_WAKEUP_TIME)(uint8_t *Enabled, uint8_t *Pending, EFI_TIME *Time);
typedef EFI_STATUS (*EFI_SET_WAKEUP_TIME)(uint8_t Enable, EFI_TIME *Time);
typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(uint64_t MemoryMapSize, uint64_t DescriptorSize, uint32_t DescriptorVersion, EFI_MEMORY_DESCRIPTOR *VirtualMap);
typedef EFI_STATUS (*EFI_CONVERT_POINTER)(uint64_t DebugDisposition, void **Address);
typedef EFI_STATUS (*EFI_GET_VARIABLE)(char16_t *VariableName, EFI_GUID *VendorGuid, uint32_t *Attributes, uint64_t *DataSize, void *Data);
typedef EFI_STATUS (*EFI_GET_NEXT_VARIABLE_NAME)(uint64_t *VariableNameSize, char16_t *VariableName, EFI_GUID *VendorGuid);
typedef EFI_STATUS (*EFI_SET_VARIABLE)(char16_t *VariableName, EFI_GUID *VendorGuid, uint32_t Attributes, uint64_t DataSize, void *Data);
typedef EFI_STATUS (*EFI_GET_NEXT_HIGH_MONO_COUNT)(uint32_t *HighCount);
typedef EFI_STATUS (*EFI_RESET_SYSTEM)(EFI_RESET_TYPE ResetType, EFI_STATUS ResetStatus, uint64_t DataSize, void *ResetData);
typedef EFI_STATUS (*EFI_UPDATE_CAPSULE)(EFI_CAPSULE_HEADER **CapsuleHeaderArray, uint64_t CapsuleCount, EFI_PHYSICAL_ADDRESS ScatterGatherList);
typedef EFI_STATUS (*EFI_QUERY_CAPSULE_CAPABILITIES)(EFI_CAPSULE_HEADER **CapsuleHeaderArray, uint64_t CapsuleCount, uint64_t *MaximumCapsuleSize, EFI_RESET_TYPE *ResetType);
typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO)(uint32_t Attributes, uint64_t *MaximumVariableStorageSize, uint64_t *RemainingVariableStorageSize, uint64_t *MaximumVariableSize);

typedef struct EFI_RUNTIME_SERVICES
{
    EFI_TABLE_HEADER                    Hdr;
    EFI_GET_TIME                        GetTime;
    EFI_SET_TIME                        SetTime;
    EFI_GET_WAKEUP_TIME                 GetWakeupTime;
    EFI_SET_WAKEUP_TIME                 SetWakeupTime;
    EFI_SET_VIRTUAL_ADDRESS_MAP         SetVirtualAddressMap;
    EFI_CONVERT_POINTER                 ConvertPointer;
    EFI_GET_VARIABLE                    GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME          GetNextVariableName;
    EFI_SET_VARIABLE                    SetVariable;
    EFI_GET_NEXT_HIGH_MONO_COUNT        GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM                    ResetSystem;
    EFI_UPDATE_CAPSULE                  UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES      QueryCapsuleCapabilities;
    EFI_QUERY_VARIABLE_INFO             QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

#endif  // RUNTIME_SERVICES_H