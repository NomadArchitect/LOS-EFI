
/*
 BIG THANK YOU TO THE FOLLOWING PEOPLE WHO HELPED ME TO MAKE THIS OS POSSIBLE
    ANGEL
    QUESO
    JESTERJUNK
    STRYKER
    AND ALL OF MY YOUTUBE SUBSCRIBERS
*/

#include "EFI/efilib.h"
//#include "EFI/gdt.h"

typedef struct BLOCKINFO
{
    void*                  BaseAddress;
    uint64_t               BufferSize;
    uint32_t               ScreenWidth;
    uint32_t               ScreenHeight;
    uint32_t               PixelsPerScanLine;
	EFI_MEMORY_DESCRIPTOR* MMap;
	uint64_t               MMapSize;
	uint64_t               MMapDescriptorSize;
	uint64_t*              rsdp;
} __attribute__((__packed__)) BLOCKINFO;

EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *system)
{
	InitEFI(image, system);
	
	DrawWallpaperBMPImage();

    BLOCKINFO bi;

    uint64_t ENTRY_POINT = 0;
	void* OSBuffer = readFile(u"los-efi\\loader.bin", &ENTRY_POINT);
    uint8_t* OSloader = (uint8_t*)OSBuffer;

	if(OSBuffer == NULL)
	{
		setTextColor(EFI_RED);
		printf(u"ERROR : OSBuffer is NULL !\r\n");
		setTextColor(EFI_GREEN);
	}
	
	if(ENTRY_POINT <= 0)
	{
		setTextColor(EFI_RED);
		printf(u"ERROR : Entry Point is ZERO !\r\n");
		setTextColor(EFI_GREEN);
	} else {
		printf(u"ENTRY POINT : %llu\r\n", ENTRY_POINT);
	}


	// RSDP
	EFI_CONFIGURATION_TABLE* configTable = SystemTable->ConfigurationTable;
	unsigned long long* tempRSDP = NULL;
	for(uint64_t index = 0; index < SystemTable->NumberOfTableEntries; index++)
	{
		if(CompareGuid(&configTable[index].VendorGuid, &ACPI_20_TABLE_GUID))
		{
			if(strcmp((char*)"RSD PTR ", (char*)configTable->VendorTable) == 0)
			{
				tempRSDP = (void*)configTable->VendorTable;
			}
		}
		configTable++;
	}

    // Memory Map
    uint64_t                MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR  *MemoryMap = NULL;
//    uint64_t                MapKey = 0;
    uint64_t                DescriptorSize = 0;
//    uint32_t                DescriptorVersion = 0;

//	SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
//	MemoryMapSize += 2 * DescriptorSize;
//	SystemTable->BootServices->AllocatePool(2, MemoryMapSize, (void **)&MemoryMap);
//	SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);

    bi.BaseAddress        = gBuffer.BaseAddress;
    bi.BufferSize         = gBuffer.BufferSize;
    bi.ScreenWidth        = gBuffer.ScreenWidth;
    bi.ScreenHeight       = gBuffer.ScreenHeight;
    bi.PixelsPerScanLine  = gBuffer.PixelsPerScanLine;
	bi.MMap               = MemoryMap;
	bi.MMapSize           = MemoryMapSize;
	bi.MMapDescriptorSize = DescriptorSize;
	bi.rsdp               = tempRSDP;

    int32_t (*KernelBinFile)(BLOCKINFO*) = ((__attribute__((ms_abi)) int32_t (*)(BLOCKINFO*)) &OSloader[ENTRY_POINT]);

//    SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);
	
//	gdt_init();

    int32_t result = KernelBinFile(&bi);
	
	setTextColor(EFI_YELLOW);
	printf(u"\r\n\r\nRETURNED RESULT FROM LOADED FILE : %d\r\n\r\n", result);
	
	setTextColor(EFI_BROWN);
	printf(u"Hit any key to shut down computer.");
	
	HitAnyKey();
	SHUTDOWN();

    return ERROR_STATUS;
}

