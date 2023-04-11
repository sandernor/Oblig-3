#include "fx.h"

fx::fx()
{
    float xmin=-1.0f, xmax=1.0f, h=0.1f;
    for (auto x=xmin; x<xmax; x+=h)
    {
    float y = pow(cos(x),2);
    mVertices.push_back(Vertex{x,y,0,x,y,0.5});
    }
   mMatrix.setToIdentity();


}

fx::~fx()
{

}

void fx::init(GLint matrixUniform)
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

void fx::draw()
{
//   glBindVertexArray( mVAO );
//   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    //   glDrawArrays(GL_LINES, 0, mVertices.size());
}

void fx::rotate()
{
    //mMatrix.rotate(10.f, 0.f, 1.0f, 0.f);
}
void fx::write(std::string filnavn)
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

float fx::numInt()
{
    float h = 0.02;
    float dx = h;
    float dy = h;
    float area = dx * dy;
    float cumSum = 0.f;
    for (float x = 0.f+h; x < 1.f; x+=h)
    {
        for (float y = 0.f+h; y < 1.f-x; y+=h)
        {
            cumSum+=area*(1.f-x-y);
        }
    }

    return cumSum;
}
