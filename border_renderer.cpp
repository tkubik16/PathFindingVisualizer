#include <iostream> 
#include "border_renderer.h"

BorderRenderer::BorderRenderer(Shader& borderShader, Shader& borderOverflowHiddenShader)
{
    this->borderShader = borderShader;
    this->borderOverflowHiddenShader = borderOverflowHiddenShader;
    this->initRenderData();
}

BorderRenderer::~BorderRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void BorderRenderer::SetScreenWidth(int width) {
    this->screenWidth = width;
}

void BorderRenderer::SetScreenHeight(int height) {
    this->screenHeight = height;
}

void BorderRenderer::DrawBox(Texture2D& texture, glm::vec2 borderPosition, glm::vec2 borderSize, glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight, float radius, glm::vec2 screenSize, float rotate, glm::vec3 color)
{
    glm::vec3 borderColor = glm::vec3(1.0, 1.0, 1.0);
    borderColor.x = color.x - 0.2;
    borderColor.y = color.y - 0.2;
    borderColor.z = color.z - 0.2;
    if (borderColor.x < 0.0)
        borderColor.x = 0.0;
    if (borderColor.y < 0.0)
        borderColor.y = 0.0;
    if (borderColor.z < 0.0)
        borderColor.z = 0.0;

    // prepare transformations
    this->borderShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(borderPosition, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * borderSize.x, 0.5f * borderSize.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * borderSize.x, -0.5f * borderSize.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(borderSize, 1.0f)); // last scale

    this->borderShader.SetMatrix4("model", model);

    glm::vec4 black(0.0, 0.0, 0.0, 1.0);

    // render textured quad
    this->borderShader.SetVector3f("boxColor", borderColor);
    this->borderShader.SetVector2f("topLeft", topLeft);
    this->borderShader.SetVector2f("topRight", topRight);
    this->borderShader.SetVector2f("bottomLeft", bottomLeft);
    this->borderShader.SetVector2f("bottomRight", bottomRight);
    this->borderShader.SetVector2f("screenSize", screenSize);
    this->borderShader.SetFloat("radius", radius);




    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void BorderRenderer::DrawBoxOverflowHidden(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 parentContentPosition, glm::vec2 parentContentSize, glm::vec4 borders, glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight, float radius, glm::vec2 screenSize, float rotate, glm::vec3 color)
{
    glm::vec3 borderColor = glm::vec3(1.0, 1.0, 1.0);
    borderColor.x = color.x - 0.2;
    borderColor.y = color.y - 0.2;
    borderColor.z = color.z - 0.2;
    if (borderColor.x < 0.0)
        borderColor.x = 0.0;
    if (borderColor.y < 0.0)
        borderColor.y = 0.0;
    if (borderColor.z < 0.0)
        borderColor.z = 0.0;
    // prepare transformations
    this->borderOverflowHiddenShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->borderOverflowHiddenShader.SetMatrix4("model", model);
    //this->boxOverflowHiddenShader.SetVector2f("parentContentPosition", parentContentPosition);
    //this->boxOverflowHiddenShader.SetVector2f("parentContentSize", parentContentSize);
    // render textured quad
    this->borderOverflowHiddenShader.SetVector3f("borderColor", borderColor);



    this->borderOverflowHiddenShader.SetVector2f("topLeft", topLeft);
    this->borderOverflowHiddenShader.SetVector2f("topRight", topRight);
    this->borderOverflowHiddenShader.SetVector2f("bottomLeft", bottomLeft);
    this->borderOverflowHiddenShader.SetVector2f("bottomRight", bottomRight);
    this->borderOverflowHiddenShader.SetVector2f("screenSize", screenSize);
    this->borderOverflowHiddenShader.SetFloat("radius", radius);



    this->borderOverflowHiddenShader.SetVector4f("borders", borders);


    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}



void BorderRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}