//
//  main.cpp
//  OpenGLTest
//
//  Created by 闫振 on 2018/2/9.
//  Copyright © 2018年 TeeMo. All rights reserved.
//

#include <stdio.h>

#include "GLTools.h"
#include <glut/glut.h>




#include "GLShaderManager.h"
#include "GLTools.h"
#include <GLUT/GLUT.h>
//freeglut Windows

GLShaderManager glshaderManager;
GLBatch triangleBatch;

//边长长度
GLfloat blockSize = 0.1f;

//正方形的4点的坐标
GLfloat vVerts[] ={
    -blockSize,-blockSize,0.0f,
    blockSize,-blockSize,0.0f,
    blockSize,blockSize,0.0f,
    -blockSize,blockSize,0.0f
};


//当窗口大小改变时，接收新的宽度和高度
void changeSize(int w,int h)
{
    glViewport(0, 0, w, h);
}


void RenderScence()
{
    
    //1.
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    //2.设置
    GLfloat vRed[] = {1.0,0.0,0.0,1.0};
    
    glshaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    
    triangleBatch.Draw();
    
    glutSwapBuffers();
    
    
}

void setupRC()
{
    
    //1.
    glClearColor(0.0, 0.0, 1.0, 1);
    
    glshaderManager.InitializeStockShaders();
    
    GLfloat vVert[] = {
        
        -0.5f,0.0f,0.0f,
        0.5f,0.0f,0.0f,
        
        0.0f,-0.5f,0.0f,
        0.0f,0.5f,0.0f,
        
    };
    
    triangleBatch.Begin(GL_TRIANGLE_FAN, 4);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
    
    
}

void specialKeys(int key,int x,int y)
{
    
    GLfloat stepSize = 0.025f;
    
    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[10];
    
    
    printf("v[0] = %f\n",blockX);
    printf("v[10] = %f\n",blockY);
    
    if (key == GLUT_KEY_UP) {
        
        blockY += stepSize;
    }
    
    if (key == GLUT_KEY_DOWN) {
        blockY -= stepSize;
    }
    
    if (key == GLUT_KEY_LEFT) {
        
        blockX -= stepSize;
        
    }
    
    if (key == GLUT_KEY_RIGHT) {
        blockX += stepSize;
    }
    
    //右边
    if (blockX > (1.0 - blockSize *2)) {
        blockX = 1.0f - blockSize * 2;
    }
    
    //左边
    if (blockX < -1.0) {
        
        blockX = -1.0f;
    }
    
    //上面
    if (blockY > 1.0) {
        blockY = 1.0;
    }
    
    //下面
    if (blockY < -1.0 + blockSize * 2) {
        
        blockY = -1.0  + blockSize * 2;
    }
    
    
    
    
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;
    
    printf("(%f,%f)\n",vVerts[0],vVerts[1]);
    
    
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;
    printf("(%f,%f)\n",vVerts[3],vVerts[4]);
    
    
    
    vVerts[6] = blockX + blockSize * 2;
    vVerts[7] = blockY;
    printf("(%f,%f)\n",vVerts[6],vVerts[7]);
    
    vVerts[9] = blockX;
    vVerts[10] = blockY;
    
    triangleBatch.CopyVertexData3f(vVerts);
    glutPostRedisplay();
    
}


int main(int argc,char *argv[] )
{
    
    gltSetWorkingDirectory(argv[0]);
    
    //1.初始化glut库
    glutInit(&argc, argv);
    
    
    /*
     GLUT_RGBA:RGBA颜色值模式
     GLUT_DOUBLE:双缓存窗口
     GLUT_DEPTH：
     GLUT_STENCIL：
     */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    
    //glut窗口的大小、标题
    glutInitWindowSize(800, 600);
    glutCreateWindow("CC_Triangle");
    
    //注册回调
    glutReshapeFunc(changeSize);
    glutDisplayFunc(RenderScence);
    glutSpecialFunc(specialKeys);
    
    
    //GLEW
    GLenum status = glewInit();
    if (status != GLEW_OK) {
        printf("GLEW ERROR:%s\n",glewGetErrorString(status));
    }
    
    //设置我需要渲染
    setupRC();
    
    glutMainLoop();
    
    
    return 0;
}

