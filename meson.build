# C Minilib Init
# ******************************************************************************
# *    Project
# ******************************************************************************
project('gtk_file_viewer', 'c',
         version: '0.0.1',
	 meson_version: '>=1.0.1',
	 default_options: [
            'werror=true',
            'c_std=c11',
         ],
)

# ******************************************************************************
# *    App
# ******************************************************************************
subdir('src')

gtk_dep = dependency('gtk4', version: '>=4.8.3', required: true)
gtk_x11_dep  = dependency('gtk4-x11', required: true)
fontconfig_dep = dependency('fontconfig', required: true)
x11_dep  = dependency('x11', required: true)

c_minilib_error_dep = dependency('c_minilib_error',
  fallback: ['c_minilib_error', 'c_minilib_error_dep'],
  required: true,
)

gtk_file_viewer_deps = [gtk_dep, gtk_x11_dep, x11_dep, fontconfig_dep, c_minilib_error_dep]
gtk_file_viewer_inc = include_directories('src')

gtk_file_viewer_exe = executable(
  'gtk_file_viewer',
  sources,
  include_directories: gtk_file_viewer_inc,
  dependencies: gtk_file_viewer_deps,  
)

