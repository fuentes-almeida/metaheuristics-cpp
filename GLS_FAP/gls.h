#ifndef GLS_H_INCLUDED
#define GLS_H_INCLUDED

long long int OriginalFSFAP_Evaluator(int **Weights, int** Neighbours,int t_num,int* solution);
long long int FSFAP_Evaluator(int **Weights, int** Neighbours,int **Features,int t_num,int* solution, int lambda);

void GenerateGraph(char* filename,int **Weights,int **Neighbours,int **Features, int t_num);

void RandomSolution(int *Transmitters,int t_num, int freq_num);
void CopyVector(int *src, int *dest,int size);

void Neighbour(int **Weights, int **Neighbours, int **Features,int *Current, int *Candidate, int t_num, int freq_num,int lambda);
void FAPHillClimbing(int **Weights, int **Neighbours, int **Features,int *Solution, int t_num,int freq_num, int lambda);

void ComputeUtilities(int *Solution, int **Weights, int** Neighbours, int **Features,int t_num);
void GuidedLocalSearch(char *filename, int **Weights, int **Neighbours, int **Features, int *Transmitters, int *BestSolution,int t_num, int freq_num,char*outputfile,int lambda);

#endif // GLS_H_INCLUDED
