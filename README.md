# Zestaw5
Opis programu:

Ten program to prosty rysownik, który tworzy obrazki na płótnie, zapisuje je do pliku. Program jest napisany w języku C++ i wykorzystuje obiektowe podejście do tworzenia obrazów na płótnie.

Jak ściągnąć repozytorium:

Upewnij się, że masz zainstalowany system kontroli wersji Git na swoim komputerze.
Otwórz terminal lub konsolę.
W wybranym katalogu, w którym chcesz umieścić repozytorium, wykonaj polecenie:

git clone https://adres_repozytorium.git
Zastąp https://adres_repozytorium.git adresem rzeczywistego repozytorium.
Jak skompilować program:

Upewnij się, że masz zainstalowanego kompilatora C++ (np. g++).
Przejdź do katalogu z repozytorium programu.
Skompiluj program, wykonując polecenie:

g++ -o program program.cpp
Gdzie program.cpp to nazwa pliku źródłowego programu.
Jak używać programu:

Program jest uruchamiany z wiersza poleceń. Oto sposób użycia:

./program <config_file>
<config_file>: Ścieżka do pliku konfiguracyjnego, który określa, co ma być narysowane na płótnie.
Struktura pliku konfiguracyjnego:

Plik konfiguracyjny powinien zawierać następujące informacje:

canvas <width> <height>: Określenie rozmiarów płótna, gdzie <width> to szerokość, a <height> to wysokość.
output <filename>: Określenie nazwy pliku, do którego zostanie zapisany obraz (może być puste, jeśli nie chcesz zapisywać obrazu).
empty <symbol>: Określenie symbolu reprezentującego puste miejsce na płótnie.
Następnie w pliku konfiguracyjnym można zdefiniować figury i światła, używając następujących komend:

rectangle <x> <y> <width> <height> <symbol>: Określenie prostokąta o lewym górnym rogu w punkcie (<x>, <y>), o szerokości <width>, wysokości <height> i symbolu <symbol>.
circle <x> <y> <radius> <symbol>: Określenie okręgu o środku w punkcie (<x>, <y>), o promieniu <radius> i symbolu <symbol>.
light <x> <y> <shadowSymbol>: Określenie światła o położeniu (<x>, <y>) i symbolu cienia <shadowSymbol>.
Przykład pliku konfiguracyjnego:


canvas 20 12
output output.txt
empty .
rectangle 3 2 2 2 #
rectangle 14 6 3 3 #
rectangle 0 2 3 2 .
rectangle 13 6 1 1 .
rectangle 12 7 2 1 .
rectangle 11 8 3 1 .
rectangle 10 9 7 1 .
rectangle 9 10 8 1 .
circle 17 2 0 *
light 15 3


Ten plik konfiguracyjny stworzy płótno o rozmiarach 20X12, zapisze obraz do pliku "output.txt", użyje kropki "." jako symbolu pustego miejsca, narysuje prostokąt "#", okrąg "*" światła  na płótnie.

Po uruchomieniu programu z odpowiednim plikiem konfiguracyjnym zostanie stworzony obraz zgodnie z zadanymi parametrami.
