AM_CPPFLAGS = -I$(top_srcdir)/include
LDADD = $(top_builddir)/src/libsylvan.la $(BENCH_LIBS)

BENCH_LOGS = b001_snladd.log
EXTRA_PROGRAMS = $(BENCH_LOGS:.log=)

.PHONY: bench-local
bench-local: $(BENCH_LOGS)

b001_snladd.log: b001_snladd$(EXEEXT)
	./b001_snladd$(EXEEXT) >$@ 2>&1
	@cat $@

CLEANFILES = $(BENCH_LOGS:.log=$(EXEEXT)) $(BENCH_LOGS)
