import pandas as pd
import matplotlib.pyplot as plt

dados = pd.read_csv('size_cdf.csv')

plt.figure(figsize=(8, 6))
plt.step(dados['pkt_size'], dados['cdf'], where='post')
plt.xlabel('Tamanho do pacote (bytes)')
plt.ylabel('CDF')
plt.title('CDF do tamanho de pacotes IPv4')
plt.xlim(left=0)
plt.tight_layout()
plt.savefig('pkt_size_cdf.png')
plt.show()
