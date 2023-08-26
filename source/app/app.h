#pragma once

#include <memory>

namespace SCOP
{
	struct AppConstants
	{
		static constexpr auto openGLMajorVersion = 3;
		static constexpr auto openGLMinorVersion = 3;
	};

	class Application
	{
		public:
			[[nodiscard]] static std::unique_ptr<Application>& initApplication(int argc, char **argv);
			void launchGameLoop();
		private:
			Application(int argc, char **argv);
			static std::unique_ptr<Application> m_application;
	};
}
