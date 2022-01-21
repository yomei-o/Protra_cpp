# -*- coding: utf-8 -*-
"""
Setup python file for Cython.
Last update: 2018/11/18
"""

from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize

src_fls = ['PyPtsim.pyx', 'src/PyPtsim.cpp']

ext = Extension('PyPtsim', sources=src_fls)

setup(
    name='PyPtsim',
    cmdclass={'build_ext': build_ext},
   include_dirs = ['src'],
    ext_modules=cythonize([ext])
)
