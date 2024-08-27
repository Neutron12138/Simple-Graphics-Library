#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include "texture.hpp"
#include "../system/image.hpp"

namespace sgl
{
    class Texture2D : public Texture
    {
    public:
        static void unbind()
        {
            Texture::unbind(TEXTURE_2D);
        }

        static Ref<Texture2D> load_from_file(const String &path, Wrap wrap = REPEAT, Filter filter = LINEAR)
        {
            Ref<Image> image = Image::load_from_file(path);
            if (image == nullptr)
                return nullptr;

            Ref<Texture2D> result = std::make_shared<Texture2D>();
            result->bind();
            result->set_data(*image);
            result->set_wrap(wrap);
            result->set_filter(filter);
            result->unbind();
            return result;
        }

    public:
        Texture2D() : Texture(TEXTURE_2D) {}

    public:
        void set_data(GLint level, Format internalformat, GLsizei width, GLsizei height,
                      Format format, DataType type, const void *pixels)
        {
            glTexImage2D(TEXTURE_2D, level, internalformat, width, height, 0, format, type, pixels);
        }

        void set_data(GLint level, Format internalformat, const Image &image)
        {
            set_data(level, internalformat, image.get_width(), image.get_height(),
                     internalformat, UNSIGNED_BYTE, image.get_data().data());
        }

        void set_data(const Image &image)
        {
            Format format;
            switch (image.get_channels())
            {
            case Image::GREY:
                format = RED;
                break;

            case Image::GA:
                format = RG;
                break;

            case Image::RGB:
                format = RGB;
                break;

            case Image::RGBA:
                format = RGBA;
                break;
            }

            set_data(0, format, image);
        }

        void generate_mipmap()
        {
            glGenerateMipmap(get_type());
        }

        void set_wrap(Wrap wrap)
        {
            glTexParameteri(TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
            glTexParameteri(TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        }

        void set_filter(Filter filter)
        {
            glTexParameteri(TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);

            if (filter == NEAREST || filter == LINEAR)
                glTexParameteri(TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
            else
                switch (filter)
                {
                case LINEAR_MIPMAP_LINEAR:
                case LINEAR_MIPMAP_NEAREST:
                    glTexParameteri(TEXTURE_2D, GL_TEXTURE_MAG_FILTER, LINEAR);
                    break;

                case NEAREST_MIPMAP_NEAREST:
                case NEAREST_MIPMAP_LINEAR:
                    glTexParameteri(TEXTURE_2D, GL_TEXTURE_MAG_FILTER, NEAREST);
                    break;
                }
        }
    };

} // namespace sgl

#endif
