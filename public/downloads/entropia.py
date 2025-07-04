import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df_entropia = pd.read_csv('entropia.csv')

entropias = []
for inicio_janela, grupo in df_entropia.groupby('window_start'):
    frequencias = grupo['packet_count'] / grupo['packet_count'].sum()
    entropia = - (frequencias * np.log2(frequencias)).sum()
    entropias.append((inicio_janela, entropia))

df_resultado = pd.DataFrame(entropias, columns=['inicio_janela', 'entropia'])
df_resultado['horario'] = pd.to_datetime(df_resultado['inicio_janela'], unit='s')

plt.figure(figsize=(12, 4))
plt.plot(df_resultado['horario'], df_resultado['entropia'], '-o', markersize=2)
plt.xlabel('Horário')
plt.ylabel('Entropia (bits)')
plt.title('Entropia de Shannon ao longo do tempo')
plt.tight_layout()
plt.savefig('linha_entropia.png')
plt.show()
