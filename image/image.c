#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *in = NULL;
	FILE *out = NULL;
	uint32_t offset = 0;
	unsigned int size = 0;
	unsigned int filesize = 0;
	uint32_t height = 0, length = 0;
	uint8_t *buff = NULL;
	uint8_t key[32];

	if ((in = fopen("task.bmp", "rb+")) == NULL){
		perror("file not open");
		return __LINE__;
	}
	fseek(in, 2, SEEK_SET);
	if (fread(&filesize, sizeof(uint32_t), 1, in)==EOF){
		perror("error read filesize");
		return __LINE__;
	}

	fseek(in, 10, SEEK_SET);
	if (fread(&offset, sizeof(uint32_t), 1, in)==EOF){
		perror("error read offset");
		return __LINE__;
	}

	fseek(in, 18, SEEK_SET);
	if (fread(&length, sizeof(uint32_t), 1, in)==EOF){
		perror("error read height");
		return __LINE__;
	}
	if (fread(&height, sizeof(uint32_t), 1, in)==EOF){
		perror("error read length");
		return __LINE__;
	}

	
	int offset_len = 0;
	if (length%4!=0){
		offset_len = (length*3/4+1)*4 - length*3;
	}
	int res_len = length*3 + offset_len;
	size = res_len*height;
	printf("filesize: %d\n", filesize);
	printf("size: %d\n", size);
	printf("offset: %d\n", offset);
	printf("height: %d, length: %d\n", height, length);

	fseek(in, offset, SEEK_SET);
	buff = (uint8_t*)malloc(sizeof(uint8_t)*size);
	if (fread(buff, sizeof(uint8_t), size, in) != size){
		perror("read to buff");
		return -1;
	}
	int k = 0;
	for (int i = size-res_len; i > -1; i-=res_len){
		if (k==32) break;
		for (int j = 0; j < res_len-offset_len; j+=3){
			if ((buff[i+j]==buff[i+j+1])&&(buff[i+j+1]==buff[i+j+2])){
				if (k<32){
					key[k++] = buff[i+j];
				}
				else break;
			}
		}
	}
	printf("k: %d\n", k);
		
	if ((out = fopen("key.txt", "wb+")) == NULL){
		perror("open out file");
		return __LINE__;
	}

	if (fwrite(key, sizeof(uint8_t), 32, out) != 32){
		perror("write to out");
		return __LINE__;
	}

	free(buff);
	fclose(in);
	fclose(out);
	return 0;
}
