#include <iostream> 
#include "box_renderer.h"

BoxRenderer::BoxRenderer(Shader& boxShader, Shader& boxOverflowHiddenShader)
{
	this->boxShader = boxShader;
    this->boxOverflowHiddenShader = boxOverflowHiddenShader;
	this->initRenderData();
}

BoxRenderer::~BoxRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void BoxRenderer::SetScreenWidth(int width) {
    this->screenWidth = width;
}

void BoxRenderer::SetScreenHeight(int height) {
    this->screenHeight = height;
}

void BoxRenderer::DrawBox(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight, float radius, glm::vec2 screenSize, float rotate, glm::vec3 color)
{
    // prepare transformations
    this->boxShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->boxShader.SetMatrix4("model", model);

    // render textured quad
    this->boxShader.SetVector3f("boxColor", color);
    this->boxShader.SetVector2f("topLeft", topLeft);
    this->boxShader.SetVector2f("topRight", topRight);
    this->boxShader.SetVector2f("bottomLeft", bottomLeft);
    this->boxShader.SetVector2f("bottomRight", bottomRight);
    this->boxShader.SetVector2f("screenSize", screenSize);
    this->boxShader.SetFloat("radius", radius);


    
    
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void BoxRenderer::DrawBoxOverflowHidden(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 parentContentPosition, glm::vec2 parentContentSize, float overflowRadius, glm::vec4 overflowTopCorners, glm::vec4 overflowBottomCorners, glm::vec4 borders, glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight, float radius, glm::vec2 screenSize, float rotate, glm::vec3 color)
{
    // prepare transformations
    this->boxOverflowHiddenShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->boxOverflowHiddenShader.SetMatrix4("model", model);
    //this->boxOverflowHiddenShader.SetVector2f("parentContentPosition", parentContentPosition);
    //this->boxOverflowHiddenShader.SetVector2f("parentContentSize", parentContentSize);
    // render textured quad
    this->boxOverflowHiddenShader.SetVector3f("boxColor", color);



    this->boxOverflowHiddenShader.SetVector2f("topLeft", topLeft);
    this->boxOverflowHiddenShader.SetVector2f("topRight", topRight);
    this->boxOverflowHiddenShader.SetVector2f("bottomLeft", bottomLeft);
    this->boxOverflowHiddenShader.SetVector2f("bottomRight", bottomRight);
    this->boxOverflowHiddenShader.SetVector2f("screenSize", screenSize);
    this->boxOverflowHiddenShader.SetFloat("radius", radius);

    

    //std::cout << radius << std::endl;
    //std::cout << "bottomRight" << std::endl;
    //std::cout << bottomRight.x << " " << bottomRight.y << std::endl;

    // TODO:: try to calculate these then send them to the shader to see if that helps
    /*
    glm::vec2 screenSize(this->screenWidth, this->screenHeight);
    float topY = (((screenSize.y - parentContentPosition.y) / screenSize.y) * 2.0) - 1.0;
    float bottomY = (((screenSize.y - (parentContentPosition.y + parentContentSize.y)) / screenSize.y) * 2.0) - 1.0;
    float leftX = ((parentContentPosition.x / screenSize.x) * 2.0) - 1.0;
    float rightX = (((parentContentPosition.x + parentContentSize.x) / screenSize.x) * 2.0) - 1.0;
    */
    /*
    std::cout << "topY: " << borders.x << std::endl;
    std::cout << "bottomY: " << borders.y << std::endl;
    std::cout << "leftX: " << borders.z << std::endl;
    std::cout << "rightX: " << borders.w << std::endl;

    std::cout << parentContentPosition.x << " " << parentContentPosition.y << std::endl;
    std::cout << parentContentSize.x << " " << parentContentSize.y << std::endl;
    */
    //glm::vec4 boundaries(topY, bottomY, leftX, rightX);
    this->boxOverflowHiddenShader.SetVector4f("boundaries", borders);
    this->boxOverflowHiddenShader.SetVector4f("overflowTopCorners", overflowTopCorners);
    this->boxOverflowHiddenShader.SetVector4f("overflowBottomCorners", overflowBottomCorners);
    this->boxOverflowHiddenShader.SetFloat("overflowRadius", overflowRadius);



    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}



void BoxRenderer::initRenderData()
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