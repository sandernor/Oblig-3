#version 410 core

layout(location = 0) in vec4 positionIn;    // 1st attribute buffer = vertex positions
layout(location = 1) in vec3 normalIn;       // 2nd attribute buffer = colors

out vec3 normalOut;                             //color sent to rest of pipeline
//out vec4 worldPosition;
out vec3 lightDirection;
out vec3 viewDirection;

uniform mat4 ppmatrix;
uniform mat4 vvmatrix;
uniform mat4 mmatrix;                        //the matrix for the model

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
    gl_Position = ppmatrix * vvmatrix * mmatrix * positionIn;

    vec4 worldPosition = mmatrix * positionIn;

    normalOut = mat3(mmatrix) * normalIn;                         //passing on the vertex color
    //normalOut = normalize(normalOut);
    //normalOut = mmatrix * normalIn;

    lightDirection = lightPosition - worldPosition.xyz;
    viewDirection = cameraPosition - worldPosition.xyz;
}

//// Ambient lighting
//vec3 ambient = ambientStrength * lightColor;

//// Diffuse lighting
//vec4 norm = normalize(fs_in.normal);
//vec3 lightDir = normalize(lightPos - fs_in.fragPos);
//float diff = max(dot(norm, vec4(lightDir, 1)), 0.0);
//vec3 diffuse = diff * lightColor;

//// Specular lighting
//vec3 viewDir = normalize(viewPos - fs_in.fragPos);
//vec3 reflectDir = reflect(-lightDir, vec3(norm));
//float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//vec3 specular = specularStrength * spec * lightColor;

//// Combined - we get Phong shading
//vec3 result = (ambient + diffuse + specular) * vec3(fs_in.normal);
//fragmentColor = vec4(result, 1.0);
