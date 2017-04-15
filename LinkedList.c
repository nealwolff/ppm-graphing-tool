/*
ppm graphing tool 1.0
LinkedList.c
by Neal Wolff
*/
typedef struct edges {
	int x;
	int y;
	int index;
	struct edges *next;
}edgeNode;

edgeNode *findY(edgeNode *subdirs, int y){
	edgeNode * current = subdirs;

	while(current != NULL)
	{	
		if(current->y<= y)
			break;

		current = current->next;
	}
	return current;
}


void createEdge(edgeNode ** head, int x, int y) {

	edgeNode * newNode; //creates a new node
	newNode= malloc(sizeof(edgeNode));

	if(head!=NULL)
		newNode->index=0;
	else
		newNode->index=(*head)->index+1;
	

	newNode->x = x;

	newNode->y = y;

	newNode->next = *head;
		

	*head = newNode;
}

void ls(edgeNode *fn){
	edgeNode * cfile = fn;

	while (cfile != NULL)
	{
		printf("x: %d y: %d \n", cfile->x, cfile->y);
		cfile = cfile->next;
	}
}

//returns an edge to be drawn using the DDA line algorithm
//returns a 2D array of x and y points along the edge
void edge(int x1, int x2, int y1, int y2,edgeNode **nSqList){
	int s, dx, dy, m, i;
	float xi, yi, x, y;
 
	dx = x2-x1;
	dy = y2-y1;
 
	if (abs(dx) > abs(dy))
		s = abs(dx);
	else
		s = abs(dy);
 
	xi = dx/(float)s;
	yi = dy/(float)s;
 
	x = x1;
	y = y1;
	
	for (m = 0; m<s; m++) {
		
		x +=xi;
		y +=yi;
		createEdge(&(*nSqList),x,y);
		
	}
}
