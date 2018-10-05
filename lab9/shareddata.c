#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv[]){
  int rank, size, i;
  const int root=0;
  MPI_Init(&argc, &argv[]);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  while(i >= 0){
    if(rank == root) {
      printf("enter integer: ");
      scanf("%d", &i);
    }
    if (i < 0){
      MPI_Finalize();
      return 0;
    }
    else{
      MPI_Bcast(&i, 1, MPI_INT, root, MPI_COMM_WORLD);
      printf("[%d]: After Bcast, i is %d\n", rank, i);
      fflush(stdout);
    }
  }

}
