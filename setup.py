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
        command.build_package_protos('./dellve_benchend/dellve_proto/')

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
        # appdirs==1.4.0
        # dellve==0.0.1
        # enum34==1.1.6
        # futures==3.0.5
        # gevent==1.2.1
        # greenlet==0.4.12
        # grpc==0.3.post19
        # grpcio==1.1.0
        # grpcio-tools==1.1.0
        # msgpack-python==0.4.8
        # packaging==16.8
        # protobuf==3.2.0
        # py==1.4.32
        # pybind11==2.0.1
        # pyparsing==2.1.10
        # pytest==3.0.6
        # six==1.10.0
        'grpcio', 
        'grpcio-tools>=1.1',
        'pybind11>=1.7', 
        'pytest>=3.0'],
      cmdclass = {
        # 'build_ext': BuildExt, 
        # 'test': PyTestCommand
        'build_proto_modules': BuildProtoModules},
      packages=[
        # 'dellve',
        'dellve_benchend'],
      tests_require=['pytest'],
      zip_safe=False)