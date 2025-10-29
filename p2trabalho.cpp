#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class Cliente {
public:
    string nome;
    int idade;
    string email;
    string cidade;
    string interesse;
    time_t ultimo_contato;

    Cliente() {}

    Cliente(string n, int i, string e, string c, string intv) : nome(n), idade(i), email(e), cidade(c), interesse(intv) {
        ultimo_contato = time(0);  
    }

    void atualizarUltimoContato() {
        ultimo_contato = time(0);  
    }
};

class SistemaMarketing {
private:
    Cliente* clientes; 
    int totalClientes;
    int capacidade;

public:
    SistemaMarketing() {
        capacidade = 100;  
        totalClientes = 0;
        clientes = new Cliente[capacidade];
    }

    ~SistemaMarketing() {
        delete[] clientes;  
    }

    void adicionarCliente(string nome, int idade, string email, string cidade, string interesse) {
        if (totalClientes < capacidade) {
            clientes[totalClientes++] = Cliente(nome, idade, email, cidade, interesse);
        } else {
            cout << "Limite de clientes atingido!" << endl;
        }
    }

    void exibirClientes() {
        if (totalClientes == 0) {
            cout << "Nenhum cliente cadastrado!" << endl;
            return;
        }
        for (int i = 0; i < totalClientes; i++) {
            cout << "Nome: " << clientes[i].nome << ", Idade: " << clientes[i].idade << ", Email: " << clientes[i].email
                 << ", Cidade: " << clientes[i].cidade << ", Interesse: " << clientes[i].interesse << endl;
        }
    }

    double calcularIdadeMedia() {
        if (totalClientes == 0) return 0.0;

        int somaIdades = 0;
        for (int i = 0; i < totalClientes; i++) {
            somaIdades += clientes[i].idade;
        }
        return static_cast<double>(somaIdades) / totalClientes;
    }

    int contarClientesPorInteresse(string interesse) {
        int contador = 0;
        for (int i = 0; i < totalClientes; i++) {
            if (clientes[i].interesse == interesse) {
                contador++;
            }
        }
        return contador;
    }

    void salvarDadosEmArquivo() {
        ofstream arquivo("clientes.csv");
        if (!arquivo.is_open()) {
            cout << "Erro ao salvar arquivo!" << endl;
            return;
        }
        for (int i = 0; i < totalClientes; i++) {
            arquivo << clientes[i].nome << "," << clientes[i].idade << "," << clientes[i].email << ","
                    << clientes[i].cidade << "," << clientes[i].interesse << endl;
        }
        arquivo.close();
        cout << "Dados salvos com sucesso!" << endl;
    }

    bool validarEmail(const string& email) {
        size_t pos = email.find("@");
        return pos != string::npos && email.find(".", pos) != string::npos;
    }
};

int main() {
    SistemaMarketing sistema;

    while (true) {
        cout << "\n1. Adicionar Cliente" << endl;
        cout << "2. Exibir Clientes" << endl;
        cout << "3. Calcular Idade Média" << endl;
        cout << "4. Contar Clientes por Interesse" << endl;
        cout << "5. Salvar Dados e Sair" << endl;
        int opcao;
        cin >> opcao;
        cin.ignore();  

        if (opcao == 1) {
            string nome, email, cidade, interesse;
            int idade;

            cout << "Nome: ";
            getline(cin, nome);

            cout << "Idade: ";
            cin >> idade;
            cin.ignore();  

            cout << "Email: ";
            getline(cin, email);

            while (!sistema.validarEmail(email)) {
                cout << "Email inválido. Insira um email válido: ";
                getline(cin, email);
            }

            cout << "Cidade: ";
            getline(cin, cidade);

            cout << "Interesse: ";
            getline(cin, interesse);

            sistema.adicionarCliente(nome, idade, email, cidade, interesse);
        } else if (opcao == 2) {
            sistema.exibirClientes();
        } else if (opcao == 3) {
            double idadeMedia = sistema.calcularIdadeMedia();
            cout << "Idade média dos clientes: " << idadeMedia << endl;
        } else if (opcao == 4) {
            string interesse;
            cout << "Digite o interesse: ";
            getline(cin, interesse);
            int quantidade = sistema.contarClientesPorInteresse(interesse);
            cout << "Número de clientes com o interesse '" << interesse << "': " << quantidade << endl;
        } else if (opcao == 5) {
            sistema.salvarDadosEmArquivo();
            break;
        }
    }

    return 0;
}

