import csv
import random

def generate_random_elements(n, start_range, end_range):
    elements = [str(random.randint(start_range, end_range)) for _ in range(n)]
    return elements

def save_to_csv(filename, elements):
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(elements)

# Ustawienia
n = 1000000                 # Liczba elementów do wygenerowania
start_range = -500        # Dolna granica zakresu
end_range = 500        # Górna granica zakresu
filename = 'random_elements.csv'  # Nazwa pliku CSV

# Generowanie elementów
elements = generate_random_elements(n, start_range, end_range)

# Zapis do pliku CSV
save_to_csv(filename, elements)

print(f"Plik '{filename}' został wygenerowany i zapisany.")