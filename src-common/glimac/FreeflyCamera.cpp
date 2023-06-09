#include "FreeflyCamera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"

void FreeflyCamera::computeDirectionVectors()
{
    m_FrontVector = glm::vec3(glm::cos(m_tetha) * glm::sin(m_phi), glm::sin(m_tetha), glm::cos(m_tetha) * glm::cos(m_phi));

    m_LeftVector = glm::vec3(glm::sin(m_phi + glm::pi<float>() / 2), 0, glm::cos(m_phi + glm::pi<float>() / 2));

    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

void FreeflyCamera::moveLeft(float t)
{
    m_position += t * m_LeftVector;
}

void FreeflyCamera::moveFront(float t)
{
    m_distance += t;
}

void FreeflyCamera::rotateLeft(float degrees)
{
    m_phi += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees)
{
    m_tetha += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::follow_character(const glm::vec3 character_position)
{
    m_position = character_position - m_distance * m_FrontVector;
}

glm::mat4 FreeflyCamera::getViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_distance * m_FrontVector, m_UpVector);
}