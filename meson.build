project('labcontrol', 'c', default_options: [
	'warning_level=1', # -Wall
	'optimization=0'
])

add_project_arguments('-Wpedantic', language: 'c')
add_project_arguments('--std=gnu99', language: 'c')


# libmicro
libmicro_inc = include_directories('libmicro/include')
libmicro_rel_src = ['proto/lap.c', 'can/can-tcp.c', 'can/can-uart.c', 'uart/uart-host.c', 'can/can-encap.c', 'utils/debug.c', 'utils/crc16.c', 'utils/termio.c']
libmicro_src = []
foreach relsrc : libmicro_rel_src
	libmicro_src += join_paths('libmicro', relsrc)
endforeach
libmicro_lib = static_library('micro', libmicro_src, include_directories: libmicro_inc)

libmicro = declare_dependency(link_with: libmicro_lib, include_directories: libmicro_inc)
# libmicro end


src = [
	'main.c', 'blutils.c', 'can-posix.c', 'cansole.c',
	'cmds-base.c', 'cmds-test.c', 'cmds-flash.c', 'cmds-borg.c', 'cmds-mood.c',
	'cmds-musicd.c', 'cmds-powercommander.c', 'cmds-treppenblink.c', 'cmds-canir.c',
	'cmds-cantemp.c', 'cmds-bastel.c', 'cmds-powermeter.c', 'cmds-gateway.c'
]

executable('labcontrol', src, dependencies: libmicro)
