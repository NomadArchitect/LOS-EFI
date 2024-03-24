

#include "clib.h"

#define HEX     16
#define DECIMAL 10

#define BITS8   7
#define BITS16 15
#define BITS32 31

#define HSPACE 1
#define VSPACE 1

#define MAX_LENGTH 22

             // ARGB             
#define ORANGE 0xffffa500
#define CYAN   0xff00ffff
#define RED    0xffff0000
#define GREEN  0xff00ff00
#define BLUE   0xff0000ff
#define PURPLE 0xff800080
#define GRAY   0xff888888
#define WHITE  0xffffffff
#define BLACK  0xff000000

typedef struct EFI_MEMORY_DESCRIPTOR
{
    uint32_t  type;
    uint64_t* PhysicalAddress;
    uint64_t* VirtualAddress;
    uint64_t  NumberOfPages;
    uint64_t  Attributes;
} EFI_MEMORY_DESCRIPTOR;

typedef struct BLOCKINFO
{
    uint64_t               BaseAddress;
    uint64_t               BufferSize;
    uint32_t               ScreenWidth;
    uint32_t               ScreenHeight;
    uint32_t               PixelsPerScanLine;
    EFI_MEMORY_DESCRIPTOR* MMap;
    uint64_t               MMapSize;
    uint64_t               MMapDescriptorSize;
    uint64_t*              rsdp;
} __attribute__((__packed__)) BLOCKINFO;

BLOCKINFO* biStruct __attribute__ ((section (".text")));
uint32_t textPosX __attribute__ ((section (".text"))) = 0;
uint32_t textPosY __attribute__ ((section (".text"))) = 0;
uint32_t FontSize __attribute__ ((section (".text"))) = 0;
uint32_t txtColor __attribute__ ((section (".text"))) = 0;

