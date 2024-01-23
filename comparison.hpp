#ifndef COMPARISON_HPP
#define COMPARISON_HPP

template <typename T> class Comparison{
public:
    int compare(T o1, T o2){
        if (o1 < o2) return -1;
        if (o1 == o2) return 0;
        return 1;
    }
};

/*

DEFAULT COMPARISON IMPLEMENTATIONS

*/

class AscIntComparison : public Comparison<int>{
public:
    int compare(int o1, int o2){
        if(o1 < o2) return -1;
        if(o1 == o2) return 0;
        return 1;
    }
};

class DescIntComparison : public Comparison<int>{
public:
    int compare(int o1, int o2){
        if(o1 > o2) return -1;
        if(o1 == o2) return 0;
        return 1;
    }
};

class AscStringComparison : public Comparison<std::string>{
public:
    int compare(std::string o1, std::string o2){
        return o1.compare(o2);
    }
};

class DescStringComparison : public Comparison<std::string>{
public:
    int compare(std::string o1, std::string o2){
        return o2.compare(o1);
    }
};

#endif