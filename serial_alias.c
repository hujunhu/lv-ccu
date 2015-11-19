#include <stdio.h>
#include <string.h>

#define DEBUG
#define SERIAL_ALIAS_NR	16

struct serial_alias {
	char adev[64];	// 对外映射的名称
	char rdev[128];	// 真实设备
};

struct serial_alias serial_alias_cfg[SERIAL_ALIAS_NR];
int serial_alias_nr = 0;

void serial_alias_init()
{
	char tmp[256];
	int ret;
	FILE *fp = fopen("./cfg/serial-alias.cfg", "rb");

	if (fp == NULL) {
		printf("%s: ./cfg/serial-alias.cfg: \n", __func__);
		perror("open failed");
		return;
	}
	while (fgets(tmp, sizeof(tmp)-1, fp) != NULL) {
		if (tmp[0] == '\n' || tmp[0] == '\r' || tmp[0] == '#')
			continue;
		ret = sscanf(tmp, "%[^:]:%[^\r\n]", serial_alias_cfg[serial_alias_nr].adev, 
				serial_alias_cfg[serial_alias_nr].rdev);
#ifdef DEBUG
		printf("%s(%ld):%s(%ld)\n", serial_alias_cfg[serial_alias_nr].adev, 
				strlen(serial_alias_cfg[serial_alias_nr].adev), 
				serial_alias_cfg[serial_alias_nr].rdev,
				strlen(serial_alias_cfg[serial_alias_nr].rdev));
#endif
		if (ret == 2) {
			serial_alias_nr += 1;
		}
		if (serial_alias_nr >= SERIAL_ALIAS_NR)
			break;
	}
	fclose(fp);
}

char *serial_get_realdev(char adev[])
{
	int i;
	for (i = 0; i < serial_alias_nr; i++) {
		if (strcmp(adev, serial_alias_cfg[i].adev) == 0)
			break;
	}

	return serial_alias_cfg[i].rdev;
}
