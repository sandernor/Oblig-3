#include "tetra2.h"
TETRA::TETRA()
{
    mVertices.push_back(Vertex{0.1,0,0.25,0,0,0});
    mVertices.push_back(Vertex{0.1,0,-0.25,0,0,0});
    mVertices.push_back(Vertex{0,1,0,0,0,0});

    mVertices.push_back(Vertex{-0.1,0,0.25,0,0,0});
    mVertices.push_back(Vertex{-0.1,0,-0.25,0,0,0});
    mVertices.push_back(Vertex{0,1,0,0,0,0});

    mVertices.push_back(Vertex{-0.1,0,0.25,0,0,0});
    mVertices.push_back(Vertex{0.1,0,0.25,0,0,0});
    mVertices.push_back(Vertex{0,1,0,0,0,0});

    mVertices.push_back(Vertex{-0.1,0,-0.25,0,0,0});
    mVertices.push_back(Vertex{0.1,0,-0.25,0,0,0});
    mVertices.push_back(Vertex{0,1,0,0,0,0});

    for(int i = 0; i < mVertices.size(); i++)
    {
         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * 0.1f;
         mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * 0.1f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * 0.1f;
    }
   mMatrix.setToIdentity();
}

TETRA::~TETRA()
{

}

void TETRA::init(GLint matrixUniform)
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

void TETRA::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void TETRA::rotate()
{
    mMatrix.rotate(90.f, 0.f, 1.0, 0.f);
}

void TETRA::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    mPosition = QVector3D{mPosition.x()-LastPos.x(), 0, mPosition.z()/10-LastPos.z()};
    done = true;
}

void TETRA::move(float dt, double a, double b, double c, double d)
{
    if (mPosition.x() > 0.6)
        back = true;
    else if (mPosition.x() < 0.05)
        back = false;

    if (back == true)
        dt *= -1;

    float posN = xFunction(mPosition.x()*10 + dt, a, b, c, d);


    QVector3D ds{mPosition.x() + dt, 0, posN};
    //QVector3D ds = mVelocity*dt;

    mMatrix.translate(mPosition.x() - ds.x(), 0, (mPosition.z() - ds.z())*0.05);

    mPosition = ds;		// hvis mPosisjon er Vector3d
    //mPosition = mPosition + ds;
    //mPosition.translate(ds.x(), ds.y(), ds.z());	// hvis mPosisjon er Matrix4x4
    //qDebug() << mPosition;
}

double TETRA::xFunction(double x, double a, double b, double c, double d) const
{
    return a * x * x * x + b * x * x + c * x + d;
}

void TETRA::move(player* player1)
{
    if (done2 == false)
    {
        LastPos = QVector3D{mPosition.x(), mPosition.y(), mPosition.z()/10};
        done2 = true;
    }


    QVector3D goal{(mPosition.x() - player1->m_xyz[0])* 0.01f, 0, (mPosition.z()/10 - player1->m_xyz[2])* 0.01f};
    mPosition = mPosition+goal;
    qDebug() << goal;

    mMatrix.translate(goal.x(), 0, goal.z());

    done = false;

}
