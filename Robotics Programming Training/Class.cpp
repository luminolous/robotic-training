#include <iostream>


using namespace std;


class Mobil {
public:
   string brand;  // Attribute
   string model;
   int tahun;


   void infoMobil() {  // Method
       cout << "Brand: " << brand << endl;
       cout << "Model: " << model << endl;
       cout << "Tahun: " << tahun << endl;
   };
};


int main() {
   Mobil mobil_toyota;
   mobil_toyota.brand = "Toyota";
   mobil_toyota.model = "Avanza";
   mobil_toyota.tahun = 2019;


   mobil_toyota.infoMobil();
}
