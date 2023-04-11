#version 410 core

in vec3 normalOut;              //color received from the pipeline (and vertex shader)
in vec3 lightDirection;
in vec3 viewDirection;
//in vec4 worldPosition;

out vec4 fragmentColor;     //color sent to fragment on screen

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;

//uniform vec3 lightPosition;
//uniform vec3 cameraPosition;
//uniform  sampler2D textureSampler;

void main()
{
    //fragmentColor = normalOut;   //color given to current fragment (pixel)
    //vec4 worldPosition = matrix * positionIn;

    //vec3 lightDirection = lightPosition - worldPosition.xyz;
    //vec3 viewDirection = cameraPosition - worldPosition.xyz;

    vec3 ambient = materialAmbient;
    vec3 diffuse = materialDiffuse * max(dot(normalize(normalOut), normalize(lightDirection)), 0.0);
    vec3 halfway = normalize(lightDirection + viewDirection);
    vec3 specular = materialSpecular * pow(max(dot(normalize(normalOut), halfway), 0.0), 64.0);
    //vec3 specular = materialSpecular * pow(max(dot(normalize(normalOut), lightDirection), 0.0), 64.0);
    //fragmentColor = vec4(1 + 0 + 0, 1.0);
    vec3 result = (ambient + diffuse + specular) * normalOut;
    fragmentColor = vec4(result, 1.0);
}

