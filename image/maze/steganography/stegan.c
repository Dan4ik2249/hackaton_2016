#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *in_a = NULL;
	FILE *in_b = NULL;
	FILE *out = NULL;
	uint32_t offset = 0;
	unsigned int size = 0;
	unsigned int filesize = 0;
	uint32_t height = 0, length = 0;
	uint8_t *buff_a = NULL;
	uint8_t *buff_b = NULL;
	uint8_t *headers = NULL;
	uint8_t *res = NULL;

	if ((in_a = fopen("a.bmp", "rb+")) == NULL){
		perror("file not open");
		return -1;
	}
	if ((in_b = fopen("b.bmp", "rb+")) == NULL){
		perror("file not open");
		return -1;
	}
	fseek(in_a, 2, SEEK_SET);
	if (fread(&filesize, sizeof(uint32_t), 1, in_a)==EOF){
		perror("error read filesize");
		return -1;
	}

	fseek(in_a, 10, SEEK_SET);
	if (fread(&offset, sizeof(uint32_t), 1, in_a)==EOF){
		perror("error read offset");
		return -1;
	}

	fseek(in_a, 18, SEEK_SET);
	if (fread(&length, sizeof(uint32_t), 1, in_a)==EOF){
		perror("error read height");
		return -1;
	}
	if (fread(&height, sizeof(uint32_t), 1, in_a)==EOF){
		perror("error read length");
		return -1;
	}
	fseek(in_a, 0, SEEK_SET);
	headers = (uint8_t*)malloc(sizeof(uint8_t)*offset);
	if (fread(headers, sizeof(uint8_t), offset, in_a) != offset){
		perror("read to headers");
		return -1;
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

	fseek(in_a, offset, SEEK_SET);
	fseek(in_b, offset, SEEK_SET);
	buff_a = (uint8_t*)malloc(sizeof(uint8_t)*size);
	buff_b = (uint8_t*)malloc(sizeof(uint8_t)*size);
	
	if (fread(buff_a, sizeof(uint8_t), size, in_a) != size){
		perror("read to buff");
		return -1;
	}
	if (fread(buff_b, sizeof(uint8_t), size, in_b) != size){
		perror("read to buff");
		return -1;
	}
	fclose(in_a);
	fclose(in_b);
	
	if ((out = fopen("result.bmp", "wb+")) == NULL){
		perror("file not open");
		return -1;
	}
	res = (uint8_t*)malloc(sizeof(uint8_t)*size);
	for (int i = 0; i<size; i+=3){
		res[i]=(buff_a[i]%2 + buff_b[i]%2)*127;
		res[i+1]=(buff_a[i+1]%2 + buff_b[i+1]%2)*127;
		res[i+2]=(buff_a[i+2]%2 + buff_b[i+2]%2)*127;
	}
	if (fwrite(headers, sizeof(uint8_t), offset, out) != offset){
		perror("write headers to out");
		return -1;
	}
	if (fwrite(res, sizeof(uint8_t), size, out) != size){
		perror("write res to out");
		return -1;
	}
	fclose(out);

	free(buff_a);
	free(buff_b);
	return 0;
}
