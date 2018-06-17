

double **training_input();
double **training_result();

double **training_matrix(struct matrixBW ** m);
double **training_matrix_result(struct matrixBW ** m);

int load(struct Network * n);
int save(struct Network * n);
