-- Sandbox Premake5 File

GameName = "IceClimbers"

workspace (GameName)
	configurations {
		"Debug",
        "Release"
    }

    platforms {
        "Win64",
        "Win32"
    }

    flags {
		--"MultiProcessorCompile"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
DependencyDir = "%{GameName}/Dependencies"
SourceDir = "%{ProjectName}/Source"

-- Dependency Directiories --
Dependencies = {}
Dependencies["Log"] = "%{DependencyDir}/spdlog"
Dependencies["SFML"] = "%{DependencyDir}/SFML"

project (GameName)
	location (GameName)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..OutputDir.."/%{prj.name}")
	objdir ("bin-int/"..OutputDir.."/%{prj.name}")

    pchheader "pch.h"
    pchsource "%{prj.name}/Source/pch.cpp"

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp"
    }

    includedirs {
        "%{prj.name}/Source",
        "%{Dependencies.Log}/include",
        "%{Dependencies.SFML}/include",
    }

    defines {
		"_CRT_SECURE_NO_WARNINGS",
        "SFML_STATIC"
    }

	filter "platforms:Win*"
		system "windows"
		systemversion "latest"

	filter "platforms:Win32"
		architecture "x32"

        libdirs {
			"%{Dependencies.SFML}/lib/Win32",
		}

		postbuildcommands {
            ("{COPY} %{prj.location}Dependencies/SFML/bin/Win32/openal32.dll %{wks.location}/bin/"..OutputDir.. "/IceClimbers")
        }


	filter "platforms:Win64"
		architecture "x64"

        libdirs {
            "%{Dependencies.SFML}/lib/Win64",
        }

        postbuildcommands {
            ("{COPY} %{prj.location}Dependencies/SFML/bin/Win64/openal32.dll %{wks.location}/bin/"..OutputDir.. "/IceClimbers")
        }

	filter "system:windows"
		systemversion "latest"

	filter "configurations:*"
		links {
	            "opengl32.lib",
	            "freetype.lib",
	            "winmm.lib",
	            "gdi32.lib",
	            "openal32.lib",
	            "flac.lib",
	            "vorbisenc.lib",
	            "vorbisfile.lib",
	            "vorbis.lib",
	            "ogg.lib"
	        }

	filter "configurations:Debug"
        defines { "DEBUG", "ENABLE_ASSERTS" }
        buildoptions "/MDd"
        runtime "Debug"
        symbols "on"

        links {
            "sfml-audio-s-d.lib",
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib"
        }

	filter "configurations:Release"
        defines "RELEASE"
        buildoptions "/MD"
        runtime "Release"
        optimize "on"

        links {
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib"
        }
