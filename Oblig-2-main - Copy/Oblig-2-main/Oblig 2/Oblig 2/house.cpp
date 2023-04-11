#include "house.h"

house::house()
{
   //top white
//   mVertices.push_back(Vertex{0,0.5,0,0.6,0.3,0});
//   mVertices.push_back(Vertex{0.5,0.5,0,0.6,0.3,0});
//   mVertices.push_back(Vertex{0,0.5,0.5,0.6,0.3,0});
//   mVertices.push_back(Vertex{0.5,0.5,0.5,0.6,0.3,0});
//   mVertices.push_back(Vertex{0.5,0.5,0,0.6,0.3,0});
//   mVertices.push_back(Vertex{0,0.5,0.5,0.6,0.3,0});

   //front 1 green
   mVertices.push_back(Vertex{0,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0.5,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.2,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.2,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.2,0.5,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0.5,0,0.6,0.3,0});

   //front 2 green
   mVertices.push_back(Vertex{0.3,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.3,0.5,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0.5,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.3,0.5,0,0.6,0.3,0});

   //front 3 green
   mVertices.push_back(Vertex{0.2,0.25,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.2,0.5,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.3,0.25,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.3,0.5,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.3,0.25,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.2,0.5,0,0.6,0.3,0});

   //side 3 blue
   mVertices.push_back(Vertex{0,0,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0.5,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0.5,0.5,0.6,0.3,0});

   //side 2 red
   mVertices.push_back(Vertex{0.5,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0.5,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0.6,0.3,0});

   //side 4 orange
   mVertices.push_back(Vertex{0,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0.5,0.5,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0.5,0,0.6,0.3,0});
   mVertices.push_back(Vertex{0,0.5,0.5,0.6,0.3,0});

   //ceiling support
   mVertices.push_back(Vertex{0.5,0.5,0.5,0,0,0});
   mVertices.push_back(Vertex{0.6,0.5,0.5,0,0,0});
   mVertices.push_back(Vertex{0.5,0.5,-0.1,0,0,0});
   mVertices.push_back(Vertex{0.5,0.5,-0.1,0,0,0});
   mVertices.push_back(Vertex{0.6,0.5,0.5,0,0,0});
   mVertices.push_back(Vertex{0.6,0.5,-0.1,0,0,0});

   mVertices.push_back(Vertex{0,0.5,0,0,0,0});
   mVertices.push_back(Vertex{-0.1,0.5,0,0,0,0});
   mVertices.push_back(Vertex{-0.1,0.5,0.6,0,0,0});
   mVertices.push_back(Vertex{-0.1,0.5,0.6,0,0,0});
   mVertices.push_back(Vertex{0,0.5,0,0,0,0});
   mVertices.push_back(Vertex{0,0.5,0.6,0,0,0});

   mVertices.push_back(Vertex{-0.1,0.5,0.5,0,0,0});
   mVertices.push_back(Vertex{-0.1,0.5,0.6,0,0,0});
   mVertices.push_back(Vertex{0.6,0.5,0.5,0,0,0});
   mVertices.push_back(Vertex{0.6,0.5,0.5,0,0,0});
   mVertices.push_back(Vertex{0.6,0.5,0.6,0,0,0});
   mVertices.push_back(Vertex{-0.1,0.5,0.6,0,0,0});

   mVertices.push_back(Vertex{-0.1,0.5,-0.1,0,0,0});
   mVertices.push_back(Vertex{-0.1,0.5,0,0,0,0});
   mVertices.push_back(Vertex{0.5,0.5,0,0,0,0});
   mVertices.push_back(Vertex{0.5,0.5,0,0,0,0});
   mVertices.push_back(Vertex{0.5,0.5,-0.1,0,0,0});
   mVertices.push_back(Vertex{-0.1,0.5,-0.1,0,0,0});

   //ceiling
   mVertices.push_back(Vertex{0,0.5,0,1,0,0});
   mVertices.push_back(Vertex{0.5,0.5,0,1,0,0});
   mVertices.push_back(Vertex{0.25,0.75,0.25,1,0,0});

   mVertices.push_back(Vertex{0,0.5,0.5,1,0,0});
   mVertices.push_back(Vertex{0,0.5,0,1,0,0});
   mVertices.push_back(Vertex{0.25,0.75,0.25,1,0,0});

   mVertices.push_back(Vertex{0,0.5,0.5,1,0,0});
   mVertices.push_back(Vertex{0.5,0.5,0.5,1,0,0});
   mVertices.push_back(Vertex{0.25,0.75,0.25,1,0,0});

   mVertices.push_back(Vertex{0.5,0.5,0,1,0,0});
   mVertices.push_back(Vertex{0.5,0.5,0.5,1,0,0});
   mVertices.push_back(Vertex{0.25,0.75,0.25,1,0,0});

   for(int i = 0; i < mVertices.size(); i++)
   {
        mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] -0.25f;
        mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] -0.25f;

        mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * 1.5f;
        mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * 1.5f;
        mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * 1.5f;
   }

   mMatrix.setToIdentity();
}

house::~house()
{

}

void house::init(GLint matrixUniform)
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

void house::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void house::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    doorBox[0] += x;
    doorBox[1] += y;
    doorBox[2] += z;
}

void house::rotate()
{
    //mMatrix.rotate(1.f, 0.f, 2.0, 0.f);
}

bool house::collision(player* player1, float d, float e)
{
    double x;
    double z;
    x = player1->m_xyz[0];
    z = player1->m_xyz[2];

    if (x+d > -0.875 && z+e > 0.125 && x+d < -0.125 && z+e < 0.875)
    {
        return true;
    }
    else
    {
        return false;
    }
}
