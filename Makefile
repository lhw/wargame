LEVELS := level1 level2 level3 level4 level5

all: $(LEVELS)

level1: level1.c
	gcc-3.4 -g -O0 -z execstack -o $@ $^
	chown root:level2 $@ 
	chmod 2555 $@

level2: level2.c
	tcc -o $@ $^
	chown root:level3 $@ 
	chmod 2555 $@

level3: level3.c
	tcc -o $@ $^
	chown root:level4 $@
	chmod 2111 $@

level4: level4.c
	gcc-3.4 -g -O0 -o $@ $^
	chown root:level5 $@
	chmod 2555 $@

level5: level5.c
	gcc-3.4 -g -O0 -o $@ $^
	chown root:endgame $@ 
	chmod 2111 $@

install:
	@for file in $(LEVELS) ; do \
		cp -a $$file /srv/$$file/$$file ; \
	done
	cp -a level1.c /srv/level1/
	cp -a  level2.c /srv/level2/
	cat level3.c | sed "s;lxcc7EQaMfIeW8Kdxz5I;xxxxxxxxxxxxxxxxxx;g" > /srv/level3/level3.c
	cp -a  level4.c /srv/level4/

clean:
	@for file in $(LEVELS) ; do \
		rm /srv/$$file/$$file* ; \
		rm $$file ; \
	done

.PHONY: cp -a clean
