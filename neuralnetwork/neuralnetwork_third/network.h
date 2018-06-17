struct network {
	struct layer *layers;
	size_t len_layers;
	
	int *sizes;
	size_t len_sizes;

	char *path;
} network_t;

struct network *create_network(int *sizes, int len, char *path);
/*
int load_weight(struct network *net, FILE *cfg);

int save_weight(struct network *net);*/
