import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df_calor = pd.read_csv('heatmap.csv')

top_ips = df_calor.groupby('src_ip')['packet_count'].sum().nlargest(20).index
df_filtrado = df_calor[df_calor['src_ip'].isin(top_ips)]

tabela_matriz = df_filtrado.pivot(
    index='src_ip',
    columns='window_start',
    values='packet_count'
).fillna(0)

matriz_valores = tabela_matriz.values
lista_ips = tabela_matriz.index.tolist()
lista_janelas = tabela_matriz.columns.values

plt.figure(figsize=(12, 8))
plt.imshow(matriz_valores, aspect='auto', origin='lower')
plt.yticks(np.arange(len(lista_ips)), lista_ips)

posicoes_xticks = np.linspace(0, len(lista_janelas) - 1, 10, dtype=int)
rotulos_xticks = lista_janelas[posicoes_xticks]
plt.xticks(posicoes_xticks, rotulos_xticks, rotation=45, ha='right')

plt.xlabel('Início da janela (s)')
plt.ylabel('IP de origem (Top 20)')
plt.title('Heatmap: pacotes por IP ao longo do tempo')
plt.tight_layout()

plt.savefig('mapa_calor.png')
plt.show()
