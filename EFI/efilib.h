
#ifndef EFI_LIB_H
#define EFI_LIB_H

#include "efi.h"

#define MAX_LENGTH 22

             // ARGB             
#define ORANGE 0xffffa500
#define CYAN   0xff00ffff
#define RED    0xffff0000
#define GREEN  0xff00ff00
#define BLUE   0xff0000ff
#define GRAY   0xff888888
#define WHITE  0xffffffff
#define BLACK  0xff000000

EFI_HANDLE                       ImageHandle;
EFI_SYSTEM_TABLE                *SystemTable;
EFI_STATUS                       ERROR_STATUS;
uint64_t                         CurrentColor;
EFI_GRAPHICS_OUTPUT_PROTOCOL    *gop;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume;
EFI_FILE_PROTOCOL               *RootFS;
void*    imageFile = NULL;

uint32_t DisplayWidth  = 0;
uint32_t DisplayHeight = 0;

struct GRAPHICSBUFFER
{
    void*    BaseAddress;
    uint64_t BufferSize;
    uint32_t ScreenWidth;
    uint32_t ScreenHeight;
    uint32_t PixelsPerScanLine;
} gBuffer;

typedef struct {
	uint32_t cols;  // Left / Right
	uint32_t rows;  // Up / Down
} Timer_Context;

EFI_EVENT timer_event;

void Delay(uint64_t d)
{
    // The Stall function is set as microseconds.
    SystemTable->BootServices->Stall(d);
}

void clearScreen()
{
	SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
}

void setTextColor(uint64_t color)
{
	CurrentColor = color;
	SystemTable->ConOut->SetAttribute(SystemTable->ConOut, CurrentColor);
}

void SetTextPosition(uint32_t Col, uint32_t Row)
{
    SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, Col, Row);
}

void printUInt64Digits(uint64_t num, int base)
{
    char16_t uint64Str[MAX_LENGTH] = {'\0'};
	
	const char16_t* digits = u"0123456789ABCDEF";
	uint64_t i = 0;

	do
	{
		uint64Str[i++] = digits[num % base];
        num /= base;
	} while(num > 0);
	
    uint64Str[i--] = '\0';
	
	for(uint64_t j = 0; j < i; j++, i--)
	{
		uint64_t temp = uint64Str[i];
		uint64Str[i]  = uint64Str[j];
		uint64Str[j]  = temp;
	}
	
	SystemTable->ConOut->OutputString(SystemTable->ConOut, uint64Str);
}

void printIntDigits(int32_t num)
{
    char16_t int32Str[12] = {'\0'};
	
	const char16_t* digits = u"0123456789";
	uint64_t i = 0;
	int negative = (num < 0);
	if(negative) {num = -num;}
	
	do
	{
		int32Str[i++] = digits[num % 10];
		num /= 10;
	} while(num > 0);
	
	if(negative) {int32Str[i++] = '-';}
	
	int32Str[i--] = '\0';
	
	for(uint64_t j = 0; j < i; j++, i--)
	{
		uint64_t temp = int32Str[i];
		int32Str[i] = int32Str[j];
		int32Str[j] = temp;
	}
	
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int32Str);
}

void printf(char16_t* txt, ...)
{
	char16_t charStr[2]   = {'\0'};

	va_list args;
	va_start(args, txt);
	
	for(uint64_t i = 0; txt[i] != '\0'; i++)
	{
		if(txt[i] == '%')
		{
			i++;
			switch(txt[i])
			{
                case u'c': {
                    charStr[0] = va_arg(args, int);
                    SystemTable->ConOut->OutputString(SystemTable->ConOut, charStr);
					break;
                }
				case 's':
				{
					uint16_t* varString = va_arg(args, uint16_t*);
					SystemTable->ConOut->OutputString(SystemTable->ConOut, varString);
					break;
				}
				case 'd':
				{
					int32_t number = va_arg(args, int32_t);
					printIntDigits(number);
					break;
				}
                case u'b':
				{
					uint64_t bin = va_arg(args, uint64_t);
					printUInt64Digits(bin, 2);
					break;
                }
				case 'x':
				{
					uint64_t hex = va_arg(args, uint64_t);
					printUInt64Digits(hex, 16);
					break;
				}
				case 'l':
				{
					if(txt[i+1] == 'l' && txt[i+2] == 'u')
					{
						i+=2;
                        uint64_t num = va_arg(args, uint64_t);
						printUInt64Digits(num, 10);
					}
					break;
				}

				default:
				{
					SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
				    SystemTable->ConOut->OutputString(SystemTable->ConOut, u"\r\nERROR : Invalid format: %");
					SystemTable->ConOut->OutputString(SystemTable->ConOut, &txt[i]);
					SystemTable->ConOut->OutputString(SystemTable->ConOut, u"\r\n");
					SystemTable->ConOut->SetAttribute(SystemTable->ConOut, CurrentColor);
					return;
					break;
				}
			}
		} else {
			charStr[0] = txt[i];
			SystemTable->ConOut->OutputString(SystemTable->ConOut, charStr);
		}
	}

	va_end(args);
}

