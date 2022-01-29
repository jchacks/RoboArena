from distutils.command.build_ext import build_ext
from os import path
from setuptools import setup, Extension
from Cython.Build import cythonize

this_directory = path.abspath(path.dirname(__file__))
with open(path.join(this_directory, "README.md"), encoding="utf-8") as f:
    long_description = f.read()


robo_arena = Extension(
    "RoboArena.core.core",
    sources=["RoboArena/core/core.pyx"],
    libraries=["RoboArena"],
    library_dirs=["lib"],
    include_dirs=[
        "../RoboArena/src/",
        "../RoboArena/vendor/spdlog/include",
        "../RoboArena/vendor/glm",
    ],
    language="c++",
    extra_compile_args=['-std=c++17', '-v'],
)

setup(
    name="RoboArena",
    version="1.0",
    description="Robocode python clone",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/jchacks/RoboArena",
    author="jchacks",
    # license='MIT',
    ext_modules=cythonize(
        [robo_arena],
        language_level="3",
        annotate=True,
    ),
    packages=['RoboArena'],
    include_package_data=True,
    zip_safe=False,
)
