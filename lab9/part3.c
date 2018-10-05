#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv[]){
  int rank, size, i;
  double d;
  struct {int a; double b;} myvalues;
  MPI_Datatype mystruct;
  MPI_Datatype types[2] = {MPI_INT, MPI_DOUBLE};
  int blocklens[2];
  MPI_Aint indices[2];
  const int root=0;
  MPI_Init(&argc, &argv[]);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  blocklens[0] = 1;
  blocklens[1] = 1;

  MPI_Address( &myvalues.a, &indices[0] );
  MPI_Address( &myvalues.b, &indices[1] );

  indices[1] = indices[1] - indices[0];
  indices[0] = 0;

  MPI_Type_struct( 2, blocklens, indices, types, &mystruct );
  MPI_Type_commit( &mystruct );

  while(i >= 0){
    if(rank == root) {
      printf("enter integer and double separated by 1 space: ");
      scanf("%d %f", &myvalues.a, &myvalues.b);
    }
    if (i < 0){
      MPI_Type_free( &mystruct );
      MPI_Finalize();
      return 0;
    }
    else{
      MPI_Bcast(&myvalues, 1, mystruct, root, MPI_COMM_WORLD);
      printf("[%d]: After Bcast, my values are %d and %f\n", rank, myvalues.a, myvalues.b);
      fflush(stdout);
    }
  }

}
