#include <iostream>
#include <vector>

using namespace std;


// Q1
// Research smart pointers provided by the standard library (since C++11). List them and
// explain the difference between them.
// 
// Answer:
// 1) unique_ptr: Can be used for Handling dynamically allocated objects in a restricted scope.
//                Do not support copying. Going out of scope invalidates the unique_ptr.
// 2) shared_ptr: Can be used for storing and passing a reference beyond the scope of a function.
//                Its Objects have the ability of taking ownership of a pointer and share that ownership: 
//                once they take ownership, the group of owners of a pointer become responsible for its deletion,
//                when the last one of them releases that ownership.
// 3) auto_ptr:   Can hold a non-owning ("weak") reference to an object that is managed by shared_ptr. 
//                It must be converted to shared_ptr in order to access the referenced object.
//
// Reference: https://en.cppreference.com/w/cpp/memory
//            http://www.cplusplus.com/reference/memory


template <class T> class SmartPointer {
    
private:
    T *iptr;
    T *aptr;
    int arrSize;

public:
    SmartPointer();
    SmartPointer(T x);

    SmartPointer(bool forArray, int size);
    SmartPointer(T arr[], int size);

    ~SmartPointer();

    T getValue();
    void setValue(T x);

    T getValue(int index);
    void setValue(int index, T element);

    void printArr();

    //Operators Overloading (Q5)
    friend SmartPointer<T> operator+(const SmartPointer<T> &p1, const SmartPointer<T> &p2) {
        //for int
        if(p1.iptr!=nullptr && p2.iptr!=nullptr) {
            return SmartPointer<T>(*p1.iptr + *p2.iptr);
        }
        //for array
        else if(p1.aptr != nullptr && p2.aptr != nullptr) {
            if(p1.arrSize!=p2.arrSize) throw std::logic_error("The arrSize cannot be different.");
            SmartPointer<T> result(true, p1.arrSize);
            for(int i = 0; i < p1.arrSize; i++) {
                result.aptr[i] = p1.aptr[i] + p2.aptr[i];
            }
            return result;
        }
        //mismatch int and array
        else {
            throw std::logic_error("The operation cannot be done with an integer and an array.");
        }
    }

    friend SmartPointer<T> operator-(const SmartPointer<T> &p1, const SmartPointer<T> &p2) {
        //for int
        if(p1.iptr!=nullptr && p2.iptr!=nullptr) {
            return SmartPointer<T>(*p1.iptr - *p2.iptr);
        }
        //for array
        else if(p1.aptr != nullptr && p2.aptr != nullptr) {
            if(p1.arrSize!=p2.arrSize) throw std::logic_error("The arrSize cannot be different.");
            SmartPointer<T> result(true, p1.arrSize);
            for(int i = 0; i < p1.arrSize; i++) {
                result.aptr[i] = p1.aptr[i] - p2.aptr[i];
            }
            return result;
        }
        //mismatch int and array
        else {
            throw std::logic_error("The operation cannot be done with an integer and an array.");
        }
    }

    friend SmartPointer<T> operator*(const SmartPointer<T> &p1, const SmartPointer<T> &p2) {
        //for int
        if(p1.iptr!=nullptr && p2.iptr!=nullptr) {
            return SmartPointer<T>(*p1.iptr * *p2.iptr);
        }
        //for array
        else if(p1.aptr != nullptr && p2.aptr != nullptr) {
            if(p1.arrSize!=p2.arrSize) throw std::logic_error("The arrSize cannot be different.");
            SmartPointer<T> result(true, p1.arrSize);
            for(int i = 0; i < p1.arrSize; i++) {
                result.aptr[i] = p1.aptr[i] * p2.aptr[i];
            }
            return result;
        }
        //mismatch int & array
        else {
            throw std::logic_error("The operation cannot be done with an integer and an array.");
        }
    }

};

//Initialization for int
template <class T> SmartPointer<T>::SmartPointer() {
    iptr = new T(0);
    aptr = nullptr;
}
template <class T> SmartPointer<T>::SmartPointer(T x) {
    if (x < 0) throw std::invalid_argument("Negative number is not supported.");
    iptr = new T(x);
    aptr = nullptr;
}

//Initalization for array
template <class T> SmartPointer<T>::SmartPointer(bool forArray, int size) {
    iptr = nullptr;
    if (size < 0) throw std::invalid_argument("Negative arrSize is not supported.");
    arrSize = size;
    aptr = new T[arrSize]();
}
template <class T> SmartPointer<T>::SmartPointer(T arr[], int size) {
    iptr = nullptr;
    if (size < 0) throw std::invalid_argument("Negative arrSize is not supported.");
    arrSize = size;
    aptr = new T[arrSize];
    for(int i = 0; i < arrSize; i++) {
        aptr[i] = arr[i];
    }
}

//Destructor
template <class T> SmartPointer<T>::~SmartPointer() {
    delete iptr;
}

