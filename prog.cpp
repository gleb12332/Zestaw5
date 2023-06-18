#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Canvas {
public:
    Canvas(int width, int height) : width(width), height(height) {
        pixels = std::vector<std::vector<char>>(height, std::vector<char>(width, ' '));
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    void setPixel(int x, int y, char symbol) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = symbol;
        }
    }

    char getPixel(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return pixels[y][x];
        }
        return ' ';
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "|";
            for (int i = 0; i < width; ++i) {
                file << "=";
            }
            file << "|" << std::endl;
            for (int y = 0; y < height; ++y) {
                file << "|";
                for (int x = 0; x < width; ++x) {
                    file << pixels[y][x];
                }
                file << "|" << std::endl;
            }
            file << "|";
            for (int i = 0; i < width; ++i) {
                file << "=";
            }
            file << "|" << std::endl;
            file.close();
            std::cout << "Image saved to file: " << filename << std::endl;
        } else {
            std::cout << "Unable to save image to file: " << filename << std::endl;
        }
    }

private:
    int width;
    int height;
    std::vector<std::vector<char>> pixels;
};

class Figure {
public:
    virtual void draw(Canvas& canvas) = 0;
};

class Rectangle : public Figure {
public:
    Rectangle(int x, int y, int width, int height, char symbol)
        : x(x), y(y), width(width), height(height), symbol(symbol) {}

    void draw(Canvas& canvas) override {
        for (int row = y; row < y + height; ++row) {
            for (int col = x; col < x + width; ++col) {
                canvas.setPixel(col, row, symbol);
            }
        }
    }

private:
    int x;
    int y;
    int width;
    int height;
    char symbol;
};

class Circle : public Figure {
public:
    Circle(int x, int y, int radius, char symbol)
        : x(x), y(y), radius(radius), symbol(symbol) {}

    void draw(Canvas& canvas) override {
        for (int row = y - radius; row <= y + radius; ++row) {
            for (int col = x - radius; col <= x + radius; ++col) {
                if (isInsideCircle(col, row)) {
                    canvas.setPixel(col, row, symbol);
                }
            }
        }
    }

private:
    bool isInsideCircle(int px, int py) const {
        int dx = px - x;
        int dy = py - y;
        return dx * dx + dy * dy <= radius * radius;
    }

    int x;
    int y;
    int radius;
    char symbol;
};

std::vector<Figure*> parseConfigFile(const std::string& filename, int& canvasWidth, int& canvasHeight,
                                    std::string& outputFile, char& emptySymbol, std::vector<Canvas>& lights) {
    std::vector<Figure*> figures;

    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::istringstream iss(line); 

            std::string command;
            iss >> command;

            if (command == "canvas") {
                iss >> canvasWidth >> canvasHeight;
            } else if (command == "output") {
                iss >> outputFile;
            } else if (command == "empty") {
                iss >> emptySymbol;
            } else if (command == "rectangle") {
                int x, y, width, height;
                char symbol;
                iss >> x >> y >> width >> height >> symbol;
                figures.push_back(new Rectangle(x, y, width, height, symbol));
            } else if (command == "circle") {
                int x, y, radius;
                char symbol;
                iss >> x >> y >> radius >> symbol;
                figures.push_back(new Circle(x, y, radius, symbol));
            } else if (command == "light") {
                int x, y;
                iss >> x >> y;
                lights.push_back(Canvas(x, y));
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open configuration file: " << filename << std::endl;
    }

    return figures;
}

void drawFiguresOnCanvas(const std::vector<Figure*>& figures, Canvas& canvas) {
    for (Figure* figure : figures) {
        figure->draw(canvas);
    }
}

void castShadows(const std::vector<Canvas>& lights, Canvas& canvas) {
    for (const Canvas& light : lights) {
        for (int row = 0; row < canvas.getHeight(); ++row) {
            for (int col = 0; col < canvas.getWidth(); ++col) {
                if (!light.getPixel(col, row) && canvas.getPixel(col, row) != ' ') {
                    canvas.setPixel(col + 1, row + 1, '.');
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./program <config_file>" << std::endl;
        return 1;
    }

    std::string configFile = argv[1];

    int canvasWidth = 0;
    int canvasHeight = 0;
    std::string outputFile;
    char emptySymbol = ' ';
    std::vector<Canvas> lights;

    std::vector<Figure*> figures = parseConfigFile(configFile, canvasWidth, canvasHeight, outputFile, emptySymbol, lights);

    if (canvasWidth <= 0 || canvasHeight <= 0) {
        std::cout << "Invalid canvas dimensions." << std::endl;
        return 1;
    }

    Canvas canvas(canvasWidth, canvasHeight);

    drawFiguresOnCanvas(figures, canvas);
    castShadows(lights, canvas);

    canvas.saveToFile(outputFile);

    for (Figure* figure : figures) {
        delete figure;
    }

    return 0;
}

/*
config_file.txt:

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

*/