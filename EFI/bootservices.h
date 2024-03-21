
#ifndef BOOT_SERVICES_H
#define BOOT_SERVICES_H

#include "typedefs.h"

typedef uint64_t     EFI_TPL;

struct EFI_BOOT_SERVICES;

typedef enum EFI_LOCATE_SEARCH_TYPE
{
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef enum EFI_INTERFACE_TYPE
{
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum EFI_ALLOCATE_TYPE
{
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum EFI_TIMER_DELAY
{
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

typedef struct EFI_DEVICE_PATH_PROTOCOL
{
    uint8_t   Type;
    uint8_t   SubType;
    uint8_t   Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
{
    EFI_HANDLE                    AgentHandle;
    EFI_HANDLE                    ControllerHandle;
    uint32_t                      Attributes;
    uint32_t                      OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef void(*EFI_EVENT_NOTIFY)(EFI_EVENT Event, void *Context);

typedef EFI_STATUS (*EFI_RAISE_TPL)(EFI_TPL NewTpl);
typedef EFI_STATUS (*EFI_RESTORE_TPL)(EFI_TPL OldTpl);
typedef EFI_STATUS (*EFI_ALLOCATE_PAGES)(EFI_ALLOCATE_TYPE Type, uint64_t MemoryType, uint64_t Pages, EFI_PHYSICAL_ADDRESS *Memory);
typedef EFI_STATUS (*EFI_FREE_PAGES)(EFI_PHYSICAL_ADDRESS Memory, uint64_t Pages);
typedef EFI_STATUS (*EFI_GET_MEMORY_MAP)(uint64_t *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap, uint64_t *MapKey, uint64_t *DescriptorSize, uint32_t *DescriptorVersion);
typedef EFI_STATUS (*EFI_ALLOCATE_POOL)(uint64_t PoolType, uint64_t Size, void **Buffer);
typedef EFI_STATUS (*EFI_FREE_POOL)(void *Buffer);
typedef EFI_STATUS (*EFI_CREATE_EVENT)(uint32_t Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, void *NotifyContext, EFI_EVENT *Event);
typedef EFI_STATUS (*EFI_SET_TIMER)(EFI_EVENT Event, EFI_TIMER_DELAY Type, uint64_t TriggerTime);
typedef EFI_STATUS (*EFI_WAIT_FOR_EVENT)(uint64_t NumberOfEvents, EFI_EVENT *Event, uint64_t *Index);
typedef EFI_STATUS (*EFI_SIGNAL_EVENT)(EFI_EVENT Event);
typedef EFI_STATUS (*EFI_CLOSE_EVENT)(EFI_EVENT Event);
typedef EFI_STATUS (*EFI_CHECK_EVENT)(EFI_EVENT Event);
typedef EFI_STATUS (*EFI_INSTALL_PROTOCOL_INTERFACE)(EFI_HANDLE *Handle, EFI_GUID *Protocol, EFI_INTERFACE_TYPE InterfaceType, void *Interface);
typedef EFI_STATUS (*EFI_REINSTALL_PROTOCOL_INTERFACE)(EFI_HANDLE Handle, EFI_GUID *Protocol, void *OldInterface, void *NewInterface);
typedef EFI_STATUS (*EFI_UNINSTALL_PROTOCOL_INTERFACE)(EFI_HANDLE Handle, EFI_GUID *Protocol, void *Interface);
typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol, void **Interface);
typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY)(EFI_GUID *Protocol, EFI_EVENT Event, void **Registration);
typedef EFI_STATUS (*EFI_LOCATE_HANDLE)(EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol, void *SearchKey, uint64_t *BufferSize, EFI_HANDLE *Buffer);
typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH)(EFI_GUID *Protocol, EFI_DEVICE_PATH_PROTOCOL **DevicePath, EFI_HANDLE *Device);
typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE)(EFI_GUID *Guid, void *Table);
typedef EFI_STATUS (*EFI_IMAGE_LOAD)(uint8_t BootPolicy, EFI_HANDLE ParentImageHandle, EFI_DEVICE_PATH_PROTOCOL *DevicePath, void *SourceBuffer, uint64_t SourceSize, EFI_HANDLE *ImageHandle);
typedef EFI_STATUS (*EFI_IMAGE_START)(EFI_HANDLE ImageHandle, uint64_t *ExitDataSize, char16_t **ExitData);
typedef EFI_STATUS (*EFI_EXIT)(EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus, uint64_t ExitDataSize, char16_t *ExitData);
typedef EFI_STATUS (*EFI_IMAGE_UNLOAD)(EFI_HANDLE ImageHandle);
typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(EFI_HANDLE ImageHandle, uint64_t MapKey);
typedef EFI_STATUS (*EFI_GET_NEXT_MONOTONIC_COUNT)(uint64_t *Count);
typedef EFI_STATUS (*EFI_STALL)(uint64_t Microseconds);
typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER)(uint64_t Timeout, uint64_t WatchdogCode, uint64_t DataSize, char16_t *WatchdogData);
typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER)(EFI_HANDLE ControllerHandle, EFI_HANDLE *DriverImageHandle, EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, uint8_t Recursive);
typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER)(EFI_HANDLE ControllerHandle, EFI_HANDLE DriverImageHandle, EFI_HANDLE ChildHandle);
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol, void **Interface, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle, uint32_t Attributes);
typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle);
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION)(EFI_HANDLE Handle, EFI_GUID *Protocol, EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer, uint64_t *EntryCount);
typedef EFI_STATUS (*EFI_PROTOCOLS_PER_HANDLE)(EFI_HANDLE Handle, EFI_GUID ***ProtocolBuffer, uint64_t *ProtocolBufferCount);
typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER)(EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID *Protocol, void *SearchKey, uint64_t *NoHandles, EFI_HANDLE **Buffer);
typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL)(EFI_GUID *Protocol, void *Registration, void **Interface);
typedef EFI_STATUS (*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(EFI_HANDLE *Handle, ...);
typedef EFI_STATUS (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(EFI_HANDLE *Handle, ...);
typedef EFI_STATUS (*EFI_CALCULATE_CRC32)(void *Data, uint64_t DataSize, uint32_t *Crc32);
typedef EFI_STATUS (*EFI_COPY_MEM)(void *Destination, void *Source, uint64_t Length);
typedef EFI_STATUS (*EFI_SET_MEM)(void *Buffer, uint64_t Size, uint8_t Value);
typedef EFI_STATUS (*EFI_CREATE_EVENT_EX)(uint32_t Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, void *NotifyContext, EFI_GUID *EventGroup, EFI_EVENT *Event);

typedef struct EFI_BOOT_SERVICES
{
    EFI_TABLE_HEADER                                 Hdr;
    EFI_RAISE_TPL                                    RaiseTPL;
    EFI_RESTORE_TPL                                  RestoreTPL;
    EFI_ALLOCATE_PAGES                               AllocatePages;
    EFI_FREE_PAGES                                   FreePages;
    EFI_GET_MEMORY_MAP                               GetMemoryMap;
    EFI_ALLOCATE_POOL                                AllocatePool;
    EFI_FREE_POOL                                    FreePool;
    EFI_CREATE_EVENT                                 CreateEvent;
    EFI_SET_TIMER                                    SetTimer;
    EFI_WAIT_FOR_EVENT                               WaitForEvent;
    EFI_SIGNAL_EVENT                                 SignalEvent;
    EFI_CLOSE_EVENT                                  CloseEvent;
    EFI_CHECK_EVENT                                  CheckEvent;
    EFI_INSTALL_PROTOCOL_INTERFACE                   InstallProtocolInterface;
    EFI_REINSTALL_PROTOCOL_INTERFACE                 ReinstallProtocolInterface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE                 UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL                              HandleProtocol;
    void                                             *Reserved;
    EFI_REGISTER_PROTOCOL_NOTIFY                     RegisterProtocolNotify;
    EFI_LOCATE_HANDLE                                LocateHandle;
    EFI_LOCATE_DEVICE_PATH                           LocateDevicePath;
    EFI_INSTALL_CONFIGURATION_TABLE                  InstallConfigurationTable;
    EFI_IMAGE_LOAD                                   LoadImage;
    EFI_IMAGE_START                                  StartImage;
    EFI_EXIT                                         Exit;
    EFI_IMAGE_UNLOAD                                 UnloadImage;
    EFI_EXIT_BOOT_SERVICES                           ExitBootServices;
    EFI_GET_NEXT_MONOTONIC_COUNT                     GetNextMonotonicCount;
    EFI_STALL                                        Stall;
    EFI_SET_WATCHDOG_TIMER                           SetWatchdogTimer;
    EFI_CONNECT_CONTROLLER                           ConnectController;
    EFI_DISCONNECT_CONTROLLER                        DisconnectController;
    EFI_OPEN_PROTOCOL                                OpenProtocol;
    EFI_CLOSE_PROTOCOL                               CloseProtocol;
    EFI_OPEN_PROTOCOL_INFORMATION                    OpenProtocolInformation;
    EFI_PROTOCOLS_PER_HANDLE                         ProtocolsPerHandle;
    EFI_LOCATE_HANDLE_BUFFER                         LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL                              LocateProtocol;
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES         InstallMultipleProtocolInterfaces;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES       UninstallMultipleProtocolInterfaces;
    EFI_CALCULATE_CRC32                              CalculateCrc32;
    EFI_COPY_MEM                                     CopyMem;
    EFI_SET_MEM                                      SetMem;
    EFI_CREATE_EVENT_EX                              CreateEventEx;
} EFI_BOOT_SERVICES;

#endif // BOOT_SERVICES_H