#include "texture.h"


Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);//���������������
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);//��һ������������󶨵�һ������Ŀ����
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    //glTexImage2D(GL_TEXTURE_2D,����      //��������һ��2D����
    //   0,��������������������           ����ͼ�����ϸ�̶�, Ĭ��Ϊ0���� 
    //   3,��������������������           ��ɫ�ɷ�R(��ɫ����)��G(��ɫ����)��B(��ɫ����)�����֣���Ϊ4����R(��ɫ����)��G(��ɫ����)��B(��ɫ����)��Alpha
    //   TextureImage[0]->sizeX,����      ����Ŀ��
    //   TextureImage[0]->sizeY,����      ����ĸ߶�
    //   0,��������������������           �߿��ֵ
    //  GL_RGB,������������               ����OpenGLͼ�������ɺ졢�̡�����ɫ�������
    //  GL_UNSIGNED_BYTE,��              ���ͼ����������޷����ֽ�����
    //  TextureImage[0]->data);����       ����OpenGL�������ݵ���Դ,������ָ������TextureImage[0]��¼�е�����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);//������˺���
        //���һ�������ƶ��������ͣ�һ������ΪGL_TEXTURE_2D������2D����
        //�ڶ�������ָ����Ӧ��ģʽ
        //GL_TEXTURE_WRAP_S   S�����ϵ���ͼģʽ
        //GL_TEXTURE_WRAP_T    T�����ϵ���ͼģʽ
        //GL_TEXTURE_MAG_FILTER    �Ŵ����
        //GL_TEXTURE_MIN_FILTER    ��С����
       // ����������ָ��Ӧģʽ�ķ���
        //GL_CLAMP    ����������������0.0, 1.0�ķ�Χ֮��.��������˻������.�������, ֻ�ǻ��Ե�������
        //GL_CLAMP_TO_EDGE    ������ģʽ�£��߿�ʼ�ձ����ԡ�λ�������Ե���߿��������Ե������Ԫ������������㣬����ʹ������߿��ϵ�����Ԫ������Ӳ��֧��ԭ�򣬶��������GL_CLAMP��GL_CLAMP_TO_EDGEЧ����ͬ
        //GL_CLAMP_TO_BORDER    �����������λ�ڷ�Χ[0, 1]֮�⣬��ôֻ�ñ߿�����Ԫ�����û�б߿���ʹ�ó����߿���ɫ�����볣���߿���ɫ���Ǻ�ɫ��
        //GL_LINEAR    ���Թ���, ʹ�þ��뵱ǰ��Ⱦ�������������4�����ؼ�Ȩƽ��ֵ���ٶȽ����޾��
        //GL_NEAREST    ʹ��������������ӽ���һ�����ص���ɫ��Ϊ��Ҫ���Ƶ�������ɫ���ٶȽϿ����־��
        //GL_LINEAR_MIPMAP_NEAREST    ʹ��GL_NEAREST����ӽ���ǰ����εĽ����ȵ������㼶��ͼ���в���, Ȼ����������ֵ�������Բ�ֵ

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