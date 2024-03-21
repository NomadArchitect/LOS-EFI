
#ifndef GOP_H
#define GOP_H

#include "typedefs.h"

// GRAPHICS
struct EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
struct EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef enum EFI_GRAPHICS_OUTPUT_BLT_OPERATION
{
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL
{
    uint8_t   Blue;
    uint8_t   Green;
    uint8_t   Red;
    uint8_t   Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef enum EFI_GRAPHICS_PIXEL_FORMAT
{
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct EFI_PIXEL_BITMASK
{
    uint32_t    RedMask;
    uint32_t    GreenMask;
    uint32_t    BlueMask;
    uint32_t    ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
{
    uint32_t                      Version;
    uint32_t                      HorizontalResolution;
    uint32_t                      VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT     PixelFormat;
    EFI_PIXEL_BITMASK             PixelInformation;
    uint32_t                      PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE
{
    uint32_t                                MaxMode;
    uint32_t                                Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION   *Info;
    uint64_t                                SizeOfInfo;
    EFI_PHYSICAL_ADDRESS                    FrameBufferBase;
    uint64_t                                FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, uint32_t ModeNumber, uint64_t *SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, uint32_t ModeNumber);
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, uint64_t SourceX, uint64_t SourceY, uint64_t DestinationX, uint64_t DestinationY, uint64_t Width, uint64_t Height, uint64_t Delta);

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE   QueryMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE     SetMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT          Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE        *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

#endif  // GOP_H