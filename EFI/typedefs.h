
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdint.h>
#include <stddef.h>  // NULL
#include <stdarg.h>

#define FALSE 0
#define TRUE  1

typedef uint_least16_t char16_t;

typedef uint64_t      EFI_STATUS;
typedef uint64_t      EFI_PHYSICAL_ADDRESS;
typedef uint64_t      EFI_VIRTUAL_ADDRESS;
typedef void         *EFI_EVENT;
typedef void         *EFI_HANDLE;

typedef enum EFI_MEMORY_TYPE
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef struct EFI_GUID
{
    uint32_t    Data1;
    uint16_t    Data2;
    uint16_t    Data3;
    uint8_t     Data4[8];
} EFI_GUID;

typedef struct EFI_TABLE_HEADER
{
    uint64_t    Signature;
    uint32_t    Revision;
    uint32_t    HeaderSize;
    uint32_t    CRC32;
    uint32_t    Reserved;
} EFI_TABLE_HEADER;

typedef struct EFI_TIME
{
	uint16_t     Year;
	uint8_t      Month;
	uint8_t      Day;
	uint8_t      Hour;
	uint8_t      Minute;
	uint8_t      Second;
	uint8_t      Pad1;
	uint32_t     Nanosecond;
	uint16_t     TimeZone;
	uint8_t      DayLight;
	uint8_t      Pad2;
} EFI_TIME;

typedef struct EFI_MEMORY_DESCRIPTOR
{
    uint32_t                   Type;
    EFI_PHYSICAL_ADDRESS       PhysicalStart;
    EFI_VIRTUAL_ADDRESS        VirtualStart;
    uint64_t                   NumberOfPages;
    uint64_t                   Attribute;
} EFI_MEMORY_DESCRIPTOR;

#endif // TYPEDEFS_H