#include "gerenciadorVeiculos.h"
#include "veiculos.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cmath> 

// --- FUNÇÃO AUXILIAR PARA CÁLCULO DE DISTÂNCIA ---
double calcularDistanciaEuclidiana(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// --- Implementação do Construtor ---
GerenciadorVeiculos::GerenciadorVeiculos() {
    carregarVeiculosDoArquivo();
}

// --- IMPLEMENTAÇÃO DO NOVO MÉTODO PÚBLICO ---
void GerenciadorVeiculos::salvarDados() const {
    salvarListaCompletaNoArquivo();
}

Veiculos* GerenciadorVeiculos::encontrarVeiculoMaisProximo(int x, int y) {
    Veiculos* veiculoMaisProximo = nullptr;
    double menorDistancia = std::numeric_limits<double>::max();

    for (Veiculos& veiculo : this->listaDeVeiculos) {
        if (!veiculo.getStatus()) {
            double distancia = calcularDistanciaEuclidiana(
                veiculo.getCoordenadaX(), 
                veiculo.getCoordenadaY(),
                x, 
                y
            );

            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                veiculoMaisProximo = &veiculo;
            }
        }
    }

    return veiculoMaisProximo;
}

// (O resto do arquivo não precisa de alterações)
// ... métodos adicionarNovoVeiculo, listarVeiculos, etc. ...
void GerenciadorVeiculos::adicionarNovoVeiculo() {
    Veiculos veiculoNovo = pedirDadosParaNovoVeiculo();
    this->listaDeVeiculos.push_back(veiculoNovo);
    salvarListaCompletaNoArquivo();
    std::cout << "\nVeiculo adicionado com sucesso!\n";
}

Veiculos GerenciadorVeiculos::pedirDadosParaNovoVeiculo() {
    string placa_lida, modelo_lido;
    char status_char;
    bool status_final;
    int coordX, coordY;

    cout << "--- Adicionar Novo Veiculo ---\n";
    do {
      cout << "Digite a placa: ";
      cin >> placa_lida;
      if(placa_lida.length() != 7){
        cout << "Erro: A placa deve conter exatamente 7 caracteres\n";
      }
    } while(placa_lida.length() != 7);

    cout << "Digite o modelo: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, modelo_lido);
    cout << "O veiculo esta ocupado? (S/N): ";
    cin >> status_char;
    status_final = (status_char == 'S' || status_char == 's');
    cout << "Digite a coordenada X do local atual: ";
    cin >> coordX;
    cout << "Digite a coordenada Y do local atual: ";
    cin >> coordY;

    return Veiculos(placa_lida, modelo_lido, status_final, coordX, coordY);
}

void GerenciadorVeiculos::carregarVeiculosDoArquivo() {
    std::ifstream arquivo(this->nomeDoArquivo, std::ios::binary);
    if (!arquivo) {
        std::cout << "Arquivo de dados nao encontrado. Um novo sera criado ao salvar o primeiro veiculo.\n";
        return;
    }
    Veiculos veiculoLido;
    while (arquivo.read(reinterpret_cast<char*>(&veiculoLido), sizeof(Veiculos))) {
        this->listaDeVeiculos.push_back(veiculoLido);
    }
    arquivo.close();
}

void GerenciadorVeiculos::listarVeiculos() const {
    std::cout << "\n--- LISTA DE VEICULOS ---\n";
    if (this->listaDeVeiculos.empty()) {
        std::cout << "Nenhum veiculo cadastrado.\n";
    } else {
        for (const auto& veiculo : this->listaDeVeiculos) {
            std::cout << "Placa: " << veiculo.getPlaca()
                      << " | Modelo: " << veiculo.getModelo()
                      << " | Status: " << (veiculo.getStatus() ? "Ocupado" : "Desocupado") 
                      << " | Local: (" << veiculo.getCoordenadaX() << ", " << veiculo.getCoordenadaY() << ")" << std::endl;
        }
    }
    std::cout << "---------------------------\n";
} 

void GerenciadorVeiculos::atualizarVeiculo() {
    std::string placa_busca;
    std::cout << "--- Atualizar Veiculo ---\n";
    std::cout << "Digite a placa do veiculo que deseja atualizar: ";
    std::cin >> placa_busca;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (Veiculos& veiculo : this->listaDeVeiculos){
        if (veiculo.getPlaca() == placa_busca) {
            std::cout << "Veiculo encontrado. Modelo atual: " << veiculo.getModelo() << ", Status atual: " << (veiculo.getStatus() ? "Ocupado" : "Desocupado") << ", Local atual: (" << veiculo.getCoordenadaX() << ", " << veiculo.getCoordenadaY() << ")" << std::endl;
            std::string novo_modelo;
            std::cout << "Digite o novo modelo (ou deixe em branco para nao alterar): ";
            std::getline(std::cin, novo_modelo);
            if (!novo_modelo.empty()) {
                veiculo.setModelo(novo_modelo);
            }
            char novo_status_char;
            cout << "Deseja alterar o status? (S/N): ";
            cin >> novo_status_char;
            if (novo_status_char == 'S' || novo_status_char == 's') {
                char ocupado_char;
                cout << "O veiculo esta ocupado? (S/N): ";
                cin >> ocupado_char;
                veiculo.setStatus(ocupado_char == 'S' || ocupado_char == 's');
            }
            char alterar_local_char;
            cout << "Deseja alterar o local? (S/N): ";
            cin >> alterar_local_char;
            if (alterar_local_char == 'S' || alterar_local_char == 's') {
                int novoX, novoY;
                cout << "Digite a nova coordenada X: ";
                cin >> novoX;
                cout << "Digite a nova coordenada Y: ";
                cin >> novoY;
                veiculo.setLocalAtual(novoX, novoY);
            }
            salvarListaCompletaNoArquivo();
            std::cout << "Veiculo atualizado com sucesso.\n";
            return;
        }
    }
    std::cout << "Veiculo com a placa '" << placa_busca << "' nao encontrado.\n";
}

void GerenciadorVeiculos::excluirVeiculo() {
    std::string placa_busca;
    std::cout << "--- Excluir Veiculo ---\n";
    std::cout << "Digite a placa do veiculo que deseja excluir: ";
    std::cin >> placa_busca;
    auto it = listaDeVeiculos.begin();
    while (it != listaDeVeiculos.end()) {
        if (it->getPlaca() == placa_busca) {
            std::cout << "Veiculo encontrado: " << it->getModelo() << std::endl;
            char confirmacao;
            std::cout << "Tem certeza que deseja excluir este veiculo? (S/N): ";
            std::cin >> confirmacao;
            if (confirmacao == 'S' || confirmacao == 's') {
                it = listaDeVeiculos.erase(it);
                salvarListaCompletaNoArquivo();
                std::cout << "Veiculo excluido com sucesso.\n";
            } else {
                std::cout << "Operacao cancelada.\n";
            }
            return;
        }
        ++it;
    }
    std::cout << "Veiculo com a placa '" << placa_busca << "' nao encontrado.\n";
}

void GerenciadorVeiculos::salvarListaCompletaNoArquivo() const {
    std::ofstream arquivo(this->nomeDoArquivo, std::ios::binary);
    if (!arquivo) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo para reescrever." << std::endl;
        return;
    }
    for (const auto& veiculo : this->listaDeVeiculos) {
     arquivo.write(reinterpret_cast<const char*>(&veiculo), sizeof(veiculo));
    }
    arquivo.close();
}