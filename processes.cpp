
#include <string>
#include <iostream>

class Process {
    //private member variables only accessible through pub member functions
    private:
        string name;
        int size;
        int s_mem_loc;
    //public getter and setter member functions
    public:
        void set_info(name, size, loc);
        int get_size();


} ;
//constructor 
Process::Process (string n, int s, int l) {
  width = a;
  height = b;
  s_mem_loc = l;
}

//overloaded constructor with initial values
Process::Process(){
    name = "unknown Process";
    size = 0;
    int s_mem_loc = 0;

}

void Process::set_info(string n, int s , int loc){
    name = n;
    size = s;
    s_mem_loc = loc;

}

int Process::get_size(void){ 

    return size;

}
