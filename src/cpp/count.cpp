
#include "count.hpp"

int64_t count(int64_t number) {
    int64_t result = 0;
    for (int64_t i = 0; i < number; i++)
    {
        result += i;
    }
    return result;
}
