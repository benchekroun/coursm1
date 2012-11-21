#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#define TAILLE 20
using namespace std;

void fusionnerpetit(int * a, int ta, int * b , int tb , int * res, int tres){
  int cpt = 0;
  int aiter = 0;
  int biter = 0;
  while(cpt < tres){
    if(a[atier] <= b[biter]){
      res[cpt] = a[aiter];
      aiter++;
      cpt++;
    }
    else{
      res[cpt] = b[biter];
      biter++;
      cpt++;
    }    
  } 
}

void fusionnergrand(int * a, int ta, int * b , int tb , int * res, int tres){
  int cpt = tres-1;
  int aiter = ta-1;
  int biter = tb-1;
  while(cpt >=0){
    if(a[atier] > b[biter]){
      res[cpt] = a[aiter];
      aiter--;
      cpt--;
    }
    else{
      res[cpt] = b[biter];
      biter--;
      cpt--;
    }    
  } 
}



void tri_insertion(int * T, int n){
  /*  pour i de 2 à n
      x ← T[i]
      j ← i
      tant que j > 1 et T[j - 1] > x
      T[j] ← T[j - 1]
      j ← j - 1
      fin tant que
      T[j] ← x
      fin pour*/
  int x= 0;
  int j = 0;
  for(int i = 2; i< n;i++){
    x= T[i];
    j=i
      while(j >1 && T[j-1] > x){
	T[j] = T[j-1];
	j--;
      }
    T[j] = x;
  }
}


int main ( int argc , char **argv ){
  srand(time(NULL));
  int pid;
  int nbprocs;
  int buf[TAILLE];
  for(int i = 0; i < TAILLE ;i++){
    buf[i] = rand()%100;
  }
  //on suppose n proportionnel au nombre de processeur
  int tranche;
  int * work;
  int * res;
  int  * recv;
  int etape = -1;
  bool finish = false;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nbprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  tranche = TAILLE / nbprocs;
  work = new int[tranche];
  res= new int[tranche];
  recv = new int[tranche];
  // init - etape n-1
  for(int x= 0; x<tranche; x++){
    work[x] = buf[x+(pid*tranche)];
  }
  //first sort
  tri_insertion(work,tranche);
  //main loop
  while(etape < nbprocs){
    etape++;

    if(etape%2 == 0){ // etape paire
      if(pid%2 == 0){
	if(pid != nbprocs-1){
	  MPI_Ssend(work, tranche, MPI_INT, (pid+1)%nbprocs, 9, MPI_COMM_WORLD);
	}
	MPI_Recv(recv, tranche, MPI_INT, (pid+1)%nbprocs , 9, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	fusionnerpetit(recv,tranche,work,tranche,res,tranche); // fusion des res
	work = res; // res devient le nouvel espace de travail
      }
      else{	
	MPI_Recv(recv, tranche, MPI_INT, ((pid-1)+nbprocs)%nbprocs, 9, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	MPI_Ssend(work, tranche, MPI_INT,((pid-1)+nbprocs)%nbprocs , 9, MPI_COMM_WORLD);
	fusionnergrand(recv,tranche,work,tranche,res,tranche); // fusion des res
	work = res; // res devient le nouvel espace de travail
	²      }
    }
    else{ //etape impaire
      if(pid%2 == 0){
 
	MPI_Ssend(work, tranche, MPI_INT,((pid-1)+nbprocs)%nbprocs , 9, MPI_COMM_WORLD);
	MPI_Recv(recv, tranche, MPI_INT, ((pid-1)+nbprocs)%nbprocs, 9, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	fusionnergrand(recv,tranche,work,tranche,res,tranche); // fusion des res
	work = res; // res devient le nouvel espace de travail
      }
      else{
	
	MPI_Recv(recv, tranche, MPI_INT, (pid+1)%nbprocs , 9, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	MPI_Ssend(work, tranche, MPI_INT, (pid+1)%nbprocs, 9, MPI_COMM_WORLD);
	fusionnerpetit(recv,tranche,work,tranche,res,tranche); // fusion des res
	work = res; // res devient le nouvel espace de travail
      }
    }
    
  } //fin while
  MPI_Gather(work,tranches,MPI_INT, buf,TAILLE,MPI_INT,0,MPI_COMM_WORLD);
  if(pid  == 0){
    for(int z = 0 ; z < TAILLE; z++){
      cout<<buf[z]<<" ";
    }
    cout<<endl;
  }
  if(work)
    delete [] work;
  if(res)
    delete [] res;
  if(recv)
    delete [] recv;
  

  
  
  MPI_Finalize();
 
  return 0 ;
}

