#include <type_traits>
#include <memory>

template<typename T, typename...Args>
inline typename std::enable_if<!std::is_array<T>::value,
        std::unique_ptr<T>>::type
make_unique(Args &&... args) {
    return std::unique_ptr<T>(std::forward<T>((args)...));
}
s