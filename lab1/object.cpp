#include "object.h"
#include <sstream>

Object::Object():
    verticesBuffer(QOpenGLBuffer::VertexBuffer),
    uvBuffer(QOpenGLBuffer::VertexBuffer),
    normalsBuffer(QOpenGLBuffer::VertexBuffer),
    indicesBuffer(QOpenGLBuffer::IndexBuffer),
    scale(1,1,1),
    selected(false),
    color(1, 1, 1)
{
}

Object::~Object()
{

}

void Object::paintObject(Camera *camera)
{
    program.bind();

    verticesBuffer.bind();
    program.setAttributeBuffer("coord", GL_FLOAT, 0, 3);

    if (uvSize > 0)
    {
        uvBuffer.bind();
        program.setAttributeBuffer("texCoordIn", GL_FLOAT, 0, 2);
    }

    normalsBuffer.bind();
    program.setAttributeBuffer("normal", GL_FLOAT, 0, 3);

    texture->bind(0);
    program.setUniformValue("tex", 0);

    program.setUniformValue("modelMatrix", modelMatrix());
    program.setUniformValue("cameraMatrix", camera->getCameraMatrix());
    program.setUniformValue("selected", selected);
    program.setUniformValue("color", color);

    indicesBuffer.bind();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}

void Object::initObject(std::string objectFileName)
{
    fileName = objectFileName;

    //buffers
    float* verticesPtr;
    float* uvPtr;
    uint* indicesPtr;
    float* normalsPtr;

    std::string filePathString = "../lab1/textures/" + fileName + ".obj";
    loadModel(filePathString, verticesPtr, uvPtr, normalsPtr, indicesPtr, verticesSize, uvSize, normalsSize, indicesSize);

    verticesBuffer.create();
    verticesBuffer.bind();
    verticesBuffer.allocate(verticesPtr, verticesSize * sizeof(float));

    if (uvSize > 0)
    {
        uvBuffer.create();
        uvBuffer.bind();
        uvBuffer.allocate(uvPtr, uvSize * sizeof(float));
    }

    indicesBuffer.create();
    indicesBuffer.bind();
    indicesBuffer.allocate(indicesPtr, indicesSize * sizeof(uint));

    normalsBuffer.create();
    normalsBuffer.bind();
    normalsBuffer.allocate(normalsPtr, normalsSize * sizeof(float));

    //ShadersProgram
    if (program.create())
    {
        program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../lab1/object.vert");
        program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../lab1/object.frag");
    }

    program.link();

    if (uvSize > 0)
    {
        filePathString = "../lab1/textures/" + fileName + ".png";
        texture = new QOpenGLTexture(QImage(filePathString.c_str()));
        program.enableAttributeArray("texCoordIn");
        texture->generateMipMaps();
    }

    program.enableAttributeArray("coord");
    program.enableAttributeArray("normal");

    //ShadersProgram
    if (programNumbers.create())
    {
        programNumbers.addShaderFromSourceFile(QOpenGLShader::Vertex, "../lab1/objectNumber.vert");
        programNumbers.addShaderFromSourceFile(QOpenGLShader::Fragment, "../lab1/objectNumber.frag");
    }

    programNumbers.link();
    programNumbers.enableAttributeArray("coord");
}

void Object::paintNumber(Camera* camera, int number)
{
    programNumbers.bind();

    verticesBuffer.bind();
    programNumbers.setAttributeBuffer("coord", GL_FLOAT, 0, 3);

    programNumbers.setUniformValue("modelMatrix", modelMatrix());
    programNumbers.setUniformValue("cameraMatrix", camera->getCameraMatrix());
    programNumbers.setUniformValue("number", (number + 1)/255.0f);

    indicesBuffer.bind();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
}

void Object::setSelected(bool value)
{
    selected = value;
}

bool Object::getSelected() const
{
    return selected;
}

QVector3D Object::getPosition() const
{
    return position;
}

void Object::setPosition(const QVector3D &value)
{
    position = value;
}

QVector3D Object::getRotation() const
{
    return rotation;
}