/*
// TODO : Find a way to work this into the loader.
uint32_t asciifont[384] __attribute__ ((section (".data"))) =  {
	0,0,0,0,                                     // 032  --  SPACE
	6204,1010571288,402659352,0,                 // 033  --  !
	102,1717969920,0,0,                          // 034  --  "
	108,1828613228,1828613228,0,                 // 035  --  #

	1579132,3334652028,101091014,2081953792,     // 036  --  $
	0,3267759128,811648646,0,                    // 037  --  %
	14444,1814853878,3704409292,1979711488,      // 038  --  &
	1579032,805306368,0,0,                       // 039  --  '

	12,405811248,808464408,201326592,            // 040  --  (
	48,403442700,202116120,805306368,            // 041  --  )
	0,26172,4282148352,0,                        // 042  --  *
	0,1579134,404226048,0,                       // 043  --  +

	0,0,1579032,805306368,                       // 044  --  ,
	0,126,0,0,                                   // 045  --  -
	0,0,24,402653184,                            // 046  --  .
	0,33950744,811647104,0,                      // 047  --  /

	56,1824966358,3603351148,939524096,          // 048  --  0
	24,947394584,404232216,2113929216,           // 049  --  1
	60,1724255256,811647174,4261412864,          // 050  --  2
	124,3322283580,101058246,2080374784,         // 051  --  3

	12,473722060,4262202380,503316480,           // 052  --  4
	254,3233857788,101058246,2080374784,         // 053  --  5
	56,1623245052,3334915782,2080374784,         // 054  --  6
	254,3322283532,405811248,805306368,          // 055  --  7

	124,3334915708,3334915782,2080374784,        // 056  --  8
	124,3334915710,101058060,2013265920,         // 057  --  9
	0,1579008,1579008,0,                         // 058  --  :
	0,1579008,1579056,0,                         // 059  --  ;

	1548,405823680,1613764620,100663296,         // 060  --  <
	0,32256,8257536,0,                           // 061  --  =
	49248,806882310,202911840,3221225472,        // 062  --  >
	124,3334867992,404226072,402653184,          // 063  --  ?

	124,3334921950,3739147456,2080374784,        // 064  --  @
	16,946652870,4274439878,3321888768,          // 065  --  A
	252,1717986940,1717986918,4227858432,        // 066  --  B
	60,1724039360,3233858150,1006632960,         // 067  --  C

	248,1818650214,1717986924,4160749568,        // 068  --  D
	254,1717725304,1751147110,4261412864,        // 069  --  E
	254,1717725304,1751146592,4026531840,        // 070  --  F
	60,1724039360,3737568870,973078528,          // 071  --  G

	198,3334915838,3334915782,3321888768,        // 072  --  H
	60,404232216,404232216,1006632960,           // 073  --  I
	30,202116108,214748364,2013265920,           // 074  --  J
	230,1717988472,2020370022,3858759680,        // 075  --  K

	240,1616928864,1616929382,4261412864,        // 076  --  L
	198,4009688790,3334915782,3321888768,        // 077  --  M
	198,3874946782,3469133510,3321888768,        // 078  --  N
	124,3334915782,3334915782,2080374784,        // 079  --  O

	252,1717986940,1616928864,4026531840,        // 080  --  P
	124,3334915782,3334919902,2081164800,        // 081  --  Q
	252,1717986940,1818650214,3858759680,        // 082  --  R
	124,3334889528,201770694,2080374784,         // 083  --  S

	126,2119833624,404232216,1006632960,         // 084  --  T
	198,3334915782,3334915782,2080374784,        // 085  --  U
	198,3334915782,3334892600,268435456,         // 086  --  V
	198,3334915798,3604414190,1811939328,        // 087  --  W

	198,3328994360,946629830,3321888768,         // 088  --  X
	102,1717986918,1008211992,1006632960,        // 089  --  Y
	254,3330673688,811647686,4261412864,         // 090  --  Z
	60,808464432,808464432,1006632960,           // 091  --  [

	0,2160091184,403441154,0,                    // 092  --  "\"
	60,202116108,202116108,1006632960,           // 093  --  ]
	16,946652672,0,0,                            // 094  --  ^
	0,0,0,4278190080,                            // 095  --  _

	48,806879232,0,0,                            // 096  --  `
	0,30732,2093796556,1979711488,               // 097  --  a
	224,1616935020,1717986918,2080374784,        // 098  --  b
	0,15462,1616928870,1006632960,               // 099  --  c

	28,202128492,3435973836,1979711488,          // 100  --  d
	0,31942,4274045126,2080374784,               // 101  --  e
	28,909258872,808464432,2013265920,           // 102  --  f
	0,30412,3435973756,214726656,                // 103  --  g

	224,1616931958,1717986918,3858759680,        // 104  --  h
	0,404226104,404232216,1006632960,            // 105  --  i
	6,100666886,101058150,1715208192,            // 106  --  j
	224,1616930412,2021157990,3858759680,        // 107  --  k

	48,808464432,808464432,939524096,            // 108  --  l
	0,60670,3604403926,3321888768,               // 109  --  m
	0,56422,1717986918,1711276032,               // 110  --  n
	0,30924,3435973836,2013265920,               // 111  --  o

	0,15462,1719427168,1610612736,               // 112  --  p
	0,30412,3435973756,202120704,                // 113  --  q
	0,56438,1717592160,4026531840,               // 114  --  r
	0,31942,1614286022,2080374784,               // 115  --  s

	0,271593724,808464438,469762048,             // 116  --  t
	0,52428,3435973836,1979711488,               // 117  --  u
	0,27756,1819044920,268435456,                // 118  --  v
	0,50902,3604403966,1811939328,               // 119  --  w

	0,50796,943208556,3321888768,                // 120  --  x
	0,50886,3334915710,101513216,                // 121  --  y
	0,65228,405823686,4261412864,                // 122  --  z
	28,808464608,808464432,469762048,            // 123  --  {

	0,808464432,3158064,805306368,               // 124  --  |
	224,808464412,808464432,3758096384,          // 125  --  }
	118,3690987520,0,0,                          // 126  --  ~
	16,946652870,3334929920,0                    // 127  --  Delete
};
*/

void MakeRectangle(uint32_t xPos, uint32_t yPos, uint32_t w, uint32_t h, uint32_t c);
void setTextPosition(uint32_t xPos, uint32_t yPos);
void setTextFontSize(uint32_t fSize);
void setTextColor(uint32_t color);
void printUInt64Digits(uint64_t num, uint64_t base);
void printIntDigits(int32_t num);
void putc(char chrNum[]);
void printf(char* txt, ...);

