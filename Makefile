all: build code chmod 


LEVELS = level1 level2 level3 level4 level5

build:
	@for file in $(LEVELS) ; do \
		gcc-3.4 -D_FORTIFY_SOURCE=0 -O0 -Wpadded -z execstack -o $$file $$file.c ; \
		mv $$file /home/$$file/ ; \
	done

code:
	cp level1.c /home/level1/
	cp level2.c /home/level2/
	cat level3.c | sed "s;lxcc7EQaMfIeW8Kdxz5I;xxxxxxxxxxxxxxxxxx;g" > /home/level3/level3.c
	cp level4.c /home/level4/

chmod:
	#
	chown level2:level1 /home/level1/level1
	chmod 4550 /home/level1/level1
	#
	chown level3:level2 /home/level2/level2
	chmod 4550 /home/level2/level2
	#
	chown level4:level3 /home/level3/level3
	chmod 4110 /home/level3/level3
	#
	chown level5:level4 /home/level4/level4
	chmod 4550 /home/level4/level4
	#
	chown endgame:level5 /home/level5/level5
	chmod 4110 /home/level5/level5


clean:
	rm /home/level1/level1*
	rm /home/level2/level2*
	rm /home/level3/level3*
	rm /home/level4/level4*
	rm /home/level5/level5*

.PHONY: clean
