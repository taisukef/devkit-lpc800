#include "ws2812b.h"

int fizzbuzz(int len) {
	int v = 20;
	
	clear();
	int n = 0;
	for (int i = 0; i < 60; i++) {
		if (n % 3 == 0 && n % 5 == 0) {
			set(0, rgb(v, v, 0));
		} else if (n % 3 == 0) {
			set(0, rgb(v, 0, 0));
		} else if (n % 5 == 0) {
			set(0, rgb(0, v, 0));
		} else {
			set(0, 0);
		}
		flush();
		wait(300000);
		rotate(0);
		n++;
		if (btn()) {
			clear();
			n = 0;
		}
	}
	return 0;
}

int hue(int len) {
	int h = 0;
	for (int j = 0; j < 300; j++) {
		for (int i = 0; i < len; i++) {
	//		set(i, rgb(rnd(v), rnd(v), rnd(v)));
			//set(i, rgb(10, 0, i));
			//set(i, rgb(i, 30 - i, 0));
			set(i, hsv2rgb(h, 80, len - i));
		}
		flush();
		wait(30000);
		h++;
		if (btn()) {
			h += 10;
		}
		h = h % 360;
	}
	return 0;
}

int atrandom(int len) {
	int v = 20;
	for (int j = 0; j < 30; j++) {
		for (int i = 0; i < len; i++) {
			set(i, rgb(rnd(v), rnd(v), rnd(v)));
		}
		flush();
		if (btn())
			wait(50000);
		else
			wait(500000);
	}
	return 0;
}

int rainbow(int len) {
	for (int i = 0; i < len; i++) {
//		set(i, rgb(rnd(v), rnd(v), rnd(v)));
		//set(i, rgb(10, 0, i));
		//set(i, rgb(i, 30 - i, 0));
		set(i, hsv2rgb(360 / len * i, 100, 10));
	}
	
	int dir = 0;
	for (int i = 0; i < 500; i++) {
		flush();
		wait(30000);
		if (btn() && systick_tick() > 300) {
			systick_clear();
			dir = !dir;
		}
		rotate(dir);
	}
	return 0;
}

int flash(int len) {
	int v = 40;
	for (int j = 0; j < 300; j++) {
		clear();
		set(rnd(len), rgb(v, v, v));
		flush();
		if (btn())
			wait(5000);
		else
			wait(50000);
	}
	return 0;
}

int start(int len) {
	int modelen = 5;
	int mode = 4;
	for (;;) {
		switch (mode) {
			case 0: rainbow(len); break;
			case 1: hue(len); break;
			case 2: fizzbuzz(len); break;
			case 3: atrandom(len); break;
			case 4: flash(len); break;
		}
		mode++;
		mode %= modelen;
	}
}
