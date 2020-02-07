AM_CFLAGS = --pedantic -Wall -std=gnu99 -O0 -I libmicro/include

noinst_LIBRARIES = libmicro.a

libmicro_a_SOURCES = libmicro/proto/lap.c libmicro/can/can-tcp.c libmicro/can/can-uart.c libmicro/uart/uart-host.c libmicro/can/can-encap.c libmicro/utils/debug.c libmicro/utils/crc16.c libmicro/utils/termio.c

bin_PROGRAMS = labcontrol

labcontrol_SOURCES = main.c blutils.c can-posix.c cmds-base.c cmds-test.c cmds-flash.c cmds-borg.c cmds-mood.c cansole.c cmds-musicd.c cmds-powercommander.c cmds-treppenblink.c cmds-canir.c cmds-cantemp.c cmds-bastel.c cmds-powermeter.c cmds-gateway.c
labcontrol_LDADD = libmicro.a