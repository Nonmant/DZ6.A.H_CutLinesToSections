//https://contest.yandex.ru/contest/27844/problems/H/

#include "funcs.h"
#include <bits/stdc++.h>

//! @brief Index of last true. If everything is false return 0
template<typename F1, typename F2>
unsigned long long binSearchLowerBound(F1 valueGenerate,
                           F2 valueCheck,
                                       unsigned long long left, unsigned long long right){
    while (left<right){
        unsigned long long cur = (left + right + 1)/2;
        auto value = valueGenerate(cur);
        if(valueCheck(value)){
            left = cur;
        } else {
            right = cur-1;
        }
    }
    return right;
}

unsigned long long getSections(
        const std::vector<unsigned long long > & lines,
        unsigned long long d){
    unsigned long long count = 0;
    for(auto line : lines){
        unsigned long long sections = line/d;
        if(sections == 0)
            break;
        count+=sections;
    }
    return count;
}

void parseFile(std::istream & input, std::ostream & output){

    unsigned long long n, k;
    input >> n >> k;

    std::vector<unsigned long long> lines(n);
    std::copy_n(std::istream_iterator<unsigned long long >(input), n, lines.begin());

    std::sort(lines.rbegin(),lines.rend());

    if(getSections(lines,1)<k){
        output << 0;
        return;
    }

    unsigned long long left = 1, right = *lines.begin();
    auto d = binSearchLowerBound(
            [](unsigned long long d){return d;},
                [&lines, &k](unsigned long long d){
                    return getSections(lines,d) >= k;
                },
                    left, right);
    output << d;
}
