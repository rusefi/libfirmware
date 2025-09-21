#include <rusefi/efistring.h>

// see strncpy man page
// this implementation helps avoiding following gcc error/warning:
// error: 'strncpy' output may be truncated copying xxx bytes from a string of length xxx

char *strlncpy(char *dest, const char *src, size_t size)
{
	size_t i;

	for (i = 0; (i < (size - 1)) && (src[i] != '\0'); i++)
		dest[i] = src[i];
	for ( ; i < size; i++)
		dest[i] = '\0';

	return dest;
}
