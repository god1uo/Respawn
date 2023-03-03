#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>; // ����glad����ȡ���еı���OpenGLͷ�ļ�

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // ����ID
    unsigned int ID;

    // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath);
    // ʹ��/�������
    void Bind();
    void UnBind();
    // uniform���ߺ���
};

#endif