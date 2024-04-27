#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

class Graph{
	bool *visited;
	vector<vector<pair<int,int>>> wide_graph;
	int size_wg;
	int *all_path;

	public:
	Graph(int size){
		size_wg = size;
		wide_graph.reserve(size);
		visited = new bool[size];
		all_path = new int[size*10];
		for (int i=0; i<size*10; i++) all_path[i]=-1;
	}

	void add(int v1, int v2, int width){
		
		wide_graph[v1].push_back(make_pair(v2,width));
		wide_graph[v2].push_back(make_pair(v1,width));
	}

	vector<int> s_Dijkstra(int start, int end){
		int size=size_wg;
		int INF = size*10000;
		vector<int> D(size, INF);

		D[start] = 0;
		for (int i = 0; i < size; i++){
			int minInd=0;
			int min = INF;
			for (int j=0;j<size;j++){
				if(D[j]<min && !visited[j]){
					min=D[j];
					minInd=j;
				}
			}
			visited[minInd]=true;
			for (pair<int,int> p: wide_graph[minInd]){
				int u = p.first;
				int w = p.second;
				if (D[u]>D[minInd]+w) {
					D[u]=D[minInd]+w;
					all_path[u]=minInd;
				}
					
			}
		}
		
		//cout << "weight: " << D[D.size()-1] << endl;
		
		vector<int> path;
		int cur = end;
		path.push_back(cur);
		while(all_path[cur]!=-1){
			cur = all_path[cur];
			path.push_back(cur);
		}
		reverse(path.begin(), path.end());
		return path;
	}
};

uint32_t height = 0, length = 0;

int** read_image(char* filename){
	FILE *in = NULL;
	uint32_t offset = 0;
	unsigned int size = 0;
	unsigned int filesize = 0;
	uint8_t *buff = NULL;

	if ((in = fopen(filename, "rb+")) == NULL){
		perror("file not open");
		return NULL;
	}
	fseek(in, 2, SEEK_SET);
	if (fread(&filesize, sizeof(uint32_t), 1, in)==EOF){
		perror("error read filesize");
		return NULL;
	}

	fseek(in, 10, SEEK_SET);
	if (fread(&offset, sizeof(uint32_t), 1, in)==EOF){
		perror("error read offset");
		return NULL;
	}

	fseek(in, 18, SEEK_SET);
	if (fread(&length, sizeof(uint32_t), 1, in)==EOF){
		perror("error read height");
		return NULL;
	}
	if (fread(&height, sizeof(uint32_t), 1, in)==EOF){
		perror("error read length");
		return NULL;
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
		return NULL;
	}
	
	
	int **mass = new int*[height];
	int k = 0;
	for (int i = size-res_len; i > -1; i-=res_len){
		int p = 0;
		mass[k] = new int[length];
		for (int j = 0; j < res_len-offset_len; j+=3){
			mass[k][p] = buff[i+j]+buff[i+j+1]+buff[i+j+2];
			p++;
		}
		k++;
	}

	free(buff);
	//fclose(in);
	return mass;
}

int main(int argc, char* argv[]){
	int **arr = NULL;
	FILE *out = NULL;
	vector<int> path;
	uint8_t key[32];
	arr = read_image(argv[1]);

	Graph gr(height*length);
	int k = 0;
	for (int i = 0; i < height; i++){
		for (int j = 0; j < length; j++){
			if (j+1<length){
				gr.add(k, k+1, arr[i][j+1]);
				}
			if (i+1<height){
				gr.add(k, k+length, arr[i+1][j]);
			}
			k++;
		}
	}
	path = gr.s_Dijkstra(0, height*length-1);
	
	int size = 0;
	for(int i = 0; i < path.size(); i++){
		int tmp = path[i];
		size+=arr[tmp/length][tmp%length];
	}
	
	cout<<"weight: "<<size<<endl;
	key[0] = size%256;
	for(int i = 0; i < 31; i++){
		int tmp = path[i];
		key[i+1] = arr[tmp/length][tmp%length]%256;
	}
	
	if ((out = fopen("key.txt", "wb+")) == NULL){
		perror("file not open");
		return -1;
	}
	if (fwrite(key, sizeof(uint8_t), 32, out) != 32){
		perror("write to out");
		return -1;
	}
	for(int i = 0; i < height; i++){
		delete[] arr[i];
	}
	delete[] arr;
	fclose(out);
	return 0;
}
