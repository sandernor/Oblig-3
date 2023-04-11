#version 410 core

layout(location = 0) in vec4 positionIn;    // 1st attribute buffer = vertex positions
//layout(location = 1) in vec2 texCoordIn;       // 2nd attribute buffer = colors
layout(location = 2) in vec2 textureCoordIn;
out vec2 texCoordOut;                             //color sent to rest of pipeline
uniform mat4 pmatrix;
uniform mat4 vmatrix;
uniform mat4 matrix;                        //the matrix for the model

void main()
{
    gl_Position = pmatrix * vmatrix * matrix * positionIn;
    texCoordOut = textureCoordIn;
}
