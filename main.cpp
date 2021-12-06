/**
 * Q2
 * Q3 Calculate a total leftover free memory (in KB) after applying worst-fit allocation strategy 
    to place blocks of size 100KB, 500KB, 150KB, 200KB, and 100KB into given initial free 
    memory blocks of 300KB, 200KB,  600KB and 250KB
 * Q4
 * 
 */

#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

struct memory_block
{
    private:
        int size;
        int order;
    public:
        memory_block(int size, int order);
    
};


void best_fit(int blocks, string init_memory_blk_size, string memory_blk_size)
{
    // seprate init_memory_blk_size into array
    int init_memory[5] = {200, 300, 400, 500, 600};

    // best fit algorithm
    for (int i = 0; i <= blocks; ++i)
    {
        memory_block memory(init_memory[i], i);
    }
    
}

void first_fit(int blocks, string init_memory_blk_size, string memory_blk_size)
{
    // first fit algorithm

user input 500 300 200 400

200 300 400 500

200 300 400 150

150 200 300 400



}

void worst_fit(int blocks, string init_memory_blk_size, string memory_blk_size)
{
    // worse fit algorithm
    
}

int main(int argc, char const *argv[])
{
    // some idea using threading
    thread t1(best_fit);
    t1.join();

    thread t2(first_fit);
    t2.join();

    thread t3(worst_fit);
    t3.join();

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