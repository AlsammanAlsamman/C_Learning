int **createMatrix()
{
	int **matrix = (int **) malloc(sizeof(int *) * ROWN);
	size_t i;
	for (i = 0; i < ROWN; i += 1)
	{
	 matrix[i] = (int *) malloc(sizeof(int) * COLN);
	}
	return matrix;

}
void initMatrix(int **matrix){
	size_t i , j;
	for (i = 0; i < ROWN; i += 1)
	{
		for (j = 0; j < COLN; j += 1)
		{
			matrix[i][j] = rand()%100;
		}
	}
}
void printMatrix(int **matrix){
	size_t i , j;
	for (i = 0; i < ROWN; i += 1)
	{
		for (j = 0; j < COLN; j += 1)
		{
			printf("%d\t",matrix[i][j]);
		}
		printf("\n");
	}
}
