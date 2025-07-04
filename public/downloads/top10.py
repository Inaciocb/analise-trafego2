import matplotlib.pyplot as plt

def plotar_top10_ips():
    ips = [
        '203.77.116.15',
        '150.121.88.208',
        '150.121.8.6',
        '150.121.77.199',
        '74.228.67.3',
        '150.121.12.34',
        '45.185.184.46',
        '120.196.31.61',
        '203.77.107.137',
        '45.185.184.47'
    ]
    contagens = [
        22182992,
        20326085,
        9275356,
        5157574,
        4460406,
        4299151,
        4157967,
        2247357,
        1406036,
        1386207
    ]
    plt.figure(figsize=(12, 6))
    plt.bar(ips, contagens)
    plt.xlabel('IP de origem')
    plt.ylabel('Pacotes enviados')
    plt.title('Top 10 IPs mais ativos')
    plt.xticks(rotation=45, ha='right')
    plt.tight_layout()
    plt.savefig('top10_ips_ativos.png')
    plt.show()

if __name__ == '__main__':
    plotar_top10_ips()
