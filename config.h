/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int gappx     = 10; /* gaps between windows */
static const unsigned int deltamv   = 20; /* deltamvmv = the amount of pixels each movement will be by */
static const unsigned int snap      = 32; /* snap pixel */
static const int showbar            = 1;  /* 0 means no bar */
static const int topbar             = 1;  /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVu Sans Mono:style=Regular:size=10", "FontAwesome:style=Regular:size=11"};
static const char dmenufont[]       = "DejaVu Sans Mono:style=Regular:size=10";

#include "../colorschemes/dwm/current.h"

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] =	  { UNSELECTED, background, UNFOCUSED },
	[SchemeSel]  =	  { SELECTED, background,  FOCUSED }
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, 0 },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "why", "yap", "jig", "hoe", "non" };

#include "i3scratch.c"
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class  instance  title  tags mask  isfloating scratchmonitor */
	{ NULL, NULL,      "newspod",     1<<4,	     0,  -1 },
	{ NULL, "mp3",     NULL,          1<<4,      1,  -1 },
	{ NULL, NULL,      "launch_once", 0,         1,  -1 },
	{ NULL, NULL,      "fuzzpass",    0,         1,  -1 },
	{ NULL, "popup",   NULL,          0,         1,  -1 },
	{ NULL, "float",   NULL,          0,         1,  -1 },
	{ NULL, NULL,      "float",       0,         1,  -1 },
	{ NULL, "scratch",   NULL,        0,         1,  -1 },
	{ NULL, NULL,	"scratch",        0,         1,  -1 },
	{ NULL, "lazarus", NULL,          1<<2,	     1,  -1 },
	{ NULL, NULL, "Firefox",          0,	     0,  -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#include "layouts.c"
/* #include "scratchpad.c" */
#include "maximize.c"
#include "moveplace.c"
#include "mv.c"
#include "focusmv.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },    /* first entry is default */
	{ NULL,      NULL },    /* no layout function means floating behavior */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

#include "cyclelayout.c"

/* key definitions */
#define MODKEY Mod4Mask
/* #define MODKEY Mod4Mask */
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-n", "float", "-g", "90x24", NULL };
/* static const char *calc[]          = { "st", "-t", scratchpadname, "-f", "Source Code Pro-15", "-e", "R", NULL }; */
static const char *calc[]          = { "roficalc.sh", NULL };
static const char term[]           = { "st"};
static const char exec[]           = { "-e" };
static const char *email[]         = { term, "-t", "neomutt", exec, "launch_once.sh", "neomutt", NULL };
static const char *mixer[]         = { term, exec, "launch_once.sh", "pulsemixer", NULL };
static const char *reddit[]        = { term, exec, "rtv", NULL };
static const char *rss[]           = { term, exec, "newspod", NULL };
static const char *sysmonitor2[]   = { term, exec, "htop", NULL };
static const char *sysmonitor[]    = { term, exec, "gotop", "-m", NULL };
static const char *nm[]            = { "dmenu_connection_manager.sh", NULL };
static const char *mute[]          = { "lmc", "mute", NULL };
static const char *vdown[]         = { "lmc", "down", "5", NULL };
static const char *ldown[]         = { "llc.sh", "down", "7", NULL };
static const char *lup[]           = { "llc.sh", "up", "7", NULL };
static const char *vup[]           = { "lmc", "up", "5", NULL };
static const char *mplay[]         = { "lmc", "toggle", NULL };
static const char *mnext[]         = { "lmc", "next", NULL };
static const char *mprev[]         = { "lmc", "prev", NULL };
static const char *search[]        = { "ducksearch", NULL };
static const char *browser[]       = { "/bin/sh", "-c", "ducksearch \"google-chrome-stable \"" , NULL };
static const char *clip[]          = { "clipmenu", NULL };
static const char *plumb[]         = { "cabl", "-c", NULL };
static const char *killit[]        = { "dmenu-killall", NULL };
static const char *dmusic[]         = { "mpdmenu", NULL };
static const char *power[]         = { "power_menu.sh", NULL };
static const char *filemanager[]   = { "dmenu-open.sh", NULL };
static const char *screenshot[]    = { "windowshot.sh", NULL };
static const char *windowshot[]    = { "windowshot.sh", "-w", NULL };
static const char *rootshot[]      = { "windowshot.sh", "-r", NULL };
static const char *tutoral[]       = { "tutorialvids", NULL };
static const char *td[]            = { "td-toggle", NULL };
static const char *dock[]          = { "dock_monitor", NULL };
static const char *undock[]        = { "single_monitor", NULL };
static const char *spell[]         = { "spellcheck.sh", NULL };
static const char *todo[]          = { "vimtodo.sh", NULL };
static const char *rotate[]        = { "rotate_screen", NULL };
static const char *kdeconnect[]    = { "dmenu_kdeconnect.sh", NULL };
static const char *pass[]	   	   = { "mypassmenu", "--type", "-p", "Select Password", "-l", "5", NULL };
static const char *barmenu[]	   = { "bar", NULL };
static const char *hide[]	   = { "hide.sh", NULL };
static const char *unhide[]	   = { "unhide.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	{ MODKEY,                       XK_grave,      view,           {.ui = ~scratchpad_mask } },
	{ MODKEY|ShiftMask,             XK_grave,      tag,            {.ui = ~scratchpad_mask } },
	TAGKEYS(							XK_1, 0)
	TAGKEYS(                        	XK_2, 1)
	TAGKEYS(                        	XK_3, 2)
	TAGKEYS(                        	XK_4, 3)
	TAGKEYS(							XK_5, 4)
	TAGKEYS(							XK_6, 0)
	TAGKEYS(                        	XK_7, 1)
	TAGKEYS(                        	XK_8, 2)
	TAGKEYS(                        	XK_9, 3)
	TAGKEYS(                        	XK_0, 4)


	{ MODKEY,                       XK_minus,              view,                 {.ui =       ~scratchpad_mask } },
	{ MODKEY|ShiftMask,             XK_minus,              tag,                  {.ui =       ~scratchpad_mask } },
	{ MODKEY,                       XK_equal,              spawn,                {.v  =       nm               } },
	{ MODKEY,                       XK_BackSpace,          killclient,           {0}  },

	{ MODKEY,                       XK_Tab,                cyclelayout,          {.i  =       +1}              },
	{ MODKEY,                       XK_q,                  killclient,           {0}  },
	{ MODKEY|ControlMask,           XK_q,                  spawn,                {.v  =       killit           } },
	{ MODKEY|ShiftMask|ControlMask, XK_q,                  quit,                 {0}  },
	{ MODKEY,                       XK_w,                  spawn,                {.v  =       search           } },
	{ MODKEY|ShiftMask,             XK_w,                  spawn,                {.v  =       browser          } },
	{ MODKEY,                       XK_e,                  spawn,                {.v  =       email            } },
	{ MODKEY,                       XK_r,                  spawn,                {.v  =       filemanager      } },
	{ MODKEY,                       XK_t,                  spawn,                {.v  =       todo             } },
	{ ShiftMask|MODKEY,             XK_t,                  spawn,                {.v  =       tutoral          } },
	{ MODKEY,                       XK_y,                  spawn,                {.v  =       mixer            } },
	{ MODKEY,                       XK_u,                  scratchpad_show,      {0}  },
	{ MODKEY|ShiftMask,             XK_u,                  scratchpad_hide,      {0}  },
	{ MODKEY|ControlMask,           XK_u,                  scratchpad_remove, 	 {0}  },
	{ MODKEY,                       XK_i,                  spawn,                {.v  =       sysmonitor2      } },
	{ MODKEY|ShiftMask,             XK_i,                  spawn,                {.v  =       sysmonitor       } },
	{ MODKEY,                       XK_p,                  spawn,                {.v  =       clip             } },
	{ MODKEY|ShiftMask,             XK_p,                  spawn,                {.v  =       plumb            } },
	{ MODKEY,                       XK_bracketleft,        spawn,                {.v  =       hide             } },
	{ MODKEY,                       XK_bracketright, 	   spawn, 				 {.v  =       unhide 		   } },
	{ MODKEY,                       XK_backslash,          spawn,                {.v  =       kdeconnect       } },
	{ MODKEY,                       XK_a,                  incnmaster,           {.i  =       +1               } },
	{ MODKEY|ControlMask,           XK_a,                  spawn,                {.v  =       vdown            } },
	{ MODKEY,                       XK_s,                  incnmaster,           {.i  =       -1               } },
	{ MODKEY|ControlMask,           XK_s,                  spawn,                {.v  =       ldown            } },
	{ MODKEY|ShiftMask,             XK_s,                  spawn,                {.v  =       spell            } },
	{ MODKEY,                       XK_d,                  spawn,                {.v  =       dmenucmd         } },
	{ MODKEY|ControlMask,           XK_d,                  spawn,                {.v  =       lup              } },
	{ MODKEY,                       XK_f,                  max,                  {.i  =       0}               },
	{ MODKEY|ShiftMask,             XK_f,                  setlayout,            {.v  =       &layouts[3]      } },
	{ MODKEY|ControlMask,           XK_f,                  spawn,                {.v  =       vup              } },
	{ MODKEY,                       XK_g,                  moveplace,            {.ui =       WIN_C            }},
	{ MODKEY|ControlMask,           XK_h,                  setmfact,             {.f  =       -0.05}           },
	// { MODKEY,                                     XK_h,         focusmon,       {.i = -1 } },
	/* { MODKEY,                       XK_h,                  viewtoleft,           {.i  =       -1               } }, */
	{ MODKEY,                       XK_h,                  focusmv,           {.i  =       -1               } },
	{ MODKEY|ShiftMask,             XK_h,                  mv,                   {.i  =       +1}              },
	{ MODKEY,                       XK_j,                  focusstack,           {.i  =       +1               } },
	{ MODKEY|ControlMask,           XK_j,                  spawn,                {.v  =       ldown            } },
	{ MODKEY|ShiftMask,             XK_j,                  mv,                   {.i  =       -2}              },
	{ MODKEY,                       XK_k,                  focusstack,           {.i  =       -1               } },
	{ MODKEY|ControlMask,           XK_k,                  spawn,                {.v  =       lup              } },
	{ MODKEY|ShiftMask,             XK_k,                  mv,                   {.i  =       +2}              },
	 /* { MODKEY,                                     XK_l,         focusmon,       {.i = +1 } }, */
	/* { MODKEY,                       XK_l,                  viewtoright,          {.i  =       +1               } }, */
	{ MODKEY,                       XK_l,                  focusmv,          {.i  =       +1               } },
	{ MODKEY|ControlMask,           XK_l,                  setmfact,             {.f  =       +0.05}           },
	{ MODKEY|ShiftMask,             XK_l,                  mv,                   {.i  =       -1}              },
	{ MODKEY,                       XK_semicolon,          view,                 {0}  },
	{ MODKEY,				      XK_apostrophe,   spawn,   {.v = scratchpadcmd} },
	 /* { MODKEY|ShiftMask,			      XK_apostrophe,   spawn,   {.v = unhide} }, */
	{ MODKEY,                       XK_Return,             spawn,                {.v  =       termcmd          } },

	{ MODKEY|ShiftMask,             XK_z,                  togglefloating,       {0}  },
	{ MODKEY,                       XK_z,                  moveplace,            {.ui =       WIN_SW           }},
	/* { MODKEY,                       XK_x,                  spawn,                {.v  =       vimclip          } }, */
	{ MODKEY|ShiftMask,             XK_x,                  spawn,                {.v  =       power            } },
	{ MODKEY,                    XK_c,         spawn,          {.v = calc } },
	/* { MODKEY|ShiftMask,             XK_c,                  killclient,           {0}  }, */
	{ MODKEY,                       XK_v,                  zoom,                 {0}  },
	/* { MODKEY,              XK_v,            zoomswap,       {0} }, */
	{ MODKEY,                       XK_b,                  moveplace,            {.ui =       WIN_SE           }},
	{ MODKEY|ShiftMask,             XK_b,                  togglebar,            {0}  },
	{ MODKEY,                       XK_n,                  spawn,                {.v  =       rss              } },
	{ MODKEY|ShiftMask,             XK_n,                  spawn,                {.v  =       reddit           } },
	{ MODKEY,                       XK_m,                  spawn,                {.v  =       dmusic            } },
	{ MODKEY|ShiftMask,             XK_m,                  spawn,                {.v  =       mute             } },
	{ MODKEY,                       XK_comma,              focusmon,             {.i  =       -1               } },
	{ MODKEY|ShiftMask,             XK_comma,              tagmon,               {.i  =       -1               } },
	{ MODKEY,                       XK_period,             focusmon,             {.i  =       +1               } },
	{ MODKEY|ShiftMask,             XK_period,             tagmon,               {.i  =       +1               } },
	{ MODKEY,                       XK_slash,              spawn,                {.v  =       pass}            },

	{ MODKEY,                       XK_F7,                 spawn,                {.v  =       dock             } },
	{ MODKEY,                       XK_F8,                 spawn,                {.v  =       undock           } },
	{ MODKEY,                       XK_F11,                spawn,                {.v  =       nm               } },
	{ 0,                            XK_Print,              spawn,                {.v  =       screenshot       }},
	{ MODKEY,                       XK_Print,              spawn,                {.v  =       windowshot		}},
	{ ShiftMask,                    XK_Print,              spawn,                {.v  =       rootshot       }},
	 /* { 0,                                          0x1008ff41,   spawn,          SHCMD("xset dpms force off")}, */
	{ 0,                            0x1008ff41,            spawn,                SHCMD("systemctl suspend")},
	{ 0,                            0x1008ff11,            spawn,                {.v  =       vdown            } },
	{ 0,                            0x1008ff13,            spawn,                {.v  =       vup              } },
	{ 0,                            0x1008ff12,            spawn,                {.v  =       mute             } },
	{ 0,                            0x1008ff74,            spawn,                {.v  =       rotate           } },
	{ 0,                            0x1008ff7f,            spawn,                {.v  =       rotate           } },
	 /* { MODKEY,                                     XK_5,         view,           {0} }, */
	 /* { MODKEY,                                     XK_6,         cyclelayout,    {.i = +1} }, */
	{ MODKEY,                       0x1008ff27,            spawn,                {.v  =       mnext            }},
	{ MODKEY,                       0x1008ff26,            spawn,                {.v  =       mprev            }},
	{ 0,                       XK_Menu,            spawn,              SHCMD("")},
};


// button definitions
// click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[2]} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkLtSymbol,		0,              Button4,        spawn,		{.v = lup} },
	{ ClkLtSymbol,		0,              Button5,        spawn,		{.v = ldown} },
	{ ClkWinTitle,          0,              Button1,        max,		{0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button3,        killclient,     {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = -1} },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = +1} },
	/* { ClkWinTitle,    		0,				Button6,           setmfact,       {.f  = -0.05}}, */
	/* { ClkWinTitle,          0, 				Button7,           setmfact,       {.f  = -0.05}}, */
	/* { ClkStatusText,        0,              Button1,        tagmon,         {.i = +1 } }, */
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = barmenu } },
	{ ClkStatusText,        0,              Button2,        togglefloating, {.v = termcmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = barmenu } },
	{ ClkStatusText,        0,              Button4,        spawn,		{.v = vup} },
	{ ClkStatusText,        0,              Button5,        spawn,		{.v = vdown} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,         		Button2,        tag,            {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkRootWin,           0,		Button3,        spawn,		{.v = barmenu } },
};
