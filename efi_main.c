
/*
 BIG THANK YOU TO THE FOLLOWING PEOPLE WHO HELPED ME TO MAKE THIS OS POSSIBLE
    ANGEL
    QUESO
    JESTERJUNK
    STRYKER
    AND ALL OF MY YOUTUBE SUBSCRIBERS
*/

#include "EFI/efilib.h"
#include "EFI/gdt.h"

EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *system)
{
	InitEFI(image, system);

	DrawWallpaperBMPImage();
	
    CreateBufferFilledBox(1, gBuffer.ScreenHeight - 42, gBuffer.ScreenWidth - 3, 40, 0xFF111111);

	printf(u"Current Screen Resolution : %dx%d\r\n\r\n", gBuffer.ScreenWidth, gBuffer.ScreenHeight);

    printf(u"\r\n\r\nHit any key to continue\r\n");

	HitAnyKey();

    // Memory Map
	// Coming Soon

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
		        printf(u"RSD PTR : 0x%x\r\n", tempRSDP);
			}
		}
		configTable++;
	}

	printf(u"\n\r\nHit any key to shutdown computer\r\n");
	HitAnyKey();
	
	//gdt_init(); // This technically should not work until we have a kernel to jump to.

    SHUTDOWN();

    return ERROR_STATUS;
}

