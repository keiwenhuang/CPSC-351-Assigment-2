#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

/*
    Q9 Calculate total RAM size and how many bits are needed to each physical address given number of pages and byte page size
*/

//Global Variables
int pages;
int byte_page_size;
int ram_size;
int physical_address;

//Getters
int get_pages()
{
    return pages;
}
int get_byte_page_size()
{
    return byte_page_size;
}
//setters
void set_pages(int p)
{
    pages = p;
};
void set_byte_page_size(int bps)
{
    byte_page_size = bps;
};

//Calculating ram_size and physical_address given by the user
void * calcPages(void * )
{
    pages = get_pages();
    byte_page_size = get_byte_page_size();

    //Multiplying pages and byte_page_size to get ram_size
    ram_size = pages * byte_page_size;
    //Using log base 2 (ram_size) = physical address
    physical_address = log2(ram_size);

    cout << "Total RAM size = " << ram_size << endl;
    cout << "Physical Address = " << physical_address << endl;

    pthread_exit(NULL);
            
};


int main()
{      

    cout << "By entering page number and byte page size. Calculate the total RAM size"
         << " and how many bits are needed to each physical address." << endl;

    cout << "Please enter a page number: " << endl;
    cin >> pages;
    set_pages(pages);
             
            
    cout << "Please enter a byte page size: " << endl;
    cin >> byte_page_size;
    set_byte_page_size(byte_page_size);

    //Creating and using thread object
    pthread_t obj;
    pthread_create(&obj, NULL, calcPages, NULL);
    pthread_join(obj, NULL);
}


