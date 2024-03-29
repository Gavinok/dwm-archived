void
max(const Arg *arg)
{
	unsigned int n;
	Client *nbc;
	if (!selmon->sel)
		return;
	/* count the number of clients  */
	for (n = 0, nbc = nexttiled(selmon->clients); nbc; nbc = nexttiled(nbc->next), n++);
	/* if the client is not fullscreen, alone, or monocle */
	if (!selmon->sel->isfullscreen && (n != 1 || selmon->sel->isfloating || selmon->lt[selmon->sellt]->arrange == NULL)  && !(selmon->lt[selmon->sellt]->arrange == monocle)){
		/* if arg is 0 use monocle size if 1 use fullscreen */
		if(selmon->showbar && (arg->i != 1)){
			setfullscreen(selmon->sel, 2);
			return;
		}
			setfullscreen(selmon->sel, 1);
	}
	else
		setfullscreen(selmon->sel, 0);
}
