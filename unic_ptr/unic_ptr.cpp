

#include <iostream>
#include <memory>

template <typename T, typename Deletor = std::default_delete<T>>
class unique_ptr {

public:
    unique_ptr()
        : pointer(nullptr) {}

    unique_ptr(T* ptr)
        : pointer(ptr) {}

    unique_ptr(T valu) {
        pointer = new T(valu);
    }

    unique_ptr(T* ptr, Deletor delet) : pointer{ ptr }, delet{ delet } {}


    unique_ptr(unique_ptr const& other) = delete;
    unique_ptr operator=(unique_ptr const& other) = delete;

    unique_ptr operator=(unique_ptr&& other) noexcept {
        pointer(std::move(other.pointer));
        other.pointer = nullptr;
    }
    unique_ptr (unique_ptr&& other) noexcept
        : pointer(std::move(other.pointer)) {
        other.pointer = nullptr;
    }

    ~unique_ptr() {
        if (pointer != nullptr)
            delet(pointer);
    }
    T* release() { 
        T* tmp = std::move(pointer);
        pointer = nullptr;
        return tmp;
    }
    void reset(T* ptr) {
        T* tp_ptr = std::move(pointer);
         pointer = ptr;
        if (tp_ptr != nullptr) {
            delet(tp_ptr);
        }
    }

    T* get() const { 
        return pointer; 
    }
    explicit operator bool() const { 
        return (get() != nullptr); 
    }
    T* operator->() const { 
        return  pointer;
    }
    T& operator*() const { 
        return *pointer;
    }
    T& operator[](size_t pos) const { 
        return (get()[pos]); 
    }
protected:
    T* pointer{};
    Deletor delet;
};

template <typename T, typename Deletor> class unique_ptr< T[], Deletor > {
public:
    unique_ptr() {
        pointer(nullptr);
    }
    unique_ptr(T* ptr)
        : pointer(ptr) {}

    unique_ptr(T valu) {
        pointer = new T(valu);
    }
     unique_ptr(T *ptr, Deletor delet) : pointer{ptr}, delet{delet} {}

     unique_ptr operator=(unique_ptr&& other) noexcept {
         pointer(std::move(other.pointer));
         other.pointer = nullptr;
     }
     unique_ptr(unique_ptr&& other) noexcept
         : pointer(std::move(other.pointer)) {
         other.pointer = nullptr;
     }

     ~unique_ptr() {
         if (pointer != nullptr)
             delet(pointer);
     }

private:
    T* pointer{};
    Deletor delet;
};
int main()
{
    
    unique_ptr<int[]> ptr{ new int[100] };
   

}