void HitAnyKey()
{
    SystemTable->ConIn->Reset(SystemTable->ConIn, 1);
    EFI_INPUT_KEY Key;

    do
	{
		Delay(1);
	} while((SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);
}

void ResetKeyboard()
{
    SystemTable->ConIn->Reset(SystemTable->ConIn, 1);
}

EFI_INPUT_KEY CheckKeystroke;
int32_t GetKey(char16_t key)
{
    if(CheckKeystroke.UnicodeChar == key)
    {
        return 1;
    } else {
        return 0;
    }
}

EFI_STATUS CheckKey()
{
    return SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &CheckKeystroke);
}

EFI_GRAPHICS_OUTPUT_BLT_PIXEL* SetGraphicsColor(uint32_t color)
{
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* GColor = {0};
    GColor->Reserved = color >> 24;
    GColor->Red      = color >> 16;
    GColor->Green    = color >> 8;
    GColor->Blue     = color;
    return GColor;
}

// This positions the pixel in the row and column ( X and Y )
void SetPixel(uint32_t xPos, uint32_t yPos, uint32_t mColor)
{
    // TODO : Add in a choice instead of defaulting to EfiBltVideoFill.
    gop->Blt(gop, SetGraphicsColor(mColor), EfiBltVideoFill, 0, 0, xPos, yPos, 1, 1, 0);
}

void CreateBufferFilledBox(uint32_t xPos, uint32_t yPos, uint32_t w, uint32_t h, uint32_t Color)
{
    // This functions puts a color filled box on the screen
    uint32_t ByteOffset = 4;
    if(xPos < 0){xPos = 0;}
    if(yPos < 0){yPos = 0;}
    if(w < 1){w = 1;}
    if(h < 1){h = 1;}
    uint32_t x;
    uint32_t y      = yPos;
    uint32_t width  = (xPos + w) * ByteOffset;
    uint32_t height = yPos + h;

    for(y = yPos; y <= height; y++)
    {
        for(x = xPos * ByteOffset; x <= width; x+=ByteOffset)
        {
            *(uint32_t*)(x + (y * gBuffer.PixelsPerScanLine * ByteOffset) + gBuffer.BaseAddress) = *(uint32_t*)&Color;
        }
    }
}

void InitializeGOP()
{
    // We initialize the Graphics Output Protocol.
    // This is used instead of the VGA interface.
	SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
    printf(L"\r\n\r\nLoading Graphics Output Protocol ... ");
    EFI_STATUS Status = SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 0, (void**)&gop);
    if(Status != EFI_SUCCESS)
    {
		SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
		printf(CheckStandardEFIError(Status));
    } else {
		SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
		printf(CheckStandardEFIError(Status));
	}

	SystemTable->ConOut->SetAttribute(SystemTable->ConOut, CurrentColor);
	
    gBuffer.BaseAddress        = (void*)gop->Mode->FrameBufferBase;
    gBuffer.BufferSize         = gop->Mode->FrameBufferSize;
    gBuffer.ScreenWidth        = gop->Mode->Info->HorizontalResolution;
    gBuffer.ScreenHeight       = gop->Mode->Info->VerticalResolution;
    gBuffer.PixelsPerScanLine  = gop->Mode->Info->PixelsPerScanLine;
}

