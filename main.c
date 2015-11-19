#include <stdio.h>
#include <string.h>

#include "string_ext.h"
#include "serial_alias.h"

int main()
{
	char tmp[] = "TEST";
	serial_alias_init();
	strlwr(tmp);
	printf("%s\n", tmp);
	printf("%s\n", serial_get_realdev("com1"));
	return 0;
}
