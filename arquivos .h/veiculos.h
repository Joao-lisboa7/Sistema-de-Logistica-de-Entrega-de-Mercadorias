#ifndef VEICULOS_H
#define VEICULOS_H

using namespace std;

class Veiculos{
  private:
    string placa;
    string modelo;
    bool status; // true = disponível, false = alugado/indisponível
  //Local* localAtural;

  public:
    Veiculos(string placa, string modelo /*, Local* localAtual  */);

  //métodos get
    string getPlaca();
    string getModelo();
    bool getStatus();
};

#endif //VEICULOS_H