void print_datetime(EFI_EVENT event, void *Context)
{
	(void)event;
	(void)Context;

    uint32_t save_col = SystemTable->ConOut->Mode->CursorColumn, save_row = SystemTable->ConOut->Mode->CursorRow;

    EFI_TIME time = {0};
    EFI_TIME_CAPABILITIES capabilities = {0};
    SystemTable->RuntimeServices->GetTime(&time, &capabilities);

    SetTextPosition(40, 24);

    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_YELLOW);
	
	const uint16_t* ampmArray[2] = {u"AM", u"PM"};
	int ampm       = 0;
	int32_t hour   = time.Hour;
	int32_t minute = time.Minute;
	if(hour > 12)
	{
		ampm = 1;
		hour -= 12;
	}
	if(hour == 0)
	{
		hour = 12;
	}	

    printf(u"%llu/%c%llu/%llu %d:%c%d %s",
            time.Month,
            time.Day    < 10 ? '0' : '\0', time.Day,
			time.Year,
            hour,
            minute < 10 ? '0' : '\0', minute,
            ampmArray[ampm]);

    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, CurrentColor);
    SetTextPosition(save_col, save_row);
}

// FILE
void InitializeFILESYSTEM()
{
    EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
	EFI_DEVICE_PATH_PROTOCOL *DevicePath;
	
    if((SystemTable->BootServices->HandleProtocol(ImageHandle, &EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&LoadedImage)) == EFI_SUCCESS)
	{
		if((SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &EFI_DEVICE_PATH_PROTOCOL_GUID, (void**)&DevicePath)) == EFI_SUCCESS)
		{
			if((SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&Volume)) == EFI_SUCCESS)
			{
				if((Volume->OpenVolume(Volume, &RootFS)) != EFI_SUCCESS)
				{
					printf(u"Loading Root File System FAILED!\r\n");
				}
			} else {
		        printf(u"Volume Handle FAILED!\r\n");
	        }
		} else {
		    printf(u"DevicePath FAILED!\r\n");
	    }
	} else {
		printf(u"LoadedImage FAILED!\r\n");
	}
}

uint64_t* GetFileSize (EFI_FILE_PROTOCOL* FileNameHandle)
{
    uint64_t* Size = 0;
    FileNameHandle->SetPosition(FileNameHandle, 0xFFFFFFFFFFFFFFFFULL);
    FileNameHandle->GetPosition(FileNameHandle, Size);
	FileNameHandle->SetPosition(FileNameHandle, 0);
    return Size;
}

void closeFile(EFI_FILE_PROTOCOL* FileHandle)
{
    // This closes the file.
    EFI_STATUS Status;
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
    printf(u"Closing File ... ");
    Status = FileHandle->Close(FileHandle);
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
    printf(CheckStandardEFIError(Status));
}

EFI_FILE_PROTOCOL* openFile(uint16_t* FileName)
{
    // This opens a file from the EFI FAT32 file system volume.
    // It loads from root, so you must supply full path if the file is not in the root.
    // Example : "somefolder//myfile"  <--- Notice the double forward slash.
    EFI_STATUS Status;
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
    printf(u"RootFS ... ");
    Status = Volume->OpenVolume(Volume, &RootFS);
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
    printf(CheckStandardEFIError(Status));
    
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
    printf(u"Opening File ... ");
    EFI_FILE_PROTOCOL* FileHandle = NULL;
    Status = RootFS->Open(RootFS, &FileHandle, FileName, 0x0000000000000001, 0);
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
    printf(CheckStandardEFIError(Status));
    
    return FileHandle;
}

void readFile(uint16_t* FileName)
{
    // We create the buffer, allocate memory for it, then read
    // the file into the buffer. After which, we close the file.
	// Currently we are using a fixed size. Eventually we will fix that.
	// Currently we have a fixed Buffer Handle as well. Eventually we will fix that.
    EFI_FILE_PROTOCOL* m_FileHandle = openFile(FileName);
    if(m_FileHandle != NULL)
    {
		uint64_t FileSize = 0;
		m_FileHandle->SetPosition(m_FileHandle, 0xFFFFFFFFFFFFFFFFULL);
		m_FileHandle->GetPosition(m_FileHandle, &FileSize);
		m_FileHandle->SetPosition(m_FileHandle, 0);
		
        SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
        printf(u"AllocatingPool ... ");
        EFI_STATUS Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, FileSize, (void**)&imageFile);
        SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
        printf(CheckStandardEFIError(Status));
    
        SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
        printf(u"Reading File ... ");
        Status = m_FileHandle->Read(m_FileHandle, &FileSize, imageFile);
        SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
        printf(CheckStandardEFIError(Status));

        closeFile(m_FileHandle);
    }
}