void main(BLOCKINFO* bi)
{
	biStruct = bi;

	setTextPosition(200, 20);
	setTextColor(GRAY);
	setTextFontSize(2);

	MakeRectangle(0, 0, 150, 150, ORANGE);
	putc("W");
	
	while(1){__asm__ ("hlt");}
}

#include "clib.c"

void MakeRectangle(uint32_t xPos, uint32_t yPos, uint32_t w, uint32_t h, uint32_t c)
{
    uint32_t x;
    uint32_t y      = yPos;
    uint32_t width  = xPos + w;
    uint32_t height = yPos + h;

    for(y = yPos; y <= height; y++)
    {
        for(x = xPos; x <= width; x++)
        {
            *(x + (y * biStruct->PixelsPerScanLine) + (uint32_t*)(biStruct->BaseAddress)) = c;
        }
    }
}

void setTextPosition(uint32_t xPos, uint32_t yPos)
{
	textPosX = xPos;
	textPosY = yPos;
}

void setTextFontSize(uint32_t fSize)
{
	FontSize = fSize;
}

void setTextColor(uint32_t color)
{
	txtColor = color;
}

void printUInt64Digits(uint64_t num, uint64_t base)   // TODO : FIX THIS
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
		char16_t temp = uint64Str[i];
		uint64Str[i]  = uint64Str[j];
		uint64Str[j]  = temp;
	}
	
	//SystemTable->ConOut->OutputString(SystemTable->ConOut, uint64Str);
}

void printIntDigits(int32_t num)   // TODO : FIX THIS
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
		char16_t temp = int32Str[i];
		int32Str[i] = int32Str[j];
		int32Str[j] = temp;
	}
	
	//SystemTable->ConOut->OutputString(SystemTable->ConOut, int32Str);
}

void putc(char chrNum[])  // TODO : FIX THIS
{
    uint32_t textColor = txtColor;

    uint32_t L = 87;
	if(*(uint32_t*)&chrNum[0] == L)
	{
		MakeRectangle(10, 10, 100, 100, textColor);
	}
}

void printf(char* txt, ...)   // TODO : FIX THIS
{
	char16_t charStr[2]  = {'\0'};

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
                    charStr[0] = (char)va_arg(args, int);
					charStr[1] = '\0';
                    //SystemTable->ConOut->OutputString(SystemTable->ConOut, charStr);
					break;
                }
				case 's':
				{
					uint16_t* varString = va_arg(args, uint16_t*);
					//SystemTable->ConOut->OutputString(SystemTable->ConOut, varString);
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
					//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
				    //SystemTable->ConOut->OutputString(SystemTable->ConOut, u"\r\nERROR : Invalid format: %");
					//SystemTable->ConOut->OutputString(SystemTable->ConOut, (short unsigned int*)&txt[i]);
					//SystemTable->ConOut->OutputString(SystemTable->ConOut, u"\r\n");
					//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, CurrentColor);
					return;
					break;
				}
			}
		} else {
			charStr[0] = txt[i];
			charStr[1] = '\0';
			putc((char*)&charStr);
			//SystemTable->ConOut->OutputString(SystemTable->ConOut, charStr);
		}
	}

	va_end(args);
}

