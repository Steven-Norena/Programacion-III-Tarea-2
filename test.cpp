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
}