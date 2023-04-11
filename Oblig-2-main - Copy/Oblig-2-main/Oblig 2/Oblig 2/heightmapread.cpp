#include "heightmapread.h"
#include <cstddef>


HR::HR()
{
    texturepath = "../Oblig 2/HM2";

    QImage image;
    image.load(texturepath);

    width = image.width();
    height = image.height();

    for (float i = 0; i < width-1; i++)
    {
        for (float j = 0; j < height-1; j++)
        {
            pColor = image.pixelColor(i, j);
            pColor = pColor.convertTo(QColor::Rgb);
            pColor = qGray(pColor.rgb());
            yValue = pColor.value();
            mVertices.push_back(Vertex{i,yValue,j});

            pColor = image.pixelColor(i+1, j);
            pColor = pColor.convertTo(QColor::Rgb);
            pColor = qGray(pColor.rgb());
            yValue = pColor.value();
            mVertices.push_back(Vertex{i+1,yValue,j});

            pColor = image.pixelColor(i, j+1);
            pColor = pColor.convertTo(QColor::Rgb);
            pColor = qGray(pColor.rgb());
            yValue = pColor.value();
            mVertices.push_back(Vertex{i,yValue,j+1});

            mVertices.push_back(Vertex{i,yValue,j+1});

            pColor = image.pixelColor(i+1, j);
            pColor = pColor.convertTo(QColor::Rgb);
            pColor = qGray(pColor.rgb());
            yValue = pColor.value();
            mVertices.push_back(Vertex{i+1,yValue,j});

            pColor = image.pixelColor(i+1, j+1);
            pColor = pColor.convertTo(QColor::Rgb);
            pColor = qGray(pColor.rgb());
            yValue = pColor.value();
            mVertices.push_back(Vertex{i+1,yValue,j+1});

        }
    }

    for(int i = 0; i < mVertices.size(); i++)
    {
        mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * xzMod * genMod;
        mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * yMod * genMod;
        mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * xzMod * genMod;

        mVertices[i].m_normal[0] = 0;
        mVertices[i].m_normal[1] = 0.000001*i;
        mVertices[i].m_normal[2] = 0.01;
    }

    mMatrix.setToIdentity();


}

HR::~HR()
{

}

void HR::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

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


}

void HR::draw()
{

}

void HR::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    tcPos[0] += x;
    tcPos[1] += y;
    tcPos[2] += z;
}

void HR::rotate()
{
    mMatrix.rotate(1.f, 2.f, 2.0, 2.f);
}

void HR::write(std::string filnavn)
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
