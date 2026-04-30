AM_CPPFLAGS = -I$(top_srcdir)/include
lib_LTLIBRARIES = libsylvan.la
libsylvan_la_SOURCES = \
	snladd.c snlsub.c snlmul.c snldiv.c snlmod.c \
	skladd.c sklsub.c sklmul.c snlnml.c \
	snlmax.c snlmin.c snlabs.c snlcmp.c snlsgn.c \
	snlgcd.c snllcm.c \
	snlbop.c snland.c snlor.c  snlxor.c snlnot.c \
	snlshl.c snlshr.c snlmsb.c \
	snlpow.c \
	snadd.c snsub.c snmul.c sndiv.c snmod.c \
	skadd.c sksub.c skmul.c snnml.c \
	snmax.c snmin.c snabs.c sncmp.c snsgn.c \
	sngcd.c snlcm.c \
	snbop.c snand.c snor.c  snxor.c snnot.c \
	snshl.c snshr.c snmsb.c \
	snpow.c \
	snzadd.c snzsub.c snzmul.c snzdiv.c snzmod.c \
	skzadd.c skzmul.c \
	snzmax.c snzmin.c snzcmp.c snzsgn.c \
	snzgcd.c snzlcm.c \
	snzbop.c snzand.c snzor.c  snzxor.c snznot.c \
	snzshl.c snzshr.c snzmsb.c \
	snzpow.c \
	snqadd.c snqsub.c snqmul.c snqdiv.c snqmod.c \
	skqadd.c skqmul.c \
	snqmax.c snqmin.c snqcmp.c snqsgn.c \
	snqgcd.c snqlcm.c \
	snqbop.c snqand.c snqor.c  snqxor.c \
	snqshl.c snqshr.c snqmsb.c \
	snqpow.c \
	snuadd.c snusub.c snumul.c snudiv.c snumod.c \
	skuadd.c skumul.c \
	snumax.c snumin.c snucmp.c snusgn.c \
	snugcd.c snulcm.c \
	snubop.c snuand.c snuor.c  snuxor.c \
	snushl.c snushr.c snumsb.c \
	snupow.c \
	sntok.c \
	sna2l.c \
	sna2i.c \
	snuc2c.c \
	snl2i.c \
	snq2u.c \
	snu2uc.c \
	snqt.c snunqt.c \
	snrev.c \
	sneset.c \
	snrbts.c \
	snget.c

.PHONY: bench-local
bench-local: $(lib_LTLIBRARIES)
