static Client *prevzoom = NULL;
static Client * findbefore(Client *c);

Client *
findbefore(Client *c) {
	Client *tmp;
	if(c == selmon->clients)
		return NULL;
	for(tmp = selmon->clients; tmp && tmp->next != c; tmp = tmp->next) ;
	return tmp;
}
void
zoomswap(const Arg *arg)
 {
 	Client *c = selmon->sel;
	Client *at = NULL, *cold, *cprevious = NULL;
 
 	if (!selmon->lt[selmon->sellt]->arrange
 	|| (selmon->sel && selmon->sel->isfloating))
 		return;
	if (c == nexttiled(selmon->clients)) {
		at = findbefore(prevzoom);
		if (at)
			cprevious = nexttiled(at->next);
		if (!cprevious || cprevious != prevzoom) {
			prevzoom = NULL;
			if(!c || !(c = nexttiled(c->next)))
				return;
		} else
			c = cprevious;
	}
	cold = nexttiled(selmon->clients);
	if (c != cold && !at)
		at = findbefore(c);
	detach(c);
	attach(c);
	/* swap windows instead of pushing the previous one down */
	if (c != cold && at) {
		prevzoom = cold;
		if(cold && at != cold) {
			detach(cold);
			cold->next = at->next;
			at->next = cold;
		}
	}
	focus(c);
	arrange(c->mon);
 }
