import matplotlib.pyplot as plt

# Чтение данных из файла
with open('result.txt', 'r') as file:
    data = file.read().split()

# Подготовка данных для построения графика
# print(data[2], data[13])
# print(data[10], data[21])
    
nsteps_40000000 = [float(data[1]) / float(data[i]) for i in range(2, 10)]
print(nsteps_40000000)
threads = [1, 2, 4, 7, 8, 16, 20, 40]

# Построение графика
plt.figure(figsize=(10, 6))
plt.plot(threads, nsteps_40000000, marker='o', label='40000000 steps')
plt.xlabel('Количество потоков p')
plt.ylabel('Ускорение Sp')
plt.title('График ускорения программы относительно количества потоков')
plt.legend()
plt.grid(True)
plt.show()

