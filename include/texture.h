#include <glad/glad.h>


class Texture2D
{
public:
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int ID;
    // Texture image dimensions
    unsigned int Width, Height; // Width and height of loaded image in pixels
    // Texture Format
    unsigned int Internal_Format; // Format of texture object
    unsigned int Image_Format; // Format of loaded image
    // Texture configuration
    unsigned int Wrap_S; // Wrapping mode on S axis
    unsigned int Wrap_T; // Wrapping mode on T axis
    unsigned int Filter_Min; // Filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // Filtering mode if texture pixels > screen pixels
    // Constructor (sets default texture modes)
    Texture2D();
    // Generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};
