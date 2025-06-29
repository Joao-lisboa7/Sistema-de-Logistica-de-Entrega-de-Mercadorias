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
  int coordenadaX;
  int coordenadaY;
  
  public:
  Veiculos();
  Veiculos(const std::string& placa_inicial, const std::string& modelo_inicial, bool status_inicial, int coordX, int coordY);
  
  //métodos get
  string getPlaca() const;
  string getModelo() const;
  bool getStatus() const;
  int getCoordenadaX() const;
  int getCoordenadaY() const;

  void setModelo(const std::string& novoModelo);
  void setStatus(bool novoStatus);
  void setLocalAtual(int novoX, int novoY);
};

void salvarVeiculoEmArquivo(const Veiculos& veiculo);

#endif //VEICULOS_H