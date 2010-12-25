-- LDPrototype
solution "LDPrototype"
	configurations { "Debug", "Release" }
	location "build"
 
		project "demo"
			kind "WindowedApp"
			language "C"
			files { "src/**.h", "src/**.c" }
			links { "SDL", "SDL_image", "SDL_mixer", "GLEW", "GL", "GLU" }

				-- turn on all Warnings, threat Warnings as Errors
				configuration { "linux", "gmake" }
					buildoptions { "-Wall", "-Werror" }
		
				configuration "Debug"
					defines { "DEBUG" }
					targetdir "build"
 
				configuration "Release"
         			defines { "NDEBUG" }
         			targetdir "build"
