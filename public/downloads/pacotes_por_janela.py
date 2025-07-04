import pandas as pd
import matplotlib.pyplot as plt

def principal():
    dados = pd.read_csv('pacotes_por_janela.csv')
    dados['horario'] = pd.to_datetime(dados['window_start'], unit='s')

    print("Primeiras linhas:")
    print(dados.head(), "\n")
    print("Estatísticas de contagem de pacotes:")
    print(dados['packet_count'].describe(), "\n")

    plt.figure(figsize=(12, 5))
    plt.plot(dados['horario'], dados['packet_count'], linewidth=1)
    plt.xlabel('Horário')
    plt.ylabel('Número de pacotes IPv4')
    plt.title('Variação de tráfego ao longo do tempo')
    plt.tight_layout()
    plt.savefig('serie_temporal_trafego.png')
    plt.show()

    dados['media_movel'] = dados['packet_count'].rolling(window=60, min_periods=1).mean()
    plt.figure(figsize=(12, 5))
    plt.plot(dados['horario'], dados['packet_count'], alpha=0.3)
    plt.plot(dados['horario'], dados['media_movel'], linewidth=1.5)
    plt.xlabel('Horário')
    plt.ylabel('Número de pacotes IPv4')
    plt.title('Tráfego IPv4 com média móvel')
    plt.tight_layout()
    plt.savefig('trafego_media_movel.png')
    plt.show()

if __name__ == '__main__':
    principal()