/*
#define BITS32 31

uint32_t asciifont[384] __attribute__ ((section (".data"))) =  {
	0,0,0,0,                                     // 032  --  SPACE
	6204,1010571288,402659352,0,                 // 033  --  !
	102,1717969920,0,0,                          // 034  --  "
	108,1828613228,1828613228,0,                 // 035  --  #

	1579132,3334652028,101091014,2081953792,     // 036  --  $
	0,3267759128,811648646,0,                    // 037  --  %
	14444,1814853878,3704409292,1979711488,      // 038  --  &
	1579032,805306368,0,0,                       // 039  --  '

	12,405811248,808464408,201326592,            // 040  --  (
	48,403442700,202116120,805306368,            // 041  --  )
	0,26172,4282148352,0,                        // 042  --  *
	0,1579134,404226048,0,                       // 043  --  +

	0,0,1579032,805306368,                       // 044  --  ,
	0,126,0,0,                                   // 045  --  -
	0,0,24,402653184,                            // 046  --  .
	0,33950744,811647104,0,                      // 047  --  /

	56,1824966358,3603351148,939524096,          // 048  --  0
	24,947394584,404232216,2113929216,           // 049  --  1
	60,1724255256,811647174,4261412864,          // 050  --  2
	124,3322283580,101058246,2080374784,         // 051  --  3

	12,473722060,4262202380,503316480,           // 052  --  4
	254,3233857788,101058246,2080374784,         // 053  --  5
	56,1623245052,3334915782,2080374784,         // 054  --  6
	254,3322283532,405811248,805306368,          // 055  --  7

	124,3334915708,3334915782,2080374784,        // 056  --  8
	124,3334915710,101058060,2013265920,         // 057  --  9
	0,1579008,1579008,0,                         // 058  --  :
	0,1579008,1579056,0,                         // 059  --  ;

	1548,405823680,1613764620,100663296,         // 060  --  <
	0,32256,8257536,0,                           // 061  --  =
	49248,806882310,202911840,3221225472,        // 062  --  >
	124,3334867992,404226072,402653184,          // 063  --  ?

	124,3334921950,3739147456,2080374784,        // 064  --  @
	16,946652870,4274439878,3321888768,          // 065  --  A
	252,1717986940,1717986918,4227858432,        // 066  --  B
	60,1724039360,3233858150,1006632960,         // 067  --  C

	248,1818650214,1717986924,4160749568,        // 068  --  D
	254,1717725304,1751147110,4261412864,        // 069  --  E
	254,1717725304,1751146592,4026531840,        // 070  --  F
	60,1724039360,3737568870,973078528,          // 071  --  G

	198,3334915838,3334915782,3321888768,        // 072  --  H
	60,404232216,404232216,1006632960,           // 073  --  I
	30,202116108,214748364,2013265920,           // 074  --  J
	230,1717988472,2020370022,3858759680,        // 075  --  K

	240,1616928864,1616929382,4261412864,        // 076  --  L
	198,4009688790,3334915782,3321888768,        // 077  --  M
	198,3874946782,3469133510,3321888768,        // 078  --  N
	124,3334915782,3334915782,2080374784,        // 079  --  O

	252,1717986940,1616928864,4026531840,        // 080  --  P
	124,3334915782,3334919902,2081164800,        // 081  --  Q
	252,1717986940,1818650214,3858759680,        // 082  --  R
	124,3334889528,201770694,2080374784,         // 083  --  S

	126,2119833624,404232216,1006632960,         // 084  --  T
	198,3334915782,3334915782,2080374784,        // 085  --  U
	198,3334915782,3334892600,268435456,         // 086  --  V
	198,3334915798,3604414190,1811939328,        // 087  --  W

	198,3328994360,946629830,3321888768,         // 088  --  X
	102,1717986918,1008211992,1006632960,        // 089  --  Y
	254,3330673688,811647686,4261412864,         // 090  --  Z
	60,808464432,808464432,1006632960,           // 091  --  [

	0,2160091184,403441154,0,                    // 092  --  "\"
	60,202116108,202116108,1006632960,           // 093  --  ]
	16,946652672,0,0,                            // 094  --  ^
	0,0,0,4278190080,                            // 095  --  _

	48,806879232,0,0,                            // 096  --  `
	0,30732,2093796556,1979711488,               // 097  --  a
	224,1616935020,1717986918,2080374784,        // 098  --  b
	0,15462,1616928870,1006632960,               // 099  --  c

	28,202128492,3435973836,1979711488,          // 100  --  d
	0,31942,4274045126,2080374784,               // 101  --  e
	28,909258872,808464432,2013265920,           // 102  --  f
	0,30412,3435973756,214726656,                // 103  --  g

	224,1616931958,1717986918,3858759680,        // 104  --  h
	0,404226104,404232216,1006632960,            // 105  --  i
	6,100666886,101058150,1715208192,            // 106  --  j
	224,1616930412,2021157990,3858759680,        // 107  --  k

	48,808464432,808464432,939524096,            // 108  --  l
	0,60670,3604403926,3321888768,               // 109  --  m
	0,56422,1717986918,1711276032,               // 110  --  n
	0,30924,3435973836,2013265920,               // 111  --  o

	0,15462,1719427168,1610612736,               // 112  --  p
	0,30412,3435973756,202120704,                // 113  --  q
	0,56438,1717592160,4026531840,               // 114  --  r
	0,31942,1614286022,2080374784,               // 115  --  s

	0,271593724,808464438,469762048,             // 116  --  t
	0,52428,3435973836,1979711488,               // 117  --  u
	0,27756,1819044920,268435456,                // 118  --  v
	0,50902,3604403966,1811939328,               // 119  --  w

	0,50796,943208556,3321888768,                // 120  --  x
	0,50886,3334915710,101513216,                // 121  --  y
	0,65228,405823686,4261412864,                // 122  --  z
	28,808464608,808464432,469762048,            // 123  --  {

	0,808464432,3158064,805306368,               // 124  --  |
	224,808464412,808464432,3758096384,          // 125  --  }
	118,3690987520,0,0,                          // 126  --  ~
	16,946652870,3334929920,0                    // 127  --  Delete
};

int32_t globalTextX = 0;
int32_t globalTextY = 0;
uint32_t FontSize   = 0;

void putc(char chrNum[])
{
    uint32_t textColor = 0xFFFFFF00;

	int x = globalTextX;
	int y = globalTextY;
	int temp = globalTextX;
	int xPos = 0;
	uint32_t Q = 0;

    for(uint32_t L = 32; L < 128; L++)
	{
		Q = L;
		if(*(uint32_t*)&chrNum[0] == L)
		{
			Q = (Q - 32) * 4;
			for(uint32_t r = 0; r < 4; r++)
			{
				for(long t = BITS32; t >= 0; t--)
				{
					if(asciifont[Q] & (unsigned int)(1 << t))
					{
						MakeRectangle(x, y, FontSize, FontSize, textColor);
					}
					x += FontSize;
					xPos++;
					if(xPos > 7)
					{
						x = temp;
						y += FontSize;
						xPos = 0;
					}
				}
				Q += 1;
			}
		}
	}
}
*/

