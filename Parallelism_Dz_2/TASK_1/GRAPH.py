import numpy as np
import matplotlib.pyplot as plt

# Считываем данные из файла
with open('result.txt', 'r') as file:
    data = file.readlines()

# Инициализируем списки для хранения данных
matrix_sizes = []
timings = []

# Обрабатываем данные из файла
for line in data:
    line = line.strip()
    if line:
        if ' ' in line:
            matrix_sizes.append(list(map(int, line.split())))
        else:
            timings.append(float(line))

# Разделяем данные по размерам матриц
matrix1_timings = timings[:len(timings)//2]
matrix2_timings = timings[len(timings)//2:]

# Создаем списки для количества потоков
threads = [1, 2, 4, 7, 8, 16, 20, 40]

# Считаем ускорение
speedup_matrix1 = [matrix1_timings[0] / t for t in matrix1_timings]
speedup_matrix2 = [matrix2_timings[0] / t for t in matrix2_timings]

# Строим графики
plt.figure(figsize=(12, 6))
plt.plot(threads, speedup_matrix1, marker='o', label='20000x20000')
plt.plot(threads, speedup_matrix2, marker='o', label='40000x40000')
plt.xlabel('Количество потоков')
plt.ylabel('Ускорение')
plt.title('График ускорения в зависимости от количества потоков')
plt.legend()
plt.grid(True)
plt.show()