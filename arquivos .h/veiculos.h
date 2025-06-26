#ifndef VEICULOS_H
#define VEICULOS_H

using namespace std;

class Veiculos{
  private:
    static const int TAM_PLACA = 8;  // 7 caracteres + 1 para o '\0'
    static const int TAM_MODELO = 16;

    char placa[TAM_PLACA];
    char modelo[TAM_MODELO];
    bool status; // true = disponível, false = alugado/indisponível
  //Local* localAtural;

  public:
    Veiculos(const std::string& placa_inicial, const std::string& modelo_inicial);

  //métodos get
    string getPlaca();
    string getModelo();
    bool getStatus();
};

#endif //VEICULOS_H