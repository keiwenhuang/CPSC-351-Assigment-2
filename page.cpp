#include <iostream>
#include <pthread.h>
#include <cmath>

using namespace std;

//Question 9
class Page
{
    private:
        int pages;
        int byte_page_size;
        int ram_size;
        int physical_address;
    public:
        //Constructor
        Page(int p, int bps)
        {
            pages = p;
            byte_page_size = bps;
        };
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
        void calculations()
        {
             ram_size = pages * byte_page_size;
            //Using log base 2 (ram_size) = physical address
            physical_address = log2(ram_size);
            cout << "Total RAM size = " << ram_size << endl;
            cout << "Physical Address = " << physical_address << endl;
        };
};

int main(int argc, char const *argv[])
{
    int pages, byte_page_size;

    cout << "By entering page number and byte page size. Calculate the total RAM size"
         << " and how many bits are needed to each physical address." << endl;

    cout << "Please enter a page number: " << endl;
    cin >> pages;

    cout << "Please enter a byte page size: " << endl;
    cin >> byte_page_size;

    Page user_input(pages, byte_page_size);
    user_input.calculations();

}
