import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('ipg_stats_per_ip.csv')
top10 = df.nlargest(10, 'ipg_mean_usec').set_index('src_ip')

plt.figure(figsize=(12, 6))
top10['ipg_mean_usec'].plot(kind='bar')
plt.ylabel('IPG médio (µs)')
plt.title('Top 10 IPs por IPG médio')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.show()
