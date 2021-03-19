#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <tuple>

const int N = 1.0e3; //Number of points.
constexpr double eps = 1.0 / N;
constexpr long double Sigma = 0.0349 + 0.00523 + 0.005;
bool flag = false;


typedef std::tuple<long double, long double, long double> coord;

typedef std::tuple<long double, long double, long double, long double> longDoubleTuple;

std::vector<coord> descart();

std::vector <coord> polar ();

std::vector <coord> coordinate_transformation(std::vector<coord>& coords);

void data_file_creation (std::string& DataType, std::vector<coord>& xx);

void default_distribution_plot(std::string& name, std::string& data, std::string xlabel, std::string ylabel, std::string title);

std::vector<longDoubleTuple> direction_beam();

std::vector<coord> coordinates_of_the_1st_interaction(std::vector<longDoubleTuple>& beams);

void cap();

std::string exec(std::string str_obj);

void plot_of_the_1st_interaction(std::string& name);

int main() {
    std::vector<coord> points = std::move(descart());
    std::string name = "Distribution of " + std::to_string(N) + " points";
    DataFileCreation(name, points);
    plot(name, name, "x", "y", name);
    return 0;
}

std::vector<coord> descart() {
    std::vector <coord> coords;
    srand(time(nullptr));
    double x, y, a, b, z = 0;
    for(int i = 0; i < N; i++) {
        do {
            a = 1;
            b = a / 2.0;
            x = 2*eps*(rand()%(N+1)) - 1;
            y = 2*eps*(rand()%(N+1)) - 1;
        } while (std::pow(x, 2) / std::pow(a, 2) + std::pow(y, 2) / std::pow(b, 2) > 1);
        coords.emplace_back(std::make_tuple(x, y, z));
    }
    return coords;
}

void plot(std::string& name, std::string& data, std::string xlabel, std::string ylabel, std::string title) {
    //if you have problems with ".svg", you have to change ".svg" to ".pdf" in strings bellow.
    FILE *gp = popen("gnuplot  -persist", "w");
    if (!gp)
        throw std::runtime_error("Error opening pipe to GNU plot.");
    std::vector<std::string> stuff = {"set term svg",
                                      "set out \'" + name + ".svg\'",
                                      "set xlabel \'" + xlabel + "\'",
                                      "set ylabel \'" + ylabel + "\'",
                                      "set grid xtics ytics",
                                      "set title \'" + title + "\'",
                                      "plot \'" /*+ data + "\'using 1:2 with lines lw 2 lt rgb 'blue',\
                                      \'" */+ data + "\' using 1:2 lw 1 lt rgb 'orange' ti \'Nodes\'",
                                      "set key box top right",
                                      "set terminal wxt",
                                      "set output",
                                      "replot"};
    for (const auto &it : stuff)
        fprintf(gp, "%s\n", it.c_str());
    pclose(gp);



    void DataFileCreation (std::string& DataType, std::vector<std::pair<double, double>>& xx){
        //For reading created files via Matlab use command: M = dlmread('/PATH/file'); xi = M(:,i);
        std::ofstream fout;
        fout.open(DataType);
        for(unsigned i = 0; i < xx.size(); i++)
            fout << xx[i].first << '\t' << xx[i].second << std::endl;
        fout.close();
    }