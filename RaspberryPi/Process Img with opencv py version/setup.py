#
#  Robot.h
#
#  Created by Wang PG on 14-8-11.
#  Copyright (c) 2014 Wang PG. All rights reserved.
#

""" 
setup.py file for Robot example 
"""  
  
from distutils.core import setup, Extension  
  
  
example_module = Extension('_Robot',  
                           sources=['Robot_wrap.cxx', 'Robot.cpp'],  
                           )  
  
setup (name = 'Robot',  
       version = '0.1',  
       author      = "Wang PG",  
       description = """Processing Image with python""",  
       ext_modules = [example_module],  
       py_modules = ["Robot"],  
       ) 