void freeFileMemory()
{
	SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
	printf(u"Freeing Pool ... ");
	EFI_STATUS Status = SystemTable->BootServices->FreePool(imageFile);
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
    printf(CheckStandardEFIError(Status));
}

void DrawBMPImage()
{
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL GColor;

    GColor.Reserved = 0xFF;
	uint8_t* tempColor = (uint8_t*)imageFile;
  
    for(int i = 0; i < 54; i++)
	{
		tempColor++;
	}
	
    for(uint32_t y = DisplayHeight; y > 0; y--)
  	{
  		for(uint32_t x = 0; x < DisplayWidth; x++)
  		{
  			GColor.Blue    = *tempColor;
  			tempColor++;
            GColor.Green   = *tempColor;
  			tempColor++;
            GColor.Red     = *tempColor;
  			tempColor++;
  			gop->Blt(gop, &GColor, EfiBltVideoFill, 0, 0, x, y, 1, 1, 0);
  		}
  	}
}

void COLD_REBOOT()
{
    // Hardware Reboot
    SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, 0);
}

void WARM_REBOOT()
{
    // Software reboot
    SystemTable->RuntimeServices->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, 0);
}

void SHUTDOWN()
{
    // Shuts off the computer
    // NOTE : This does not work in VirtualBox.
    // WORKS in QEMU !!!
    SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, 0);
}

void CPU_HALT()
{
	while(1)
	{
		Delay(1);
	};
}

void InitEFI(EFI_HANDLE handle, EFI_SYSTEM_TABLE  *table)
{
	ImageHandle   = handle;
	SystemTable   = table;
	ERROR_STATUS  = 0;
	SystemTable->ConOut->Reset(SystemTable->ConOut, 1);
	
	setTextColor(EFI_GREEN);

	SystemTable->BootServices->SetWatchdogTimer(0, 0x10000, 0, NULL);

	InitializeGOP();

	InitializeFILESYSTEM();

	// Create timer event, to update aliens around once per second
	SystemTable->BootServices->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, print_datetime, NULL, &timer_event);

	// Set Timer for the timer event to run every 1 second (in 100ns units)
    SystemTable->BootServices->SetTimer(timer_event, TimerPeriodic, 10000000);
}

#endif  // EFI_LIB_H

	//printf(u"\r\n");


    //uint64_t* tempImage = imageFile;
	//printf(u"ADDRESS : %s\r\n", &tempImage[8]);

	//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
	//printf(u"Freeing Pool ... ");
	//Status = SystemTable->BootServices->FreePool(g);
    //SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
    //printf(CheckStandardEFIError(Status));
	//for(int m = 0; m < 5; m++)
	//{
	//	uint8_t g = *tempImage;
	//	printf(u"%x  ", g);
	//	tempImage++;
	//}

	//int w, h, bitDepth;

  //  imageFile->SetPosition(imageFile, 8);
    // (void *Destination, void *Source, uint64_t Length)
	//fseek(pFile, 8, SEEK_CUR);
	//fread(&image_data_address, 4, 1, pFile);
	//fseek(pFile, 4, SEEK_CUR);
	//fread(w, 4, 1, pFile);
	//fread(h, 4, 1, pFile);
	//fseek(pFile, 2, SEEK_CUR);
	//fread(bitDepth, 2, 1, pFile);
	//uint8_t g = *tempImage;
	//uint8_t* tempImage = (uint8_t*)imageFile;
	//uint8_t g[5];
	//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
	//printf(u"AllocatingPool ... ");
	//EFI_STATUS Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, 5, (void**)&g);
	//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
	//printf(CheckStandardEFIError(Status));
	//
	//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_BROWN);
	//printf(u"Copying Memory ... ");
	//Status = SystemTable->BootServices->CopyMem(g, &tempImage[8], 4);
	//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_CYAN);
	//printf(CheckStandardEFIError(Status));