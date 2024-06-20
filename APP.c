#include <assert.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE* fp;
	int fd;
	char c[] = "Hello Driver";
	char buffer[200];

	/* 打开文件用于读写 */
	fp = fopen("file.txt", "w+");
	if (fp == NULL)
	{
		perror("fopen");
		return -1;
	}
	//memset(fp, 0, sizeof(buffer)*200);

	/* 写入数据到文件 */
	fwrite(c, strlen(c) + 1, 1, fp);

	/* 指针移动到文件的起始位置 */
	fseek(fp, 0, SEEK_SET);

	/* 读取并显示数据 */
	fread(buffer, strlen(c) + 1, 1, fp);

	fd = open("/dev/ioctl_demo", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	/* 将一个文件写入到内核模块申请的内存中 */
	ioctl(fd, 0, buffer);
	
	/* 将内核模块的内存读出并写入文件file.txt中 */
	fwrite(buffer, strlen(c) + 1, 1, fp);
	
	/* 关闭文件 */
	fclose(fp);
	close(fd);

	return 0;
}