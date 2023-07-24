#include "texture.h"


Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);//产生的是纹理对象
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);//将一个命名的纹理绑定到一个纹理目标上
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    //glTexImage2D(GL_TEXTURE_2D,　　      //此纹理是一个2D纹理
    //   0,　　　　　　　　　　           代表图像的详细程度, 默认为0即可 
    //   3,　　　　　　　　　　           颜色成分R(红色分量)、G(绿色分量)、B(蓝色分量)三部分，若为4则是R(红色分量)、G(绿色分量)、B(蓝色分量)、Alpha
    //   TextureImage[0]->sizeX,　　      纹理的宽度
    //   TextureImage[0]->sizeY,　　      纹理的高度
    //   0,　　　　　　　　　　           边框的值
    //  GL_RGB,　　　　　　               告诉OpenGL图像数据由红、绿、蓝三色数据组成
    //  GL_UNSIGNED_BYTE,　              组成图像的数据是无符号字节类型
    //  TextureImage[0]->data);　　       告诉OpenGL纹理数据的来源,此例中指向存放在TextureImage[0]记录中的数据
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);//纹理过滤函数
        //其第一个参数制定纹理类型，一般设置为GL_TEXTURE_2D即操作2D纹理
        //第二个参数指定响应的模式
        //GL_TEXTURE_WRAP_S   S方向上的贴图模式
        //GL_TEXTURE_WRAP_T    T方向上的贴图模式
        //GL_TEXTURE_MAG_FILTER    放大过滤
        //GL_TEXTURE_MIN_FILTER    缩小过滤
       // 第三个参数指对应模式的方法
        //GL_CLAMP    将纹理坐标限制在0.0, 1.0的范围之内.如果超出了会如何呢.不会错误, 只是会边缘拉伸填充
        //GL_CLAMP_TO_EDGE    在这种模式下，边框始终被忽略。位于纹理边缘或者靠近纹理边缘的纹理单元将用于纹理计算，但不使用纹理边框上的纹理单元，由于硬件支持原因，多数情况下GL_CLAMP与GL_CLAMP_TO_EDGE效果相同
        //GL_CLAMP_TO_BORDER    如果纹理坐标位于范围[0, 1]之外，那么只用边框纹理单元（如果没有边框，则使用常量边框颜色，我想常量边框颜色就是黑色）
        //GL_LINEAR    线性过滤, 使用距离当前渲染像素中心最近的4个纹素加权平均值，速度较慢无锯齿
        //GL_NEAREST    使用纹理中坐标最接近的一个像素的颜色作为需要绘制的像素颜色，速度较快会出现锯齿
        //GL_LINEAR_MIPMAP_NEAREST    使用GL_NEAREST对最接近当前多边形的解析度的两个层级贴图进行采样, 然后用这两个值进行线性插值

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}