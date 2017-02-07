#! /usr/bin/env python

from setuptools import setup
from setuptools import Extension
from setuptools.command.build_ext import build_ext
from setuptools.command.test import test as TestCommand
import distutils.command.build
import distutils.dir_util
import distutils.spawn
import os
import os.path
import setuptools
import setuptools.command.install
import sys

__version__ = "0.0.1"

class get_pybind_include(object):
    """Helper class to determine the pybind11 include path
    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)

ext_modules = [
    Extension(
        'dellve',
        ['dellve/src/DELLvePy.cpp'],
        include_dirs=[
            "dellve/include",
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True)
        ],
        language='c++',
        extra_compile_args=['-std=c++11'],
    ),
]

# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14] compiler flag.
    The c++14 is prefered over c++11 (when it is available).
    """
    if has_flag(compiler, '-std=c++14'):
        return '-std=c++14'
    elif has_flag(compiler, '-std=c++11'):
        return '-std=c++11'
    else:
        raise RuntimeError('Unsupported compiler -- at least C++11 support '
                           'is needed!')

class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }

    if sys.platform == 'darwin':
        c_opts['unix'] += ['-stdlib=libc++', '-mmacosx-version-min=10.7']

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        if ct == 'unix':
            opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
            opts.append(cpp_flag(self.compiler))
            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
        for ext in self.extensions:
            ext.extra_compile_args = opts
        build_ext.build_extensions(self)

class PyTestCommand(TestCommand):
    def initialize_options(self):
        TestCommand.initialize_options(self)
        self.pytest_args = []

    def run_tests(self):
        # Check for CMake is available
        if distutils.spawn.find_executable('cmake') is None:
            print "CMake is required for CMake installation"
            print "Please install Cmake version >= 3.5 and try again"
            sys.exit(-1)

        # Create build dir
        save_dir = os.getcwd()
        build_dir = os.path.join(os.path.split(__file__)[0], 'build')
        distutils.dir_util.mkpath(build_dir)
        os.chdir(build_dir)

        try: # Build & Test C/C++
            distutils.spawn.spawn(['cmake','../'])
            distutils.spawn.spawn(['make'])
            distutils.spawn.spawn(['make','test'])
        except distutils.spawn.DistutilsExecError:
            sys.exit(-1)

        os.chdir(save_dir) # return to original directory

        # Run PyTest
        import shlex
        import pytest
        errno = pytest.main(["dellve/test/python"])
        sys.exit(errno)

setup(name='dellve',
      version=__version__,
      author='Konstantyn Komarov',
      author_email='komarov.konstant@utexas.edu',
      description='DELLvePy - Python wrapper for DELLveBench HPC benchmark plugin-suite',
      license='MIT',
      long_description=open('README.md').read(),
      ext_modules=ext_modules,
      platforms = ['GNU/Linux','Mac OS-X','Unix'],
      install_requires=['pybind11>=1.7', 'pytest>=3.0'],
      cmdclass = {'build_ext': BuildExt, 'test': PyTestCommand},
      packages=['dellve'],
      tests_require=['pytest'],
      zip_safe=False)