#include "texturedcube.h"
#include <cstddef>

texCube::texCube()
{
    mVertices.push_back(Vertex{0,0,0,0,1});
    mVertices.push_back(Vertex{0.5,0,0,1,1});
    mVertices.push_back(Vertex{0,0,0.5,0,0});
    mVertices.push_back(Vertex{0.5,0,0.5,1,0});
    mVertices.push_back(Vertex{0.5,0,0,1,1});
    mVertices.push_back(Vertex{0,0,0.5,0,0});

    //top white
    mVertices.push_back(Vertex{0,0.5,0,0,1});
    mVertices.push_back(Vertex{0.5,0.5,0,1,1});
    mVertices.push_back(Vertex{0,0.5,0.5,0,0});
    mVertices.push_back(Vertex{0.5,0.5,0.5,1,0});
    mVertices.push_back(Vertex{0.5,0.5,0,1,1});
    mVertices.push_back(Vertex{0,0.5,0.5,0,0});

    //side 1 green
    mVertices.push_back(Vertex{0,0,0,0,1});
    mVertices.push_back(Vertex{0,0.5,0,0,0});
    mVertices.push_back(Vertex{0.5,0,0,1,1});
    mVertices.push_back(Vertex{0.5,0,0,1,1});
    mVertices.push_back(Vertex{0.5,0.5,0,1,0});
    mVertices.push_back(Vertex{0,0.5,0,0,0});

    //side 3 blue
    mVertices.push_back(Vertex{0,0,0.5,0,1});
    mVertices.push_back(Vertex{0,0.5,0.5,0,0});
    mVertices.push_back(Vertex{0.5,0,0.5,1,1});
    mVertices.push_back(Vertex{0.5,0.5,0.5,1,0});
    mVertices.push_back(Vertex{0.5,0,0.5,1,1});
    mVertices.push_back(Vertex{0,0.5,0.5,0,0});

    //side 2 red
    mVertices.push_back(Vertex{0.5,0,0,0,1});
    mVertices.push_back(Vertex{0.5,0.5,0,1,1});
    mVertices.push_back(Vertex{0.5,0.5,0.5,1,0});
    mVertices.push_back(Vertex{0.5,0,0,0,1});
    mVertices.push_back(Vertex{0.5,0,0.5,0,0});
    mVertices.push_back(Vertex{0.5,0.5,0.5,1,0});

    //side 4 orange
    mVertices.push_back(Vertex{0,0,0,0,1});
    mVertices.push_back(Vertex{0,0,0.5,1,1});
    mVertices.push_back(Vertex{0,0.5,0.5,1,0});
    mVertices.push_back(Vertex{0,0,0,0,1});
    mVertices.push_back(Vertex{0,0.5,0,0,0});
    mVertices.push_back(Vertex{0,0.5,0.5,1,0});

    for(int i = 0; i < mVertices.size(); i++)
    {
         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] -0.25f;
         mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] -0.25f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] -0.25f;

         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * 0.3f;
         mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * 0.3f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * 0.3f;
    }

    mMatrix.setToIdentity();
}

texCube::~texCube()
{

}

void texCube::init(GLint matrixUniform)
{
    texUniform = matrixUniform;

    initializeOpenGLFunctions();




    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

//    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );

//    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_st)));
    glEnableVertexAttribArray(2);

    //enable the matrixUniform
    // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );
    glBindVertexArray(0);

    texturepath = "../Oblig 2/Norg";

    QImage image;
    image.load(texturepath);
    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture->setData(image);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Nearest);

    texture->bind(0);




}

void texCube::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( texUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    //texture->bind(0);
//    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void texCube::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    tcPos[0] += x;
    tcPos[1] += y;
    tcPos[2] += z;
}

void texCube::rotate()
{
    mMatrix.rotate(1.f, 2.f, 2.0, 2.f);
}
