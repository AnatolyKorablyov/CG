#pragma once
#include "DispatchEvent.h"
#include <glm/vec3.hpp>

typedef glm::vec3 CColor;

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

    // CAbstractWindow interface
protected:
    void OnUpdateWindow(float deltaSeconds) override;
	void DrawWings();
	void DrawFoots();
	void DrawBody();
	void DrawFace();
	void OnDrawWindow(const glm::ivec2 &size) override;

private:
    void SetupView(const glm::ivec2 &size);


    float m_time = 0.f;
};
