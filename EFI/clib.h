
#ifndef C_LIB_H
#define C_LIB_H

#include <stddef.h>  // size_t

size_t strlen(const char* str)
{
	const char* strCount = str;

	while (*strCount++);
	return strCount - str - 1;
}

int strcmp(const char* a, const char* b)
{
	size_t length = strlen(a);
	for(size_t i = 0; i < length; i++)
	{
		if(a[i] < b[i]){return -1;}
		if(a[i] > b[i]){return 1;}
	}
	return 0;
}

#endif  // C_LIB_H