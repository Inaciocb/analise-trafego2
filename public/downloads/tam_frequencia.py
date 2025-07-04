import pandas as pd
import matplotlib.pyplot as plt

def carregar_dados():
    return pd.read_csv('tam_frequencia.csv')

def plotar_relacao_tamanho_frequencia(dados):
    tamanhos = dados['pkt_size']
    frequencia = dados['frequency']
    plt.figure(figsize=(10,6))
    plt.plot(tamanhos, frequencia, marker='o')
    plt.xlabel('Tamanho do Pacote (bytes)')
    plt.ylabel('Frequência (nº de pacotes)')
    plt.title('Relação entre Tamanho dos Pacotes e Frequência de Envio')
    plt.tight_layout()
    plt.savefig('tam_frequencia_linha.png')
    plt.show()

if __name__ == '__main__':
    dados = carregar_dados()
    plotar_relacao_tamanho_frequencia(dados)
