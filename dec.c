#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>


int get_key(uint32_t *key){
	FILE *fkey = NULL;
	if ((fkey = fopen("key.txt", "rb+")) == NULL){
		perror("Opening Error(fkey)");
		return __LINE__;
	}
	fread(key, sizeof(uint32_t), 32, fkey);
	fclose(fkey);
	return 0;
}

int main(int argc, char *argv[]){
	uint32_t key[8];
	memset(key, 8, 0);
	char filein[] = "encrypted";
	char fileout[] = "out1";
	FILE *in = NULL;
	FILE *out = NULL;
	int size = 0;
	int i = 0;
	uint32_t text_block, key_block = 0;

	if ((in = fopen(filein, "rb+")) == NULL){
		perror("Oening error(filein)");
		return __LINE__;
	}
	if ((out = fopen(fileout, "wr+")) == NULL){
		perror("Opening error(fileout)");
		return __LINE__;
	}

	get_key(key);
	
	time_t mytime = time(NULL);
    	struct tm *now = localtime(&mytime);
	printf("Time start: %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);

	while(!feof(in)){
		size = fread(&text_block, sizeof(uint8_t), 4, in);
		//printf("%x\n", text_block);
		key_block ^= key[i%8];
		key_block = key_block*134775813 + 1;

		text_block ^= key_block;
		if (fwrite(&text_block, sizeof(uint8_t), size, out) == EOF){
			perror("Error write");
			return __LINE__;
		}
		i++;
		//printf("enc block: %x\n", text_block);
	}
	
	time_t nextime = time(NULL);
	struct tm *next = localtime(&nextime);
	printf("Time finish: %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);
	printf("FINISH");
	fclose(in);
	fclose(out);
	return 0;
}
