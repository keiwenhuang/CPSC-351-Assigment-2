/**
 * Q2 Calculate a total number of free memory blocks (aka “holes”) in KB after applying best-fit allocation strategy
 * Q3 Calculate a total leftover free memory (in KB) after applying worst-fit allocation strategy
 * Q4 Calculate a total leftover free memory (in KB) after applying first -fit allocation strategy 
 */

#include <iostream>
#include <sstream>
#include <thread>
#include <pthread.h>
#include <vector>
#include <mutex>

using namespace std;

// arg for thread
struct memory_block
{
    private:
        int size;
        int order;
    public:
        memory_block(int size, int order);
};

// global variable for user input
// blocks, init memory, process memory
mutex mtx;


// best fit - Calculate a total number of free memory blocks (aka “holes”) 
void *best_fit(void* arg)
{
    // seprate init_memory_blk_size, memory_blk_size into array
    // hard coded sample, need to make it dynamic
    int init_memory[5] = {200, 300, 400, 100, 600}; 
    int process_memory[5] = {150, 250, 50, 450, 300};
    int free_memory = 0;

    // best fit algorithm
    // ??? trying to implement OOP here, but actully not sure how to implement in this
    mtx.lock();
    for (int i = 0; i <= blocks; ++i)
    {
        memory_block memory(init_memory[i], i);
    }

    for (int i = 0; i <= blocks; ++i)
    {
        // find best fit block for current process
        int best_index = -1;
        for (int j = 0; j <= blocks; ++j)
        {
            if (init_memory[j] >= process_memory[i])
            {
                if (best_index == -1)
                {
                    best_index = j;
                } else if (init_memory[best_index] > init_memory[j])
                {
                    best_index = j;
                }
            }
        } 
        init_memory[best_index] -= process_memory[i];
    }

    for (int i = 0; i <= blocks; ++i)
    {
        free_memory += init_memory[i];
    }
    mtx.unlock();
}

// first fit - Calculate a total leftover free memory (in KB)
void *first_fit(void *arg)
{
    mtx.lock();
    // algorithm
    int init_memory[5] = {200, 300, 400, 100, 600}; 
    int process_memory[5] = {150, 250, 50, 450, 300};
    int free_memory = 0;

    for (int i = 0; i <= blocks; ++i)
    {
        for (int j = 0; j <= blocks; ++j)
        {
            if (init_memory[j] >= process_memory[i])
            {
                init_memory[j] -= process_memory[i];
                break;
            }
        }
    }

    for (int i = 0; i <= blocks; ++i)
    {
        free_memory += init_memory[i];
    }
    mtx.unlock();
}

// worse fit - Calculate a total leftover free memory (in KB)
void *worst_fit(void* arg)
{
    mtx.lock();
    // algorithm
    int init_memory[5] = {200, 300, 400, 100, 600}; 
    int process_memory[5] = {150, 250, 50, 450, 300};
    int free_memory = 0;

    for (int i = 0; i <= blocks; ++i)
    {
        int worst_index = -1;
        for (int j = 0; j <= blocks; ++j)
        {
            if (init_memory[j] >= process_memory[i])
            {
                if (worst_index == -1)
                {
                    worst_index = j;
                } else if (init_memory[worst_index] < init_memory[j])
                {
                    worst_index = j;
                }
            }
        }
        init_memory[worst_index] -= process_memory[i];
    }

    for (int i = 0; i <= blocks; ++i)
    {
        free_memory += init_memory[i];
    }
    mtx.unlock();
}

int main(int argc, char const *argv[])
{
    // some idea using threading
pthread_t tid0;
pthread_create(&tid0, NULL, best_fit, NULL);
pthread_t tid1;
pthread_create(&tid1, NULL, first_fit, NULL);
pthread_t tid2;
pthread_create(&tid2, NULL, worst_fit, NULL);

    // thread t1(best_fit);
    // t1.join();

    // thread t2(first_fit);
    // t2.join();

    // thread t3(worst_fit);
    // t3.join();

    int user_choice;
    int blocks;
    string init_memory_blk_size;
    string memory_blk_size;
    bool invalid = false;

    // 1 input from user
    // pass input as object into fit funtion
    // use threads to run fit functions
    // print result

    do 
    {
        cout << "Which method you want to use? " << endl;
        cout << "1. Best Fit" << endl;
        cout << "2. Worst Fit" << endl;
        cout << "3. First Fit" << endl;
        cout << "Choice: ";
        cin >> user_choice;
    } while (user_choice != 1 || user_choice != 2 || user_choice != 3);
    
    do
    {
        cout << "\nHow free memory blocks? ";
        cin >> blocks;
    } while (!isdigit(blocks));


    cout << "\nInitial free memory blocks: ";
    cin >> init_memory_blk_size;

    cout << "\nMemory blocks to be placed: " << endl;
    cin >> memory_blk_size;

    if(user_choice == 1)
        best_fit(blocks, init_memory_blk_size, memory_blk_size);
    else if(user_choice == 2)
        worst_fit(blocks, init_memory_blk_size, memory_blk_size);
    else if(user_choice == 3)
        first_fit(blocks, init_memory_blk_size, memory_blk_size);
    else
        cout << "Invalid Option" << endl;

    return 0;
}