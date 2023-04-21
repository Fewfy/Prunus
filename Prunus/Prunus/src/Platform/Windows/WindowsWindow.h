#pragma once

#include "Prunus/Window.h"
#include "Prunus/Renderer/GraphicsContext.h"
struct GLFWwindow;

namespace Prunus
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		bool IsVSync() const override;
		void SetVSync(bool enabled) override;
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void* GetNativeWindow() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string Title;
			unsigned int Height;
			unsigned int Width;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		GraphicsContext* m_Context;
	};
}