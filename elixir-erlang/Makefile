### ERLANG MAKEFILE ###
ERLC     = erlc
ERL      = erl -boot start_clean
ESRCS    = $(wildcard *.erl)
EBEAMS   = $(ESRCS:.erl=.beam)
EFLAGS   = -Ddebug -W1

.PHONY:
all: clean compile

compile: ${EBEAMS} subdirs

subdirs:
	@echo "cd sub dirs & make all"

%.beam: %.erl
	${ERLC} ${EFLAGS} $<

run:
	${ERL} -pa '/root' -s study cost milk

clean:
	-rm -rf ${EBEAMS} erl_crash.dump 2> /dev/null
	@echo "cd sub dirs & make clean"
