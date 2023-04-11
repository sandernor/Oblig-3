#include "oarpu.h"

Opickup::Opickup()
{
    mVertices.push_back(Vertex{0.4,1,0,1,0.5,0});
    mVertices.push_back(Vertex{0.5,0.9,0,1,0.5,0});
    mVertices.push_back(Vertex{-0.1,0.4,0,1,0.5,0});

    mVertices.push_back(Vertex{-0.4,1,0,1,0.5,0});
    mVertices.push_back(Vertex{-0.5,0.9,0,1,0.5,0});
    mVertices.push_back(Vertex{0.1,0.4,0,1,0.5,0});

    //top white
    mVertices.push_back(Vertex{-0.44,0,0,1,0.5,0});
    mVertices.push_back(Vertex{-0.46,0.03,0,1,0.5,0});
    mVertices.push_back(Vertex{0.1,0.6,0,1,0.5,0});

    mVertices.push_back(Vertex{0.44,0,0,1,0.5,0});
    mVertices.push_back(Vertex{0.46,0,0,1,0.5,0});
    mVertices.push_back(Vertex{-0.1,0.6,0,1,0.5,0});

    for(int i = 0; i < mVertices.size(); i++)
    {
         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * 0.2f;
         mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * 0.2f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * 0.2f;
    }

    mMatrix.setToIdentity();
}

Opickup::~Opickup()
{

}

void Opickup::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    initializeOpenGLFunctions();

    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    //enable the matrixUniform
    // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

    glBindVertexArray(0);
}

void Opickup::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void Opickup::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    pickPos[0] += x;
    pickPos[1] += y;
    pickPos[2] += z;
}

void Opickup::rotate()
{
    mMatrix.rotate(2.f, 0.f, 1.0, 0.f);
}
