#include <iostream>
using namespace std;
int a, n, t;
int main()
{
    cout << "Hi! Try to guess a number! \n";
    a = rand() % 99 + 1;
while (a!=t) {
    n++;
    cout << n << " Try: \n";
    cin >> t;
    if (t>a) cout << " Less \n";
    if(t<a) cout << " Greater \n";
}
cout << "You guessed right! \n";
    return 0;
}

