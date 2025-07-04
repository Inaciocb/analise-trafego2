#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <iomanip>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Uso: " << argv[0] << " total_dist_per_window.csv\n";
    return 1;
  }

  std::ifstream arquivo_entrada(argv[1]);
  if (!arquivo_entrada)
  {
    std::cerr << "Erro ao abrir arquivo: " << argv[1] << "\n";
    return 1;
  }

  std::string linha;
  std::getline(arquivo_entrada, linha); // pula o cabeçalho

  std::map<uint64_t, uint64_t> total_por_janela;
  while (std::getline(arquivo_entrada, linha))
  {
    std::istringstream ss(linha);
    std::string token;
    uint64_t janela, contagem;

    if (!std::getline(ss, token, ','))
      continue;
    janela = std::stoull(token);

    if (!std::getline(ss, token, ','))
      continue;
    contagem = std::stoull(token);

    total_por_janela[janela] += contagem;
  }
  arquivo_entrada.close();

  if (total_por_janela.empty())
  {
    std::cerr << "Nenhum dado encontrado em " << argv[1] << "\n";
    return 1;
  }

  std::vector<uint64_t> janelas;
  std::vector<long double> contagens;
  for (auto &par : total_por_janela)
  {
    janelas.push_back(par.first);
    contagens.push_back(par.second);
  }
  size_t n_janelas = contagens.size();

  long double soma_contagens = 0;
  for (auto c : contagens)
    soma_contagens += c;
  long double media_contagens = soma_contagens / n_janelas;

  long double soma_quadrados = 0;
  for (auto c : contagens)
  {
    long double delta = c - media_contagens;
    soma_quadrados += delta * delta;
  }
  long double variancia = soma_quadrados / n_janelas;
  long double desvio_padrao = std::sqrt(variancia);

  long double coef_variacao = desvio_padrao / media_contagens;
  long double limiar_rajada = media_contagens + desvio_padrao;

  bool em_rajada = false;
  uint64_t inicio_rajada = 0;
  std::vector<long double> duracoes_rajadas;

  for (size_t i = 0; i < n_janelas; ++i)
  {
    if (!em_rajada && contagens[i] > limiar_rajada)
    {
      em_rajada = true;
      inicio_rajada = janelas[i];
    }
    else if (em_rajada && contagens[i] <= limiar_rajada)
    {
      duracoes_rajadas.push_back((janelas[i] - inicio_rajada) * 1.0L);
      em_rajada = false;
    }
  }
  if (em_rajada)
  {
    duracoes_rajadas.push_back((janelas.back() - inicio_rajada + 1) * 1.0L);
  }

  long double soma_duracoes = 0;
  for (auto d : duracoes_rajadas)
    soma_duracoes += d;
  long double duracao_media = duracoes_rajadas.empty() ? 0 : soma_duracoes / duracoes_rajadas.size();

  std::cout << "Janelas processadas:             " << n_janelas << "\n"
            << "Média de pkts por janela:        " << std::fixed << std::setprecision(2) << media_contagens << "\n"
            << "Desvio-padrão de pkts por janela: " << std::fixed << std::setprecision(2) << desvio_padrao << "\n"
            << "Burstiness (CV):                 " << std::fixed << std::setprecision(4) << coef_variacao << "\n"
            << "Número de rajadas:               " << duracoes_rajadas.size() << "\n"
            << "Duração média de rajada (s):     " << std::fixed << std::setprecision(2) << duracao_media << "\n";

  return 0;
}
