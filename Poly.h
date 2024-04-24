#ifndef POLY_H_
#define POLY_H_

#include <iostream>
#include <cassert>
#include <math.h>
class Poly {
private:
    int miejsce;
    double *tablica = NULL;

public:
    Poly(){
		tablica=NULL;
		miejsce=0;
    }
    Poly(double zmienna){
		tablica=new double[1];
		miejsce=1;
        tablica[0] = zmienna;
    }
    Poly(const Poly &other) : miejsce(other.miejsce), tablica(new double[other.miejsce + 1]) {
        for (int i = 0; i < miejsce; i++) {
            tablica[i] = other.tablica[i];
        }
    }
    ~Poly() {
        delete[] tablica;
    }

    Poly &operator=(const Poly &other) {
        if (this == &other) {
            return *this;
        }
     
       double *temp = new double[other.miejsce + 1];
       miejsce = other.miejsce;
        delete[] tablica;
        tablica=temp;
        for (int i = 0; i < miejsce; ++i) {
            tablica[i] = other.tablica[i];
        }
        return *this;
    }

    double &operator[](int index) {
        if (index >= miejsce) {
            double *nowa_tablica = new double[index + 1];
            for (int i = 0; i < miejsce; i++) {
                nowa_tablica[i] = tablica[i];
            }
            for (int i = miejsce; i <= index; i++) {
                nowa_tablica[i] = 0.0;
            }
            delete[] tablica;

            tablica = nowa_tablica;
            miejsce = index + 1;
        }
        return tablica[index];
    }

friend Poly operator+(const Poly &second, const Poly &other) {
    int max_of_elements_other = other.miejsce;
    int max_of_elements_this = second.miejsce;

    int max_miejsce = std::max(max_of_elements_other, max_of_elements_this);
    Poly result;
    result.tablica = new double[max_miejsce];
    result.miejsce = max_miejsce;
    
    for (int i = 0; i < max_miejsce; ++i) {
        double coeff1 = (i < max_of_elements_this) ? second.tablica[i] : 0;
        double coeff2 = (i < max_of_elements_other) ? other.tablica[i] : 0;
        result.tablica[i] = coeff1 + coeff2;
    }

    return result;
}

    friend Poly operator-(const Poly &second, const Poly &other) {
    int max_of_elements_other = other.miejsce;
    int max_of_elements_this = second.miejsce;

    int max_miejsce = std::max(max_of_elements_other, max_of_elements_this);
    Poly result;
    result.tablica = new double[max_miejsce];
    result.miejsce = max_miejsce;

    for (int i = 0; i < max_miejsce; ++i) {
        double coeff1 = (i < max_of_elements_this) ? second.tablica[i] : 0;
        double coeff2 = (i < max_of_elements_other) ? other.tablica[i] : 0;
        result.tablica[i] = coeff1 - coeff2;
    }
    return result;
}

  friend Poly operator*(const Poly& first, const Poly& second){
		Poly wynik;
        wynik[first.miejsce + second.miejsce - 1]=0.0;
        for(int i = 0; i < wynik.miejsce; i++){
            wynik.tablica[i] = 0;
        }
        for (int i = 0; i < first.miejsce; ++i) {
            for (int j = 0; j < second.miejsce; ++j) {
                wynik[i + j] += first.tablica[i] * second.tablica[j];
            }
        }
        return wynik;
}
    double operator()(double x) const {
        double result = 0;
        double power = 1;

        for (int i = 0; i < miejsce; ++i) {
            result += tablica[i] * power;
            power *= x;
        }

        return result;
    }
friend std::ostream &operator<<(std::ostream &os, const Poly &poly){
        int licznik = 0;
        for (int i = poly.miejsce - 1; i >= 0; i--) {
            if (poly.tablica[i] == 0) {
                licznik++;
                if (licznik == poly.miejsce) {
                    os << "0";
                    break;
                }
                continue;
            }
            if (i == 0) {
                os << poly.tablica[i];
                continue;
            }
            if(i==1){
                os << poly.tablica[i] << "x";
            }
            if(i!=1)
            os << poly.tablica[i] << "x^" << i;
            if (poly.tablica[i - 1] == 0) {
                for (int j = i - 2; j >= 0; j--) {
                    if (poly.tablica[j] > 0) {
                        os << " + ";
                        break;
                    }
                    if (poly.tablica[j] < 0) {
                        os << " ";
                        break;
                    }
                }
                continue;
            }
            os << " + ";
        }
        return os;
    }
};

#endif // POLY_H_
