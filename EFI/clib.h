
#ifndef C_LIB_H
#define C_LIB_H

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

#endif  // C_LIB_H