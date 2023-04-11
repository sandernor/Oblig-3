#include "cube3.h"

player::player()
{
    //bottom brown
   mVertices.push_back(Vertex{0,0,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,0,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,0,0.5,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,0,0.5,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,0,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,0,0.5,0.5,0.25,0.1});

   // head top brown
   mVertices.push_back(Vertex{0,1,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,1,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,1,0.5,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,1,0.5,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,1,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,1,0.5,0.5,0.25,0.1});

   //back blue
   mVertices.push_back(Vertex{0,0,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0.5,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0.5,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0.5,0,0,0.2,0.8});

   //front blue
   mVertices.push_back(Vertex{0,0,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0.5,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0.5,0.5,0,0.2,0.8});

   //side left blue
   mVertices.push_back(Vertex{0.5,0,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0.5,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0,0.2,0.8});

   //side right blue
   mVertices.push_back(Vertex{0,0,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0.5,0.5,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0.5,0,0,0.2,0.8});
   mVertices.push_back(Vertex{0,0.5,0.5,0,0.2,0.8});

   //side 2.1 head back brown
   mVertices.push_back(Vertex{0,0.5,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,1,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,0.5,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,0.5,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,1,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,1,0,0.5,0.25,0.1});

   //side 2.3 face brown
   mVertices.push_back(Vertex{0,0.5,0.5,0.5,0.5,0});
   mVertices.push_back(Vertex{0,1,0.5,0.5,0.5,0});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0.5,0.5,0});
   mVertices.push_back(Vertex{0.5,1,0.5,0.5,0.5,0});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0.5,0.5,0});
   mVertices.push_back(Vertex{0,1,0.5,0.5,0.5,0});

   //side 2.2 head left brown
   mVertices.push_back(Vertex{0.5,0.5,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,1,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,1,0.5,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,0.5,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,0.5,0.5,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0.5,1,0.5,0.5,0.25,0.1});

   //side 2.4 head right brown
   mVertices.push_back(Vertex{0,0.5,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,0.5,0.5,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,1,0.5,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,0.5,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,1,0,0.5,0.25,0.1});
   mVertices.push_back(Vertex{0,1,0.5,0.5,0.25,0.1});

   //point
   mVertices.push_back(Vertex{0.25,0,0.25,0,0,0});

   for(int i = 0; i < mVertices.size(); i++)
   {
        mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] -0.25f;
        mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] -0.25f;

        mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * 0.1f;
        mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * 0.1f;
        mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * 0.1f;
   }

    camCirk.push_back(Vertex{0,0,-1.2f,0,0,0});
    camCirk.push_back(Vertex{0.8f,0,-0.8f,0,0,0});
    camCirk.push_back(Vertex{1.2f,0,0,0,0,0});
    camCirk.push_back(Vertex{0.8f,0,0.8f,0,0,0});
    camCirk.push_back(Vertex{0,0,1.2f,0,0,0});
    camCirk.push_back(Vertex{-0.8f,0,0.8f,0,0,0});
    camCirk.push_back(Vertex{-1.2f,0,0,0,0,0});
    camCirk.push_back(Vertex{-0.8f,0,-0.8f,0,0,0});

   mMatrix.setToIdentity();



   m_xyz[0] = 0;
   m_xyz[1] = 0;
   m_xyz[2] = 0;
}

player::~player()
{

}

void player::init(GLint matrixUniform)
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

void player::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void player::drawBoat()
{
    mVertices.push_back(Vertex{0,0,0,1,0.5,0});
    mVertices.push_back(Vertex{1,0,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0,1,1,0.5,0});
    mVertices.push_back(Vertex{1,0,1,1,0.5,0});
    mVertices.push_back(Vertex{1,0,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0,1,1,0.5,0});

    //side 1 green
    mVertices.push_back(Vertex{0,0.5,0,1,0.5,0});
    mVertices.push_back(Vertex{1,0.5,0,1,0.5,0});
    mVertices.push_back(Vertex{1,0,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0.5,0,1,0.5,0});
    mVertices.push_back(Vertex{1,0,0,1,0.5,0});

    //side 3 blue
    mVertices.push_back(Vertex{0,0.5,1,1,0.5,0});
    mVertices.push_back(Vertex{1,0.5,1,1,0.5,0});
    mVertices.push_back(Vertex{1,0,1,1,0.5,0});
    mVertices.push_back(Vertex{0,0,1,1,0.5,0});
    mVertices.push_back(Vertex{0,0.5,1,1,0.5,0});
    mVertices.push_back(Vertex{1,0,1,1,0.5,0});

    //side 2 red
    mVertices.push_back(Vertex{0,0,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0,1,1,0.5,0});
    mVertices.push_back(Vertex{0,0.5,1,1,0.5,0});
    mVertices.push_back(Vertex{0,0.5,1,1,0.5,0});
    mVertices.push_back(Vertex{0,0.5,0,1,0.5,0});
    mVertices.push_back(Vertex{0,0,0,1,0.5,0});

    //side 4 orange
    mVertices.push_back(Vertex{1,0,0,1,0.5,0});
    mVertices.push_back(Vertex{1,0,1,1,0.5,0});
    mVertices.push_back(Vertex{1,0.5,1,1,0.5,0});
    mVertices.push_back(Vertex{1,0.5,1,1,0.5,0});
    mVertices.push_back(Vertex{1,0.5,0,1,0.5,0});
    mVertices.push_back(Vertex{1,0,0,1,0.5,0});
    mMatrix.setToIdentity();

    for(int i = 61; i < mVertices.size(); i++)
    {
         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] -0.5f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] -0.5f;

         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * 0.1f;
         mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * 0.1f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * 0.1f;
    }
}

void player::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    m_xyz[0] += x;
    m_xyz[1] += y;
    m_xyz[2] += z;
}

void player::rotate()
{
    //mMatrix.rotate(1.f, 0.f, 2.0, 0.f);
}

void player::rotate2()
{
    //mMatrix.rotate(1.f, 0.f, -2.0, 0.f);
}


