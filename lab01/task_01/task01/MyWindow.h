#pragma once
#include "AbstractWindow.h"
class CMyWindow :
	public CAbstractWindow
{
public:
	CMyWindow();
	~CMyWindow();
protected:
	virtual void OnUpdateWindow(float deltaSeconds) override;
	virtual void OnDrawWindow(const glm::ivec2 & size) override;
	void OnWindowEvent(const SDL_Event &event) override;

private:
	void SetupView(const glm::ivec2 &size);

	float m_time = 0.0f;
};

