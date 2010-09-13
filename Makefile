all: level1 level2 level4 level5

clean:
	rm /home/level1/level1*
	rm /home/level2/level2*
	rm /home/level4/level4*

level1: level1.c
	gcc-3.4 -D_FORTIFY_SOURCE=0 -Wpadded -z execstack -o level1 level1.c
	mv level1 /home/level1/
	cp level1.c /home/level1/
	chown level2:level1 /home/level1/level1
	chmod 4550 /home/level1/level1
	chmod 644 /home/level1/level1.c

level2: level2.c
	gcc-3.4 -D_FORTIFY_SOURCE=0 -Wpadded -z execstack -o level2 level2.c
	mv level2 /home/level2/
	cp level2.c /home/level2/
	chown level3:level2 /home/level2/level2
	chmod 4550 /home/level2/level2
	chmod 644 /home/level2/level2.c

level4: level4.c
	gcc-3.4 -D_FORTIFY_SOURCE=0 -Wpadded -z execstack -o level4 level4.c
	mv level4 /home/level4/
	chown level5:level4 /home/level4/level4
	chmod 4110 /home/level4/level4
	cat level4.c | sed "s;lxcc7EQaMfIeW8Kdxz5I;xxxxxxxxxxxxxxxxxx;g" > /home/level4/level4.c

level5: level5.c
	gcc-3.4 -D_FORTIFY_SOURCE=0 -Wpadded -z execstack -o level5 level5.c
	mv level5 /home/level5/
	cp level5.c /home/level5/
	chown level6:level5 /home/level5/level5
	chmod 4550 /home/level5/level5
	chmod 644 /home/level5/level5.c

level6: level6.c
	gcc-3.4 -D_FORTIFY_SOURCE=0 -Wpadded -z execstack -o level6 level6.c
	mv level6 /home/level6/
	chown endgame:level6 /home/level6/level6
	chmod 4550 /home/level6/level6

.PHONY: clean
