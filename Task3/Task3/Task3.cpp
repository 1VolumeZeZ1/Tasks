#include <iostream>

using namespace std;

int main(void)
{
    float   ch1, ch2, res;
    char    sim;
    cout << "Two Numbers: \n";
    cin >> ch1 >> ch2;
    cout << "Action: \n";
    cin >> sim;
    switch (sim)
    {
    case '*':
        res = ch1 * ch2;
        break;
    case '/':
        res = ch1 / ch2;
        break;
    case '-':
        res = ch1 - ch2;
        break;
    case '+':
        res = ch1 + ch2;
        break;
    default:
        cout << "ERROR...\n";
        system("pause");
        return 0;
    }
    cout << ch1 << sim << ch2 << "=" << res << endl;
    system("pause");
    return 0;
}