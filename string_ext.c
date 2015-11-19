/*
 * 外扩字符串处理函数
 */

#include "string_ext.h"

char *strupr(char *str)
{
	char *out = str;
	for (; *str != '\0'; str++)
		*str = toupper(*str);
	return out;
}

char *strlwr(char *str)
{
	char *out = str;
	for (; *str != '\0'; str++)
		*str = tolower(*str);
	return out;
}
