#include "door.h"

DOOR::DOOR()
{
    //bottom brown
   mVertices.push_back(Vertex{0.15,0.375,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,0.375,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,0,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,0,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.15,0,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.15,0.375,0,0.5,0.25,0.1});

   //knob
   mVertices.push_back(Vertex{0.13,0.2,-0.01,1,1,0});
   mVertices.push_back(Vertex{0.11,0.2,-0.01,1,1,0});
   mVertices.push_back(Vertex{0.12,0.17,-0.01,1,1,0});
   mVertices.push_back(Vertex{0.13,0.185,-0.01,1,1,0});
   mVertices.push_back(Vertex{0.11,0.185,-0.01,1,1,0});
   mVertices.push_back(Vertex{0.12,0.215,-0.01,1,1,0});

   mMatrix.setToIdentity();
}

DOOR::~DOOR()
{

}

void DOOR::init(GLint matrixUniform)
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

void DOOR::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void DOOR::rotate()
{

    mMatrix.rotate(75.f, 0.f, 1.0, 0.f);
    once = true;
}

void DOOR::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    m_xyz[0] += x;
    m_xyz[1] += y;
    m_xyz[2] += z;
}

bool DOOR::collision(player* player1)
{
//    m_xyz[0] = -0.575;
//    m_xyz[2] = 0.125;
    double x;
    double z;
    x = player1->m_xyz[0];
    z = player1->m_xyz[2];

    if (x < m_xyz[0]+0.15 && z > m_xyz[2]-0.05 && x > m_xyz[0]+0.025 && z < m_xyz[2]+0.2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void DOOR::open()
{

}
