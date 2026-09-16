import matplotlib.pyplot as plt 
import numpy as np 

def ejercicio_loops():
    '''
    # result execution loops:

    ====== avergage for iter=30 =========
    first loop
    N=4000: 38.1688 ms
    N=8000: 152.357 ms
    N=10000: 238.793 ms

    second loop
    N=4000: 95.6525 ms
    N=8000: 503.087 ms
    N=10000: 933.818 ms
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
    plt.close()


def matriz_mult_i_j_k():
    '''
    N = 100
    classic i-j-k multiply time: 15.164 ms
    performance i-k-j multiply time: 4.57 ms
    N = 500
    classic i-j-k multiply time: 520.819 ms
    performance i-k-j multiply time: 456.025 ms
    N = 1000
    classic i-j-k multiply time: 6094.39 ms
    performance i-k-j multiply time: 3734.19 ms
    N = 1300
    classic i-j-k multiply time: 13971.7 ms
    performance i-k-j multiply time: 8167.01 ms
    N = 1500
    classic i-j-k multiply time: 21636.8 ms
    performance i-k-j multiply time: 12605.9 ms
    N = 1600
    classic i-j-k multiply time: 26245.4 ms
    performance i-k-j multiply time: 15436.3 ms
    '''
    n = [100, 500, 1000, 1300, 1500, 1600]
    t_classic = [15.164, 520.819, 6094.39, 13971.7, 21636.8, 26245.4]
    t_perf = [4.57, 456.025, 3734.19, 8167.01, 12605.9, 15436.3]

    n_suave = np.linspace(min(n), max(n), 300)

    # Ajuste Teórico (Cúbico O(N³)) para Clásico
    c1 = t_classic[-1] / (n[-1]**3)
    t_classic_teorico = c1 * (n_suave**3)
    
    # Ajuste Teórico (Cúbico O(N³)) para Performance
    c2 = t_perf[-1] / (n[-1]**3)
    t_perf_teorico = c2 * (n_suave**3)

    plt.figure(figsize=(9, 6))

    plt.scatter(n, t_classic, color='#d62728', edgecolors='black', s=70, zorder=5, label='Mediciones: Clásico i-j-k')
    plt.plot(n_suave, t_classic_teorico, color='#d62728', linestyle='--', linewidth=2, label='Tendencia Teórica $O(N^3)$ (Clásico)')

    plt.scatter(n, t_perf, color='#2ca02c', edgecolors='black', s=70, zorder=5, label='Mediciones: Performance i-k-j')
    plt.plot(n_suave, t_perf_teorico, color='#2ca02c', linestyle='-.', linewidth=2, label='Tendencia Teórica $O(N^3)$ (Performance)')

    plt.title('Comparación de Tiempo de Ejecución: Multiplicación de Matrices', fontsize=14, fontweight='bold', pad=15)
    plt.xlabel('Tamaño de la matriz (N)', fontsize=12)
    plt.ylabel('Tiempo de ejecución (ms)', fontsize=12)

    plt.xlim(min(n) - 100, max(n) + 100)
    plt.ylim(0, max(t_classic) + 2000)
    plt.grid(True, linestyle=':', alpha=0.6)
    plt.legend(fontsize=11, loc='upper left')

    plt.savefig('verificacion_matriz_mult.png', dpi=300, bbox_inches='tight')
    plt.close()

def matriz_mult_bloques():
    '''
    N = 100
    classic i-j-k multiply time: 9.322 ms
    performance i-k-j multiply time: 4.748 ms
    blocked multiply time: 3.089 ms
    ... (omitted for brevity)
    N = 1600
    classic i-j-k multiply time: 25425.4 ms
    performance i-k-j multiply time: 14993.6 ms
    blocked multiply time: 12175.7 ms
    '''
    n = [100, 500, 1000, 1300, 1400, 1500, 1600]
    t_classic = [9.322, 507.7, 5510.63, 13571, 16753.7, 20812.7, 25425.4]
    t_perf = [4.748, 452.065, 3656.83, 8043.4, 10026.2, 12381.1, 14993.6]
    t_blocked = [3.089, 375.047, 2976.52, 6558.87, 8152.99, 10066, 12175.7]

    n_suave = np.linspace(min(n), max(n), 300)

    # Ajuste Teórico (Cúbico O(N³)) para Clásico
    c1 = t_classic[-1] / (n[-1]**3)
    t_classic_teorico = c1 * (n_suave**3)
    
    # Ajuste Teórico (Cúbico O(N³)) para Performance
    c2 = t_perf[-1] / (n[-1]**3)
    t_perf_teorico = c2 * (n_suave**3)

    # Ajuste Teórico (Cúbico O(N³)) para Blocked
    c3 = t_blocked[-1] / (n[-1]**3)
    t_blocked_teorico = c3 * (n_suave**3)

    plt.figure(figsize=(9, 6))

    plt.scatter(n, t_classic, color='#d62728', edgecolors='black', s=70, zorder=5, label='Mediciones: Clásico i-j-k')
    plt.plot(n_suave, t_classic_teorico, color='#d62728', linestyle='--', linewidth=2, label='Tendencia Teórica (Clásico)')

    plt.scatter(n, t_perf, color='#2ca02c', edgecolors='black', s=70, zorder=5, label='Mediciones: Performance i-k-j')
    plt.plot(n_suave, t_perf_teorico, color='#2ca02c', linestyle='-.', linewidth=2, label='Tendencia Teórica (Performance)')

    plt.scatter(n, t_blocked, color='#1f77b4', edgecolors='black', s=70, zorder=5, label='Mediciones: Blocked')
    plt.plot(n_suave, t_blocked_teorico, color='#1f77b4', linestyle=':', linewidth=2, label='Tendencia Teórica (Blocked)')

    plt.title('Comparación de Tiempo de Ejecución: Incluyendo Bloques', fontsize=14, fontweight='bold', pad=15)
    plt.xlabel('Tamaño de la matriz (N)', fontsize=12)
    plt.ylabel('Tiempo de ejecución (ms)', fontsize=12)

    plt.xlim(min(n) - 100, max(n) + 100)
    plt.ylim(0, max(t_classic) + 2000)
    plt.grid(True, linestyle=':', alpha=0.6)
    plt.legend(fontsize=11, loc='upper left')

    plt.savefig('verificacion_matriz_bloques.png', dpi=300, bbox_inches='tight')
    plt.close()

if __name__ == '__main__':
    # ejercicio_loops()
    # matriz_mult_i_j_k()
    matriz_mult_bloques()
