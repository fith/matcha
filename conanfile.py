from conans import ConanFile, CMake

class MatchaConan(ConanFile):
    name = "Matcha"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    requires = ["zlib/1.2.11",
                "bzip2/1.0.8",
                # "libpng/1.6.37@bincrafters/stable",
                "sdl2/2.0.12@bincrafters/stable",
                # "sdl2_image/2.0.5@bincrafters/stable",
                "sdl2_mixer/2.0.4@bincrafters/stable"] # comma-separated list of requirements
    generators = "cmake", "gcc", "txt"
    build_policy = "missing"

    def configure(self):
        # self.options["sdl2_image"].bmp = False
        # self.options["sdl2_image"].gif = False
        # self.options["sdl2_image"].lbm = False
        # self.options["sdl2_image"].pcx = False
        # self.options["sdl2_image"].pnm = False
        # self.options["sdl2_image"].svg = False
        # self.options["sdl2_image"].tga = False
        # self.options["sdl2_image"].xcf = False
        # self.options["sdl2_image"].xpm = False
        # self.options["sdl2_image"].xv = False
        # self.options["sdl2_image"].jpg = False
        # self.options["sdl2_image"].tif = False
        # self.options["sdl2_image"].png = True
        # self.options["sdl2_image"].webp = False
        # self.options["sdl2_image"].imageio = False

        self.options["sdl2_mixer"].shared = False
        self.options["sdl2_mixer"].fPIC = False
        self.options["sdl2_mixer"].cmd = False
        self.options["sdl2_mixer"].wav = True
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