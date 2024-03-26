
void init8Bit(void)
{
	CLEAR_8BIT(0);
	CLEAR_8BIT(1);
	CLEAR_8BIT(2);
	CLEAR_8BIT(3);
	CLEAR_8BIT(4);
	CLEAR_8BIT(5);
	CLEAR_8BIT(6);
	CLEAR_8BIT(7);
}

void PrintMemory(uint32_t m)
{
    if(m == 0)
	{
			uint8_t st[] = "0. ReservedMemoryType";
			Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 1)
	{
			uint8_t st[] = "1. LoaderCode";
			Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 2)
	{
            uint8_t st[] = "2. LoaderData";
			Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 3)
	{
		   uint8_t st[] = "3. BootServicesCode";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 4)
	{
	       uint8_t st[] = "4. BootServicesData";
	       Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 5)
	{
	       uint8_t st[] = "5. RuntimeServicesCode";
	       Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 6)
	{
	       uint8_t st[] = "6. RuntimeServicesData";
	       Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 7)
	{
		   uint8_t st[] = "7. ConventionalMemory";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 8)
	{
	       uint8_t st[] = "8. UnusableMemory";
	       Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 9)
	{
	       uint8_t st[] = "9. ACPIReclaimMemory";
	       Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 10)
	{
		   uint8_t st[] = "10. ACPIMemoryNVS";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 11)
	{
		   uint8_t st[] = "11. MemoryMappedIO";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 12)
	{
		   uint8_t st[] = "12. MemoryMappedIOPortSpace";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 13)
	{
		   uint8_t st[] = "13. PalCode";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 14)
	{
		   uint8_t st[] = "14. PersistentMemory";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 15)
	{
		   uint8_t st[] = "15. UnacceptedMemoryType";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else if(m == 16)
	{
		   uint8_t st[] = "16. MaxMemoryType";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	} else
	{
		   uint8_t st[] = "UNKNOWN";
		   Print(st, textPos->x, textPos->y, 1, CYAN);
	}
}

uint64_t GetTotalRam()
{
    uint64_t totalRam = 0;
	uint64_t MMapEntries = biStruct->MMapSize / biStruct->MMapDescriptorSize;
	for(uint32_t i = 0; i < MMapEntries; i++)
	{
		EFI_MEMORY_DESCRIPTOR* description = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)biStruct->MMap + (i * biStruct->MMapDescriptorSize));
		if(description->type == 7)
		{
			totalRam += description->NumberOfPages;
		}
	}
	totalRam *= 4096;
	return totalRam;
}

/*
	uint8_t testMap = 9; //  00001001 == 9
	                     //  Result should be Bit 0 and 3
	
	bitmap8 = &testMap;
	
	uint8_t g0 = GET_8BIT(0);

	if(g0 == 1)
	{
		textPos->y+=16;
	    textPos->x = 20;
		uint8_t st5[] = "Bit 0 = 1";
		Print(st5, textPos->x, textPos->y, 1, ORANGE);
	}
*/


/*
uint64_t GetTotalRam()
{
	// Test CODE
//	uint32_t looped = 0;
    uint64_t totalRam = 0;
	uint64_t MMapEntries = biStruct->MMapSize / biStruct->MMapDescriptorSize;
	for(uint32_t i = 0; i < MMapEntries; i++)
	{
		EFI_MEMORY_DESCRIPTOR* description = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)biStruct->MMap + (i * biStruct->MMapDescriptorSize));
		if(description->type == 7)
		{
			//if((description->NumberOfPages * 4096) > totalRam)
			//{
				//totalRam = description->NumberOfPages * 4096;
				//totalRam += (description->NumberOfPages * 4096);
				totalRam += description->NumberOfPages;
			//}
//			looped++;
		}
//		textPos->x += 230;
//		if(textPos->x > 700 || looped > 3)
//		{
//			looped = 0;
//	        textPos->y += 16;
//	        textPos->x  = 20;
//		}
//		PrintMemory(description->type);
	}
	totalRam *= 4096;
	return totalRam;
}
*/