/*
typedef struct GRAPHICS_COLOR_PIXEL
{
    uint8_t   Blue;
    uint8_t   Green;
    uint8_t   Red;
    uint8_t   Alpha;
} GRAPHICS_COLOR_PIXEL;
*/

/*
void wprintf(const char16_t* txt, ...);
void itoa(int32_t n, char* buffer, int basenumber);
*/

//biStruct->BaseAddress = (bi->BaseAddress - 128);  // With the FIX from the EFI, this should not be needed anymore.
	
//	printf("W");
//	char test[2] = {'\0'};
//	test[0] = *(char*)"W";
//	if(test[0] == 87)
//	{
//		MakeRectangle(10, 10, 100, 100, txtColor);
//	}

/*

void wprintf(const char16_t* txt, ...)
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
                    charStr[0] = (char16_t)va_arg(args, int);
					(void)charStr;
                    //SystemTable->ConOut->OutputString(SystemTable->ConOut, charStr);
					break;
                }
				case 's':
				{
					uint16_t* varString = va_arg(args, uint16_t*);
					(void)varString;
					//SystemTable->ConOut->OutputString(SystemTable->ConOut, varString);
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
					//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);
				    //SystemTable->ConOut->OutputString(SystemTable->ConOut, u"\r\nERROR : Invalid format: %");
					//SystemTable->ConOut->OutputString(SystemTable->ConOut, &txt[i]);
					//SystemTable->ConOut->OutputString(SystemTable->ConOut, u"\r\n");
					//SystemTable->ConOut->SetAttribute(SystemTable->ConOut, CurrentColor);
					return;
					break;
				}
			}
		} else {
			//charStr[0] = txt[i];
			if((char)txt[i] == 87)
			{
				MakeRectangle(10, 10, 100, 100, txtColor);
			}
			//putc(charStr);
			//SystemTable->ConOut->OutputString(SystemTable->ConOut, charStr);
		}
	}

	va_end(args);
}

void itoa(int32_t n, char* buffer, int basenumber)
{
	int32_t hold;
	int i, j;
	hold = n;
	i = 0;

	do{
		hold = n % basenumber;
		buffer[i++] = (char)((hold < 10) ? (hold + '0') : (hold + 'a' - 10));
	} while(n /= basenumber);
	buffer[i--] = 0;
	
	for(j = 0; j < i; j++, i--)
	{
		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = (char)hold;
	}
}
*/