static Client * scratchpad_last_showed = NULL;
/* scratchpad */
static const unsigned scratchpad_mask = 1u << sizeof tags / sizeof * tags;

static void scratchpad_hide ()
{
	if (selmon -> sel)
	{
		selmon -> sel -> tags = scratchpad_mask;
		focus(NULL);
		arrange(selmon);
	}
}


static void scratchpad_show_client (Client * c)
{
	scratchpad_last_showed = c;
	c -> tags = selmon->tagset[selmon->seltags];
	focus(c);
	arrange(selmon);
}

static void scratchpad_show_first (void)
{
	for (Client * c = selmon -> clients; c != NULL; c = c -> next)
	{
		if (c -> tags == scratchpad_mask)
		{
			scratchpad_show_client (c);
			break;
		}
	}
}
static _Bool scratchpad_last_showed_is_killed (void)
{
	_Bool killed = 1;
	for (Client * c = selmon -> clients; c != NULL; c = c -> next)
	{
		if (c == scratchpad_last_showed)
		{
			killed = 0;
			break;
		}
	}
	return killed;
}

static void scratchpad_remove ()
{
	if (selmon -> sel && scratchpad_last_showed != NULL && selmon -> sel == scratchpad_last_showed)
		scratchpad_last_showed = NULL;
}

static void scratchpad_show ()
{
	if (scratchpad_last_showed == NULL || scratchpad_last_showed_is_killed ())
		scratchpad_show_first ();
	else
	{
		if (scratchpad_last_showed -> tags != scratchpad_mask)
		{
			scratchpad_last_showed -> tags = scratchpad_mask;
			focus(NULL);
			arrange(selmon);
		}
		else
		{
			_Bool found_current = 0;
			_Bool found_next = 0;
			for (Client * c = selmon -> clients; c != NULL; c = c -> next)
			{
				if (found_current == 0)
				{
					if (c == scratchpad_last_showed)
					{
						found_current = 1;
						continue;
					}
				}
				else
				{
					if (c -> tags == scratchpad_mask)
					{
						found_next = 1;
						scratchpad_show_client (c);
						break;
					}
				}
			}
			if (found_next == 0) scratchpad_show_first ();
		}
	}
}


