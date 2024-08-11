#include <string>

using namespace std;

static string formatRupiah(int num)
{
    string delimiter = ".";
    string output = to_string(num);
    int inspost = output.length() - 3;
    while (inspost > 0)
    {
        output.insert(inspost, delimiter);
        inspost -= 3;
    }
    return "Rp." + output + ",00";
}