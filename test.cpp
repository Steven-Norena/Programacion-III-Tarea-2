//
// Created by STEVEN on 12/04/2026.
//
#include "CoreNumeric.h"

struct Vector2D {
    double x, y;

    Vector2D operator+(const Vector2D& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2D operator-(const Vector2D& other) const {
        return {x - other.x, y - other.y};
    }
    Vector2D operator*(const Vector2D& other) const {
        return {x * other.x, y * other.y};
    }

    Vector2D operator/(std::size_t n) const {
        return {x / n, y / n};
    }

    bool operator>(const Vector2D& other) const {
        return (x*x + y*y) > (other.x*other.x + other.y*other.y);
    }
};

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

int main() {
    std::cout << "--- Pruebas de Exito ---" << std::endl;

    std::vector<int> v_int = {10, 20, 30};
    std::cout << "Mean (int): " << core_numeric::mean(v_int) << std::endl;

    std::vector<double> v_double = {1.5, 2.5, 3.5};
    std::cout << "Variance (double): " << core_numeric::variance(v_double) << std::endl;

    auto s1 = core_numeric::sum_variadic(1, 2, 33, 4);
    auto s4 = core_numeric::max_variadic(1, 2.7, 3, 4);
    std::cout << "Sum Variadic: " << s1 << " | Max Variadic: " << s4 << std::endl;

    std::vector<Vector2D> v_vec = {{1, 2}, {3, 4}, {5, 6}};
    std::cout << "Mean Vector2D: " << core_numeric::mean(v_vec) << std::endl;
    std::cout << "Max Vector2D: " << core_numeric::max(v_vec) << std::endl;

    auto sq_sum = core_numeric::transform_reduce(v_int, [](int x) { return x * x; });
    std::cout << "Transform Reduce (sq sum): " << sq_sum << std::endl;
    return 0;

    //---- ERRORES DE COMPILACIÓN -----

    // --- CASO 1: Concept 'Divisible' ---
    // El tipo std::string es Iterable y Addable (se puede concatenar usando el operador +),
    // pero no es Divisible, ya que no se puede dividir una palabra entre un número.
    /*
    std::vector<std::string> palabras = {"Hola", "Mundo"};
    auto err1 = core_numeric::mean(palabras);
    */

    // --- CASO 2: Concept 'Iterable' ---
    // Intentar pasar un tipo de dato simple a una función que espera un contenedor.
    /*
    int numero_simple = 100;
    auto err3 = core_numeric::sum(numero_simple);
    */


    // --- CASO 3: Concept 'Addable' en Variadics ---
    // Si creamos una estructura vacía que no tiene sobrecarga de operador '+',
    // las funciones variádicas deben rechazarla.
    /*
    struct ObjetoInutil {};
    ObjetoInutil obj1, obj2;
    auto err4 = core_numeric::sum_variadic(obj1, obj2);
    */


    // --- CASO 4: Mezcla de tipos incompatibles en Variadics ---
    // Intentar usar variance_variadic con tipos de datos que no se pueden operar entre sí
    /*
    auto err5 = core_numeric::variance_variadic("texto", 1.5, 10);
    */
}