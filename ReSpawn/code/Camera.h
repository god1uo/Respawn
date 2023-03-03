#pragma once

/*Rx,Ry,Rz,0     1,0,0,-Px
  Ux,Uy,Uz,0  *  0,1,0,-Py
  Dx,Dy,Dz,0     0,0,1,-Pz
  0 ,0 ,0 ,1     0,0,0,1
*/
/*glm::vec3 cameraPos = glm::vec3(0.f, 0.f, -3.f);
glm::vec3 cameraLookPoint = glm::vec3(0.0f, 0.0f, -0.0f);
glm::vec3 cameraInverseDirection = glm::normalize(cameraPos - cameraLookPoint);
glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);
glm::vec3 cameraRight = glm::cross(cameraInverseDirection, cameraUp);
glm::vec3 cameraOrthoUp = glm::cross(cameraInverseDirection, cameraRight);*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Camera
{
private:
	glm::vec3 m_Pos;
	glm::vec3 m_Up;
	glm::vec3 m_Dir;
	glm::vec3 m_Right;
	glm::mat4 m_LookAt;
	float m_Speed{};
public:

	static Camera& GetInstance() {
		static Camera __Instance{ Camera() };
		return __Instance;
	}

	void Initialization(glm::vec3 pos, glm::vec3 point, glm::vec3 up) {
		m_Pos = pos;
		m_Up = up;
		m_Dir = glm::normalize(m_Pos - point);
		m_Right = glm::normalize(glm::cross(m_Up, m_Dir));
		m_Up = glm::normalize(glm::cross(m_Dir, m_Right));
		UpdataLookAt();
	}

	void Updata(glm::vec3 up, glm::vec3 dir) {
		m_Up = up;
		m_Dir = glm::normalize(dir);
		m_Right = glm::normalize(glm::cross(m_Up, m_Dir));
		m_Up = glm::normalize(glm::cross(m_Dir, m_Right));
		UpdataLookAt();
	}

	void UpdataLookAt() {
		m_LookAt = { glm::vec4(m_Right,0),glm::vec4(m_Up,0),glm::vec4(m_Dir,0),glm::vec4(-m_Pos,1) };
	}

	void Front() {
		m_Pos -= m_Speed * m_Dir;
		UpdataLookAt();
	}
	void Back() {
		m_Pos += m_Speed * m_Dir;
		UpdataLookAt();
	}
	void Left() {
		m_Pos -= m_Speed * m_Right;
		UpdataLookAt();
	}
	void Right() {
		m_Pos += m_Speed * m_Right;
		UpdataLookAt();
	}
	void Up() {
		m_Pos += m_Speed * m_Up;
		UpdataLookAt();
	}
	void Down() {
		m_Pos -= m_Speed * m_Up;
		UpdataLookAt();
	}
	void MouseMove(const float yaw, const float pitch) {
		m_Dir.x = cos(glm::radians(pitch))*sin(glm::radians(yaw));
		m_Dir.y = sin(glm::radians(pitch));
		m_Dir.z = cos(glm::radians(pitch))*cos(glm::radians(yaw));
		Updata(m_Up, m_Dir);
	}
	glm::vec3 GetRight() const {
		return m_Right;
	}
	glm::vec3 GetDir() const {
		return m_Dir;
	}
	glm::mat4 GetLookAt() const {
		return m_LookAt;
	}
	void SetSpeed(float value) {
		m_Speed = value;
	}
private:
	Camera()
	{
		Initialization(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	}
};