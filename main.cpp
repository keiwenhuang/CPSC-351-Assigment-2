/**
 * Q2
 * Q3
 * Q4
 */

#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

void best_fit()
{

}

void first_fit()
{

}

void worst_fit()
{

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
    string initial_memory_blocks;
    string memory_blocks;

    cout << "Which method you want to use? " << endl;
    cout << "1. Best Fit" << endl;
    cout << "2. Worst Fit" << endl;
    cout << "3. First Fit" << endl;
    cout << "Choice: ";
    cin >> user_choice;

    cout << "\nHow free memory blocks? ";
    cin >> blocks;

    cout << "\nInitial free memory blocks: ";
    cin >> initial_memory_blocks;

    cout << "\nMemory blocks to be placed: " << endl;
    cin >> memory_blocks;
    


    return 0;
}