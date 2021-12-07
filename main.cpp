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
vector<Memory> init_memory;
vector<Memory> process_memory;
int free_memory;

// best fit - Calculate a total number of free memory blocks (aka “holes”) 
void *best_fit(void* arg)
{
    // best fit algorithm
    mtx.lock();
    cout << "blocks in best: " << memory.get_block() << endl;

    for (int i = 0; i < memory.get_block(); ++i)
    {
        cout << "init memory " << i << " " << init_memory[i].get_memory() << endl;
        cout << "process memory " << i << " " << process_memory[i].get_memory() << endl;
    }

    for (int i = 0; i < memory.get_block(); ++i)
    {
        // find best fit block for current process
        int best_index = -1;
        for (int j = 0; j < memory.get_block(); ++j)
        {
            if (init_memory[j].get_memory() >= process_memory[i].get_memory())
            {
                if (best_index == -1)
                {
                    best_index = j;
                } else if (init_memory[best_index].get_memory() > init_memory[j].get_memory())
                {
                    best_index = j;
                }
            }
        } 
        int newVal = init_memory[best_index].get_memory() - process_memory[i].get_memory();
        init_memory[best_index].set_memory(newVal);
    }

    for (int i = 0; i < memory.get_block(); ++i)
    {
        free_memory += init_memory[i].get_memory();
    }
    cout << "Free Memory From Best Fit Is: " << free_memory << endl;
    mtx.unlock();
    return 0;
}

// first fit - Calculate a total leftover free memory (in KB)
void *first_fit(void *arg)
{
    mtx.lock();
    // algorithm

    for (int i = 0; i < memory.get_block(); ++i)
    {
        cout << "init memory " << i << " " << init_memory[i].get_memory() << endl;
        cout << "process memory " << i << " " << process_memory[i].get_memory() << endl;
    }

    for (int i = 0; i < memory.get_block(); ++i)
    {
        for (int j = 0; j < memory.get_block(); ++j)
        {
            if (init_memory[j].get_memory() >= process_memory[i].get_memory())
            {
                int newVal = init_memory[j].get_memory() - process_memory[i].get_memory();
                init_memory[j].set_memory(newVal);
                break;
            }
        }
    }

    for (int i = 0; i < memory.get_block(); ++i)
    {
        free_memory += init_memory[i].get_memory();
    }
    cout << "Free Memory From First Fit Is: " << free_memory << endl;

    mtx.unlock();
    return 0;
}

// worse fit - Calculate a total leftover free memory (in KB)
void *worst_fit(void* arg)
{
    mtx.lock();
    // algorithm

    for (int i = 0; i < memory.get_block(); ++i)
    {
        cout << "init memory " << i << " " << init_memory[i].get_memory() << endl;
        cout << "process memory " << i << " " << process_memory[i].get_memory() << endl;
    }

    for (int i = 0; i < memory.get_block(); ++i)
    {
        int worst_index = -1;
        for (int j = 0; j < memory.get_block(); ++j)
        {
            if (init_memory[j].get_memory() >= process_memory[i].get_memory())
            {
                if (worst_index == -1)
                {
                    worst_index = j;
                } else if (init_memory[worst_index].get_memory() < init_memory[j].get_memory())
                {
                    worst_index = j;
                }
            }
        }
        int newVal = init_memory[worst_index].get_memory() - process_memory[i].get_memory();
        init_memory[worst_index].set_memory(newVal);
    }

    for (int i = 0; i < memory.get_block(); ++i)
    {
        free_memory += init_memory[i].get_memory();
    }

    cout << "Free Memory From Worst Fit Is: " << free_memory << endl;

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
		init_memory.push_back(memory);
        // cout << "memory: " << input << ", blocks: " << blocks << endl; 
        // cout << "int memory: " << init_memory[i].get_memory() << endl;
        // cout << "ini memory: " << memory.get_memory() << ", init block: " << memory.get_block() << endl;
	}

    // int process_blks[blocks];
    cout << "\nProcess free memory blocks: " << endl;
	for(int i = 0; i < blocks; ++i)
	{
        cin >> input;
        memory.set_block(blocks);
        memory.set_memory(input);
		process_memory.push_back(memory);
        // cout << "pro memory: " << process_memory[i].get_memory() << endl;
        // cout << "pro memory: " << memory.get_memory() << ", pro block: " << memory.get_block() << endl;
	}

    // for (int i = 0; i < memory.get_block(); ++i)
    // {
    //     cout << "init memory " << i << " " << init_memory[i].get_memory() << endl;
    //     cout << "process memory " << i << " " << process_memory[i].get_memory() << endl;
    // }

    // some idea using threading
    pthread_t tid0, tid1, tid2;
    pthread_create(&tid0, NULL, best_fit, NULL);
    pthread_create(&tid1, NULL, first_fit, NULL);
    pthread_create(&tid2, NULL, worst_fit, NULL);

    
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}