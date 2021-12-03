#include <iostream>
#include <pthread.h>

using namespace std
/**
 * Q9
 */
class Page
{
    private:
        int pages;
        int byte_page_size;
        int ram_size;
        int physical_address;
    public:

};

int main(int argc, char const *argv[])
{
    cout << "By entering page number and byte page size. Calculate the total RAM size"
         << " and how many bits are needed to each physical address." << endl;

    cout << "Please enter a page number " << endl;
    cin >> pages;

    cout << "Please enter a byte page size" << endl;
    cin >> byte_page_size;

    ram_size = pages * byte_page_size;
    // log base 2 (ram_size) = physical address
    physical_address = log2(ram_size);

    cout << "Total RAM size = " << ram_size << endl;
    cout << "Physical Address = " << physical_address << endl;


    
}