//Get & Set for int
template <class T> T SmartPointer<T>::getValue() {
    return *iptr;
}
template <class T> void SmartPointer<T>::setValue(T x) {
    *iptr = x;
}

//Get & Set for array
template <class T> T SmartPointer<T>::getValue(int index) {
    return aptr[index];
}
template <class T> void SmartPointer<T>::setValue(int index, T element) {
    aptr[index] = element;
}

//Help to test array operations (Print)
template <class T> void SmartPointer<T>::printArr() {
    for(int i=0; i<arrSize; i++) {cout << getValue(i) << " ";}
    cout << endl;
}


int main() {

    cout << "Tests begin!\n" << endl;

    cout << "Allocate an integer variable and will initialize it to 11:" << endl;
    SmartPointer<int> sPointer1(11);
    cout << sPointer1.getValue() << '\n' <<endl;

    cout << "Allocate an integer variable and will initialize it to -11 (Exception Handling):" << endl;
    try {
        SmartPointer<int> sPointer2(-11);
    } catch (std::exception &e) {
        cout << e.what() << '\n' << endl;
    }

    cout << "Allocate an integer variable by default:" << endl;
    SmartPointer<int> sPointer3;
    cout << sPointer3.getValue() << '\n' <<endl;

    cout << "differ the initialization of your allocated int variable to a later moment (sPointer3 -> 133 in this case):" << endl;
    sPointer3.setValue(133);
    cout << sPointer3.getValue() << '\n' << endl;

    cout << "Allocate a float number 13.31:" << endl;
    SmartPointer<float> sPointer4;
    sPointer4.setValue(13.31);
    cout << sPointer4.getValue() << '\n' <<endl;

    cout << "Allocate a float number -13.31 (Exception Handling):" << endl;
    try {
        SmartPointer<double> sPointer6(-13.31);
    } catch (std::exception &e) {
        cout << e.what() << '\n' << endl;
    }

    cout << "Allocate a float variable by default:" << endl;
    SmartPointer<float> sPointer7;
    cout << sPointer7.getValue() << '\n' <<endl;

    cout << "Test Operators:" << endl;
    SmartPointer<float> sPointer8;
    sPointer8.setValue(1.5);
    SmartPointer<float> sPointer9;
    sPointer9.setValue(2.5);
    SmartPointer<float> sPointer10 = sPointer9 + sPointer8;
    SmartPointer<float> sPointer11 = sPointer9 - sPointer8;
    SmartPointer<float> sPointer12 = sPointer9 * sPointer8;
    cout << "sPointer9 + sPointer8 = " << sPointer10.getValue() << endl;
    cout << "sPointer9 - sPointer8 = " << sPointer11.getValue() << endl;
    cout << "sPointer9 * sPointer8 = " << sPointer12.getValue() << '\n' << endl;

    cout << "Allocate size-5 int arrayA {10, 9, 8, 7, 6}:" << endl;
    int arrayA[5] = {10, 9, 8 ,7, 6};
    SmartPointer<int> sPointerA(arrayA, 5);
    cout << "arrayA: ";
    sPointerA.printArr();
    cout << endl;

    cout << "Allocate size-5 int arrayB by default:" << endl;
    SmartPointer<int> sPointerB(true, 5);
    cout << "arrayB: ";
    sPointerB.printArr();
    cout << endl;

    cout << "Set sPointerB[2] to 2:" << endl;
    sPointerB.setValue(2, 2);
    cout << "arrayB: ";
    sPointerB.printArr();
    cout << endl;

    cout << "Set sPointerB[3] to 3:" << endl;
    sPointerB.setValue(3, 3);
    cout << "arrayB: ";
    sPointerB.printArr();
    cout << endl;

    cout << "Allocate size-5 int arrayC {1, 2, 3, 4, 5} and getValue of 3rd index:" << endl;
    int arrayC[5] = {1, 2, 3 ,4, 5};
    SmartPointer<int> sPointerC(arrayC, 5);
    cout << "arrayC: ";
    sPointerC.printArr();
    cout << "3rd element of arrayC is: " << sPointerC.getValue(2) << '\n' << endl;

    cout << "Test Operators for arrays:" << endl;
    SmartPointer<int> sPointerD = sPointerA + sPointerC;
    cout << "arratA + arrayC = ";
    sPointerD.printArr();
    SmartPointer<int> sPointerE = sPointerA - sPointerC;
    cout << "arratA - arrayC = ";
    sPointerE.printArr();
    SmartPointer<int> sPointerF = sPointerA * sPointerC;
    cout << "arratA * arrayC = ";
    sPointerF.printArr();
    cout << endl;

    cout << "Test Negative arrSize (Exception Handling):" << endl;
    try {
        SmartPointer<int> sPointerG(true, -5);
    } catch (std::exception &e) {
        cout << e.what() << '\n' << endl;
    }


}