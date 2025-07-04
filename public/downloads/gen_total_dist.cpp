#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cstdint>

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Uso: " << argv[0]
              << " dist_tempo_por_ip.csv dist_total_por_janela.csv\n";
    return 1;
  }
  const char *arquivo_entrada = argv[1];
  const char *arquivo_saida = argv[2];

  std::ifstream entrada(arquivo_entrada);
  if (!entrada)
  {
    std::cerr << "Erro ao abrir: " << arquivo_entrada << "\n";
    return 1;
  }

  std::unordered_map<uint64_t, uint64_t> soma_por_janela;
  std::string linha;
  std::getline(entrada, linha); // pula cabeçalho

  while (std::getline(entrada, linha))
  {
    std::istringstream ss(linha);
    std::string token;
    uint64_t janela, contagem;

    if (!std::getline(ss, token, ','))
      continue;
    janela = std::stoull(token);

    if (!std::getline(ss, token, ','))
      continue;
    if (!std::getline(ss, token, ','))
      continue;
    contagem = std::stoull(token);

    soma_por_janela[janela] += contagem;
  }
  entrada.close();

  std::ofstream saida(arquivo_saida);
  if (!saida)
  {
    std::cerr << "Erro ao criar: " << arquivo_saida << "\n";
    return 1;
  }
  saida << "inicio_janela,contagem_pacotes\n";
  for (const auto &par : soma_por_janela)
  {
    saida << par.first << "," << par.second << "\n";
  }
  saida.close();

  std::cout << "Arquivo gerado: " << arquivo_saida << "\n";
  return 0;
}
