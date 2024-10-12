#include <iostream>

#include "content_box_renderer.h"


ContentBoxRenderer::ContentBoxRenderer(Shader& contentBoxShader, Shader& contentBoxOverflowHiddenShader)
{
    this->contentBoxShader = contentBoxShader;
    this->contentBoxOverflowHiddenShader = contentBoxOverflowHiddenShader;
    this->initRenderData();
}

ContentBoxRenderer::~ContentBoxRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void ContentBoxRenderer::SetScreenWidth(int width) {
    this->screenWidth = width;
}

void ContentBoxRenderer::SetScreenHeight(int height) {
    this->screenHeight = height;
}

void ContentBoxRenderer::DrawContentBox(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    
    // prepare transformations
    this->contentBoxShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->contentBoxShader.SetMatrix4("model", model);

    // render textured quad
    this->contentBoxShader.SetVector3f("boxColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);
}

void ContentBoxRenderer::DrawContentBox(Texture2D& texture, glm::vec2 position, bool wireframe, glm::vec2 size, float rotate, glm::vec3 color)
{
    glm::vec3 contentBoxColor = glm::vec3(1.0, 1.0, 1.0);
    contentBoxColor.x = color.x - 0.2;
    contentBoxColor.y = color.y - 0.2;
    contentBoxColor.z = color.z - 0.2;
    if (contentBoxColor.x < 0.0)
        contentBoxColor.x = 0.0;
    if (contentBoxColor.y < 0.0)
        contentBoxColor.y = 0.0;
    if (contentBoxColor.z < 0.0)
        contentBoxColor.z = 0.0;

    // prepare transformations
    this->contentBoxShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->contentBoxShader.SetMatrix4("model", model);

    // render textured quad
    this->contentBoxShader.SetVector3f("boxColor", contentBoxColor);
    //this->shader.SetVector3f("boxColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);
}

void ContentBoxRenderer::DrawContentBoxOverflowHidden(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 parentContentPosition, glm::vec2 parentContentSize, float rotate, glm::vec3 color)
{
    glm::vec3 contentBoxColor = glm::vec3(1.0, 1.0, 1.0);
    contentBoxColor.x = color.x - 0.2;
    contentBoxColor.y = color.y - 0.2;
    contentBoxColor.z = color.z - 0.2;
    if (contentBoxColor.x < 0.0)
        contentBoxColor.x = 0.0;
    if (contentBoxColor.y < 0.0)
        contentBoxColor.y = 0.0;
    if (contentBoxColor.z < 0.0)
        contentBoxColor.z = 0.0;

    // prepare transformations
    this->contentBoxOverflowHiddenShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->contentBoxOverflowHiddenShader.SetMatrix4("model", model);
    this->contentBoxOverflowHiddenShader.SetVector2f("parentContentPosition", parentContentPosition);
    this->contentBoxOverflowHiddenShader.SetVector2f("parentContentSize", parentContentSize);
    // render textured quad
    this->contentBoxOverflowHiddenShader.SetVector3f("boxColor", contentBoxColor);

    // TODO:: only works when the content box changes size. Need to find the smallest content box up the tree maybe
    // calculate per element based on parents somehow as well. the smallest one is what matters. might need to be based on pixels
    // before converting to screen coordiantes
    glm::vec2 screenSize(this->screenWidth, this->screenHeight);
    float topY = (((screenSize.y - parentContentPosition.y) / screenSize.y) * 2.0) - 1.0;
    float bottomY = (((screenSize.y - (parentContentPosition.y + parentContentSize.y)) / screenSize.y) * 2.0) - 1.0;
    float leftX = ((parentContentPosition.x / screenSize.x) * 2.0) - 1.0;
    float rightX = (((parentContentPosition.x + parentContentSize.x) / screenSize.x) * 2.0) - 1.0;
    /*
    std::cout << "topY: " << topY << std::endl;
    std::cout << "bottomY: " << bottomY << std::endl;
    std::cout << "leftX: " << leftX << std::endl;
    std::cout << "rightX: " << rightX << std::endl;

    std::cout << parentContentPosition.x << " " << parentContentPosition.y << std::endl;
    std::cout << parentContentSize.x << " " << parentContentSize.y << std::endl;
    */
    glm::vec4 boundaries(topY, bottomY, leftX, rightX);
    this->contentBoxOverflowHiddenShader.SetVector4f("boundaries", boundaries);


    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void ContentBoxRenderer::DrawContentBoxOverflowHidden(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec2 parentContentPosition, glm::vec2 parentContentSize, float overflowRadius, glm::vec4 overflowTopCorners, glm::vec4 overflowBottomCorners, glm::vec4 borders, glm::vec2 topLeft, glm::vec2 topRight, glm::vec2 bottomLeft, glm::vec2 bottomRight, float radius, glm::vec2 screenSize, bool wireframe, float rotate, glm::vec3 color)
{
    glm::vec3 contentBoxColor = glm::vec3(1.0, 1.0, 1.0);
    contentBoxColor.x = color.x - 0.2;
    contentBoxColor.y = color.y - 0.2;
    contentBoxColor.z = color.z - 0.2;
    if (contentBoxColor.x < 0.0)
        contentBoxColor.x = 0.0;
    if (contentBoxColor.y < 0.0)
        contentBoxColor.y = 0.0;
    if (contentBoxColor.z < 0.0)
        contentBoxColor.z = 0.0;

    // prepare transformations
    this->contentBoxOverflowHiddenShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->contentBoxOverflowHiddenShader.SetMatrix4("model", model);
    //this->contentBoxOverflowHiddenShader.SetVector2f("parentContentPosition", parentContentPosition);
    //this->contentBoxOverflowHiddenShader.SetVector2f("parentContentSize", parentContentSize);
    // render textured quad
    //this->contentBoxOverflowHiddenShader.SetVector3f("boxColor", contentBoxColor);
    this->contentBoxOverflowHiddenShader.SetVector3f("boxColor", glm::vec4(0.0,0.0,0.0,1.0));

    // TODO:: try to calculate these then send them to the shader to see if that helps
    /*
    glm::vec2 screenSize(this->screenWidth, this->screenHeight);
    float topY = (((screenSize.y - parentContentPosition.y) / screenSize.y) * 2.0) - 1.0;
    float bottomY = (((screenSize.y - (parentContentPosition.y + parentContentSize.y)) / screenSize.y) * 2.0) - 1.0;
    float leftX = ((parentContentPosition.x / screenSize.x) * 2.0) - 1.0;
    float rightX = (((parentContentPosition.x + parentContentSize.x) / screenSize.x) * 2.0) - 1.0;
    */
    /*
    std::cout << "topY: " << topY << std::endl;
    std::cout << "bottomY: " << bottomY << std::endl;
    std::cout << "leftX: " << leftX << std::endl;
    std::cout << "rightX: " << rightX << std::endl;

    std::cout << parentContentPosition.x << " " << parentContentPosition.y << std::endl;
    std::cout << parentContentSize.x << " " << parentContentSize.y << std::endl;
    */

    this->contentBoxOverflowHiddenShader.SetVector2f("topLeft", topLeft);
    this->contentBoxOverflowHiddenShader.SetVector2f("topRight", topRight);
    this->contentBoxOverflowHiddenShader.SetVector2f("bottomLeft", bottomLeft);
    this->contentBoxOverflowHiddenShader.SetVector2f("bottomRight", bottomRight);
    this->contentBoxOverflowHiddenShader.SetVector2f("screenSize", screenSize);
    this->contentBoxOverflowHiddenShader.SetFloat("radius", radius);
    //glm::vec4 boundaries(topY, bottomY, leftX, rightX);

    this->contentBoxOverflowHiddenShader.SetVector4f("boundaries", borders);
    this->contentBoxOverflowHiddenShader.SetVector4f("overflowTopCorners", overflowTopCorners);
    this->contentBoxOverflowHiddenShader.SetVector4f("overflowBottomCorners", overflowBottomCorners);
    this->contentBoxOverflowHiddenShader.SetFloat("overflowRadius", overflowRadius);


    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);
}

void ContentBoxRenderer::initRenderData()
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