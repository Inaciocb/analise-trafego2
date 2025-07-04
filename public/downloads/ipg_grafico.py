import pandas as pd
import matplotlib.pyplot as plt

dados = pd.read_csv('ipg_stats_per_ip.csv')

plt.figure(figsize=(10, 6))
plt.boxplot(dados['ipg_mean_usec'], vert=True)
plt.ylabel('IPG médio (µs)')
plt.title('Distribuição do IPG médio por IP')
plt.tight_layout()
plt.savefig('ipg_boxplot.png')
plt.show()

top10 = dados.nlargest(10, 'ipg_mean_usec').set_index('src_ip')
plt.figure(figsize=(12, 6))
top10['ipg_mean_usec'].plot(kind='line', marker='o')
plt.ylabel('IPG médio (µs)')
plt.title('Top 10 IPs por IPG médio')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('ipg_top10_line.png')
plt.show()
