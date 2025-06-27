#ifndef VEICULOS_H
#define VEICULOS_H
#include <string>

using namespace std;


class Veiculos{
  private:
  static const int TAM_PLACA = 8; 
  static const int TAM_MODELO = 16;
  
  char placa[TAM_PLACA];
  char modelo[TAM_MODELO];
  bool status; 
  //Local* localAtural;
  
  public:
  Veiculos();
  Veiculos(const std::string& placa_inicial, const std::string& modelo_inicial);
  
  //métodos get
  string getPlaca() const;
  string getModelo() const;
  bool getStatus() const;

  void setModelo(const std::string& novoModelo);
};

void salvarVeiculoEmArquivo(const Veiculos& veiculo);

#endif //VEICULOS_H