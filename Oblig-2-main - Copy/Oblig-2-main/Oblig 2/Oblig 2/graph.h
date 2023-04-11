#ifndef GRAPH_H
#define GRAPH_H

#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include "vertex.h"

class GRAPH : protected QOpenGLFunctions_4_1_Core
{
private:
    std::vector<Vertex0> mVertices;
    //QOpenGLContext *mContext;

 public:
    GRAPH();
    //void setContext(QOpenGLContext *context);
    void init(GLuint mVAO, GLuint mVBO);
    void draw();
};

#endif // GRAPH_H
