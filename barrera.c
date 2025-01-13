#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>



sem_t barrera;
pthread_mutex_t mutex; //=PTHREAD_MUTEX_INITIALIZER;
int NH=10;
int cont=0;


void * hilo(void *idH){
   int id=*(int *)idH;
   int a;
   a=(rand()%5)+1;
   printf("\nHilo %d tardaré %d segs\n",id,a);
   sleep(a);
   printf("\nHilo %d, llegue a la barrera\n",id);
   pthread_mutex_lock(&mutex);
   cont++;
   if (cont==NH)
    sem_post(&barrera);
   pthread_mutex_unlock(&mutex);
   sem_wait(&barrera);
   sem_post(&barrera);
   printf("\nHilo %d, sali de la barrera\n",id);
   pthread_exit(NULL);

}
int main(){
int id[NH];
int i;
pthread_t hilos[NH];
   sem_init(&barrera,0,0);
   for(i=0;i<NH;i++){
      // pthread_mutex_init(&sfilosofos[i],NULL);
      id[i]=i;

   }

   for(i=0;i<NH;i++){
      pthread_create(&hilos[i],NULL,hilo,&id[i]);
   }

   for(i=0;i<NH;i++){
      pthread_join(hilos[i],NULL);
   }
}
