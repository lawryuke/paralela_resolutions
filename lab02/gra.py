import matplotlib.pyplot as plt 
import numpy as np 

'''
# result execution loops:

====== avergage =========
first loop
N=0: 38.1688 ms
N=1: 152.357 ms
N=2: 238.793 ms

second loop
N=0: 95.6525 ms
N=1: 503.087 ms
N=2: 933.818 ms
'''

n = [4000, 8000, 10000]
t1 = [38.1688, 152.357, 238.793]
t2 = [95.6525, 503.087, 933.818]

n_suave = np.linspace(min(n), max(n), 300)

# Ajuste para el Primer Bucle (Cuadrático O(N²))
c1 = t1[-1] / (n[-1]**2)
t1_teorico = c1 * (n_suave**2)

# Ajuste para el Segundo Bucle (Regresión polinómica para capturar su tendencia exacta)
coef_t2 = np.polyfit(n, t2, 2)
t2_teorico = np.polyval(coef_t2, n_suave)

# 3. Configuración del gráfico
plt.figure(figsize=(9, 6))

# Graficar Primer Bucle (Puntos + Línea de tendencia)
plt.scatter(n, t1, color='#1f77b4', edgecolors='black', s=70, zorder=5, label='Mediciones: Primer Bucle')
plt.plot(n_suave, t1_teorico, color='#1f77b4', linestyle='--', linewidth=2, label='Tendencia Teórica $O(N^2)$')

# Graficar Segundo Bucle (Puntos + Línea de tendencia)
plt.scatter(n, t2, color='#ff7f0e', edgecolors='black', s=70, zorder=5, label='Mediciones: Segundo Bucle')
plt.plot(n_suave, t2_teorico, color='#ff7f0e', linestyle='-.', linewidth=2, label='Tendencia Real (Bucle 2)')

# 4. Personalización del diseño académico
plt.title('Comparación de Tiempo de Ejecución: Loops de Algoritmos', fontsize=14, fontweight='bold', pad=15)
plt.xlabel('Tamaño de la entrada (N)', fontsize=12)
plt.ylabel('Tiempo promedio de ejecución (ms)', fontsize=12)

# Configurar límites y formato de los ejes
plt.xlim(min(n) - 500, max(n) + 500)
plt.ylim(0, max(t2) + 100)
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend(fontsize=11, loc='upper left')

# 5. Exportar imagen en alta resolución para el reporte y mostrar
plt.savefig('verificacion_loops.png', dpi=300, bbox_inches='tight')
plt.show()
