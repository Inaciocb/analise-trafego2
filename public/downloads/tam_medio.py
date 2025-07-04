import pandas as pd
import matplotlib.pyplot as plt

def main():
    df = pd.read_csv('size_stats_per_ip.csv')

    print("Primeiras linhas:\n", df.head(), "\n")
    print("Estatísticas descritivas:\n", df['avg_pkt_size_bytes'].describe(), "\n")

    plt.figure(figsize=(10, 6))
    plt.boxplot(df['avg_pkt_size_bytes'], vert=True)
    plt.ylabel('Tamanho médio do pacote (bytes)')
    plt.title('Distribuição do tamanho médio de pacotes por IP')
    plt.tight_layout()
    plt.savefig('size_boxplot.png')
    plt.show()

    top10 = df.nlargest(10, 'avg_pkt_size_bytes').set_index('src_ip')
    plt.figure(figsize=(12, 6))
    top10['avg_pkt_size_bytes'].plot(kind='bar')
    plt.ylabel('Tamanho médio do pacote (bytes)')
    plt.title('Top 10 IPs por tamanho médio de pacote')
    plt.xticks(rotation=45, ha='right')
    plt.tight_layout()
    plt.savefig('size_top10.png')
    plt.show()

if __name__ == '__main__':
    main()
