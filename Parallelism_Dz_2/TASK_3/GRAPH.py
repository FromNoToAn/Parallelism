import matplotlib.pyplot as plt

# Чтение данных из файла
with open('result.txt', 'r') as file:
    data = file.read().split()

# Подготовка данных для построения графика

ver_1 = [float(data[1]) / float(data[i]) for i in range(1, 81)]
# print(ver_1)
ver_2 = [float(data[81]) / float(data[i]) for i in range(82, 162)]
# print(ver_2)
threads = [i for i in range (1, 81)]

# Построение графика
plt.figure(figsize=(10, 6))
plt.plot(threads, ver_1, marker='o', label='ver 1')
plt.plot(threads, ver_2, marker='o', label='ver 2')
plt.xlabel('Количество потоков p')
plt.ylabel('Ускорение Sp')
plt.title('График ускорения программы относительно количества потоков')
plt.legend()
plt.grid(True)
plt.show()

