AM_CPPFLAGS = -I$(top_srcdir)/include
lib_LTLIBRARIES = libsylvan.la
libsylvan_la_SOURCES = \
	snladd.c snlsub.c snlmul.c snldiv.c snlmod.c \
	snlgcd.c snllcm.c snlmax.c snlmin.c \
	skladd.c sklsub.c sklmul.c skldiv.c \
	snlpow.c \
	snadd.c snsub.c snmul.c sndiv.c snmod.c \
	sngcd.c snlcm.c snmax.c snmin.c \
	skadd.c sksub.c skmul.c skdiv.c \
	snpow.c \
	snzadd.c snzsub.c snzmul.c snzdiv.c snzmod.c \
	snzgcd.c snzlcm.c snzmax.c snzmin.c \
	skzadd.c skzmul.c skzdiv.c \
	snzpow.c \
	snuladd.c snulsub.c snulmul.c snuldiv.c snulmod.c \
	snulgcd.c snullcm.c snulmax.c snulmin.c \
	skuladd.c skulmul.c skuldiv.c \
	snulpow.c \
	snuadd.c snusub.c snumul.c snudiv.c snumod.c \
	snugcd.c snulcm.c snumax.c snumin.c \
	skuadd.c skumul.c skudiv.c \
	snupow.c \
	sntok.c \
	sna2l.c \
	sna2i.c \
	snuc2c.c \
	snl2i.c \
	snul2u.c \
	snu2uc.c \
	snqt.c snunqt.c \
	snrev.c \
	snget.c \
	sneset.c

.PHONY: bench-local
bench-local: $(lib_LTLIBRARIES)
