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

class Memory
{
    private:
        int blocks;
        int memory;

    public:
        int get_block();
        void set_block(int);
        int get_memory();
        void set_memory(int);
};

int Memory::get_block()
{
    return blocks;
}

void Memory::set_block(int blk)
{
    blocks = blk;
}

int Memory::get_memory()
{
    return memory;
}

void Memory::set_memory(int memo)
{
    memory = memo;
}

mutex mtx;
Memory memory;
// int blocks = 5;
// int init_memory[5] = {200, 300, 400, 100, 600}; 
// int process_memory[5] = {150, 250, 50, 450, 300};

//global vectors
vector<Memory> init_memory_blocks;
vector<Memory> process_memory_blocks;

// best fit - Calculate a total number of free memory blocks (aka “holes”) 
void *best_fit(void* arg)
{
    mtx.lock();
    vector<Memory> free_memory_blocks;
    free_memory_blocks = init_memory_blocks;
    int free_memory;

    // best fit algorithm
    for (int i = 0; i < memory.get_block(); ++i)
    {
        // find best fit block for current process
        int best_index = -1;
        for (int j = 0; j < memory.get_block(); ++j)
        {
            if (free_memory_blocks[j].get_memory() < process_memory_blocks[i].get_memory() && j == memory.get_block() - 1) cout << "Process "  << i + 1 << " cannot be allocated." << endl;
            if (free_memory_blocks[j].get_memory() >= process_memory_blocks[i].get_memory())
            {
                if (best_index == -1)
                {
                    best_index = j;
                } else if (free_memory_blocks[best_index].get_memory() > free_memory_blocks[j].get_memory())
                {
                    best_index = j;
                }
            }
        } 
        int newVal = free_memory_blocks[best_index].get_memory() - process_memory_blocks[i].get_memory();
        free_memory_blocks[best_index].set_memory(newVal);
    }

    for (int i = 0; i < memory.get_block(); ++i)
    {
        free_memory += free_memory_blocks[i].get_memory();
    }
    cout << "Free Memory From Best Fit Is: " << free_memory << endl << endl;
    mtx.unlock();
    return 0;
}

// first fit - Calculate a total leftover free memory (in KB)
void *first_fit(void *arg)
{
    mtx.lock();
    vector<Memory> free_memory_blocks; //empty box
    free_memory_blocks = init_memory_blocks; //assign the init memory to the vector of memory

    int free_memory; //how much free memory in whole vector
    int not_placed_index; // index 1 , where memory wasnt enough for process 

    // algorithm
    for (int i = 0; i < memory.get_block(); ++i) // 150 ...gets process memory  
    {    //i = 100
        for (int j = 0; j < memory.get_block(); ++j) // 200 -> 50, 300, 400, etc.. // checks if process memory fits in the memory block
        {   //j = 450
            if (free_memory_blocks[j].get_memory() < process_memory_blocks[i].get_memory() && j == memory.get_block() - 1) cout << "Process "  << i + 1 << " cannot be allocated." << endl;
            if (free_memory_blocks[j].get_memory() >= process_memory_blocks[i].get_memory())
            {
                int newVal = free_memory_blocks[j].get_memory() - process_memory_blocks[i].get_memory(); // 50 remaing memory after inserting the process
                free_memory_blocks[j].set_memory(newVal); //sets the remaining memory for the specific memory block after insertion
                break;
            }
        }
    }
        //goes through every memory block and calculates remaining free mem
    for (int i = 0; i < memory.get_block(); ++i)
    {
        free_memory += free_memory_blocks[i].get_memory();
    }
    cout << "Free Memory From First Fit Is: " << free_memory << endl << endl;

    mtx.unlock();
    return 0;
}

// worse fit - Calculate a total leftover free memory (in KB)
void *worst_fit(void* arg)
{
    mtx.lock();
    vector<Memory> free_memory_blocks;
    free_memory_blocks = init_memory_blocks;
    int free_memory;

    // algorithm
    for (int i = 0; i < memory.get_block(); ++i)
    {
        int worst_index = -1;
        for (int j = 0; j < memory.get_block(); ++j)
        {
            if (free_memory_blocks[j].get_memory() < process_memory_blocks[i].get_memory() && j == memory.get_block() - 1) cout << "Process "  << i + 1 << " cannot be allocated." << endl;
            if (free_memory_blocks[j].get_memory() >= process_memory_blocks[i].get_memory())
            {
                if (worst_index == -1)
                {
                    worst_index = j;
                } else if (free_memory_blocks[worst_index].get_memory() < free_memory_blocks[j].get_memory())
                {
                    worst_index = j;
                }
            }
        }
        int newVal = free_memory_blocks[worst_index].get_memory() - process_memory_blocks[i].get_memory();
        free_memory_blocks[worst_index].set_memory(newVal);
    }

    for (int i = 0; i < memory.get_block(); ++i)
    {
        free_memory += free_memory_blocks[i].get_memory();
    }

    cout << "Free Memory From Worst Fit Is: " << free_memory << endl << endl;

    mtx.unlock();
    return 0;
}

int main(int argc, char const *argv[])
{
    int user_choice;
    int blocks;
    bool invalid = false;

    cout << "\nHow many free memory blocks? ";
    cin >> blocks;

    int input = 0;
    cout << "\nInitial free memory blocks: " << endl;

	for(int i = 0; i < blocks; ++i)
	{
        cin >> input;
        memory.set_block(blocks);
        memory.set_memory(input);
		init_memory_blocks.push_back(memory);
	}

    // int process_blks[blocks];
    cout << "\nProcess free memory blocks: " << endl;
	for(int i = 0; i < blocks; ++i)
	{
        cin >> input;
        memory.set_block(blocks);
        memory.set_memory(input);
		process_memory_blocks.push_back(memory);
	}

    // some idea using threading
    pthread_t tid0, tid1, tid2;
    pthread_create(&tid0, NULL, best_fit, NULL);
    pthread_create(&tid1, NULL, first_fit, NULL);
    pthread_create(&tid2, NULL, worst_fit, NULL);

    
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_exit(NULL);

    return 0;
}