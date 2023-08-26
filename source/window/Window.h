#pragma once

#include <cstddef>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace SCOP
{
	class Window
	{
		public:
			Window(std::size_t t_width, std::size_t t_height);
			~Window();
			static void resize(GLFWwindow* t_window, int t_width, int t_height);
			void checkKeysInputs();
			void update();
			[[nodiscard]] std::size_t getWidth(void) const;
			[[nodiscard]] std::size_t getHeight(void) const;
			[[nodiscard]] bool isClosed() const;

		private:
			GLFWwindow* m_window {nullptr};
			const std::string m_title = "scop";
			size_t m_width{0};
			size_t m_height{0};
	};
};
