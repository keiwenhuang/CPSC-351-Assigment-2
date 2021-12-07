#include <iostream>
#include <sstream>
#include <thread>
#include <pthread.h>
#include <vector>
#include <mutex>

using namespace std;

void *addition(void *arg)
{
    int *a, *b, newVal;
    newVal = (int*)a + (int*)b;
    cout << "a + b is " << newVal << endl;;
}

void *subtraction(void *arg)
{
    int *a, *b, newVal;
    newVal = (int*)a - (int*)b;
    cout << "a + b is " << newVal << endl;;
}

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;  
    return 0;
}
