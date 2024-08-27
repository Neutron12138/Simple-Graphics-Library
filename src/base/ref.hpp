#ifndef REF_HPP
#define REF_HPP

#include <memory>
#include "../base/type.hpp"
#include "../system/string.hpp"

namespace sgl
{
    template <typename T>
    class Ref : public std::shared_ptr<T>
    {
    public:
        using std::shared_ptr<T>::operator=;

        Ref() : std::shared_ptr<T>() {}
        Ref(std::nullptr_t) : std::shared_ptr<T>(nullptr) {}
        template <typename P>
        Ref(P *ptr) : std::shared_ptr<T>(ptr) {}
        Ref(const std::shared_ptr<T> &from) : std::shared_ptr<T>(from) {}
        Ref(const Ref<T> &from) : std::shared_ptr<T>(from) {}

    public:
        T &operator*() const
        {
            if (is_null())
                throw to_string("Unable to resolve reference null pointer.");

            return std::shared_ptr<T>::operator*();
        }

        T *operator->() const
        {
            if (is_null())
                throw to_string("Unable to resolve reference null pointer.");

            return std::shared_ptr<T>::operator->();
        }

    public:
        Bool is_null() const
        {
            return std::shared_ptr<T>::get() == nullptr;
        }
    };

    template <typename T>
    class WeakRef : public std::weak_ptr<T>
    {
    public:
        using std::weak_ptr<T>::weak_ptr;
        using std::weak_ptr<T>::operator=;
    };

} // namespace sgl

#endif
