#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;
/*
    Q9 Calculate total RAM size and how many bits are needed to each physical address given number of pages and byte page size
*/

class Page
{
    private:
        int pages;
        int byte_page_size;
        int ram_size;
        int physical_address;
    public:
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
       static void *calcPages(void *);
};
        void * Page::calcPages(void * )
        {
            Page user_input;
            int pages;
            int byte_page_size;
            int ram_size;
            int physical_address;
            pages = user_input.get_pages();

             ram_size = pages * byte_page_size;
            //Using log base 2 (ram_size) = physical address
            physical_address = log2(ram_size);
            cout << "Total RAM size = " << ram_size << endl;
            cout << "Physical Address = " << physical_address << endl;

            pthread_exit(NULL);
            

        };


int main()
{
            Page user_input;
            int pages;
            int byte_page_size;
            int ram_size;
            int physical_address;
            
       cout << "By entering page number and byte page size. Calculate the total RAM size"
                 << " and how many bits are needed to each physical address." << endl;

             cout << "Please enter a page number: " << endl;
             cin >> pages;
             user_input.set_pages(pages);
             
            
             cout << "Please enter a byte page size: " << endl;
             cin >> byte_page_size;
             user_input.set_byte_page_size(byte_page_size);

             
    Page *page_ptr = new Page();
    pthread_t test;
    
    pthread_create(&test, NULL, Page::calcPages, page_ptr);

    pthread_join(test, NULL);

    //Page user_input;
    //user_input.calcPages();
}