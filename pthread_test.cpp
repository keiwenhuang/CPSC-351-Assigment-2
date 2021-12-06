#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int N = 5;

void* sub_thread(void* arg){



  cout << "This sub_thread"<<(long)arg << '\n' ;

  pthread_exit(NULL);
}

int main(){

  pthread_t my_thread;

  long id;
  for(id = 1 ; id <= 5; id++){

    //creating multiple threads.
    int ret =  pthread_create(&my_thread, NULL, &sub_thread , (void*)id);

        if(ret != 0) {
          printf("Error: pthread_create() failed\n");
          exit(EXIT_FAILURE);
          }
    }

         pthread_exit(NULL);




  return 0;
}