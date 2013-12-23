from distutils.core import setup, Extension

setup(
	ext_modules = [
		Extension('_fgg', ['fgg.i', '../../fgg.cpp'],
			library_dirs=[],
			libraries=[],
			extra_compile_args=[],
			extra_link_args=[])
	]
)
