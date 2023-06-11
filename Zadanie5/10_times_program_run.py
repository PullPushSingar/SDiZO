import subprocess

program_path = "C:\\Users\\huber\\Desktop\\0STUDIA\\SDIZO\\SDiZO\\Zadanie5\\pliki_wykonywalne\\wersja_badawcza.exe"
number_of_runs = 10

for i in range(number_of_runs):
    print(f"Uruchomienie {i + 1}")
    subprocess.run(program_path)

print("Skrypt zakończony.")
