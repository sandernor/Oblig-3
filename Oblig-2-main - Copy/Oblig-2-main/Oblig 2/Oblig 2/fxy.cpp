#include "fxy.h"

fxy::fxy()
{
    int i = 1;
    float xmin=-3.0f, xmax=3.0f, ymin=-3.0f, ymax=3.0f, h=0.06f;
    for (auto x=xmin; x<xmax; x+=h)
    for (auto z=ymin; z<ymax; z+=h)
    {
    float y = sin(M_PI*x)*sin(M_PI*z);
    mVertices.push_back(Vertex{x,y,z,0.4f+(x*z/4),0.75f+(y/4),0.4f+(y/4), i});
    y = sin(M_PI*(x+h))*sin(M_PI*z);
    mVertices.push_back(Vertex{x+h,y,z,0.4f+(x*z/4),0.75f+(y/4),0.4f+(y/4), i+1});
    y = sin(M_PI*x)*sin(M_PI*(z+h));
    mVertices.push_back(Vertex{x,y,z+h,0.4f+(x*z/4),0.75f+(y/4),0.4f+(y/4), i+2});
    mVertices.push_back(Vertex{x,y,z+h,0.4f+(x*z/4),0.75f+(y/4),0.4f+(y/4), i+3});
    y = sin(M_PI*(x+h))*sin(M_PI*z);
    mVertices.push_back(Vertex{x+h,y,z,0.4f+(x*z/4),0.75f+(y/4),(y/4), i+4});
    y = sin(M_PI*(x+h))*sin(M_PI*(z+h));
    mVertices.push_back(Vertex{x+h,y,z+h,0.4f+(x*z/4),0.75f+(y/4),0.4f+(y/4), i+5});
    i += 6;
    }

    for (int i = 0; i < mVertices.size(); i++)
    {
        if (mVertices[i].m_xyz[0] > -1 && mVertices[i].m_xyz[2] >-1 && mVertices[i].m_xyz[0] < 1 && mVertices[i].m_xyz[2] < 1)
        {
            mVertices[i].m_xyz[1] = 0;
            mVertices[i].m_normal[1] = 0.75f;
        }
        if (mVertices[i].m_xyz[1] > 0.5f)
        {
            mVertices[i].m_normal[0] = 1;
            mVertices[i].m_normal[1] = 1;
            mVertices[i].m_normal[2] = 1;
        }
    }
   mMatrix.setToIdentity();


}

fxy::~fxy()
{

}

void fxy::init(GLint matrixUniform)
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

//   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
//   glEnableVertexAttribArray(2);

   //enable the matrixUniform
   // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

   glBindVertexArray(0);
}

void fxy::draw()
{
//   glBindVertexArray( mVAO );
//   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    //   glDrawArrays(GL_LINES, 0, mVertices.size());
}

void fxy::rotate()
{
    //mMatrix.rotate(10.f, 0.f, 1.0f, 0.f);
}
void fxy::write(std::string filnavn)
{
    std::ofstream outf{ filnavn };
        if (!outf)
        {
            std::cerr << "Warning: " << filnavn << " could not be written to!\n";
        }

        outf << mVertices.size() << '\n';
        foreach (auto Vertex, mVertices) {
            outf << Vertex <<'\n';
        }

        outf.close();
        mVertices.clear();
}

void fxy::collision(player* player1, BOAT* boat)
{
    double x;
    double z;
    double y = 0;
    double j;
    x = player1->m_xyz[0];
    z = player1->m_xyz[2];
    j = player1->m_xyz[1];

    if (x > -1 && z > -1 && x < 1 && z < 1)
    {
        player1->move(0,y-j,0);
        //boat->move(0, -1, 0);
    }
    else
    {
        y = sin(M_PI*x)*sin(M_PI*z);
        if (player1->boat == false)
            player1->move(0,y-j,0);
        else
        {
            if (y < -0.1)
                return;
            else
            {
                player1->move(0,y-j,0);
                //boat->move(0, -1, 0);
            }
        }
    }

}
