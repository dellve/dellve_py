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

class BuildProtoModules(setuptools.Command):
    """Command to generate project *_pb2.py modules from proto files."""
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        from grpc.tools import command
        command.build_package_protos('./dellve_system_manager/dellve_proto/')

setup(name='dellve',
      version=__version__,
      author='Konstantyn Komarov',
      author_email='komarov.konstant@utexas.edu',
      description='DELLvePy - Python wrapper for DELLveBench HPC benchmark plugin-suite',
      license='MIT',
      long_description=open('README.md').read(),
      # ext_modules=ext_modules,
      platforms = ['GNU/Linux','Mac OS-X','Unix'],
      install_requires=[
        'grpcio>=1.1', 
        'grpcio-tools>=1.1',
        'pybind11>=1.7', 
        'pytest>=3.0'],
      cmdclass = {
        # 'build_ext': BuildExt, 
        # 'test': PyTestCommand
        'build_proto_modules': BuildProtoModules},
      packages=[
        # 'dellve',
        'dellve_system_manager'],
      tests_require=['pytest'],
      zip_safe=False)