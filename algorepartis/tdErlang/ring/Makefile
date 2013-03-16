ERLC=erlc
MODULES=ring lcr peterson
BEAMS=$(addsuffix .beam,$(MODULES))

all: $(BEAMS)

lcr: $(BEAMS)
	./lcr 30000

peterson: $(BEAMS)
	./peterson 30000

%.beam: %.erl
	$(ERLC) $<

clean:
	-rm $(BEAMS)
