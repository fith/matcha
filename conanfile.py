from conans import ConanFile, CMake

class MatchaConan(ConanFile):
    name = "Matcha"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    requires = ["sdl2/2.0.12@bincrafters/stable",
                "sdl2_mixer/2.0.4@bincrafters/stable"] # comma-separated list of requirements
    generators = "cmake", "gcc", "txt"
    build_policy = "missing"

    def configure(self):
        self.options["sdl2_mixer"].shared = False
        self.options["sdl2_mixer"].cmd = False
        self.options["sdl2_mixer"].wav = False
        self.options["sdl2_mixer"].flac = False
        self.options["sdl2_mixer"].mpg123 = False
        self.options["sdl2_mixer"].mad = False
        self.options["sdl2_mixer"].ogg = True
        self.options["sdl2_mixer"].opus = False
        self.options["sdl2_mixer"].mikmod = False
        self.options["sdl2_mixer"].modplug = False
        self.options["sdl2_mixer"].fluidsynth = False
        self.options["sdl2_mixer"].nativemidi = False

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin