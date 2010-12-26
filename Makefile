LEVELS := level1 level2 level3 level4 level5

all: $(LEVELS)

level1: level1.c
	gcc-3.4 -g -O0 -z execstack -o $@ $^
	chown level1:level2 $@ 
	chmod 2550 $@

level2: level2.c
#	gcc-3.4 -g -O0 -D_FORTIFY_SOURCE=0 -z execstack -o $@ $^
	tcc -o $@ $^
	chown level2:level3 $@ 
	chmod 2550 $@

level3: level3.c
	tcc -o $@ $^
	chown level3:level4 $@
	chmod 2110 $@

level4: level4.c
	gcc-3.4 -g -O0 -o $@ $^
	chown level4:level5 $@
	chmod 2550 $@

level5: level5.c
	gcc-3.4 -g -O0 -o $@ $^
	chown level5:endgame $@ 
	chmod 2110 $@

install:
	@for file in $(LEVELS) ; do \
		cp -a $$file /home/$$file/$$file ; \
	done
	install level1.c /home/level1/
	install  level2.c /home/level2/
	cat level3.c | sed "s;lxcc7EQaMfIeW8Kdxz5I;xxxxxxxxxxxxxxxxxx;g" > /home/level3/level3.c
	install  level4.c /home/level4/

clean:
	@for file in $(LEVELS) ; do \
		rm /home/$$file/$$file* ; \
		rm $$file ; \
	done

.PHONY: install clean
