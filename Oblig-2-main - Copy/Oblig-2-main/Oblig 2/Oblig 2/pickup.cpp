#include "pickup.h"

pickup::pickup()
{
    mVertices.push_back(Vertex{0,0,0,1,1,0});
    mVertices.push_back(Vertex{0.5,0,0,1,1,0});
    mVertices.push_back(Vertex{0,0,0.5,1,1,0});
    mVertices.push_back(Vertex{0.5,0,0.5,1,1,0});
    mVertices.push_back(Vertex{0.5,0,0,1,1,0});
    mVertices.push_back(Vertex{0,0,0.5,1,1,0});

    //top white
    mVertices.push_back(Vertex{0,0.5,0,1,1,1});
    mVertices.push_back(Vertex{0.5,0.5,0,1,1,1});
    mVertices.push_back(Vertex{0,0.5,0.5,1,1,1});
    mVertices.push_back(Vertex{0.5,0.5,0.5,1,1,1});
    mVertices.push_back(Vertex{0.5,0.5,0,1,1,1});
    mVertices.push_back(Vertex{0,0.5,0.5,1,1,1});

    //side 1 green
    mVertices.push_back(Vertex{0,0,0,0,1,0});
    mVertices.push_back(Vertex{0,0.5,0,0,1,0});
    mVertices.push_back(Vertex{0.5,0,0,0,1,0});
    mVertices.push_back(Vertex{0.5,0,0,0,1,0});
    mVertices.push_back(Vertex{0.5,0.5,0,0,1,0});
    mVertices.push_back(Vertex{0,0.5,0,0,1,0});

    //side 3 blue
    mVertices.push_back(Vertex{0,0,0.5,0,0,1});
    mVertices.push_back(Vertex{0,0.5,0.5,0,0,1});
    mVertices.push_back(Vertex{0.5,0,0.5,0,0,1});
    mVertices.push_back(Vertex{0.5,0.5,0.5,0,0,1});
    mVertices.push_back(Vertex{0.5,0,0.5,0,0,1});
    mVertices.push_back(Vertex{0,0.5,0.5,0,0,1});

    //side 2 red
    mVertices.push_back(Vertex{0.5,0,0,1,0,0});
    mVertices.push_back(Vertex{0.5,0.5,0,1,0,0});
    mVertices.push_back(Vertex{0.5,0.5,0.5,1,0,0});
    mVertices.push_back(Vertex{0.5,0,0,1,0,0});
    mVertices.push_back(Vertex{0.5,0,0.5,1,0,0});
    mVertices.push_back(Vertex{0.5,0.5,0.5,1,0,0});

    //side 4 orange
    mVertices.push_back(Vertex{0,0,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0,0.5,1,0.5,0});
    mVertices.push_back(Vertex{0,0.5,0.5,1,0.5,0});
    mVertices.push_back(Vertex{0,0,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0.5,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0.5,0.5,1,0.5,0});

    for(int i = 0; i < mVertices.size(); i++)
    {
         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] -0.25f;
         mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] -0.25f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] -0.25f;

         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * 0.1f;
         mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * 0.1f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * 0.1f;
    }

    mMatrix.setToIdentity();
}

pickup::~pickup()
{

}

void pickup::init(GLint matrixUniform)
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

void pickup::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void pickup::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    pickPos[0] += x;
    pickPos[1] += y;
    pickPos[2] += z;
}

void pickup::rotate()
{
    mMatrix.rotate(1.f, 2.f, 2.0, 2.f);
}
