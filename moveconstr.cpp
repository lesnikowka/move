#include <iostream>

template<class T>
class Vector {
    int n = 0;
    T* data = nullptr;
public:
    Vector() = default;
    Vector(int n_) : n(n_) {
        std::cout << "Const with paremeters" << std::endl;
        if (n < 0)
            throw std::exception("size cannot be less than 0");
        else 
            data = new T[n];
    }
    ~Vector() {
        std::cout << "Destructor" << std::endl;
        delete[] data;
    }
    Vector(const Vector& v) {
        std::cout << "Copy const" << std::endl;
        n = v.n;
        data = new T[n];
        memcpy(data, v.data, n * sizeof(T));
    }
    Vector& operator=(const Vector& v) {
        std::cout << "operator=" << std::endl;
        if (this == &v) return *this;
        if (n != v.n) {
            delete[] data;
            n = v.n;
            data = new T[n];
        }
        memcpy(data, v.data, n * sizeof(T));
        return *this;
    }
    int get_size() noexcept {
        return n; 
    }
    // move const:
    Vector(Vector&& v) {
        std::cout << "move const" << std::endl;
        n = v.n;
        data = v.data;
        v.data = nullptr;  // delete[] nullptr не делает ничего
        v.n = 0;
        // или std::swap(v.data,data)
    }
    Vector& operator=(Vector&& v) {
        std::cout << "move operator=" << std::endl;
        if (this == &v) {
            return *this;
        }
        delete[] data;
        data = v.data;
        n = v.n;
        v.data = nullptr;
        return *this;
    }
};

int main() {
    //{
    //    Vector<int> v;
    //    std::cout << v.get_size()<<std::endl;
    //}
    //{
    //    Vector<int> v(10);
    //    std::cout << v.get_size() << std::endl;
    //}
    //{
    //    Vector<int> v(10);
    //    Vector<int> v2(v);
    //    std::cout << v2.get_size() << std::endl;
    //}
    //{
    //    Vector<int> v(10);
    //    Vector<int> v2;
    //    v2 = v;
    //    std::cout << v2.get_size() << std::endl;
    //}
    //{
    //    Vector<int> v(10);
    //    Vector<int> v2 = v;
    //    std::cout << v2.get_size() << std::endl;
    //}

    { // MOVE:
        

        Vector<int> v2(10);
        Vector<int> v = std::move(v2);
    }
}
