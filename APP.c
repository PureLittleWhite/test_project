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

	/* ���ļ����ڶ�д */
	fp = fopen("file.txt", "w+");
	if (fp == NULL)
	{
		perror("fopen");
		return -1;
	}
	//memset(fp, 0, sizeof(buffer)*200);

	/* д�����ݵ��ļ� */
	fwrite(c, strlen(c) + 1, 1, fp);

	/* ָ���ƶ����ļ�����ʼλ�� */
	fseek(fp, 0, SEEK_SET);

	/* ��ȡ����ʾ���� */
	fread(buffer, strlen(c) + 1, 1, fp);

	fd = open("/dev/ioctl_demo", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	/* ��һ���ļ�д�뵽�ں�ģ��������ڴ��� */
	ioctl(fd, 0, buffer);
	
	/* ���ں�ģ����ڴ������д���ļ�file.txt�� */
	fwrite(buffer, strlen(c) + 1, 1, fp);
	
	/* �ر��ļ� */
	fclose(fp);
	close(fd);

	return 0;
}