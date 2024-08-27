#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <stb/stb_image.h>
#include "../base/ref.hpp"

namespace sgl
{
    class Image
    {
    public:
        enum Channels
        {
            NONE,
            GREY,
            GA,
            RGB,
            RGBA,
        };

        static Ref<Image> load_from_file(const String &path, SizeT desired_channels = 0)
        {
            Ref<Image> result = std::make_shared<Image>();
            if (!result->load(path, desired_channels))
                return nullptr;
            else
                return result;
        }

    private:
        std::vector<stbi_uc> m_data = {};
        SizeT m_width = 0;
        SizeT m_height = 0;
        Channels m_channels = NONE;

    public:
        std::vector<stbi_uc> &get_data() { return m_data; }
        const std::vector<stbi_uc> &get_data() const { return m_data; }
        SizeT get_width() const { return m_width; }
        SizeT get_height() const { return m_height; }
        Channels get_channels() const { return m_channels; }

    public:
        Bool load(const String &path, SizeT desired_channels = 0)
        {
            int width, height, channels;
            stbi_uc *data = stbi_load(path.data(), &width, &height, &channels, desired_channels);
            if (data == nullptr)
            {
                print("Failed to load image from file :\"", path, "\".");
                return false;
            }

            m_data = std::vector<stbi_uc>(data, data + width * height * channels);
            m_width = width;
            m_height = height;
            m_channels = Channels(channels);

            stbi_image_free(data);

            return true;
        }

        void clear()
        {
            m_data.clear();
            m_width = 0;
            m_height = 0;
            m_channels = NONE;
        }
    };

} // namespace sgl

#endif
