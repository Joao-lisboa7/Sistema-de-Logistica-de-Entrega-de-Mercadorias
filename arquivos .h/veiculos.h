#ifndef VEICULOS_H
#define VEICULOS_H

using namespace std;

class Veiculos{
  private:
    string placa;
    string modelo;
    string status;
  //Local* localAtural;

  public:
    Veiculos(string placa, string modelo, string status/*, Local* localAtual  */);

  //métodos get
    string getPlaca();
    string getModelo();
    string getStatus();
};

#endif //VEICULOS_H