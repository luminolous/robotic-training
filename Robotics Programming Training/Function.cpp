# include <iostream>
using namespace std;

int latihan1(int a, int b)
{
    int hasil;
    hasil = a + b;
    return hasil;
}



int main() {
    int a;
    cout << "Masukkan angka pertama : ";
    cin >> a;
    int b;
    cout << "Masukkan angka kedua : ";
    cin >> b;
    cout << latihan1(a, b) << endl;
}
