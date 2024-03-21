
/*
 BIG THANK YOU TO THE FOLLOWING PEOPLE WHO HELPED ME TO MAKE THIS OS POSSIBLE
    ANGEL
    QUESO
    JESTERJUNK
	STRYKER
	AND ALL OF MY YOUTUBE SUBSCRIBERS
*/

//#define BMP_IMPLEMENTATION
//#include "bmp.h"
#include "EFI/efilib.h"

unsigned long long strlen(const char* str)
{
	const char* strCount = str;

	while (*strCount++);
	return strCount - str - 1;
}

int strcmp(const char* a, const char* b)
{
	int length = strlen(a);
	for(int i = 0; i < length; i++)
	{
		if(a[i] < b[i]){return -1;}
		if(a[i] > b[i]){return 1;}
	}
	return 0;
}

// From the GNU-EFI
int64_t RtCompareGuid(EFI_GUID* Guid1, EFI_GUID* Guid2)
{
    int32_t *g1, *g2, r;
    g1 = (int32_t *) Guid1;
    g2 = (int32_t *) Guid2;
    r  = g1[0] - g2[0];
    r |= g1[1] - g2[1];
    r |= g1[2] - g2[2];
    r |= g1[3] - g2[3];
    return r;
}

int64_t CompareGuid(EFI_GUID* Guid1, EFI_GUID* Guid2)
{
    return RtCompareGuid (Guid1, Guid2);
}

/*
struct GDTEntry
{
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_mid;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
} __attribute__((__packed__));

struct GDTRegister
{
    uint16_t    limit;
    uint64_t    base;
} __attribute__((__packed__));

static struct {
    struct GDTEntry entry[5];
} __attribute__((__packed__)) gdt;

static struct GDTRegister GDTReg;

void gdt_init() {
    gdt.entry[0].limit_low = 0;
    gdt.entry[0].base_low = 0;
    gdt.entry[0].base_mid = 0;
    gdt.entry[0].access = 0;
    gdt.entry[0].granularity = 0;
    gdt.entry[0].base_high = 0;

    gdt.entry[1].limit_low = 0;
    gdt.entry[1].base_low = 0;
    gdt.entry[1].base_mid = 0;
    gdt.entry[1].access = 0b10011010;
    gdt.entry[1].granularity = 0b00100000;
    gdt.entry[1].base_high = 0;

    gdt.entry[2].limit_low = 0;
    gdt.entry[2].base_low = 0;
    gdt.entry[2].base_mid = 0;
    gdt.entry[2].access = 0b10010010;
    gdt.entry[2].granularity = 0;
    gdt.entry[2].base_high = 0;

    gdt.entry[3].limit_low = 0;
    gdt.entry[3].base_low = 0;
    gdt.entry[3].base_mid = 0;
    gdt.entry[3].access = 0b11111010;
    gdt.entry[3].granularity = 0b00100000;
    gdt.entry[3].base_high = 0;

    gdt.entry[4].limit_low = 0;
    gdt.entry[4].base_low = 0;
    gdt.entry[4].base_mid = 0;
    gdt.entry[4].access = 0b11110010;
    gdt.entry[4].granularity = 0;
    gdt.entry[4].base_high = 0;

    GDTReg.limit = (uint16_t) sizeof(gdt) - 1;
    GDTReg.base = (uint64_t) &gdt;

    __asm__ __volatile__("lgdt %0" :: "m"(GDTReg) : "memory");
	
	__asm__ __volatile__(
        "push %0\n\t"
        "push $1f\n\t"
        "lretq\n\t"
        "1:\n\t"
        "mov %1, %%ds\n\t"
        "mov %1, %%es\n\t"
        "mov %1, %%fs\n\t"
        "mov %1, %%gs\n\t"
        "mov %1, %%ss\n\t"
        :: "rmi"(0x08), "rm"(0x10)
        : "memory"
    );
}
*/

EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *system)
{
	
	InitEFI(image, system);

    if(gBuffer.ScreenHeight < 700)
	{
		DisplayWidth  = 800;
        DisplayHeight = 450;
	    readFile(u"EFI\\Boot\\LOS-Wallpaper-450.bmp");
	} else if((gBuffer.ScreenHeight >= 700) && (gBuffer.ScreenHeight < 800))
	{
		DisplayWidth  = 1364;
        DisplayHeight = 700;
	    readFile(u"EFI\\Boot\\LOS-Wallpaper-700.bmp");
	} else if((gBuffer.ScreenHeight >= 800) && (gBuffer.ScreenHeight < 1000))
	{
		DisplayWidth  = 1280;
        DisplayHeight = 800;
	    readFile(u"EFI\\Boot\\LOS-Wallpaper-800.bmp");
    } else if(gBuffer.ScreenHeight >= 1000)
	{
		DisplayWidth  = 1920;
        DisplayHeight = 1080;
	    readFile(u"EFI\\Boot\\LOS-Wallpaper-1080.bmp");
	}
	DrawBMPImage();
	
    CreateBufferFilledBox(1, gBuffer.ScreenHeight - 42, gBuffer.ScreenWidth - 3, 40, 0xFF111111);

	printf(u"Current Screen Resolution : %dx%d\r\n\r\n", gBuffer.ScreenWidth, gBuffer.ScreenHeight);

    printf(u"\r\n\r\nHit any key to continue\r\n");

    int lX = 10;
	int lY = 10;
	uint32_t m_color = 0xFF00FF00;
    for(uint32_t L = 0; L < 200; L++)
	{
		SetPixel(lX, lY, m_color);
		lX++;
		lY++;
		m_color++;
	}

	HitAnyKey();
	freeFileMemory();

    // Memory Map
	// ff

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
    SHUTDOWN();

    return ERROR_STATUS;
}

