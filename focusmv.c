/**
 * @author      : Gavin Jaeger-Freeborn (gavinfreeborn@gmail.com)
 * @file        : focusmv.c
 * @created     : Fri 27 Dec 2019 07:53:40 PM MST
 */

// +1=right
// -1=left
	void
focusmv(const Arg *arg) 
{
	Monitor *m;
	int axis = arg->i;
	if (mons->next || ((m = dirtomon(arg->i)) == selmon)){ /* if only one monitor */
		focusmon(arg); /* switch workspaces instead of monitors */
		return;
	}
	if (axis == 1)
		viewtoright(arg);
	else
		viewtoleft(arg);
	return;
}

