#pragma once

#include <memory>
#include "ObjParser.h"

namespace SCOP
{
	struct AppConstants
	{
		static constexpr auto openGLMajorVersion = 4;
		static constexpr auto openGLMinorVersion = 6;
	};

	class Application
	{
		public:
			[[nodiscard]] static std::unique_ptr<Application>& initApplication(int argc, char **argv);
			void launchGameLoop();
		private:
			Application(int argc, char **argv);
			static std::unique_ptr<Application> m_application;
            ObjParser m_3dParser;
	};
}
