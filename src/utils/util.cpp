#include "util.h"

int mygcd(int a, int b)
{
    return b ? mygcd(b, a%b) : a;
}
