#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h>

void
pbmgrid(char **grid, int w, int h, FILE* f)
{
	int x, y;
	
	if (f == NULL)
		f = stdout;
	
	fprintf(f, "P1\n");
	fprintf(f, "%d %d\n", w, h);
	/* foreach row */
	for (y = 0; y < h; y++) {
		/* foreach cell */
		for (x = 0; x < w; x++) {
			if (grid[x][y] == 1)
				fputc('0', f);
			else
				fputc('1', f);
			if (x != (w-1))
				fputc(' ', f);
		}
		fputc('\n', f);
	}
}

void
randgrid(char **grid, int w, int h)
{
	int x, y;

	/* foreach row */
	for(y = 0; y < h; y++) {
		/* foreach cell */
		for(x = 0; x < w; x++) {
			grid[x][y] = rand() % 2 == 1;
		}
	}
}

char **
allocf(int width, int height)
{
	char **f;
	int i;

	f = calloc(sizeof(char *), width);
	for (i = 0; i < width; i++)
		f[i] = calloc(sizeof(char), height);

	return f;
}

void
clearf(char **field, int width, int height)
{
	int x, y;
	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			field[x][y] = 0;
		}
	}
}

void
freef(char **field, int width) {
	int i;
	for (i = 0; i < width; i++)
		free(field[i]);
	free(field);
}

void
draw_sin(char **grid, int w, int h, double scale, double offset)
{
	int x;
	int y = 0;
	double v;

	for (x = 0; (x < w) && y < h; x++) {
		v = sin((double)x/scale + offset);
		y = (int)(v * scale) + 4*scale;
		if (y < h)
			grid[x][y] = 1;
	}
}

void
draw_cos(char **grid, int w, int h, double scale, double offset)
{
	int x;
	int y = 0;
	double v;

	for (x = 0; (x < w) && y < h; x++) {
		v = cos((double)x/scale + offset);
		y = (int)(v * scale) + 4*scale;
		if (y < h)
			grid[x][y] = 1;
	}
}

void
draw_tan(char **grid, int w, int h, double scale, double offset)
{
	int x;
	int y = 0;
	double v;

	for (x = 0; (x < w) && y < h; x++) {
		v = tan((double)x/scale + offset);
		y = (int)(v * scale) + 4*scale;
		if (y < h && x < w && y >= 0 && x >= 0)
			grid[x][y] = 1;
	}
}

int
main(void) {
	int width = 640;
	int height = 480;
	int i;
	int frames = 500;
	char fpath[100];
	char **grid;

	/* init */
	grid = allocf(width, height);
	
	double scale = 50.0;
	double offset = 1.0;
	double offset2 = 1.0;
	double offset3 = 1.0;
	double offset4 = 1.0;
	
	for (i = 0; i < frames; i++) {
		snprintf(fpath, 100, "plt_pbm_%05d.pbm", i);
		FILE *pbmf = fopen(fpath, "w");
		
		clearf(grid, width, height);
		draw_sin(grid, width, height, scale, offset);
		draw_cos(grid, width, height, scale, offset2);
		draw_sin(grid, width, height, scale, offset3);
		draw_cos(grid, width, height, scale, offset4);
		offset += 0.1;
		offset2 += 0.12;
		offset3 += 0.13;
		offset4 += 0.15;
		
		pbmgrid(grid, width, height, pbmf);
		fclose(pbmf);
		fprintf(stderr, "i: %d\n", i);
	}

	/* clean up */
	freef(grid, width);

	return 0;
}