void Object::setRotation(const QVector3D &value)
{
    rotation = value;
}

QVector3D Object::getScale() const
{
    return scale;
}

void Object::setScale(const QVector3D &value)
{
    scale = value;
}

QVector3D Object::getColor() const
{
    return color;
}

void Object::setColor(const QVector3D &value)
{
    color = value;
}

std::string Object::getFileName() const
{
    return fileName;
}

QMatrix4x4 Object::modelMatrix() const
{
    QMatrix4x4 result;

    result.translate(position);

    result.scale(scale);

    result.rotate(rotation.x(), 1, 0, 0);
    result.rotate(rotation.y(), 0, 1, 0);
    result.rotate(rotation.z(), 0, 0, 1);

    return result;
}

void Object::loadModel(const std::string& filename, float* &vertices, float* &uv, float* &normals, uint* &indices, uint &verticesSize, uint &uvSize, uint &normalsSize, uint &indicesSize)
{
    std::ifstream f(filename);
    std::vector<uint> vertexIndices;
    std::vector<uint> uvIndices;
    std::vector<uint> normalIndices;
    std::vector<float> tempVertices;
    std::vector<float> tempUv;
    std::vector<float> tempNormals;
    while (true)
    {
        std::string line;
        std::getline(f, line, '\n');
        if (f.eof())
            break;
        else
        {
            if (line.substr(0, 2) == "v ")
            {
                float vertexX, vertexY, vertexZ;
                std::stringstream s;
                s << line.substr(2);
                s >> vertexX >> vertexY >> vertexZ;
                tempVertices.push_back(vertexX);
                tempVertices.push_back(vertexY);
                tempVertices.push_back(vertexZ);
            }
            else if (line.substr(0, 3) == "vt ")
            {
                float uvX, uvY;
                std::stringstream s;
                s << line.substr(3);
                s >> uvX >> uvY;
                tempUv.push_back(uvX);
                tempUv.push_back(uvY);
            }
            else if (line.substr(0, 3) == "vn ")
            {
                float nX = 0, nY = 0, nZ = 0;
                std::stringstream s;
                s << line.substr(3);
                s >> nX >> nY >> nZ;
                tempNormals.push_back(nX);
                tempNormals.push_back(nY);
                tempNormals.push_back(nZ);
            }
            else if (line.substr(0, 2) == "f ")
            {
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3]; // normals are for the next time
                std::stringstream s;
                char c;
                s << line.substr(2);
                for (int i = 0; i < 3; i++)
                    s >> vertexIndex[i] >> c >> uvIndex[i] >> c >> normalIndex[i];
                //fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                //there is a -1 because C++ indexing starts at 0 and OBJ indexing starts at 1
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);

                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);

                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }
    }

    verticesSize = vertexIndices.size() * 3;
    vertices = new float[verticesSize];

    uvSize = uvIndices.size() * 2;
    uv = new float[uvSize];

    indicesSize = vertexIndices.size();
    indices = new uint[indicesSize];

    normalsSize = normalIndices.size() * 3;
    normals = new float[normalsSize];

    for(uint i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i] - 1;
        float x = tempVertices[(vertexIndex) * 3];
        float y = tempVertices[(vertexIndex) * 3 + 1];
        float z = tempVertices[(vertexIndex) * 3 + 2];

        vertices[i * 3] = x;
        vertices[i * 3 + 1] = y;
        vertices[i * 3 + 2] = z;

        uint uvIndex = uvIndices[i] - 1;
        x = tempUv[(uvIndex) * 2];
        y = tempUv[(uvIndex) * 2 + 1];
        uv[i * 2] = x;
        uv[i * 2 + 1] = y;

        uint normalIndex = normalIndices[i] - 1;
        x = tempNormals[(normalIndex) * 3];
        y = tempNormals[(normalIndex) * 3 + 1];
        z = tempNormals[(normalIndex) * 3 + 2];
        normals[i * 3] = x;
        normals[i * 3 + 1] = y;
        normals[i * 3 + 2] = z;

        indices[i] = i;
    }
}
