#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

namespace sgl
{
    class NonCopyable
    {
    public:
        NonCopyable() = default;
        NonCopyable(const NonCopyable &) = delete;
        NonCopyable &operator=(const NonCopyable &) = delete;
    };

} // namespace sgl

#endif
