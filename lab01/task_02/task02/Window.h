#pragma once
#include "DispatchEvent.h"

struct CColor
{
	float R;
	float G;
	float B;
};

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
