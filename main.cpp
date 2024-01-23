#include <iostream>
#include "datastructures.hpp"

int main(){
    AscStringComparison comp;
    std::string array[] = {"ZZZ", "AAA", "Hello", "World"};
    OrderedArrayList<std::string> test(comp, array, 4);

    std::cout << "Length: " << test.size() << std::endl;

    for(int i = 0 ; i < test.size() ; i++)
        std::cout << " " << test.get(i) << " ";


    std::cout << std::endl << test.find("World") << std::endl;

    return 0;
}
