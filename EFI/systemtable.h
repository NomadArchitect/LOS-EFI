
#ifndef IMAGE_PROTOCOL_H
#define IMAGE_PROTOCOL_H

#include "bootservices.h"
#include "textprotocol.h"
#include "runtimeservices.h"

struct EFI_GUID EFI_LOADED_IMAGE_PROTOCOL_GUID   = {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
struct EFI_GUID EFI_DEVICE_PATH_PROTOCOL_GUID    = {0x09576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
struct EFI_GUID ACPI_20_TABLE_GUID               = {0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};

typedef struct EFI_CONFIGURATION_TABLE
{
    EFI_GUID                    VendorGuid;
    void                        *VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct EFI_SYSTEM_TABLE
{
	EFI_TABLE_HEADER                              hdr;
	char16_t                                     *FirmwareVendor;
	uint32_t                                      FirmwareVersion;
	EFI_HANDLE                                    ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL               *ConIn;
	EFI_HANDLE                                    ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL              *ConOut;
	EFI_HANDLE                                    StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL              *StdErr;
	EFI_RUNTIME_SERVICES                         *RuntimeServices;
	EFI_BOOT_SERVICES                            *BootServices;
	uint64_t                                      NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE                      *ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef struct EFI_LOADED_IMAGE_PROTOCOL
{
    uint32_t                     Revision;
    EFI_HANDLE                   ParentHandle;
    EFI_SYSTEM_TABLE            *SystemTable;
    EFI_HANDLE                   DeviceHandle;
    EFI_DEVICE_PATH_PROTOCOL    *FilePath;
    void                        *Reserved;
    uint32_t                     LoadOptionsSize;
    void                        *LoadOptions;
    void                        *ImageBase;
    uint64_t                     ImageSize;
} EFI_LOADED_IMAGE_PROTOCOL;

#endif // IMAGE_PROTOCOL_H