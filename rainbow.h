#include <stdlib.h>
#include <stdio.h>

int ***rainbow_graph_create(int v) {
  int ***g;
  
  g = (int ***) malloc(sizeof(int**) * (v-2));
  for (int i = 0; i < v-2; ++i) {
    g[i] = (int **) malloc(sizeof(int*) * (v-i-2));
    for (int j = i+1; j < v-1; ++j) {
      g[i][j-i-1] = (int *) malloc(sizeof(int) * (v-j-1));
      for (int k = j+1; k < v; ++k) {
	g[i][j-i-1][k-j-1] = -1;
      }
    }
  }
  
  return g;
}

int rainbow_graph_get(int ***g, int i, int j, int k) {
  return g[i][j-i-1][k-j-1]; 
}

void rainbow_graph_set(int ***g, int i, int j, int k, int c) {
  g[i][j-i-1][k-j-1] = c;

  return;
}

void rainbow_graph_print(int ***g, int v) {
  int e = 0;
  
  for (int i = 0; i < v-2; ++i) {
    for (int j = i+1; j < v-1; ++j) {
      for (int k = j+1; k < v; ++k) {
	printf("e%d(%d): %d %d %d\n", e, g[i][j-i-1][k-j-1], i, j, k);
	e ++;
      }
    }
  }

  return;
}

int rainbow_check(int ***g, int i, int j, int k, int h) {
  int e[4];

  e[0] = rainbow_graph_get(g, i, j, k);
  e[1] = rainbow_graph_get(g, i, j, h);
  e[2] = rainbow_graph_get(g, i, k, h);
  e[3] = rainbow_graph_get(g, j, k, h);

  for (int a = 0; a < 4; ++a) {
    for (int b = a+1; b < 4; ++b) {
      if (e[a] == e[b]) {
	return 0; 
      }
    }
  }
  
  return 1;
}

void rainbow_find(int ***g, int v, int c, int l, int i, int j, int k, int h) { 
  if (l == 4) {
    if (rainbow_graph_get(g, j, k, h) == -1) {  
      for (int a = 0; a < c; ++a) {
	rainbow_graph_set(g, j, k, h, a);

	if (rainbow_check(g, i, j, k, h)) {
	  continue;
	}

	else {
	  if (h+1 < v) {
	    rainbow_find(g, v, c, 1, i, j, k, h+1);
	  }
	  else if (k+2 < v) {
	    rainbow_find(g, v, c, 1, i, j, k+1, k+2);
	  }
	  else if (j+3 < v) {
	    rainbow_find(g, v, c, 1, i, j+1, j+2, j+3);
	  }
	  else if (i+4 < v) {
	    rainbow_find(g, v, c, 1, i+1, i+2, i+3, i+4);
	  }
	  else {
	    int *u = (int *) malloc(sizeof(int) * c);

	    for (int a = 0; a < c; ++a) {
	      u[a] = 0;
	    }

	    for (int a1 = 0; a1 < v-2; ++a1) {
	      for (int a2 = a1+1; a2 < v-1; ++a2) {
		for (int a3 = a2+1; a3 < v; ++a3) {
		  u[g[a1][a2-a1-1][a3-a2-1]] ++;
		}
	      }
	    }
	    
	    int flag = 1;
	    for (int a = 0; a < c; ++a) {
	      if (u[a] == 0) {
		flag = 0;
		break;
	      }
	    }

	    free(u);
	    
	    if (flag) {
	      rainbow_graph_print(g, v);
	      puts("");
	    }
	  }
	}
      }
    }

    else {
      if (!rainbow_check(g, i, j, k, h)) {
	if (h+1 < v) {
	  rainbow_find(g, v, c, 1, i, j, k, h+1);
	}
	else if (k+2 < v) {
	  rainbow_find(g, v, c, 1, i, j, k+1, k+2);
	}
	else if (j+3 < v) {
	  rainbow_find(g, v, c, 1, i, j+1, j+2, j+3);
	}
	else if (i+4 < v) {
	  rainbow_find(g, v, c, 1, i+1, i+2, i+3, i+4);
	}
	else {
	  int *u = (int *) malloc(sizeof(int) * c);
	  
	  for (int a = 0; a < c; ++a) {
	    u[a] = 0;
	  }
	  
	  for (int a1 = 0; a1 < v-2; ++a1) {
	    for (int a2 = a1+1; a2 < v-1; ++a2) {
	      for (int a3 = a2+1; a3 < v; ++a3) {
		u[g[a1][a2-a1-1][a3-a2-1]] ++;
	      }
	    }
	  }
	  
	  
	  int flag = 1;
	  for (int a = 0; a < c; ++a) {
	    if (u[a] == 0) {
	      flag = 0;
	      break;
	    }
	  }

	  free(u);
	  
	  if (flag) {
	    rainbow_graph_print(g, v);
	    puts("");
	  }
	}
      }
    }

    rainbow_graph_set(g, j, k, h, -1);
  }

  else if (l == 3) {
    if (rainbow_graph_get(g, i, k, h) == -1) {
      for (int a = 0; a < c; ++a) {
	rainbow_graph_set(g, i, k, h, a);
	rainbow_find(g, v, c, 4, i, j, k, h);
      }
      
      rainbow_graph_set(g, i, k, h, -1);
    }

    else {
      rainbow_find(g, v, c, 4, i, j, k, h);
    }
  }

  else if (l == 2) {
    if (rainbow_graph_get(g, i, j, h) == -1) {
      for (int a = 0; a < c; ++a) {
	rainbow_graph_set(g, i, j, h, a);
	rainbow_find(g, v, c, 3, i, j, k, h);
      }

      rainbow_graph_set(g, i, j, h, -1);
    }

    else {
      rainbow_find(g, v, c, 3, i, j, k, h);
    }
  }

  else if (l == 1) {
    if (rainbow_graph_get(g, i, j, k) == -1) {
      for (int a = 0; a < c; ++a) {
	rainbow_graph_set(g, i, j, k, a);
	rainbow_find(g, v, c, 2, i, j, k, h);
      }

      rainbow_graph_set(g, i, j, k, -1);
    }

    else {
      rainbow_find(g, v, c, 2, i, j, k, h);
    }
  }
  
  return;
}
